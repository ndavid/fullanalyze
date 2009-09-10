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

#ifdef _WINDOWS
#include <windows.h>

#	undef min
#	undef max
#endif

#include "CloudControl.h"

#include <list>
#include <sstream>
#include <limits>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <wx/xrc/xmlres.h>
#include <wx/checkbox.h>
#include <wx/bmpbuttn.h>
#include <wx/textctrl.h>
#include <wx/confbase.h>
#include <wx/progdlg.h>
#include <wx/toolbar.h>
#include <wx/tooltip.h>
#include <wx/filedlg.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/msgdlg.h>
#include <wx/icon.h>
#include <wx/file.h>
#include <wx/log.h>

extern void InitXmlResource();


#include "3d/Cloud.h"
#include "3d/PointCloud.h"


#include "CloudSettingsControl.h"
#include "CloudInfosControl.h"
#include "PointCloudSettingsControl.h"

#ifdef BUILD_FULLWAVE
#include "fullwave/FullwaveCloudSettingsControl.h"
#endif

#include "CloudViewGlobalSettingsControl.h"
#include "3d/GLPanel.h"
#include "3d/PointCloudCanvas.h"

#include "LidarFormat/geometry/RegionOfInterest2D.h"


#include "define_id_FA3D.h"


#include "gui/resources/eye.xpm"
#include "gui/resources/Measure.xpm"
#include "gui/resources/polygon_icon.xpm"
#include "gui/resources/image_icon.xpm"


////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                  ///
///                                 CloudSelectableStaticText                                             ///
///                                                                                                  ///
////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(CloudSelectableStaticText, wxStaticText)
EVT_LEFT_DOWN(CloudSelectableStaticText::OnClick)
END_EVENT_TABLE()

void CloudSelectableStaticText::OnClick(wxMouseEvent& event)
{

	// On effectue la modification de couleur sur le calque selectionne et on change le flag
	if (m_isSelected == false)
	{
		//SetBackgroundColour( m_selectedColour );
		SetForegroundColour(m_selectedColour);
		//ClearBackground();
		SetLabel( GetLabel());
		m_isSelected = true;
	}
	else
	{
		//SetBackgroundColour( m_unselectedColour );
		SetForegroundColour(m_unselectedColour);
		//ClearBackground();
		SetLabel( GetLabel());
		m_isSelected = false;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                  ///
///                                 CloudControlRow                                                  ///
///                                                                                                  ///
////////////////////////////////////////////////////////////////////////////////////////////////////////

CloudControlRow::CloudControlRow(CloudControl* parent, const std::string &name, const unsigned int index, CloudSettingsControl *cloudSettings, const std::string &tooltip) :
	m_parent(parent), m_index(index)
{
	// On ajoute l'ensemble des controles
	wxString name_wx(name.c_str(), *wxConvCurrent);
	wxString tool(tooltip.c_str(), *wxConvCurrent);
	wxFont fontFrameViewer(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	m_nameStaticText = new CloudSelectableStaticText(m_parent, m_parent, wxID_HIGHEST + 12000, name_wx);
	m_nameStaticText->SetFont(fontFrameViewer);
	m_nameStaticText->SetToolTip(tool);

	m_visibilityCheckBox = new wxCheckBox(m_parent, ID_FA_VISIBILITY + m_index, _(""));
	m_visibilityCheckBox->SetValue(true);
	m_visibilityCheckBox->SetToolTip(_("Change layer visibility"));
	m_visibilityCheckBox->Connect(ID_FA_VISIBILITY + m_index, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CloudControl::OnCheckVisibility), NULL, m_parent);

//	m_transformationCheckBox = new wxCheckBox(m_parent, ID_FA_TRANSFORMATION + m_index, _(""));
//	m_transformationCheckBox->SetValue(true);
//	m_transformationCheckBox->SetToolTip(_("Change layer transformability"));
//	m_transformationCheckBox->Connect(ID_FA_TRANSFORMATION + m_index, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(CloudControl::OnCheckTransformable), NULL, m_parent);

	m_boxSizer = new wxBoxSizer(wxHORIZONTAL);

	// L'icone du bouton  info depend du type : vecteur ou image
	if (dynamic_cast<PointCloudSettingsControl*> (cloudSettings) != NULL)
	    m_infoButton = new wxBitmapButton(m_parent, ID_FA_INFO + m_index, wxXmlResource::Get()->LoadBitmap( wxT("APPLICATIONS-OTHERS_16x16") ));
	else
	    m_infoButton = new wxBitmapButton(m_parent, ID_FA_INFO + m_index, wxXmlResource::Get()->LoadBitmap( wxT("APPLICATIONS-GRAPHICS_16x16") ) );

	m_infoButton->SetToolTip(wxT("Display layer informations"));
	m_boxSizer->Add(m_infoButton, 0, wxALL | wxALIGN_CENTRE, 5);
	m_infoButton->Connect(ID_FA_INFO + m_index, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CloudControl::OnInfoButton), NULL, m_parent);

    m_deleteButton = new wxBitmapButton(m_parent, ID_FA_DELETE + m_index, wxXmlResource::Get()->LoadBitmap( wxT("USER-TRASH_16x16") ) );
	m_deleteButton->SetToolTip(wxT("Delete layer"));
	m_boxSizer->Add(m_deleteButton, 0, wxALL | wxALIGN_CENTRE, 5);
	m_deleteButton->Connect(ID_FA_DELETE + m_index, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CloudControl::OnDeleteButton), NULL, m_parent);

    m_settingsButton = new wxBitmapButton(m_parent, ID_FA_SETTINGS + m_index, wxXmlResource::Get()->LoadBitmap( wxT("APPLICATIONS-SYSTEM_16x16") ) );

	m_settingsButton->SetToolTip(wxT("Layer settings"));
	m_boxSizer->Add(m_settingsButton, 0, wxALL | wxALIGN_CENTRE, 5);
	m_settingsButton->Connect(ID_FA_SETTINGS + m_index, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CloudControl::OnSettingsButton), NULL, m_parent);

	// On lie la ligne au LayerSettingsControl
	m_cloudSettingsControl = cloudSettings;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                  ///
