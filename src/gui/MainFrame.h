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

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <string>
#include <map>
#include <list>

#include "boost/shared_ptr.hpp"

#include <wx/wx.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>

#include "LidarFormat/extern/matis/tpoint2d.h"

//Panels dérivés de la lib ITKViewerLib
class PanelViewerFWSensor;
class PanelViewerFWOrtho;
class PanelViewer;
//Panel de plot2D
class Plot;
//Panneau OpenGL
class GLPanel;
//Paneau de sélection des fichiers
class FilesPanel;

using boost::shared_ptr;

#include "convenient/MacrosITKViewer.hpp"

class MainFrame : public wxFrame
{
	public:
		MainFrame();
		virtual ~MainFrame();

		void DestroyPanel(wxPanel* panel);


	private:

		///Création des fenêtres
		void InitFenetres();
		///Initialisation des menus
		void InitMenus();


		void UpdateMenuWindows();

		///Ouverture d'un menu (lance la maj du menu fenêtres)
		void OnOpenMenu(wxMenuEvent &event);

		void OnMenuClickWindows(wxCommandEvent &event);
		void OnAfficheOptions(wxCommandEvent &event);


		///car bug avec gtk si le panel est créé au démarrage de l'appli...
		void notifyGLPanelCreated();
		void notifyPlotPanelCreated();
		void notifyShowPanelSensorViewer();

		///////////////////DATA

		//Garbage collectors
		std::list<wxPanel*> m_garbageCollectorPanels; //pour les panels ouverts non principaux (ie mis à part le paneau de fichiers et le paneau de viewer principal


		///////////////////
		///FENETRES

		///Gestionnaire de la fenetre
		wxAuiManager m_dockManager;

		///Panneaux principaux
		PanelViewerFWOrtho *m_panelViewerMain; //panel viewer (ortho)
		FilesPanel *m_panelMainFiles; //panel de gestion des fichiers

		///Fenetres filles

		///Visu2D pour la geom capteur d'une bande d'un chantier
		PanelViewerFWSensor *m_panelViewerSensor;
		PanelViewer *m_panelImageProcessing;

		///Panel de plot de courbes FW
		Plot *m_panelPlot;
		GLPanel *m_panel3D;


		///////////////////////////////////////////


		wxStatusBar *m_status;
		wxLogWindow* m_logWindow;

		/////////////////////////////
		///MENUS


		wxMenuBar *m_menuBar;
		wxMenu *m_menuSurveys;
		wxMenu *m_menuProcessings;
		wxMenu *m_menuWindow;
		wxMenu *m_menuHelp;

		enum
		{
			//TODO to be cleaned
			menu_about,
			menu_options,
			menu_exportASCII,
			menu_calculeZone,
			menu_calculeBande,
			menu_afficheNuagePts,
			menu_afficheProfils,
			menu_afficheOndes3D,
			menu_chargerNouveauChantier,
			menu_classif,
			menu_imagesCapteurAttribut,
			menu_imageFluctuationsLaser,
			menu_conversionXYZtoBin,
			menu_conversionXYZL3toBinL2E,
			menu_conversionXYZL3DensitetoBinL2E,
			menu_conversionEcho2TxLaser,
			menu_conversionFW,
			menu_enCours,
			menu_RIEGL_to_NewFormat,
			menu_creationImagesGeorefGlobales,
			menu_chargerOrtho,
			menu_afficherTrajecto,
			menu_calculeClassifFeatures,
			menu_segmentation,

			//Attention ne rien définir après !! la suite des id est utilisée pour les menus des fenêtres
			menu_WindowsDockAll
		};

		DECLARE_ITKVIEWER_METHODS_FOR_EVENTS_TABLE();
		DECLARE_EVENT_TABLE();
};

#endif // MAINFRAME_H
