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

#ifndef SELECTEDFULLWAVEDATA_H_
#define SELECTEDFULLWAVEDATA_H_


#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/format/FullwaveFile.h"

using Lidar::FullwaveLidarDataContainer;
using Lidar::LidarCenteringTransfo;
using Lidar::FullwaveFile;
using Lidar::LidarDataContainer;

struct SelectedFullwaveData
{
		struct FullwaveData
		{
			shared_ptr<FullwaveLidarDataContainer> m_container;

			LidarCenteringTransfo m_transfo;

			std::string m_path;
			std::string m_basename;
			std::string m_extension;
		};

		typedef std::vector<FullwaveData> DataContainerType;

		DataContainerType m_data;

		FullwaveData& front()
		{
			assert(!m_data.empty());
			return m_data.front();
		}
};


#endif /* SELECTEDFULLWAVEDATA_H_ */