///                                 CloudControl                                                     ///
///                                                                                                  ///
////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(CloudControl, wxFrame)
EVT_CLOSE(CloudControl::OnCloseWindow)
EVT_BUTTON(ID_FA_INFO,CloudControl::OnInfoButton)
EVT_BUTTON(ID_FA_DELETE,CloudControl::OnDeleteButton)
EVT_BUTTON(ID_FA_GLOBAL_SETTINGS_BUTTON, CloudControl::OnGlobalSettingsButton)
// Gestion des evenements de la toolbar
EVT_TOOL(wxID_RESET,CloudControl::OnReset)
// Gestion des evenements "globaux" du LayerControl
EVT_BUTTON(wxID_UP,CloudControl::OnLayerUp)
EVT_BUTTON(wxID_DOWN,CloudControl::OnLayerDown)
//EVT_BUTTON(ID_FA_VISIBILITY_BUTTON,CloudControl::OnVisibilityButton)
EVT_BUTTON(wxID_SAVE,CloudControl::OnSaveDisplayConfigButton)
EVT_BUTTON(wxID_OPEN,CloudControl::OnLoadDisplayConfigButton)
EVT_CHAR(CloudControl::OnChar)
END_EVENT_TABLE()

CloudControl::CloudControl(wxWindow *parent, PointCloudCanvas* ptCloudCanvas, boost::function<void()> notifyRefresh): //, boost::function<void(double, double, double)> setTranslation) :
	wxFrame(parent, wxID_ANY, _("Cloud control !")),
	m_pointCloudCanvas(ptCloudCanvas),
	m_numberOfClouds(0),
	m_notifyRefresh(notifyRefresh),
	m_cloudViewGlobalSettingsControl(new CloudViewGlobalSettingsControl(this, boost::bind(&CloudControl::updateFromGlobalViewSettingsControl, this)))

//	m_notifySetTranslation(setTranslation)

