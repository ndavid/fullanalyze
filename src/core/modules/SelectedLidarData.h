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

#ifndef SELECTEDLIDARDATA_H_
#define SELECTEDLIDARDATA_H_

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/LidarFile.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"

using Lidar::LidarDataContainer;
using Lidar::LidarCenteringTransfo;
using Lidar::LidarEcho;
using Lidar::LidarFile;

struct SelectedLidarData
{
	struct LidarData
	{
		shared_ptr<LidarDataContainer> m_container;

		LidarCenteringTransfo m_transfo;

		std::string m_path;
		std::string m_basename;
		std::string m_extension;
	};

	typedef std::vector<LidarData> DataContainerType;

	DataContainerType m_data;

	LidarData& front()
	{
		assert(!m_data.empty());
		return m_data.front();
	}
};

#endif /* SELECTEDLIDARDATA_H_ */
