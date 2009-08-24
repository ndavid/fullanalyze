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

#include <algorithm>

#include "boost/bind.hpp"

#include <wx/filename.h>
#include <wx/config.h>

#include "gui/define_id.hpp"
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


#include "MainFrame.h"

MainFrame::MainFrame() :
	wxFrame( NULL, -1, _("FullAnalyze"), wxDefaultPosition, wxSize( 1280, 1024 ), wxDEFAULT_FRAME_STYLE)
{
	//////////   Status bar
	wxConfigBase *pConfig = wxConfigBase::Get();
	double fontSize;
	if ( pConfig )
		wxConfigBase::Get()->Read(_T("/Options/FontSize"), &fontSize, 8);
	// On tente un setting de la font pour pouvoir afficher les infos dans la status bar qd il y a bcp d'images ...
	wxFont fontFrameViewer((unsigned int)fontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	m_status = new wxStatusBar ( this, wxID_ANY, wxST_SIZEGRIP, _("statusBar") );

	this->SetStatusBar( m_status );
	this->GetStatusBar()->SetFont(fontFrameViewer);


	this->CenterOnScreen();

	/////////// Mise en place AUI :
	m_dockManager.SetManagedWindow(this);

	/////////// Log window
	m_logWindow = new wxLogWindow (this, _("Log window FullAnalyze"));
	m_logWindow->Show(false);

//	m_dockManager.Update();

	InitMenus();
	InitFenetres();


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
	m_dockManager.UnInit();
}


void MainFrame::DestroyPanel( wxPanel* panel )
{
	if (panel)
		panel->Destroy();
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


	/////// Toolbar
	wxAuiPaneInfo paneInfoToolbar;
	paneInfoToolbar.ToolbarPane();
	paneInfoToolbar.Caption( _("Toolbar") );
	paneInfoToolbar.Top();
	paneInfoToolbar.Fixed();
	m_dockManager.AddPane(m_panelViewerMain->GetToolBar(), paneInfoToolbar);



	m_status->SetStatusText( _("FullAnalyze - Adrien Chauve") );
	// tell the manager to "commit" all the changes just made
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

	this->SetMenuBar( m_menuBar );
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



IMPLEMENTS_ITKVIEWER_METHODS_FOR_EVENTS_TABLE(MainFrame,m_panelViewerMain)

BEGIN_EVENT_TABLE(MainFrame, wxFrame)

	ADD_ITKVIEWER_EVENTS_TO_TABLE(MainFrame)

	/////////////MENUS
	//Ouverture d'un menu -> lance la maj du menu windows
	EVT_MENU_OPEN(MainFrame::OnOpenMenu)
	//Clique sur un élément du menu windows : affiche ou cache le panneau correspondant
	EVT_MENU_RANGE(menu_WindowsDockAll, menu_WindowsDockAll+100, MainFrame::OnMenuClickWindows)
	//Autres menus : lance la fonction concernée
	EVT_MENU(menu_options, MainFrame::OnAfficheOptions)
	EVT_MENU(menu_about, MainFrame::OnAbout)
END_EVENT_TABLE()