{
	// Initialising resources ...
	wxXmlResource::Get()->InitAllHandlers();
	InitXmlResource();

	SetIcon(wxArtProvider::GetIcon(wxART_LIST_VIEW, wxART_TOOLBAR, wxSize(32,32)));	// Couleur de fond grisee

	wxColour bgcolor(220, 220, 220);
	SetBackgroundColour(bgcolor);
	ClearBackground();

	// Ajout de la barre d'outils
	this->CreateToolBar(wxNO_BORDER | wxTB_HORIZONTAL, 500);
	InitToolbar(this->GetToolBar());

	// On initialise le sizer qui permet de gerer efficacement le positionnement des controles des differentes lignes
	m_sizer = new wxFlexGridSizer(1, 3, 5, 5);

	// On ajoute l'ensemble des boutons "globaux"
	// Un sizer pour les fleches "up" et "down"
	wxBoxSizer* upDownButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	// Fleche "up"
	wxBitmapButton* upButton = new wxBitmapButton(this, wxID_UP, wxXmlResource::Get()->LoadBitmap( wxT("GO-UP_16x16") ) );
	//upButton->SetToolTip( _("
	upDownButtonSizer->Add(upButton, 0, wxALL | wxALIGN_CENTRE, 5);
	// Fleche "down"
    upDownButtonSizer->Add(new wxBitmapButton(this, wxID_DOWN, wxXmlResource::Get()->LoadBitmap( wxT("GO-DOWN_16x16") ) ) , 0, wxALL | wxALIGN_CENTRE, 5);
	m_sizer->Add(upDownButtonSizer, 0, wxALL | wxALIGN_CENTRE, 5);
	// Bouton pour inverser la visibilite de tous les calques selectionnes
	wxBitmapButton* visibilityButton = new wxBitmapButton(this, ID_FA_VISIBILITY_BUTTON, wxXmlResource::Get()->LoadBitmap( wxT("EYE_16x16") ));
	visibilityButton->SetToolTip(_("Change selected layers visibility"));
	m_sizer->Add(visibilityButton, 0, wxALL | wxALIGN_CENTRE, 5);
//	// Bouton pour inverser la transformabilite (!!!) de tous les calques selectionnes
//	wxBitmapButton* transformabilityButton = new wxBitmapButton(this, ID_FA_TRANSFORMATION_BUTTON, wxBitmap(measure_xpm));
//	transformabilityButton->SetToolTip(_("Change selected layers transformability"));
//	m_sizer->Add(transformabilityButton, 0, wxALL | wxALIGN_CENTRE, 5);

	wxBoxSizer *globalSettingsSizer = new wxBoxSizer(wxHORIZONTAL);

	// Bouton pour les modifications globales
	wxBitmapButton* globalSettingsButton = new wxBitmapButton(this, ID_FA_GLOBAL_SETTINGS_BUTTON, wxXmlResource::Get()->LoadBitmap( wxT("PREFERENCES-SYSTEM_16x16") ) );
	globalSettingsButton->SetToolTip(_("Global settings control"));
	globalSettingsSizer->Add(globalSettingsButton, 0, wxALL | wxALIGN_CENTRE, 5);

	// Bouton pour la sauvegarde de la configuration d'affichage
	wxBitmapButton* saveDisplayConfig = new wxBitmapButton(this, wxID_SAVE, wxXmlResource::Get()->LoadBitmap( wxT("DOCUMENT-SAVE_16x16") ) );
	saveDisplayConfig->SetToolTip(_("Save display configuration"));
	globalSettingsSizer->Add(saveDisplayConfig, 0, wxALL | wxALIGN_CENTRE, 5);

	// Bouton pour l'ouverture d'une configuration d'affichage
	wxBitmapButton* loadDisplayConfig = new wxBitmapButton(this, wxID_OPEN, wxXmlResource::Get()->LoadBitmap( wxT("DOCUMENT-OPEN_16x16") ) );
	loadDisplayConfig->SetToolTip(_("Load display configuration"));
	globalSettingsSizer->Add(loadDisplayConfig, 0, wxALL | wxALIGN_CENTRE, 5);

	m_sizer->Add(globalSettingsSizer, 0, wxALL | wxALIGN_CENTRE, 5);

	m_sizer->SetSizeHints(this);
	SetSizer(m_sizer);

	Layout();

}

void CloudControl::OnGlobalSettingsButton(wxCommandEvent& event)
{
	m_cloudViewGlobalSettingsControl->Show(!m_cloudViewGlobalSettingsControl->IsVisible());
}

