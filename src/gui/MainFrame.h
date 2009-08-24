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
