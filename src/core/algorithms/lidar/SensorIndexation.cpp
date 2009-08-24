/***********************************************************************

This file is part of the FullAnalyze project source files.

FullAnalyze is an open source software for handling, visualizing and 
processing lidar data (waveforms and point clouds). FullAnalyze is 
distributed under the CeCILL-B licence. See Licence_CeCILL-B_V1-en.txt 
or http://www.cecill.info for more details.


Homepage: 

	http://fullanalyze.sourceforge.net
	
Copyright:
	
	Institut Geographique National & CEMAGREF (2009)

Author: 

	Adrien Chauve
	
	

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
 
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