bool CloudControl::drawAxes() const
{
	return m_cloudViewGlobalSettingsControl->drawAxes();
}

bool CloudControl::drawBBox() const
{
	return m_cloudViewGlobalSettingsControl->drawBBox();
}

wxColour CloudControl::backgroundColor() const
{
	return m_cloudViewGlobalSettingsControl->backgroundColor();
}

void CloudControl::updateFromGlobalViewSettingsControl() const
{
	m_pointCloudCanvas->setFar(m_cloudViewGlobalSettingsControl->getFar());
	m_pointCloudCanvas->setTranslationScale(m_cloudViewGlobalSettingsControl->translation());
	m_pointCloudCanvas->setZoom(m_cloudViewGlobalSettingsControl->zoom());
	m_pointCloudCanvas->setRotationScale(m_cloudViewGlobalSettingsControl->rotation());

	m_notifyRefresh();
}

void CloudControl::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
	// On ne fait que cacher la fenetre. Ca permet de garder les settings courants et de ne pas recalculer tout a chaque fois ...
	Hide();
}

void CloudControl::AddRow(const std::string &name, CloudSettingsControl *cloudSettings, const std::string &tooltip)
{
	// Le nom du layer a une longueur maximale de 20 caracteres
	std::string layer_name = name;
	layer_name = name + " ";
	std::ostringstream layer_index;
	layer_index << m_numberOfClouds;
	//layer_name = layer_name + layer_index.str();
	wxString layerName(layer_name.substr(0, 50).c_str(), *wxConvCurrent);
	std::string ln(layerName.fn_str());

	// on ajoute la ligne dans le conteneur
	m_rows.push_back(boost::shared_ptr<CloudControlRow>(new CloudControlRow(this, ln, m_numberOfClouds, cloudSettings, tooltip)));
	// On ajoute a proprement parler les controles de la ligne dans le LayerControl
	m_sizer->Add(m_rows[m_numberOfClouds]->m_nameStaticText, 0, wxTOP | wxALIGN_LEFT, 5);

	m_sizer->Add(m_rows[m_numberOfClouds]->m_visibilityCheckBox, 0, wxALL | wxALIGN_CENTRE, 5);
	m_rows[m_numberOfClouds]->m_visibilityCheckBox->SetValue(m_clouds[m_numberOfClouds]->isVisible());


	m_sizer->Add(m_rows[m_numberOfClouds]->m_boxSizer, wxGROW);
	m_sizer->Fit(this);

	m_numberOfClouds++;
}

bool CloudControl::InitToolbar(wxToolBar* toolBar)
{
	toolBar->SetMargins(5, 5);

	// Set up toolba
	toolBar->AddTool(wxID_NEW, _("N"), wxXmlResource::Get()->LoadBitmap( wxT("DOCUMENT-NEW_22x22") ) , wxNullBitmap, wxITEM_NORMAL, _("New file"));
	toolBar->AddTool(wxID_OPEN, _("O"), wxXmlResource::Get()->LoadBitmap( wxT("DOCUMENT-OPEN_22x22") ) , wxNullBitmap, wxITEM_NORMAL, _("Open file"));
	toolBar->AddTool(wxID_SAVE, _("S"), wxXmlResource::Get()->LoadBitmap( wxT("DOCUMENT-SAVE_22x22") ) , wxNullBitmap, wxITEM_NORMAL, _("Save file"));
	toolBar->AddTool(wxID_RESET, _("R"), wxXmlResource::Get()->LoadBitmap( wxT("EDIT-CLEAR_22x22") ) , wxNullBitmap, wxITEM_NORMAL, _("Reset"));

	toolBar->Realize();

	return true;
}

void CloudControl::updateGUIfromClouds()
{
	for (unsigned int id = 0;id<m_clouds.size();++id)
	{
//		m_rows[id]->m_transformationCheckBox->SetValue( m_clouds[id]->IsTransformable() );
		m_rows[id]->m_visibilityCheckBox->SetValue( m_clouds[id]->isVisible() );
	}
}

void CloudControl::updateFromCrop(const RegionOfInterest2D& region)
{
	for(iterator it = begin(); it != end(); ++it)
	{
		(*it)->updateFromCrop(region);
	}

	centreScene();
	m_notifyRefresh();
}

