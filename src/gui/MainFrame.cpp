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

#include <algorithm>

#include "boost/bind.hpp"

#include <wx/filename.h>
#include <wx/config.h>
#include <wx/xrc/xmlres.h>
#include <wx/stattext.h>


#include "gui/3d/define_id_FA3D.h"
#include "gui/3d/CloudControl.h"
#include "gui/ApplicationSettings.hpp"
#include "gui/LayerControl.hpp"

///FA event handler (singleton)
#include "core/modules/FAEventHandler.h"


///panels
#include "3d/GLPanel.h"
#include "gui/plot/plot.h"
#include "gui/images/PanelViewerFWSensor.h"
#include "gui/images/PanelViewerFWOrtho.h"

#include "gui/files/FilesPanel.h"

#include "gui/icones/geometry_moving_16x16.xpm"
#include "gui/icones/icone_move16_16.xpm"


#include "MainFrame.h"

MainFrame::MainFrame() :
	BasicViewerFrame( NULL, -1, _("FullAnalyze"), wxDefaultPosition, wxSize( 1280, 1024 ), wxDEFAULT_FRAME_STYLE)
{



	InitMenus();
	InitFenetres();
	InitToolBars();

	wxConfigBase *pConfig = wxConfigBase::Get();

	//Réglage des options par défaut
//	wxConfigBase *pConfig = wxConfigBase::Get();
	int threadNb;
	pConfig->Read(_T("/FA/Options/FitThreadNumber"), &threadNb, 1);
	pConfig->Write(_T("/FA/Options/FitThreadNumber"), threadNb);

	wxString fitType;
	pConfig->Read(_T("/FA/Options/FitType"), &fitType, _("SMAX_NOFIT_DI"));
	pConfig->Write(_T("/FA/Options/FitType"), fitType);

	wxString FWRieglFilePath;
	pConfig->Read(_T("/FA/Paths/FWRieglFilePath"), &FWRieglFilePath, _("/home/achauve/fw-draix/070406_090036.sdf"));
	pConfig->Write(_T("/FA/Paths/FWRieglFilePath"), FWRieglFilePath);

	wxString TrajectoBinFilePath;
	pConfig->Read(_T("/FA/Paths/TrajectoBinFilePath"), &TrajectoBinFilePath, _("/home/achauve/fw-draix/GE606136_01.bin"));
	pConfig->Write(_T("/FA/Paths/TrajectoBinFilePath"), TrajectoBinFilePath);


	bool LoadWoleImage, BilinearZoom;
	pConfig->Read(_T("/Options/LoadWoleImage"), &LoadWoleImage, 0);
	pConfig->Write(_T("/Options/FitThreadNumber"), LoadWoleImage);
	pConfig->Read(_T("/Options/BilinearZoom"), &BilinearZoom, 0);
	pConfig->Write(_T("/Options/BilinearZoom"), BilinearZoom);


}

MainFrame::~MainFrame()
{
}


void MainFrame::DestroyPanel( wxPanel* panel )
{
	if (panel)
		panel->Destroy();
}

wxAboutDialogInfo MainFrame::getAboutInfo() const
{
	wxAboutDialogInfo info;
	info.AddDeveloper(_("Author:"));
	info.AddDeveloper(_("Adrien Chauve"));
	info.AddDeveloper(_(""));
	info.AddDeveloper(_("Contributors:"));
	info.AddDeveloper(_("Olivier Tournaire (GilViewer)"));
	info.AddDeveloper(_("Nicolas David (CMake master)"));
	info.SetName(_("FullAnalyze"));
	info.SetVersion(_("0.1.0"));
	info.SetWebSite(_("http://fullanalyze.sourceforge.net") );
	info.SetDescription(_("Handling, processing and visualizing lidar data (waveforms and point clouds)"));
	info.SetCopyright(_("adrien.chauve@gmail.com  - IGN/CEMAGREF"));
	return info;
}


void MainFrame::OnAfficheOptions( wxCommandEvent &event )
{
//	wxAuiPaneInfo &infoOptions = m_dockManager.GetPane( m_panelFAConfig );
//	infoOptions.Show( !infoOptions.IsShown() );
//	m_dockManager.Update();

}

void MainFrame::notifyGLPanelCreated()
{
	///// ajout du panneau 3D au dock
	m_panel3D = FAEventHandler::Instance()->getPanel3D();
	wxAuiPaneInfo paneInfo3D;
	paneInfo3D.Caption( _("Cloud view") );
	paneInfo3D.Right();
	paneInfo3D.MinSize(wxSize(500,200));
	paneInfo3D.MaximizeButton(true);
	m_dockManager.AddPane( m_panel3D, paneInfo3D );
	m_dockManager.Update();

	m_faToolBar->EnableTool(ID_FA_SHOW_HIDE_CLOUD_CONTROL, true);


	Connect(ID_FA_SHOW_HIDE_CLOUD_CONTROL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(GLPanel::OnShowCloudControl), NULL, m_panel3D);

}

