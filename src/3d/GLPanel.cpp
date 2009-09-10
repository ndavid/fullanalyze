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

