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

#include <boost/filesystem.hpp>
//#include <boost/shared_ptr.hpp>

#include <wx/dcbuffer.h>
#include <wx/minifram.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/log.h>
#include <wx/statusbr.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/filepicker.h>
#include <wx/valtext.h>
#include <wx/colour.h>
#include <wx/msgdlg.h>

//#include "3d/GLPanel.h"
#include "gui/3d/CloudControl.h"
#include "gui/3d/define_id_FA3D.h"

#include "3d/fullwave/FullwaveCloud.h"


#include "FullwaveCloudSettingsControl.h"

FullwaveCloudSettingsControl::FullwaveCloudSettingsControl(unsigned int index, CloudControl* parent, wxWindowID id, const wxString& title, long style, const wxPoint& pos, const wxSize& size) :
	CloudSettingsControl(parent),
	FullwaveCloudSettingsControlModel(parent),
	m_parent(parent),
	m_fwCld(static_cast<FullwaveCloud&>(*m_parent->getClouds()[index]))
{
	m_index = index;

//	//construction de la liste des attributs
//	std::vector<std::string> listeAttributs;
//	m_ptCld.getAttributeList(listeAttributs);
//	for(std::vector<std::string>::iterator it=listeAttributs.begin(); it!=listeAttributs.end(); ++it)
//	{
//		m_choiceColorAttributeName->Append(wxString(it->c_str(), *wxConvCurrent));
//		m_choiceRGB->Append(wxString(it->c_str(), *wxConvCurrent));
//	}
//	m_choiceColorAttributeName->Select(0);
//	m_choiceRGB->Select(0);
//
//
	//initialisation des données du pointcloud à partir de celles de l'interface
	applySSampling();
	applyColorSingle();

//	initColorAttribute();
//	generateTextureAttribute();

	m_fwCld.colorMode(FullwaveCloud::SINGLE_COLOR);
	m_fwCld.viewMode(FullwaveCloud::SEGMENTS);

}


BEGIN_EVENT_TABLE(FullwaveCloudSettingsControl, wxDialog)
EVT_CLOSE(FullwaveCloudSettingsControl::OnCloseWindow)
EVT_BUTTON(wxID_OK, FullwaveCloudSettingsControl::OnOKButton)

EVT_SPINCTRL(ID_SpinCtrlSSEch, FullwaveCloudSettingsControl::OnSSampling)
//EVT_BUTTON(wxID_CANCEL,FullwaveCloudSettingsControl::OnCancelButton)
EVT_BUTTON(wxID_APPLY, FullwaveCloudSettingsControl::OnApplyButton)

EVT_COLOURPICKER_CHANGED(ID_ColourPickerColorSingle, FullwaveCloudSettingsControl::OnSingleColorColourPickerChanged)

EVT_RADIOBUTTON(ID_RadioBtnColorSingle, FullwaveCloudSettingsControl::OnRadioBtnColorSingle)
//EVT_RADIOBUTTON(ID_RadioBtnColorAttribute, FullwaveCloudSettingsControl::OnRadioBtnColorAttribute)

EVT_RADIOBUTTON(ID_RadioBtnShapesSegments, FullwaveCloudSettingsControl::OnRadioBtnShapesSegments)
EVT_RADIOBUTTON(ID_RadioBtnShapesSpheres, FullwaveCloudSettingsControl::OnRadioBtnShapesSpheres)
EVT_RADIOBUTTON(ID_RadioBtnShapesNormals, FullwaveCloudSettingsControl::OnRadioBtnShapesNormals)

EVT_SLIDER(ID_SliderSphereRatioAmplitude, FullwaveCloudSettingsControl::OnSliderSpheresRatioAmplitude)
EVT_SLIDER(ID_SliderSpheresLevelOfDetails, FullwaveCloudSettingsControl::OnSliderSpheresLevelOfDetails)

//EVT_CHOICE(ID_ChoiceColorAttributeName, FullwaveCloudSettingsControl::OnChoiceColorAttributeName)
//EVT_CHOICE(ID_ChoiceRGB, FullwaveCloudSettingsControl::OnChoiceColorRedName)
//
//EVT_SLIDER(ID_SliderAttributeMinValue, FullwaveCloudSettingsControl::OnSliderAttributeMinValue)
//EVT_SLIDER(ID_SliderAttributeMaxValue, FullwaveCloudSettingsControl::OnSliderAttributeMaxValue)
//
//
//EVT_FILEPICKER_CHANGED(ID_FilePickerAttributeLut, FullwaveCloudSettingsControl::OnFileChangeAttributeLut)

