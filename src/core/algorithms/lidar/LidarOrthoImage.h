/***********************************************************************

This file is part of the FullAnalyze project source files.

FullAnalyze is a software for handling, visualizing and processing lidar
data (waveforms and point clouds).


Homepage:

	http://fullanalyze.sourceforge.net

Copyright:

	Institut Geographique National & CEMAGREF (2009)

Author:

	Adrien Chauve



    FullAnalyze is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FullAnalyze is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with FullAnalyze.  If not, see <http://www.gnu.org/licenses/>.

***********************************************************************/

#ifndef LIDARORTHOIMAGE_H_
#define LIDARORTHOIMAGE_H_

#include <algorithm>
#include <numeric>

#include <boost/shared_ptr.hpp>
#include "boost/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/io/tiff_io.hpp>

#include "LidarFormat/tools/Orientation2D.h"

using boost::shared_ptr;

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/geometry/LidarSpatialIndexation2D.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "tools/OutilsMaths.h"

namespace gil=boost::gil;


namespace Lidar
{


template<class TIterator>
struct FonctorIndexToIterator
{
	FonctorIndexToIterator(const TIterator &it): it_(it){}

	typename TIterator::value_type operator()(const unsigned int index)
	{
		return *(it_ + index);
	}
	private:
		TIterator it_;
};


template<class TFuncIndexToZ>
struct SortByZ
{
		SortByZ(TFuncIndexToZ f_):
			f(f_){}

		bool operator()(const unsigned int i1, const unsigned int i2)
		{
			return f(i1) < f(i2);
		}

		TFuncIndexToZ f;
};


struct FonctorSimpleMNS
{
		void operator()(gil::gray32F_view_t& mns, const LidarSpatialIndexation2D::GriddedDataType& grid, const shared_ptr<const LidarDataContainer>& lidarContainer, const Orientation2D& ori) const
		{
			const LidarConstIteratorAttribute<float> beginZ(lidarContainer->beginAttribute<float>("z"));
			FonctorIndexToIterator< LidarConstIteratorAttribute<float> > foncIndexToZ(beginZ);

			for(int lig = 0; lig < mns.height(); ++lig)
			{
				gil::gray32F_view_t::x_iterator mns_it = mns.row_begin(lig);

				for(int col = 0; col < mns.width(); ++col)
				{
					const LidarSpatialIndexation2D::NeighborhoodListeType& neighborhood = grid(col,lig);

					if(!neighborhood.empty())
					{
						std::vector<double> listeAltis(neighborhood.size());
						std::transform( neighborhood.begin(), neighborhood.end(), listeAltis.begin(), foncIndexToZ );
						mns_it[col] = *std::max_element(listeAltis.begin(), listeAltis.end());
					}
				}

			}
		}

};




struct FonctorDensityImage
{
		void operator()(gil::gray32F_view_t& orthoImage, const LidarSpatialIndexation2D::GriddedDataType& grid, const shared_ptr<const LidarDataContainer>& lidarContainer, const Orientation2D& ori) const
		{
			for(int lig = 0; lig < orthoImage.height(); ++lig)
			{
				gil::gray32F_view_t::x_iterator src_it = orthoImage.row_begin(lig);

				for(int col = 0; col < orthoImage.width(); ++col)
				{
					const LidarSpatialIndexation2D::NeighborhoodListeType& neighborhood = grid(col,lig);

					if(!neighborhood.empty())
						src_it[col] = neighborhood.size();
				}

			}
		}
};





using gil::gray32F_image_t;

template<typename PixelType = float, class Image = gray32F_image_t>
struct LidarOrthoImage
{
		template<class InterpolatorFonctorT>
		shared_ptr<Image> operator()(const shared_ptr<const LidarDataContainer>& lidarContainer, const LidarCenteringTransfo& transfo, const float resolution, InterpolatorFonctorT interpolator, const PixelType blankValue = -999)
		{
			LidarSpatialIndexation2D spatialIndexation(*lidarContainer);
			spatialIndexation.setResolution(resolution);
			spatialIndexation.indexData();

			m_ori = spatialIndexation.getOri();
			Orientation2D centeredOri = m_ori;
//			std::cout << "transfo : " << transfo.getTransfo() << std::endl;
			LidarCenteringTransfo newTransfo(transfo);
			newTransfo.applyTransfoOrientation(m_ori);

			const LidarSpatialIndexation2D::GriddedDataType& grid = spatialIndexation.getSpatialIndexation();

			shared_ptr<Image> orthoImage(new Image(grid.GetTaille().x, grid.GetTaille().y));
			typename Image::view_t orthoImageView  = view(*orthoImage);

			fill_pixels(orthoImageView, blankValue);

			interpolator(orthoImageView, grid, lidarContainer, centeredOri);

			return orthoImage;
		}

		Orientation2D getOri() const { return m_ori; }

	private:
		Orientation2D m_ori;
};


}//namespace Lidar


#endif /* LIDARORTHOIMAGE_H_ */
