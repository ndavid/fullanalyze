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


#include "PanelViewerFW.h"
#include "layers/VectorLayerGhost.h"
#include "gui/LayerControl.hpp"

BEGIN_EVENT_TABLE(PanelViewerFW, PanelViewer)

END_EVENT_TABLE()

PanelViewerFW::PanelViewerFW(wxFrame *parent):
	PanelViewer(parent)
{

}

PanelViewerFW::~PanelViewerFW()
{
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

wxAboutDialogInfo PanelViewerFW::getAboutInfo() const
{
	wxAboutDialogInfo info;
	info.AddDeveloper(_("Adrien Chauve (Author)"));
	info.AddDeveloper(_("Olivier Tournaire (Co-author of the raster/vector 2D viewer GilViewer)"));
	info.SetName(_("FullAnalyze"));
	info.SetVersion(_("0.1"));
	info.SetWebSite(_("http://fullanalyze.sourceforge.net") );
	info.SetDescription(_("Handling, processing and visualizing lidar data (waveforms and point clouds)"));
	info.SetCopyright(_("adrien.chauve@gmail.com  - IGN/CEMAGREF"));
	return info;
}