void MainFrame::notifyPlotPanelCreated()
{
	///// ajout du panneau 3D au dock
	m_panelPlot = FAEventHandler::Instance()->getPlotPanel();
	wxAuiPaneInfo paneInfoPlot;
	paneInfoPlot.Caption( _("Plot view") );
	paneInfoPlot.Right();
	paneInfoPlot.MinSize(wxSize(500,200));
	paneInfoPlot.MaximizeButton(true);
	m_dockManager.AddPane( m_panelPlot, paneInfoPlot );

	m_dockManager.GetPane(FAEventHandler::Instance()->getPlotPanel()).Show();

	m_dockManager.Update();
}

void MainFrame::notifyShowPanelSensorViewer()
{
	m_dockManager.GetPane(m_panelViewerSensor).Show();
	m_dockManager.Update();
}

void MainFrame::InitToolBars()
{
	m_orthoToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTB_HORIZONTAL);
	wxStaticText *textOrthoToolBar = new wxStaticText(m_orthoToolBar,wxID_ANY, _(" Ortho "));
	m_orthoToolBar->AddControl(textOrthoToolBar);
	m_orthoToolBar->AddTool(ID_FA_ORTHO_NAVIGATE, _("MN"), wxBitmap(icone_move16_16_xpm), wxNullBitmap, wxITEM_RADIO, _("Navigate in the window"));
	m_orthoToolBar->AddTool(ID_FA_ORTHO_MOVE_SELECTION, _("MN"), wxBitmap(geometry_moving_16x16_xpm), wxNullBitmap, wxITEM_RADIO, _("Move selection"));
//	m_orthoToolBar->AddTool(ID_FA_ORTHO_RECTANGLE_SELECTION, _("SHCC"), wxXmlResource::Get()->LoadBitmap( wxT("RECTANGLE_16x16") ), wxNullBitmap, wxITEM_RADIO, _("Rectangular selection"));
//	m_orthoToolBar->AddTool(ID_FA_ORTHO_CIRCLE_SELECTION, _("MN"), wxXmlResource::Get()->LoadBitmap(wxT("HELP_BROWSER_22x22")), wxNullBitmap, wxITEM_RADIO, _("Circular selection"));
	m_orthoToolBar->AddTool(ID_FA_ORTHO_RECTANGLE_SELECTION, _("SHCC"), wxXmlResource::Get()->LoadBitmap( wxT("PROCESS-STOP_16x16") ), wxNullBitmap, wxITEM_RADIO, _("Rectangular selection"));
	m_orthoToolBar->AddTool(ID_FA_ORTHO_CIRCLE_SELECTION, _("MN"), wxXmlResource::Get()->LoadBitmap(wxT("PROCESS-STOP_16x16")), wxNullBitmap, wxITEM_RADIO, _("Circular selection"));
	m_orthoToolBar->AddTool(ID_FA_ORTHO_NO_SELECTION, _("MN"), wxXmlResource::Get()->LoadBitmap(wxT("PROCESS-STOP_16x16")), wxNullBitmap, wxITEM_NORMAL, _("No selection"));

	m_orthoToolBar->Realize();

	wxAuiPaneInfo paneInfoToolbarMainViewer;
	paneInfoToolbarMainViewer.ToolbarPane();
	paneInfoToolbarMainViewer.Caption( _("Toolbar Viewer Ortho") );
	paneInfoToolbarMainViewer.Top();
	m_dockManager.AddPane(m_orthoToolBar, paneInfoToolbarMainViewer);



	m_faToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTB_HORIZONTAL);

	// Creating an image list storing the toolbar icons
	const wxSize imageSize(16,16);

	m_faToolBar->AddTool(ID_SHOW_HIDE_LAYER_CONTROL, _("SHCC"), wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_TOOLBAR, imageSize), wxNullBitmap, wxITEM_NORMAL, _("Show / Hide layer control"));
	m_faToolBar->AddTool(ID_FA_LIDAR_DISPLAY_PROJECTED_POINTS, _("SHCC"), wxXmlResource::Get()->LoadBitmap( wxT("POINTS_16x16") ), wxNullBitmap, wxITEM_NORMAL, _("Show / Hide lidar projected points"));

	m_faToolBar->AddTool(ID_FA_SHOW_HIDE_CLOUD_CONTROL, _("SHCC"), wxArtProvider::GetBitmap(wxART_LIST_VIEW, wxART_TOOLBAR, imageSize), wxNullBitmap, wxITEM_NORMAL, _("Show / Hide cloud control"));
	m_faToolBar->Realize();
	m_faToolBar->EnableTool(ID_FA_SHOW_HIDE_CLOUD_CONTROL, false);

	wxAuiPaneInfo paneInfoFAToolbar;
	paneInfoFAToolbar.ToolbarPane();
	paneInfoFAToolbar.Top();
	paneInfoFAToolbar.Caption( _("Toolbar 3D") );
	m_dockManager.AddPane(m_faToolBar, paneInfoFAToolbar);


	///Shortcuts
	wxAcceleratorEntry entries[5];
	entries[0].Set(wxACCEL_NORMAL, WXK_F2, ID_FA_ORTHO_NAVIGATE);
	entries[1].Set(wxACCEL_NORMAL, WXK_F3, ID_FA_ORTHO_MOVE_SELECTION);
	entries[2].Set(wxACCEL_NORMAL, WXK_F4, ID_FA_ORTHO_RECTANGLE_SELECTION);
	entries[3].Set(wxACCEL_NORMAL, WXK_F5, ID_FA_ORTHO_CIRCLE_SELECTION);
	entries[4].Set(wxACCEL_NORMAL, WXK_F6, ID_FA_ORTHO_NO_SELECTION);
	wxAcceleratorTable acceleratorTable(5, entries);
	SetAcceleratorTable(acceleratorTable);


	m_dockManager.Update();
}

