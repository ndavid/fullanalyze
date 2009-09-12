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

#ifndef MNS_H_
#define MNS_H_

#include <boost/shared_ptr.hpp>
#include "extern/gil/extension/matis/float_images.hpp"

#include "LidarFormat/tools/Orientation2D.h"

using boost::shared_ptr;




namespace Lidar
{

class LidarDataContainer;
class LidarCenteringTransfo;


class MNS
{
	public:
		MNS(const LidarDataContainer& lidarContainer, const Lidar::LidarCenteringTransfo& transfo, const float resolution);

		shared_ptr<boost::gil::gray32F_image_t> run();

		Orientation2D getOri() const { return m_ori; }

	private:
		const LidarDataContainer& m_lidarContainer;
		const float m_resolution;
		const Lidar::LidarCenteringTransfo m_transfo;
		Orientation2D m_ori;
};

} //namespace Lidar

#endif /* MNS_H_ */
