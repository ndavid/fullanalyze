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

#include <boost/bind.hpp>

#include "wx/glcanvas.h"
#include "gui/MainFrame.h"

#include "GLPanel.h"
#include "PointCloudCanvas.h"

#include "gui/3d/CloudControl.h"

GLPanel::GLPanel(wxFrame *parent) :
	wxPanel(parent)
{

	m_pointCloudCanvas = new PointCloudCanvas(this);


	wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

	mainSizer->Add(m_pointCloudCanvas, 1, wxALL | wxGROW, 10);

	this->SetSizer(mainSizer);
	this->SetAutoLayout(true);


}

CloudControl* GLPanel::getCloudControl()
{
	return m_pointCloudCanvas->getCloudControl();
}

GLPanel::~GLPanel()
{
}



void GLPanel::OnMouse(wxMouseEvent& event)
{
//	if(event.MiddleIsDown() && event.m_controlDown)
//	{
//		std::cout<<"GLPanel fermé par middle click !\n";
//		m_parentDockManager->DetachPane(this);
//		m_parentDockManager->Update();
//
//
//		static_cast<Dock*>(m_parent)->DestroyPanel(this);
//	}
//
//	else if(event.MiddleIsDown() && event.m_shiftDown)
//	{
//		m_pointCloudCanvas->Update();
//		Refresh();
//	}

	if(event.MiddleIsDown())
	{
		///Affichage du cloud control
		wxPoint pos = event.GetPosition();
		pos += GetScreenPosition();

		m_pointCloudCanvas->getCloudControl()->SetPosition(pos);
		m_pointCloudCanvas->getCloudControl()->Show(!m_pointCloudCanvas->getCloudControl()->IsVisible());
	}

	event.Skip();

}




BEGIN_EVENT_TABLE(GLPanel, wxPanel)
EVT_MOUSE_EVENTS(GLPanel::OnMouse)
END_EVENT_TABLE()

