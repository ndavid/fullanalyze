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


#include <boost/shared_ptr.hpp>
#include "boost/gil/extension/matis/float_images.hpp"

#include "LidarFormat/tools/Orientation2D.h"

using boost::shared_ptr;

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/geometry/LidarSpatialIndexation2D.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"


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

struct FonctorSimpleMNS
{
		FonctorSimpleMNS(const shared_ptr<const LidarDataContainer>& lidarContainer):
			m_beginZ(lidarContainer->beginAttribute<float>("z"))
			{}

		float operator()(const LidarSpatialIndexation2D::NeighborhoodListeType& neighborhood) const
		{
			std::vector<double> listeAltis(neighborhood.size());
			std::transform( neighborhood.begin(), neighborhood.end(), listeAltis.begin(), FonctorIndexToIterator< LidarConstIteratorAttribute<float> >(m_beginZ) );
			return *std::max_element(listeAltis.begin(), listeAltis.end());
		}

	private:
		const LidarConstIteratorAttribute<float> m_beginZ;
};


struct FonctorDensityImage
{
		float operator()(const LidarSpatialIndexation2D::NeighborhoodListeType& neighborhood) const
		{
			return neighborhood.size();
		}
};





using boost::gil::gray32F_image_t;

template<typename PixelType = float, class Image = gray32F_image_t>
struct LidarOrthoImage
{
		template<class Fonction>
		shared_ptr<Image> operator()(const shared_ptr<const LidarDataContainer>& lidarContainer, const LidarCenteringTransfo& transfo, const float resolution, Fonction f, const PixelType blankValue = -999)
		{
			LidarSpatialIndexation2D spatialIndexation(*lidarContainer);
			spatialIndexation.setResolution(resolution);
			spatialIndexation.indexData();

			m_ori = spatialIndexation.getOri();
			std::cout << "transfo : " << transfo.getTransfo() << std::endl;
			LidarCenteringTransfo newTransfo(transfo);
			newTransfo.applyTransfoOrientation(m_ori);

			const LidarSpatialIndexation2D::GriddedDataType& grid = spatialIndexation.getSpatialIndexation();

			shared_ptr<Image> orthoImage(new Image(grid.GetTaille().x, grid.GetTaille().y));
			typename Image::view_t orthoImageView  = view(*orthoImage);

			fill_pixels(orthoImageView, blankValue);

			for(int col = 0; col < orthoImageView.width(); ++col)
			{
				for(int lig = 0; lig < orthoImageView.height(); ++lig)
				{
					const LidarSpatialIndexation2D::NeighborhoodListeType& neighborhood = grid(col,lig);

					if(!neighborhood.empty())
					{
						orthoImageView(col,lig) = f(neighborhood);
					}
				}

			}

			return orthoImage;
		}

		Orientation2D getOri() const { return m_ori; }

	private:
		Orientation2D m_ori;
};


}//namespace Lidar


#endif /* LIDARORTHOIMAGE_H_ */