void CloudControl::OnInfoButton(wxCommandEvent& event)
{
	// Get layer index
	unsigned int id = static_cast<unsigned int> (event.GetId()) - static_cast<unsigned int> (ID_FA_INFO);

	CloudInfosControl *ilsc;

//	// Test if the layer is a vector one or an image one ...
//	boost::shared_ptr<VectorLayer> vl = boost::dynamic_pointer_cast<VectorLayer>(m_clouds[id]);
//	//if (typeid( m_layers[id] ) == typeid(VectorLayer))
//	if (vl != NULL)
//	{
//		wxString title(_("Vector settings"));
//		title << _(" : ") << wxString(m_clouds[id]->Name().c_str(), *wxConvCurrent);
//		vl->GetInfos();
//		ilsc = new CloudInfosControl(m_clouds[id]->GetInfos(), this, wxID_ANY, title, wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL | wxCLOSE_BOX);
//	}
//	else
	{
		wxString title(_("Cloud settings"));
		title << _(" : ") << wxString(m_clouds[id]->name().c_str(), *wxConvCurrent);
		ilsc = new CloudInfosControl(m_clouds[id]->getInfos(), this, wxID_ANY, title, wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL | wxCLOSE_BOX);
	}
	ilsc->Show();
}


void CloudControl::OnDeleteButton(wxCommandEvent& event)
{
	// Get layer index
	unsigned int id = static_cast<unsigned int> (event.GetId()) - static_cast<unsigned int> (ID_FA_DELETE);

	//Swap
	for (unsigned int i = id; i < m_numberOfClouds - 1; ++i)
	{
		SwapRows(i, i + 1);
	}

	//Destroy de la row
	m_rows.back()->m_nameStaticText->Destroy();
	m_rows.back()->m_visibilityCheckBox->Destroy();
//	m_rows.back()->m_transformationCheckBox->Destroy();
	m_rows.back()->m_infoButton->Destroy();
	m_rows.back()->m_deleteButton->Destroy();
	m_rows.back()->m_settingsButton->Destroy();
	m_rows.back()->m_cloudSettingsControl->destroy();
	m_sizer->Remove(m_rows.back()->m_boxSizer);

	m_rows.pop_back();

	//Delete de la layer
	m_clouds.pop_back();

	--m_numberOfClouds;
	centreScene();

	//
	m_sizer->Fit(this);

}

void CloudControl::OnSettingsButton(wxCommandEvent& event)
{
	// Get layer index
	unsigned int id = static_cast<unsigned int> (event.GetId()) - static_cast<unsigned int> (ID_FA_SETTINGS);
	// Test if the layer is a vector one or an image one ...
//	if (typeid(m_clouds[id]) == typeid(shared_ptr<PointCloud>))
//	{
//		wxString title(_("Image settings"));
//		title << _(" : ") << wxString(m_clouds[id]->name().c_str(), *wxConvCurrent);
//		m_rows[id]->m_cloudSettingsControl->show(!m_rows[id]->m_cloudSettingsControl->isVisible());
//	}
//	else
	{
		wxString title(_("Image settings"));
		title << _(" : ") << wxString(m_clouds[id]->name().c_str(), *wxConvCurrent);
		m_rows[id]->m_cloudSettingsControl->show(!m_rows[id]->m_cloudSettingsControl->isVisible());
	}
}

void CloudControl::OnCheckVisibility(wxCommandEvent& event)
{
	// On commence par recupere l'indice du calque
	unsigned int id = static_cast<unsigned int> (event.GetId()) - static_cast<unsigned int> (ID_FA_VISIBILITY);
	// On inverse ...
	m_clouds[id]->isVisible(m_rows[id]->m_visibilityCheckBox->GetValue());
	// ... et on refresh
//	m_clouds[id]->hasToBeUpdated(true);
	m_notifyRefresh();
}


