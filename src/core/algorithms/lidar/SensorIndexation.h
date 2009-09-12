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

#ifndef FULLWAVESENSORINDEXATION_H_
#define FULLWAVESENSORINDEXATION_H_

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "LidarFormat/geometry/RasterSpatialIndexation.h"


namespace Lidar
{

class LidarDataContainer;



class SensorIndexation : public RasterSpatialIndexation
{
	public:
		SensorIndexation(const shared_ptr<const Lidar::LidarDataContainer>& lidarContainer, const unsigned int nbCols, const char* shotNumberAttributeName = "shotNumber", const char* echoNumberAttributeName = "echoNumber");
		virtual ~SensorIndexation();

		void indexToColRow(const unsigned int index, unsigned int& col, unsigned int& row) const
		{
			col = index % m_nbCols;
			row = index / m_nbCols;
		}

		const unsigned int indexFromColRow(const unsigned int col, const unsigned int row) const
		{
			return row*m_nbCols + col;
		}

		void GetCenteredNeighborhood(NeighborhoodListeType &list, const TPoint2D<float> &centre, const float approxNeighborhoodSize, const NeighborhoodFunctionType IsInside = defaultIsInside) const {}


	private:
		virtual void findBBox();
		virtual void fillData();

		//reference data
		const shared_ptr<const Lidar::LidarDataContainer> m_lidarContainer;
		const unsigned int m_nbCols;
		const char* m_shotNumberAttributeName;
		const char* m_echoNumberAttributeName;
};

}//namespace Lidar

#endif /* FULLWAVESENSORINDEXATION_H_ */
