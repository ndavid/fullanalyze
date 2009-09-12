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

#ifndef SENSORATTRIBUTEIMAGE_H_
#define SENSORATTRIBUTEIMAGE_H_


#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "extern/gil/extension/matis/float_images.hpp"

namespace Lidar
{

class LidarDataContainer;



class SensorAttributeImage
{
	public:
		SensorAttributeImage(const shared_ptr<const Lidar::LidarDataContainer>& lidarContainer, const unsigned int nbCols);

		shared_ptr<boost::gil::gray32F_image_t> run(const char* attributeName);

	private:
		const shared_ptr<const Lidar::LidarDataContainer> m_lidarContainer;
		const unsigned int m_nbCols;
};


}//namespace Lidar

#endif /* SENSORATTRIBUTEIMAGE_H_ */