void MainFrame::InitFenetres()
{
	////Création des panneaux principaux : visu ortho et gestion des fichiers

	FAEventHandler::Instance()->init(this);
	FAEventHandler::Instance()->setNotifyGLPanelCreated( boost::bind(&MainFrame::notifyGLPanelCreated, this) );
	FAEventHandler::Instance()->setNotifyPlotPanelCreated( boost::bind(&MainFrame::notifyPlotPanelCreated, this) );
	FAEventHandler::Instance()->setNotifyShowPanelSensorViewer( boost::bind(&MainFrame::notifyShowPanelSensorViewer, this) );

	///panneau ortho
	m_panelViewerMain = FAEventHandler::Instance()->getPanelFWOrtho();
	wxAuiPaneInfo paneInfoViewerMain;
	paneInfoViewerMain.Caption( _("Cartographic view") );
	paneInfoViewerMain.Center();
	m_dockManager.AddPane( m_panelViewerMain, paneInfoViewerMain );

	//panel de sélection des fichiers
	m_panelMainFiles = FAEventHandler::Instance()->getFilesPanel();
	wxAuiPaneInfo paneInfoMainFilesPanel;
	paneInfoMainFilesPanel.Caption( _("Files") );
	paneInfoMainFilesPanel.Left();
	paneInfoMainFilesPanel.MinSize( wxSize( 75, 75 ) ); //quand docké
	m_dockManager.AddPane(m_panelMainFiles, paneInfoMainFilesPanel);


	///panneau sensor
	m_panelViewerSensor = FAEventHandler::Instance()->getPanelFWSensor();
	wxAuiPaneInfo paneInfoViewerSensor;
	paneInfoViewerSensor.Caption( _("Sensor view") );
	paneInfoViewerSensor.Right();
	paneInfoViewerSensor.Hide();
	paneInfoViewerSensor.MinSize( wxSize( 300, 300 ) );
	m_dockManager.AddPane( m_panelViewerSensor, paneInfoViewerSensor );


	m_statusBar->SetStatusText( _("FullAnalyze") );

	m_dockManager.Update();


}

void MainFrame::InitMenus()
{
	m_menuBar = new wxMenuBar ( );


	////Window
	m_menuWindow = new wxMenu;
//	m_menuWindow->Append( menu_WindowsDockAll, _("Docker toutes les fenêtres"));
//	m_menuWindow->AppendSeparator();

	////Help
	m_menuHelp = new wxMenu;
//	m_menuHelp->Append( menu_options, _("Options\tAlt-O"));
//	m_menuHelp->AppendSeparator();
	m_menuHelp->Append( menu_about, _("About"));

	/////Processings
	m_menuProcessings = new wxMenu;
//	m_menuProcessings->Append( menu_enCours, _("En cours...\tF9"));

	////All
	m_menuBar->Append( m_menuWindow, _("Window"));
//	m_menuBar->Append( m_menuProcessings, _("Processings"));
	m_menuBar->Append( m_menuHelp, _("Help"));

	SetMenuBar( m_menuBar );
}

void MainFrame::OnOpenMenu( wxMenuEvent &event )
{
	UpdateMenuWindows();
	event.Skip();
}

struct LessInfoPane
{
	bool operator()(const wxAuiPaneInfo& p1, const wxAuiPaneInfo& p2)
	{
		return p1.caption < p2.caption;
	}
};

