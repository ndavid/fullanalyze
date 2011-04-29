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

		while(it>= itb && it<ite && !fwHelper.hasBackscatteredSequences(it))
		{
			//si le bord de bande n'a pas de retour (arrive fréquemment sur la zone accidentée du brusquet) on recherche le signal le plus proche à l'intérieur de la bande
			if(increment<0)
			{
				it -= -increment;
			}
			else
				it += increment;
		}

		if(it>= itb && it<ite && fwHelper.hasBackscatteredSequences(it))
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
