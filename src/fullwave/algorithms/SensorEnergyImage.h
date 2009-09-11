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

#ifndef SENSORENERGYIMAGE_H_
#define SENSORENERGYIMAGE_H_

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "extern/gil/extension/matis/float_images.hpp"


namespace Lidar
{

class FullwaveLidarDataContainer;

class SensorEnergyImage
{
	public:
		SensorEnergyImage(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer);

		shared_ptr<boost::gil::gray32F_image_t> run() const;

	private:
		const shared_ptr<const FullwaveLidarDataContainer> m_fwContainer;
};


}//namespace Lidar

#endif /* SENSORENERGYIMAGE_H_ */
