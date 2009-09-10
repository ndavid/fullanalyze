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

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public 
    License along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 
***********************************************************************/

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/geometry/LidarSpatialIndexation2D.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "MNS.h"

using namespace boost::gil;

namespace Lidar
{

MNS::MNS(const LidarDataContainer& lidarContainer, const Lidar::LidarCenteringTransfo& transfo, const float resolution):
	m_lidarContainer(lidarContainer), m_resolution(resolution), m_transfo(transfo)
{

}


template<class TIterator>
struct FonctorIndexToIterator
{
	FonctorIndexToIterator(const TIterator &it): it_(it){}

	typename TIterator::value_type operator()(const unsigned int index)
	{
//		std::cout << *it_ << std::endl;
		return *(it_ + index);
	}
	private:
		TIterator it_;
};


shared_ptr<gray32F_image_t>  MNS::run()
{

	LidarSpatialIndexation2D spatialIndexation(m_lidarContainer);
	spatialIndexation.setResolution(m_resolution);
	spatialIndexation.indexData();

	m_ori = spatialIndexation.getOri();
	std::cout << "transfo : " << m_transfo.getTransfo() << std::endl;
	m_transfo.applyTransfoOrientation(m_ori);

	const LidarSpatialIndexation2D::GriddedDataType& grid = spatialIndexation.getSpatialIndexation();

	shared_ptr<gray32F_image_t> result_image(new gray32F_image_t(grid.GetTaille().x, grid.GetTaille().y));
	gray32F_image_t::view_t mns  = view(*result_image);

	const LidarConstIteratorAttribute<float> beginZ = m_lidarContainer.beginAttribute<float>("z");

	for(int col = 0; col < mns.width(); ++col)
	{
		for(int lig = 0; lig < mns.height(); ++lig)
		{
			if(!grid(col,lig).empty())
			{
				std::vector<double> listeAltis(grid(col,lig).size());
				std::transform( grid(col,lig).begin(), grid(col,lig).end(), listeAltis.begin(), FonctorIndexToIterator< LidarConstIteratorAttribute<float> >(beginZ) );
				mns(col,lig) = *std::max_element(listeAltis.begin(), listeAltis.end());
//				std::cout << "valeur de mns après : " << mns(col,lig) << std::endl;
			}
		}
	}


	return result_image;
}


} //namespace Lidar
