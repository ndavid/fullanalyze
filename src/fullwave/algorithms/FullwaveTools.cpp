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

#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/format/FullwaveEcho.h"

#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "FullwaveTools.h"

namespace FullwaveTools
{

	using namespace Lidar;

	inline void helperCalculeEmprise(LidarConstIteratorEcho it, const FullwaveEchoHelper& fwHelper, std::vector<double>& stripX, std::vector<double>& stripY, const int increment, const FullwaveLidarDataContainer& fwContainer, const LidarCenteringTransfo& transfo)
	{
		const LidarConstIteratorEcho itb = fwContainer.beginEcho();
		const LidarConstIteratorEcho ite = fwContainer.endEcho();

		while( !fwHelper.hasBackscatteredSequences(it) && it>= itb && it<ite)
		{
			//si le bord de bande n'a pas de retour (arrive fréquemment sur la zone acidentée du brusquet) on recherche le signal le plus proche à l'intérieur de la bande
			if(increment<0)
			{
				it -= -increment;
			}
			else
				it += increment;
		}

		if(fwHelper.hasBackscatteredSequences(it))
		{
			TPoint2D<float> pt(fwHelper.originXNthSequence(it, 1), fwHelper.originYNthSequence(it, 1));
			TPoint2D<double> ptTransfo = transfo.applyTransfo(pt);
			stripX.push_back(ptTransfo.x);
			stripY.push_back(ptTransfo.y);
		}
	}

//	inline void helperCalculeEmprise(const LidarConstIteratorEcho it, std::vector<double>& stripX, std::vector<double>& stripY)
//	{
//		if( hasBackscatteredSequences(*it) )
//		{
//			stripX.push_back(originXNthSequence(*it, 1));
//			stripY.push_back(originYNthSequence(*it, 1));
//		}
//	}

//	inline void helperCalculeEmprise(const LidarEcho& it, std::vector<double>& stripX, std::vector<double>& stripY)
//	{
//		if( hasBackscatteredSequences(it) )
//		{
//			stripX.push_back( it.value<FWOriginType>(stringOriginX()) +  it.value<FWDirectionType>(stringDirectionX()) * it.value<FWRangeBeginType>(stringNthSequenceRangeBegin(1)) );
//			stripY.push_back( it.value<FWOriginType>(stringOriginY()) +  it.value<FWDirectionType>(stringDirectionY()) * it.value<FWRangeBeginType>(stringNthSequenceRangeBegin(1)) );
//		}
//	}


	////TODO pour les bandes aux bords très bruités (cf bande 3 brusquet, ajouter un filtrage... sur Z ? prendre une médiane des bords de bande ?...
	void calculeEmprise(const FullwaveLidarDataContainer& fwContainer, std::vector<double>& stripX, std::vector<double>& stripY, const LidarCenteringTransfo& transfo)
	{
		LidarConstIteratorEcho beginEcho = fwContainer.beginEcho();

		stripX.clear();
		stripX.reserve(2*fwContainer.getNbCols() + 2*fwContainer.getNbRows());
		stripY.clear();
		stripY.reserve(2*fwContainer.getNbCols() + 2*fwContainer.getNbRows());

		std::cout << "nbCol=" << fwContainer.getNbCols() << " ; nbRows=" << fwContainer.getNbRows() << "\n";

		FullwaveEchoHelper fwHelper(fwContainer);


//		première ligne (haut)
		for(LidarConstIteratorEcho it = fwContainer.beginEcho(); it < fwContainer.beginEcho()+ fwContainer.getNbCols() && it < fwContainer.endEcho(); ++it)
		{
			helperCalculeEmprise(it, fwHelper, stripX, stripY, +fwContainer.getNbCols(), fwContainer, transfo);
		}

		std::cout << "size : " << stripX.size() << "\n";

		//bord droit (on se déplace sur la dernière colonne, en commençant à la fin de la première ligne)
		for(LidarConstIteratorEcho it = fwContainer.beginEcho() +  2 * fwContainer.getNbCols() -1; it < fwContainer.endEcho(); it += fwContainer.getNbCols())
		{
			helperCalculeEmprise(it, fwHelper, stripX, stripY, -1 , fwContainer, transfo);
		}

		std::cout << "size : " << stripX.size() << "\n";


		//dernière ligne (bas)
		for(LidarConstIteratorEcho it = fwContainer.endEcho() - 1 -1; it > fwContainer.endEcho() -1 - fwContainer.getNbCols() +1; --it)
		{
			helperCalculeEmprise(it, fwHelper, stripX, stripY, -fwContainer.getNbCols(), fwContainer, transfo);
		}

		std::cout << "size : " << stripX.size() << "\n";

		//bord gauche
		for(LidarConstIteratorEcho it = fwContainer.endEcho() -1 - 2* fwContainer.getNbCols() + 1; it > fwContainer.beginEcho(); it -= fwContainer.getNbCols())
		{
			helperCalculeEmprise(it, fwHelper, stripX, stripY, +1, fwContainer, transfo);
		}

		std::cout << "size : " << stripX.size() << "\n";


	}







}
