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

#include "LidarFormat/LidarDataContainer.h"
#include "core/algorithms/lidar/SensorIndexation.h"

#include "SensorAttributeImage.h"


using namespace boost::gil;

namespace Lidar
{

SensorAttributeImage::SensorAttributeImage(const shared_ptr<const Lidar::LidarDataContainer>& lidarContainer, const unsigned int nbCols):
	m_lidarContainer(lidarContainer),
	m_nbCols(nbCols)
{

}


shared_ptr<gray32F_image_t>  SensorAttributeImage::run(const char* attributeName)
{

	SensorIndexation sensorIndexation(m_lidarContainer, m_nbCols);
	sensorIndexation.setResolution(1);
	sensorIndexation.indexData();


	const SensorIndexation::GriddedDataType& grid = sensorIndexation.getSpatialIndexation();

	shared_ptr<gray32F_image_t> result_image(new gray32F_image_t(grid.GetTaille().x, grid.GetTaille().y));
	gray32F_image_t::view_t sensorImage  = view(*result_image);

	const LidarConstIteratorAttribute<float> beginAttribute = m_lidarContainer->beginAttribute<float>(attributeName);

	for(int col = 0; col < sensorImage.width(); ++col)
	{
		for(int lig = 0; lig < sensorImage.height(); ++lig)
		{
			if(!grid(col,lig).empty())
			{
				sensorImage(col,lig) = *(beginAttribute + *grid(col,lig).begin());
			}
		}
	}


	return result_image;
}


} //namespace Lidar