void CloudControl::OnReset(wxCommandEvent& event)
{
	// Pour chaque calque, on reinitialise
	for (CloudControl::iterator it = begin(); it != end(); ++it)
	{
//		(*it)->ZoomFactor(1.);
//		(*it)->TranslationX(0.);
//		(*it)->TranslationY(0.);
//		(*it)->HasToBeUpdated(true);
//		(*it)->IsTransformable(true);
		(*it)->isVisible(true);
	}

	// Et on remet les checkbox en place (true)
	for (unsigned int i = 0; i < m_numberOfClouds; ++i)
	{
		m_rows[i]->m_visibilityCheckBox->SetValue(true);
	}

	m_pointCloudCanvas->reset();

	// On refresh le tout ...
	m_notifyRefresh();
}


#include <boost/lambda/lambda.hpp>
#include <boost/algorithm/string/case_conv.hpp>


void CloudControl::AddCloud(const shared_ptr<Cloud> &cloud)
{
	m_clouds.push_back(cloud);
	centreScene();


	// On construite le SettingsControl en fonction du type de calque ajoute
	CloudSettingsControl *settingsControl;
	boost::shared_ptr<PointCloud> ptC = boost::dynamic_pointer_cast<PointCloud>(cloud);
	if (ptC != NULL)
		settingsControl = new PointCloudSettingsControl(m_clouds.size() - 1, this);
#ifdef BUILD_FULLWAVE
	else
		settingsControl = new FullwaveCloudSettingsControl(m_clouds.size() - 1, this);
#endif
//	layer->SetNotifyLayerSettingsControl( boost::bind( &CloudSettingsControl::update, settingsControl ) );
	// On ajoute la ligne correspondante
	std::string name = "  ";
	name = name + boost::filesystem::basename(cloud->name());
	AddRow(name, settingsControl, cloud->name());
}

void CloudControl::initScene()
{
	m_xG = 0;
	m_yG = 0;
	m_zG = 0;

	m_maxX = -std::numeric_limits<float>::max();
	m_maxY = -std::numeric_limits<float>::max();
	m_maxZ = -std::numeric_limits<float>::max();
	m_minX = std::numeric_limits< double >::max();
	m_minY = std::numeric_limits< double >::max();
	m_minZ = std::numeric_limits< double >::max();

	m_maxi = 1;
}

void CloudControl::centreScene()
{

	using namespace std;



	bool empty = true;

	for (iterator it = begin(); it != end(); ++it)
	{
		if(!((*it)->m_isEmpty))
			empty = false;
	}

	//Récupération des min/max de tous les clouds
	if(!empty)
	{
		initScene();

		for (iterator it = begin(); it != end(); ++it)
		{
			if(!((*it)->m_isEmpty))
			{
				m_minX = min( m_minX, (*it)->m_minX );
				m_maxX = max( m_maxX, (*it)->m_maxX );
				m_minY = min( m_minY, (*it)->m_minY );
				m_maxY = max( m_maxY, (*it)->m_maxY );
				m_minZ = min( m_minZ, (*it)->m_minZ );
				m_maxZ = max( m_maxZ, (*it)->m_maxZ );
			}
		}

		m_xG = ( m_maxX + m_minX ) / 2;
		m_yG = ( m_maxY + m_minY ) / 2;
		m_zG = ( m_maxZ + m_minZ ) / 2;

		m_maxi = max( max( fabs( m_maxX - m_xG ), fabs( m_minX - m_xG ) ), max( max( fabs( m_maxY - m_yG ), fabs( m_minY - m_yG ) ), max( fabs( m_maxZ - m_zG ), fabs( m_minZ - m_zG ) ) ) );

	}

//
//	//Centrage de chaque nuage de pts
//	for (iterator it = begin(); it != end(); ++it)
//	{
//		(*it)->centreCloud( TPoint3D< double > ( m_xG, m_yG, m_zG ), m_maxi );
//	}


	//Translation au centre des nuages de points
	m_pointCloudCanvas->setTranslation(-m_xG, -m_yG, -m_zG);
	m_pointCloudCanvas->setSizeOfWorld(m_maxi);


	m_notifyRefresh();
}

