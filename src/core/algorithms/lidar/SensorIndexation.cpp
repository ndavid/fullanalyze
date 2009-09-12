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

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>


#include "tools/OutilsMaths.h"
#include "LidarFormat/LidarDataContainer.h"

#include "SensorIndexation.h"

namespace Lidar
{


SensorIndexation::SensorIndexation(const shared_ptr<const LidarDataContainer>& lidarContainer, const unsigned int nbCols, const char* shotNumberAttributeName , const char* echoNumberAttributeName):
	m_lidarContainer(lidarContainer),
	m_nbCols(nbCols),
	m_shotNumberAttributeName(shotNumberAttributeName),
	m_echoNumberAttributeName(echoNumberAttributeName)
{

}





void SensorIndexation::findBBox()
{
	//x : col
	//y : lig

	m_bboxMin.x = std::numeric_limits<double>::max();
	m_bboxMin.y = std::numeric_limits<double>::max();
	m_bboxMax.x = -std::numeric_limits<double>::max();
	m_bboxMax.y = -std::numeric_limits<double>::max();

	LidarConstIteratorAttribute<unsigned int> itb = m_lidarContainer->beginAttribute<unsigned int>(m_shotNumberAttributeName);
	const LidarConstIteratorAttribute<unsigned int> ite = m_lidarContainer->endAttribute<unsigned int>(m_shotNumberAttributeName);

	unsigned int col, row;

	for(;itb !=ite; ++itb)
	{
		indexToColRow(*itb, col, row);

		m_bboxMax.x = std::max( m_bboxMax.x, (float) col);
		m_bboxMax.y = std::max( m_bboxMax.y, (float) row);
		m_bboxMin.x = std::min( m_bboxMin.x, (float) col);
		m_bboxMin.y = std::min( m_bboxMin.y, (float) row);
	}

//	std::cout << "FullwaveSpatialIndexation  bbox = " << m_bboxMin << " ; " << m_bboxMax << std::endl;

}



struct SortByNumEcho: public std::binary_function<const unsigned int,const unsigned int, bool>
{
		SortByNumEcho(const LidarConstIteratorAttribute<short>& itBegin):
			m_itBegin(itBegin)
		{}

		bool operator()(const unsigned int echo1, const unsigned int echo2) const
		{
			return *(m_itBegin + echo1) < *(m_itBegin + echo2);
		}
	private:
		const LidarConstIteratorAttribute<short> m_itBegin;
};



void SensorIndexation::fillData()
{
	const LidarConstIteratorAttribute<int> itBeginShot = m_lidarContainer->beginAttribute<int>(m_shotNumberAttributeName);
	LidarConstIteratorAttribute<int> itb = m_lidarContainer->beginAttribute<int>(m_shotNumberAttributeName);
	const LidarConstIteratorAttribute<int> ite = m_lidarContainer->endAttribute<int>(m_shotNumberAttributeName);

	const LidarConstIteratorAttribute<short> itBeginEcho = m_lidarContainer->beginAttribute<short>(m_echoNumberAttributeName);


	unsigned int col, row;

	for(;itb !=ite; ++itb)
	{
		indexToColRow(*itb, col, row);
		m_griddedData(static_cast<unsigned int>(col-m_bboxMin.x), static_cast<unsigned int>(row-m_bboxMin.y)).push_back(itb - itBeginShot);
	}

	using namespace std;
	for(GriddedDataType::iterator it = m_griddedData.begin(); it!=m_griddedData.end(); ++it)
	{
		sort(it->begin(), it->end(), SortByNumEcho(itBeginEcho));
	}


}




SensorIndexation::~SensorIndexation()
{
}


}//namespace Lidar