//EVT_SET_FOCUS(PointCloudSettingsControl::OnGetFocus)
END_EVENT_TABLE()


void FullwaveCloudSettingsControl::show(const bool toBeShown)
{
	Show(toBeShown);
}

void FullwaveCloudSettingsControl::destroy()
{
	Destroy();
}

bool FullwaveCloudSettingsControl::isVisible() const
{
	return IsVisible();
}

void FullwaveCloudSettingsControl::OnApplyButton(wxCommandEvent &event)
{
	apply();
}

void FullwaveCloudSettingsControl::OnSSampling(wxSpinEvent& event)
{
	applySSampling();
	refreshScene();
}

void FullwaveCloudSettingsControl::OnOKButton(wxCommandEvent &event)
{
	// On ne fait que cacher ...
	apply();
	Hide();
}

void FullwaveCloudSettingsControl::OnCloseWindow(wxCloseEvent& event)
{
	Hide();
}


void FullwaveCloudSettingsControl::OnRadioBtnColorSingle(wxCommandEvent& event)
{
	m_fwCld.colorMode(FullwaveCloud::SINGLE_COLOR);
	applyColorSingle();
	refreshScene();
}


void FullwaveCloudSettingsControl::OnRadioBtnShapesSegments(wxCommandEvent& event)
{
	m_fwCld.viewMode(FullwaveCloud::SEGMENTS);
	refreshScene();
}

void FullwaveCloudSettingsControl::OnRadioBtnShapesSpheres(wxCommandEvent& event)
{
	m_fwCld.viewMode(FullwaveCloud::SPHERES);
	applyShapesSpheres();
	refreshScene();
}

void FullwaveCloudSettingsControl::OnRadioBtnShapesNormals(wxCommandEvent& event)
{
	m_fwCld.viewMode(FullwaveCloud::NORMALS);
	refreshScene();
}


void FullwaveCloudSettingsControl::OnSingleColorColourPickerChanged(wxColourPickerEvent& event)
{
	applyColorSingle();
	refreshScene();
}


void FullwaveCloudSettingsControl::OnSliderSpheresRatioAmplitude(wxCommandEvent& event)
{
	const double MIN_RATIO_AMPLITUDE = 0.001;
	const double STEP_RATIO_AMPLITUDE = 0.001;


	double x = MIN_RATIO_AMPLITUDE + m_sliderSpheresRatioAmplitude->GetValue() * STEP_RATIO_AMPLITUDE;
	wxString xs;
	xs<<x;
	m_textCtrlSpheresRatioAmplitude->SetValue(xs);
	applyShapesSpheres();
	refreshScene();
}

void FullwaveCloudSettingsControl::OnSliderSpheresLevelOfDetails(wxCommandEvent& event)
{
	double x = m_sliderSpheresLevelOfDetails->GetValue();
	wxString xs;
	xs<<x;
	m_textCtrlSpheresLevelOfDetails->SetValue(xs);
	applyShapesSpheres();
	refreshScene();
}



void FullwaveCloudSettingsControl::refreshScene()
{
	m_parent->refreshScene();
}

void FullwaveCloudSettingsControl::apply()
{
	applySSampling();

	if(m_radioBtnColorSingle->GetValue())
		applyColorSingle();
//	else if(m_radioBtnColorAttribute->GetValue())
//		applyColorAttribute();


	if(m_radioBtnShapesSpheres->GetValue())
		applyShapesSpheres();


	refreshScene();
}


void FullwaveCloudSettingsControl::applySSampling()
{
	m_fwCld.ssEchantillonnage(m_spinCtrlSSEch->GetValue());
}

void FullwaveCloudSettingsControl::applyColorSingle()
{
	wxColour color=m_colourPickerColorSingle->GetColour();
	m_fwCld.singleColor(TPoint3D<float>(color.Red()/255., color.Green()/255., color.Blue()/255.));
}


void FullwaveCloudSettingsControl::applyShapesSpheres()
{
	//calcul de la matrice de texture
	double ratio;
	double details;
	wxString ratioLabel = m_textCtrlSpheresRatioAmplitude->GetValue();
	wxString detailsLabel = m_textCtrlSpheresLevelOfDetails->GetValue();
	if ( !ratioLabel.ToDouble(&ratio) )
	{
		::wxMessageBox(_("Bad ratio value !"));
		return;
	}
	if ( !detailsLabel.ToDouble(&details) )
	{
		::wxMessageBox(_("Bad details value !"));
		return;
	}

	m_fwCld.ratioAmplitude(ratio);
	m_fwCld.sphereDetails(static_cast<unsigned char>(details));
}