void CloudControl::SwapRows(const unsigned int firstRow, const unsigned int secondRow)
{
	if (firstRow < 0 || secondRow < 0)
	{
		std::ostringstream oss;
		oss << "You passed a negative index for a row !" << std::endl;
		oss << "firstRow = " << firstRow << "  --  secondRow = " << secondRow << std::endl;
		oss << "File : " << __FILE__ << std::endl;
		oss << "Line : " << __LINE__ << std::endl;
		oss << "Function : " << __FUNCTION__ << std::endl;
		// On est dans du wx, je m'autorise une MessageBox ...
		std::string mess(oss.str());
		wxString mes(mess.c_str(), *wxConvCurrent);
		::wxLogMessage(mes);
		return;
	}
	else if (firstRow >= m_numberOfClouds || secondRow >= m_numberOfClouds)
	{
		std::ostringstream oss;
		oss << "You passed an invalid index for a row !" << std::endl;
		oss << "firstRow = " << firstRow << "  --  secondRow = " << secondRow << std::endl;
		oss << "m_numberOfLayers = " << m_numberOfClouds << std::endl;
		oss << "File : " << __FILE__ << std::endl;
		oss << "Line : " << __LINE__ << std::endl;
		oss << "Function : " << __FUNCTION__ << std::endl;
		// On est dans du wx, je m'autorise une MessageBox ...
		std::string mess(oss.str());
		wxString mes(mess.c_str(), *wxConvCurrent);
		::wxLogMessage(mes);
		return;
	}

	//statictext
	{
		// On fait aussi la mise a jour du tooltip ...
		wxString temp(m_rows[firstRow]->m_nameStaticText->GetLabel());
		wxString strTooltip(m_rows[firstRow]->m_nameStaticText->GetToolTip()->GetTip());

		m_rows[firstRow]->m_nameStaticText->SetLabel(m_rows[secondRow]->m_nameStaticText->GetLabel());
		m_rows[firstRow]->m_nameStaticText->GetToolTip()->SetTip(m_rows[secondRow]->m_nameStaticText->GetToolTip()->GetTip());
		m_rows[secondRow]->m_nameStaticText->SetLabel(temp);
		m_rows[secondRow]->m_nameStaticText->GetToolTip()->SetTip(strTooltip);
		m_rows[firstRow]->m_nameStaticText->IsSelected(false);
		m_rows[secondRow]->m_nameStaticText->IsSelected(true);
	}

	//visibility

	{
		bool temp(m_rows[firstRow]->m_visibilityCheckBox->GetValue());
		m_rows[firstRow]->m_visibilityCheckBox->SetValue(m_rows[secondRow]->m_visibilityCheckBox->GetValue());
		m_rows[secondRow]->m_visibilityCheckBox->SetValue(temp);
	}

//	//transform
//	{
//		bool temp(m_rows[firstRow]->m_transformationCheckBox->GetValue());
//		m_rows[firstRow]->m_transformationCheckBox->SetValue(m_rows[secondRow]->m_transformationCheckBox->GetValue());
//		m_rows[secondRow]->m_transformationCheckBox->SetValue(temp);
//	}

	//cloud
	{
		shared_ptr<Cloud> temp = m_clouds[firstRow];
		m_clouds[firstRow] = m_clouds[secondRow];
		m_clouds[secondRow] = temp;
	}

	//cloudSettingscontrol
	{
		CloudSettingsControl *temp = m_rows[firstRow]->m_cloudSettingsControl;
		m_rows[firstRow]->m_cloudSettingsControl = m_rows[secondRow]->m_cloudSettingsControl;
		m_rows[secondRow]->m_cloudSettingsControl = temp;

		m_rows[firstRow]->m_cloudSettingsControl->index(firstRow);
		m_rows[secondRow]->m_cloudSettingsControl->index(secondRow);
	}

//	// Finalement, si necessaire, il faut changer le bitmap associe au bouton d'infos
//	{
//		if (dynamic_cast<VectorLayerSettingsControl*> (m_rows[firstRow]->m_cloudSettingsControl))
//			m_rows[firstRow]->m_infoButton->SetBitmapLabel(wxBitmap(polygon_icon_xpm));
//		else if (dynamic_cast<PointCloudSettingsControl*> (m_rows[firstRow]->m_cloudSettingsControl))
//			m_rows[firstRow]->m_infoButton->SetBitmapLabel(wxBitmap(image_icon_xpm));
//		if (dynamic_cast<VectorLayerSettingsControl*> (m_rows[secondRow]->m_cloudSettingsControl))
//			m_rows[secondRow]->m_infoButton->SetBitmapLabel(wxBitmap(polygon_icon_xpm));
//		else if (dynamic_cast<PointCloudSettingsControl*> (m_rows[secondRow]->m_cloudSettingsControl))
//			m_rows[secondRow]->m_infoButton->SetBitmapLabel(wxBitmap(image_icon_xpm));
//	}
}

