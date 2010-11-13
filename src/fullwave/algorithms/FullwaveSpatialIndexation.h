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

#ifndef FULLWAVESPATIALINDEXATION_H_
#define FULLWAVESPATIALINDEXATION_H_


#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "LidarFormat/geometry/RasterSpatialIndexation.h"

namespace Lidar
{
	class FullwaveLidarDataContainer;


/*!
 * \class Classe d'indexation spatiale d'ondes fullwave au format raster : créé un tableau 2D en géométrie ortho autour de la BBOX des points (ou dans une image donnée) à la résolution donnée et indexe dans chaque pixel
 * la pile d'ondes correspondante
 *
 *
 */
class FullwaveSpatialIndexation : public RasterSpatialIndexation
{
	public:

		enum IndexationMethod
		{
			FIRST_LAST_EACH_SEQ, //index first and last point of each sequence of a waveform
			FIRST, //index first point of the first sequence
			LAST, //index last point of the last sequence
			MAXIMUM //index the point whose amplitude is the max of all sequences
		};

		FullwaveSpatialIndexation(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer, IndexationMethod method = LAST);
		virtual ~FullwaveSpatialIndexation();

		virtual void GetCenteredNeighborhood(NeighborhoodListeType &list, const TPoint2D<float> &centre, const float approxNeighborhoodSize, const NeighborhoodFunctionType isInside ) const;

	private:
		virtual void findBBox();
		virtual void fillData();

		void insertPoint(const float x, const float y, const unsigned int index);

		void fillFirst();
		void fillLast();
		void fillFirstLastEachSeq();
		void fillMaximum();

		//reference data
		shared_ptr<const FullwaveLidarDataContainer> m_fwContainer;
		IndexationMethod m_indexationMethod;
};

}//namespace Lidar



#endif /* FULLWAVESPATIALINDEXATION_H_ */
