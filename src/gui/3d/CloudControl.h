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

#ifndef __CLOUD_CONTROL_HPP__
#define __CLOUD_CONTROL_HPP__

#include <vector>

#include <boost/shared_ptr.hpp>

#include <wx/stattext.h>
#include <wx/frame.h>

class Cloud;

class wxCheckBox;
class wxBitmapButton;
class wxBoxSizer;
class wxFlexGridSizer;
class wxToolBar;


class CloudControl;
class CloudSettingsControl;
class CloudViewGlobalSettingsControl;
class RegionOfInterest2D;
class PointCloudCanvas;


using boost::shared_ptr;

class CloudSelectableStaticText : public wxStaticText
{
public:
    CloudSelectableStaticText(wxWindow* parent, CloudControl* cloudcontrol, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxALIGN_LEFT, const wxString& name = _("staticText")) : wxStaticText(parent,id,label,pos,size, wxBG_STYLE_CUSTOM, name), m_parent(cloudcontrol), m_isSelected(false)
    {
	    //SetBackgroundStyle(wxBG_STYLE_CUSTOM);
        m_unselectedColour.Set( 100 , 50 , 50 );
        m_selectedColour.Set( 255 , 50 , 50 );
        SetForegroundColour( m_unselectedColour );
    };
    /// Destructeur
    virtual ~CloudSelectableStaticText() {};

    /// Accesseur en lecture au flag de selection
    bool IsSelected() const { return m_isSelected; }
    /// Accesseur en ecriture au flag de selection
    void IsSelected(const bool isSelected) { m_isSelected = isSelected; if(m_isSelected) SetForegroundColour( m_selectedColour ); else SetForegroundColour( m_unselectedColour );}

    /// Cette methode permet de "selectionner" un calque. Lors d'un clic sur le nom du calque, la couleur de fond change
    void OnClick(wxMouseEvent& event);

private:
    /// La couleur lorsque le texte n'a pas ete selectionne (220,220,220)
    wxColour m_unselectedColour;
    /// La couleur lorsque le texte a pas ete selectionne (120,120,220)
    wxColour m_selectedColour;
    /// Le LayerControl auquel appartient le texte
    CloudControl* m_parent;
    /// Flage indiquant si le texte est selectionne
    bool m_isSelected;

    DECLARE_EVENT_TABLE();
};

#include <boost/function.hpp>

class CloudControlRow
{
public:
	CloudControlRow( CloudControl* parent , const std::string &name , const unsigned int index , CloudSettingsControl *cloudSettings  , const std::string &tooltip="");
	~CloudControlRow(){}

	CloudSelectableStaticText	*m_nameStaticText;
	wxCheckBox				*m_visibilityCheckBox;
//	wxCheckBox				*m_transformationCheckBox;
	wxBitmapButton			*m_infoButton;
	wxBitmapButton			*m_deleteButton;
	wxBitmapButton			*m_settingsButton;
	wxBoxSizer				*m_boxSizer;
	CloudControl			*m_parent;
	CloudSettingsControl	*m_cloudSettingsControl;
	unsigned int			m_index;
};


class CloudControl: public wxFrame
{
	friend class CloudControlRow;

public:
    CloudControl(wxWindow *parent, PointCloudCanvas* ptCloudCanvas, boost::function<void()> notifyRefresh); //, boost::function<void(double, double, double)> setTranslation);

	/// Cette methode permet d'ajouter un calque
	void AddCloud(const shared_ptr<Cloud> &cloud);

	inline unsigned int GetNumberOfClouds() { return m_numberOfClouds; }

	void updateGUIfromClouds();

	///Callback pour updater la visu des nuages après un crop
	void updateFromCrop(const RegionOfInterest2D& region);

	// Iterateurs pour acceder aux clouds
	typedef std::vector <shared_ptr<Cloud> > CloudContainerType;
	typedef CloudContainerType::iterator iterator;
	typedef CloudContainerType::const_iterator const_iterator;
	typedef CloudContainerType::reverse_iterator reverse_iterator;
	typedef CloudContainerType::const_reverse_iterator const_reverse_iterator;