void MainFrame::UpdateMenuWindows()
{
	//on vide le menu Windows sauf les n premiers éléments indépendants des fenêtres de l'appli
	for (size_t i = 0; i < m_menuWindow->GetMenuItemCount(); ++i)
	{
		m_menuWindow->Delete( m_menuWindow->FindItemByPosition( i ) );
	}


	wxAuiPaneInfoArray &tableauPanes = m_dockManager.GetAllPanes();

	//on reremplit le menu avec la liste des panneaux donnée par le dockManager
	for (size_t i = 0; i < tableauPanes.size(); ++i)
	{
		wxAuiPaneInfo &currentPaneInfo = tableauPanes[i];

		if (m_menuWindow->FindItem( currentPaneInfo.caption ) == wxNOT_FOUND)
		{
			wxMenuItem *menuCourant = m_menuWindow->AppendCheckItem( menu_WindowsDockAll + i + 1, currentPaneInfo.caption );

			if (currentPaneInfo.IsShown())
				menuCourant->Check( true );
		}

	}

}

void MainFrame::OnMenuClickWindows( wxCommandEvent &event )
{
	//gestion du clic sur un sous menu de m_menuWindow
	wxMenuItem *menuFound = m_menuWindow->FindItem( event.GetId() );

	//Recherche de la fenêtre dans la liste du dock
	wxAuiPaneInfoArray &tableauPanes = m_dockManager.GetAllPanes();
	for (size_t i = 0; i < tableauPanes.size(); ++i)
	{
		wxAuiPaneInfo &currentPaneInfo = tableauPanes[i];

		if (menuFound->GetItemLabelText() == currentPaneInfo.caption)
		{
			currentPaneInfo.Show( menuFound->IsChecked() );
			m_dockManager.Update();
			break;
		}

	}

}

void MainFrame::onLidarDisplayProjectedPoints(wxCommandEvent &event)
{
	FAEventHandler::Instance()->lidarDisplayProjectedPoints(!FAEventHandler::Instance()->lidarDisplayProjectedPoints());
}


void MainFrame::onOrthoNavigate(wxCommandEvent &event)
{
	m_panelViewerMain->SetModeNavigation();
}

void MainFrame::onOrthoMoveSelection(wxCommandEvent &event)
{
	m_panelViewerMain->SetModeGeometryMoving();
}

void MainFrame::onOrthoRectangleSelection(wxCommandEvent &event)
{
	m_panelViewerMain->SetModeCapture();
	m_panelViewerMain->SetGeometryRectangle();
}

void MainFrame::onOrthoCircleSelection(wxCommandEvent &event)
{
	m_panelViewerMain->SetModeCapture();
	m_panelViewerMain->SetGeometryCircle();
}

void MainFrame::onOrthoNoSelection(wxCommandEvent &event)
{
	m_panelViewerMain->SetGeometryNull();
	m_panelViewerMain->SetModeNavigation();
	if(m_panel3D)
		m_panel3D->getCloudControl()->resetCrop();
}



IMPLEMENTS_GILVIEWER_METHODS_FOR_EVENTS_TABLE(MainFrame,m_panelViewerMain)

BEGIN_EVENT_TABLE(MainFrame, BasicViewerFrame)

	ADD_GILVIEWER_EVENTS_TO_TABLE(MainFrame)

	/////////////MENUS
	//Ouverture d'un menu -> lance la maj du menu windows
	EVT_MENU_OPEN(MainFrame::OnOpenMenu)
	//Clique sur un élément du menu windows : affiche ou cache le panneau correspondant
	EVT_MENU_RANGE(menu_WindowsDockAll, menu_WindowsDockAll+100, MainFrame::OnMenuClickWindows)
	//Autres menus : lance la fonction concernée
	EVT_MENU(menu_options, MainFrame::OnAfficheOptions)
	EVT_MENU(menu_about, MainFrame::OnAbout)

	EVT_TOOL(ID_FA_LIDAR_DISPLAY_PROJECTED_POINTS, MainFrame::onLidarDisplayProjectedPoints)
	EVT_TOOL(ID_FA_ORTHO_NAVIGATE, MainFrame::onOrthoNavigate)
	EVT_TOOL(ID_FA_ORTHO_MOVE_SELECTION, MainFrame::onOrthoMoveSelection)
	EVT_TOOL(ID_FA_ORTHO_RECTANGLE_SELECTION, MainFrame::onOrthoRectangleSelection)
	EVT_TOOL(ID_FA_ORTHO_CIRCLE_SELECTION, MainFrame::onOrthoCircleSelection)
	EVT_TOOL(ID_FA_ORTHO_NO_SELECTION, MainFrame::onOrthoNoSelection)
END_EVENT_TABLE()
