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

#include <iostream>
#include <stdexcept>
#include <algorithm>


//#include "itk/Image.h"

#include "tools/OutilsMaths.h"
#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/format/FullwaveEcho.h"

#include "FullwaveSpatialIndexation.h"

namespace Lidar
{

FullwaveSpatialIndexation::FullwaveSpatialIndexation(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer):
	m_fwContainer(fwContainer)
{
}



///Voisinage grossier carré XY autour du centre, de demi-côté approxNeighborhoodSize, puis raffiné avec la fonction passée en paramètre dans le sous-ensemble grossier
void FullwaveSpatialIndexation::GetCenteredNeighborhood(NeighborhoodListeType &list, const TPoint2D<float> &centre, const float approxNeighborhoodSize, const NeighborhoodFunctionType isInside ) const
{
	list.clear();

	FullwaveEchoHelper fwHelper(*m_fwContainer);

	//Récupération des pixels à visiter
	int colonne, ligne;
	m_ori.MapToImage( centre.x, centre.y, colonne, ligne );

	const int tailleVoisinage = static_cast<int> ( std::ceil( approxNeighborhoodSize / m_resolution ) );

	const int colMin = std::max( 0, colonne - tailleVoisinage );
	const int colMax = std::min( m_griddedData.GetTaille().x - 1, colonne + tailleVoisinage );
	const int ligMin = std::max( 0, ligne - tailleVoisinage );
	const int ligMax = std::min( m_griddedData.GetTaille().y - 1, ligne + tailleVoisinage );

	const unsigned int evalNbPoints = (colMax-colMin+1)*(ligMax-ligMin+1)*m_resolution*m_nbPointsParM2;
	list.reserve(evalNbPoints);

	const LidarConstIteratorEcho itBeginEcho = m_fwContainer->beginEcho();

	for (int col = colMin; col <= colMax; ++col)
	{
		for (int lig = ligMin; lig <= ligMax; ++lig)
		{
			std::vector<unsigned int>::const_iterator itb = m_griddedData(col, lig).begin();
			const std::vector<unsigned int>::const_iterator ite = m_griddedData(col, lig).end();
			for (; itb != ite; ++itb)
			{
				const LidarConstIteratorEcho itEcho(itBeginEcho + *itb);

				for(unsigned int i=1; i<=2; ++i)
				{
					if(fwHelper.hasBackscatteredNthSequence(itEcho,i))
					{
						if (isInside(fwHelper.originXNthSequence(itEcho, i), fwHelper.originYNthSequence(itEcho, i), fwHelper.originZNthSequence(itEcho, i))
								|| isInside(fwHelper.endXNthSequence(itEcho, i), fwHelper.endYNthSequence(itEcho, i), fwHelper.endZNthSequence(itEcho, i))
							)
						{
							list.push_back(*itb);
							break;
						}
					}
					else
						break;
				}



			}

		}
	}
}



void FullwaveSpatialIndexation::findBBox()
{
	m_bboxMin.x = std::numeric_limits<double>::max();
	m_bboxMin.y = std::numeric_limits<double>::max();
	m_bboxMax.x = -std::numeric_limits<double>::max();
	m_bboxMax.y = -std::numeric_limits<double>::max();

	FullwaveEchoHelper fwHelper(*m_fwContainer);

	LidarConstIteratorEcho itb = m_fwContainer->beginEcho();
	const LidarConstIteratorEcho ite = m_fwContainer->endEcho();

	for(;itb !=ite; ++itb)
	{
		for(unsigned int i=1; i<=2; ++i)
		{
			if(fwHelper.hasBackscatteredNthSequence(itb,i))
			{
				m_bboxMax.x = std::max( m_bboxMax.x, fwHelper.originXNthSequence(itb, i) );
				m_bboxMax.y = std::max( m_bboxMax.y, fwHelper.originYNthSequence(itb, i) );
				m_bboxMin.x = std::min( m_bboxMin.x, fwHelper.originXNthSequence(itb, i) );
				m_bboxMin.y = std::min( m_bboxMin.y, fwHelper.originYNthSequence(itb, i) );

				m_bboxMax.x = std::max( m_bboxMax.x, fwHelper.endXNthSequence(itb, i) );
				m_bboxMax.y = std::max( m_bboxMax.y, fwHelper.endYNthSequence(itb, i) );
				m_bboxMin.x = std::min( m_bboxMin.x, fwHelper.endXNthSequence(itb, i) );
				m_bboxMin.y = std::min( m_bboxMin.y, fwHelper.endYNthSequence(itb, i) );
			}
			else
				break;
		}

	}

//	std::cout << "FullwaveSpatialIndexation  bbox = " << m_bboxMin << " ; " << m_bboxMax << std::endl;

}


inline void FullwaveSpatialIndexation::insertPoint(const float x, const float y, const unsigned int index)
{
	int col, ligne;
	m_ori.MapToImage( x, y, col, ligne );

	//dans le cas où la bbox n'a pas été calculée mais fournie dan le constructeur, il faut tester si on sort de la grille
	if(col>=0 && ligne>=0 && col<m_griddedData.GetTaille().x && ligne<m_griddedData.GetTaille().y)
		m_griddedData(col, ligne).push_back(index);
}

void FullwaveSpatialIndexation::fillData()
{
	FullwaveEchoHelper fwHelper(*m_fwContainer);
	const LidarConstIteratorEcho itBegin = m_fwContainer->beginEcho();

	LidarConstIteratorEcho itb = m_fwContainer->beginEcho();
	const LidarConstIteratorEcho ite = m_fwContainer->endEcho();


	for(;itb<ite; ++itb)
	{
//		for(unsigned int i=1; i<=2; ++i)
//		{
//			if(fwHelper.hasBackscatteredNthSequence(itb,i))
//			{
//				unsigned int index = itb - itBegin;
//				insertPoint( fwHelper.originXNthSequence(itb, i), fwHelper.originYNthSequence(itb, i), index );
//				insertPoint( fwHelper.endXNthSequence(itb, i), fwHelper.endYNthSequence(itb, i), index );
//			}
//			else
//				break;
//		}

		int i=1;
		if(fwHelper.hasBackscatteredNthSequence(itb,2))
			i=2;
		if(fwHelper.hasBackscatteredNthSequence(itb,i))
		{
			insertPoint( fwHelper.endXNthSequence(itb, i), fwHelper.endYNthSequence(itb, i), itb - itBegin );
		}

	}



}


FullwaveSpatialIndexation::~FullwaveSpatialIndexation()
{
}

}//namespace Lidar
