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
