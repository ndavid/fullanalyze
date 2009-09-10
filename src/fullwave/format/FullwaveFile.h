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

#ifndef FULLWAVEFILE_H_
#define FULLWAVEFILE_H_

#include <string>

#include "LidarFormat/LidarFile.h"

namespace Lidar
{

class FullwaveLidarDataContainer;

class FullwaveFile : public LidarFile
{
	public:
		explicit FullwaveFile(const std::string &xmlFileName);
		virtual ~FullwaveFile();

		static void save(const FullwaveLidarDataContainer& fwContainer, const std::string& xmlFileName, const LidarCenteringTransfo& transfo);

	private:

};


} //namespace Lidar

#endif /* FULLWAVEFILE_H_ */