	iterator begin(){ return m_clouds.begin();}
	iterator end(){ return m_clouds.end();}
	const_iterator begin() const { return m_clouds.begin();}
	const_iterator end() const { return m_clouds.end();}
	reverse_iterator rbegin(){ return m_clouds.rbegin();}
	reverse_iterator rend(){ return m_clouds.rend();}
	const_reverse_iterator rbegin() const { return m_clouds.rbegin();}
	const_reverse_iterator rend() const { return m_clouds.rend();}


	CloudContainerType& getClouds(){ return m_clouds; }

	void refreshScene() { m_notifyRefresh(); }

	bool drawAxes() const;
	bool drawBBox() const;
	wxColour backgroundColor() const;

	void updateFromGlobalViewSettingsControl() const;


//	inline PanelViewer* GetPanelViewer() {return m_glPanel;}

//	std::vector< boost::shared_ptr<CloudControlRow> > GetRows() const { return m_rows; }

	/// Cette methode permet de swapper 2 lignes
	void SwapRows(const unsigned int firstRow , const unsigned int secondRow);

private:
	 void OnCloseWindow(wxCloseEvent& event);
	/// Cette methode permet d'afficher les informations sur le calque
	void OnInfoButton(wxCommandEvent& event);
	/// Cette methode permet de sauvegarder le calque
	void OnDeleteButton(wxCommandEvent& event);
	/// Cette methode permet d'acceder aux parametres d'affichage du calque
	void OnSettingsButton(wxCommandEvent& event);
	void OnCheckVisibility(wxCommandEvent& event);
	/// Cette methode permet de remettre l'ensemble des calques a leur position initiale, de reinitialiser les transformations, de tout rendre visible et transformable
	void OnReset(wxCommandEvent& event);
	/// Cette methode permet de deplacer (vers le haut) les calques selectionnes
	void OnLayerUp(wxCommandEvent& event);
	/// Cette methode permet de deplacer (vers le bas) les calques selectionnes
	void OnLayerDown(wxCommandEvent& event);
	/// Cette methode permet d'inverser la visibilite des calques selectionnes
	void OnVisibilityButton(wxCommandEvent& event);
	/// Cette methode permet de sauvegarder dans un fichier XML les layers affiches ainsi que la configuration d'affichage courante
	void OnSaveDisplayConfigButton(wxCommandEvent& event);
	/// Cette methode permet de lire a partir d'un fichier XML les layers affiches ainsi que la configuration d'affichage courante
	void OnLoadDisplayConfigButton(wxCommandEvent& event);

	void OnGlobalSettingsButton(wxCommandEvent& event);

	/// Cette methode permet de construire la barre d'outils
	bool InitToolbar(wxToolBar* toolBar);

	/// Cette methode permet d'ajouter une ligne dans le LayerControl (elle est appelee lors de l'ajout d'un calque)
	void AddRow(const std::string &name , CloudSettingsControl *layersettings , const std::string &tooltip = "" );

	// Keyboard events
	void OnChar(wxKeyEvent& event);

	///Pour maintenir le centrage des nuages
	void initScene();
	void centreScene();

protected:
	PointCloudCanvas* m_pointCloudCanvas;

	wxFlexGridSizer		*m_sizer;
	unsigned int		m_numberOfClouds;
	CloudContainerType	m_clouds;
	std::vector< boost::shared_ptr<CloudControlRow> > m_rows;

	boost::function<void()> m_notifyRefresh;

	CloudViewGlobalSettingsControl *m_cloudViewGlobalSettingsControl;


//	boost::function<void(double, double, double)> m_notifySetTranslation;


	///Centre et max de la scène 3D
	float m_xG, m_yG, m_zG;
	float m_maxX, m_minX, m_maxY, m_minY, m_maxZ, m_minZ;
	float m_maxi;


	DECLARE_EVENT_TABLE();
};

#endif // __CLOUD_CONTROL_HPP__