void CloudControl::OnLayerUp(wxCommandEvent& WXUNUSED(event))
{
	for (unsigned int i = 0; i < m_numberOfClouds; ++i)
	{
		if (m_rows[i]->m_nameStaticText->IsSelected())
		{
			SwapRows(i, i - 1);
			break;
		}
	}

	Refresh();
	m_notifyRefresh();

}

void CloudControl::OnLayerDown(wxCommandEvent& WXUNUSED(event))
{
	for (unsigned int i = 0; i < m_numberOfClouds; ++i)
	{
		if (m_rows[i]->m_nameStaticText->IsSelected())
		{
			SwapRows(i, i + 1);
			break;
		}
	}

	Refresh();
	m_notifyRefresh();
}

void CloudControl::OnVisibilityButton(wxCommandEvent& event)
{
	// On parcourt tous les calques et on inverse la visibilite si la selection est a true
	for (unsigned int i = 0; i < m_numberOfClouds; ++i)
	{
		if (m_rows[i]->m_nameStaticText->IsSelected() == true)
		{
			m_rows[i]->m_visibilityCheckBox->SetValue(!m_rows[i]->m_visibilityCheckBox->GetValue());
			m_clouds[i]->isVisible(m_rows[i]->m_visibilityCheckBox->GetValue());
		}
	}

	// On refresh le tout ...
	m_notifyRefresh();
}


//TODO to be cleaned

//void CloudControl::OnTransformationButton(wxCommandEvent& event)
//{
//	// On parcourt tous les calques et on inverse la transformabilite (!!!) si la section est a true
//	for (unsigned int i = 0; i < m_numberOfClouds; ++i)
//	{
//		if (m_rows[i]->m_nameStaticText->IsSelected() == true)
//		{
//			m_rows[i]->m_transformationCheckBox->SetValue(!m_rows[i]->m_transformationCheckBox->GetValue());
//			m_clouds[i]->IsTransformable(m_rows[i]->m_transformationCheckBox->GetValue());
//		}
//	}
//
//	// On refresh le tout ...
//	m_glPanel->Refresh();
//}



void CloudControl::OnSaveDisplayConfigButton(wxCommandEvent& event)
{
//	// Choix du fichier de sauvegarde
//	wxFileDialog* fd = new wxFileDialog(this, _("Sauvegarde de la configuration d'affichage"), _(""), _(""), _("*.xml"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
//	if (fd->ShowModal() == wxID_OK)
//	{
//		std::string savename(fd->GetPath().fn_str());
//		if (boost::filesystem::extension(savename) != ".xml")
//			boost::filesystem::change_extension(savename, ".xml");
//
//		XMLDisplayConfigurationIO::Write(this, savename.c_str());
//	}
//	delete fd;
}

void CloudControl::OnLoadDisplayConfigButton(wxCommandEvent& event)
{
//	// Choix du fichier de sauvegarde
//	wxFileDialog* fd = new wxFileDialog(this, _("Chargement d'une configuration d'affichage"), _(""), _(""), _("*.xml"), wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
//	if (fd->ShowModal() == wxID_OK)
//	{
//		wxString message;
//		message << _("Lecture d'un fichier de configration d'affichage : ") << fd->GetPath();
//		::wxLogMessage(message);
//
//		std::string loadname(fd->GetPath().fn_str());
//		if (boost::filesystem::extension(loadname) != ".xml")
//		{
//			wxLogMessage(_("Le fichier de configuration doit avoir l'extension .xml !"), _("Erreur !"));
//			return;
//		}
//
//		XMLDisplayConfigurationIO::Read(this, loadname);
//		m_glPanel->Refresh();
//	}
//
}

void CloudControl::OnChar(wxKeyEvent& event)
{

	if (event.GetKeyCode() == 'l')
	{
		this->Hide();
	}

	event.Skip();
}


