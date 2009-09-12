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

#ifndef PANELVIEWERFW_H_
#define PANELVIEWERFW_H_

#include "LidarFormat/extern/matis/tpoint2d.h"

//Panel de visu 2D de la lib ITKViewerLib
#include "gui/PanelViewer.hpp"

class VectorLayerGhost;

class PanelViewerFW : public PanelViewer
{
	public:
		virtual ~PanelViewerFW();

		///Récupère les deux extrêmités de la sélection rectangulaire
		std::pair<TPoint2D<int>,TPoint2D<int> > GetSelection();

		///Affiche ou non le disque de voisinage
		void AfficheVoisinage(const bool affiche);
		void SetRayonVoisinage(const double rayon);

	protected:
		PanelViewerFW(wxFrame *parent);
		DECLARE_EVENT_TABLE();




};

#endif /*PANELVIEWERFW_H_*/
