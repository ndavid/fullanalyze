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



#include "PanelViewerFW.h"
#include "layers/VectorLayerGhost.h"
#include "gui/LayerControl.hpp"

BEGIN_EVENT_TABLE(PanelViewerFW, PanelViewer)
EVT_MOTION(PanelViewerFW::OnMouseMove)
END_EVENT_TABLE()

PanelViewerFW::PanelViewerFW(wxFrame *parent):
	PanelViewer(parent)
{

}

PanelViewerFW::~PanelViewerFW()
{
}


void PanelViewerFW::OnMouseMove(wxMouseEvent &event)
{
	SetFocus();
	event.Skip();
}

void PanelViewerFW::SetRayonVoisinage( const double rayon )
{
	//voisinage par défaut = cercle
	m_ghostLayer.m_circle.second = rayon;// + 0.5;
}

std::pair<TPoint2D<int>,TPoint2D<int> > PanelViewerFW::GetSelection()
{
	return std::make_pair( TPoint2D< int > ( m_ghostLayer.m_rectangleSelection.first.x, m_ghostLayer.m_rectangleSelection.first.y ), TPoint2D< int > ( m_ghostLayer.m_rectangleSelection.second.x, m_ghostLayer.m_rectangleSelection.second.y ) );
}



