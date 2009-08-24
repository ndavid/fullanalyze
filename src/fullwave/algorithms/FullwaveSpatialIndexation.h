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
		FullwaveSpatialIndexation(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer);
		virtual ~FullwaveSpatialIndexation();

		virtual void GetCenteredNeighborhood(NeighborhoodListeType &list, const TPoint2D<float> &centre, const float approxNeighborhoodSize, const NeighborhoodFunctionType isInside ) const;

	private:
		virtual void findBBox();
		virtual void fillData();

		void insertPoint(const float x, const float y, const unsigned int index);

		//reference data
		shared_ptr<const FullwaveLidarDataContainer> m_fwContainer;
};

}//namespace Lidar



#endif /* FULLWAVESPATIALINDEXATION_H_ */
