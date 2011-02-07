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

#ifdef _WINDOWS
#include <windows.h>
#include <wx/msw/winundef.h>
#endif




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
#include "CloudControl.h"
#include "define_id_FA3D.h"

#include "3d/PointCloud.h"


#include "PointCloudSettingsControl.h"


PointCloudSettingsControl::PointCloudSettingsControl(unsigned int index, CloudControl* parent, wxWindowID id, const wxString& title, long style, const wxPoint& pos, const wxSize& size) :
	PointCloudSettingsControlModel(parent),
	CloudSettingsControl(parent),
	m_parent(parent),
	m_ptCld(static_cast<PointCloud&>(*m_parent->getClouds()[index]))
{
	m_index = index;

	//construction de la liste des attributs
	std::vector<std::string> listeAttributs;
	m_ptCld.getAttributeList(listeAttributs);
	for(std::vector<std::string>::iterator it=listeAttributs.begin(); it!=listeAttributs.end(); ++it)
	{
		m_choiceColorAttributeName->Append(wxString(it->c_str(), *wxConvCurrent));
		m_choiceRGB->Append(wxString(it->c_str(), *wxConvCurrent));
	}
	m_choiceColorAttributeName->Select(0);
	m_choiceRGB->Select(0);


	//initialisation des données du pointcloud à partir de celles de l'interface
	applyPointSize();
	applySSampling();
	applyColorSingle();

	initColorAttribute();
	generateTextureAttribute();

	m_ptCld.colorMode(PointCloud::SINGLE_COLOR);

}

BEGIN_EVENT_TABLE(PointCloudSettingsControl, wxDialog)
EVT_CLOSE(PointCloudSettingsControl::OnCloseWindow)
EVT_BUTTON(wxID_OK, PointCloudSettingsControl::OnOKButton)
EVT_SPINCTRL(ID_SpinCtrlPointSize, PointCloudSettingsControl::OnPointSize)
EVT_SPINCTRL(ID_SpinCtrlSSEch, PointCloudSettingsControl::OnSSampling)
//EVT_BUTTON(wxID_CANCEL,PointCloudSettingsControl::OnCancelButton)
EVT_BUTTON(wxID_APPLY, PointCloudSettingsControl::OnApplyButton)
EVT_COLOURPICKER_CHANGED(ID_ColourPickerColorSingle, PointCloudSettingsControl::OnSingleColorColourPickerChanged)

EVT_RADIOBUTTON(ID_RadioBtnColorSingle, PointCloudSettingsControl::OnRadioBtnColorSingle)
EVT_RADIOBUTTON(ID_RadioBtnColorAttribute, PointCloudSettingsControl::OnRadioBtnColorAttribute)
EVT_RADIOBUTTON(ID_RadioBtnColorRGB, PointCloudSettingsControl::OnRadioBtnColorRGB)

EVT_CHOICE(ID_ChoiceColorAttributeName, PointCloudSettingsControl::OnChoiceColorAttributeName)
EVT_CHOICE(ID_ChoiceRGB, PointCloudSettingsControl::OnChoiceColorRedName)

EVT_SLIDER(ID_SliderAttributeMinValue, PointCloudSettingsControl::OnSliderAttributeMinValue)
EVT_SLIDER(ID_SliderAttributeMaxValue, PointCloudSettingsControl::OnSliderAttributeMaxValue)


EVT_FILEPICKER_CHANGED(ID_FilePickerAttributeLut, PointCloudSettingsControl::OnFileChangeAttributeLut)

//EVT_SET_FOCUS(PointCloudSettingsControl::OnGetFocus)
END_EVENT_TABLE()


void PointCloudSettingsControl::show(const bool toBeShown)
{
	Show(toBeShown);
}

void PointCloudSettingsControl::destroy()
{
	Destroy();
}

bool PointCloudSettingsControl::isVisible() const
{
	return IsVisible();
}


void PointCloudSettingsControl::OnApplyButton(wxCommandEvent &event)
{
	apply();
}

void PointCloudSettingsControl::OnSingleColorColourPickerChanged(wxColourPickerEvent& event)
{
	applyColorSingle();
	refreshScene();
}

void PointCloudSettingsControl::OnSSampling(wxSpinEvent& event)
{
	applySSampling();
	refreshScene();
}

void PointCloudSettingsControl::OnPointSize(wxSpinEvent& event)
{
	applyPointSize();
	refreshScene();
}

void PointCloudSettingsControl::OnRadioBtnColorSingle(wxCommandEvent& event)
{
	m_ptCld.colorMode(PointCloud::SINGLE_COLOR);
	applyColorSingle();
	refreshScene();
}

void PointCloudSettingsControl::OnRadioBtnColorAttribute(wxCommandEvent& event)
{
	m_ptCld.colorMode(PointCloud::ATTRIBUTE);
	generateTextureAttribute();
	applyColorAttribute();
	refreshScene();
}

void PointCloudSettingsControl::OnRadioBtnColorRGB(wxCommandEvent& event)
{
	m_ptCld.colorMode(PointCloud::RGB);
	applyColorRGB();
	refreshScene();
}

void PointCloudSettingsControl::OnChoiceColorAttributeName(wxCommandEvent& event)
{
	initColorAttribute();
	applyColorAttribute();
	refreshScene();
}

void PointCloudSettingsControl::OnChoiceColorRedName(wxCommandEvent& event)
{
	applyColorRGB();
	refreshScene();
}



void PointCloudSettingsControl::OnSliderAttributeMinValue(wxCommandEvent& event)
{
	double x=m_attributeCurrentMinValue+(m_attributeCurrentMaxValue-m_attributeCurrentMinValue)*m_sliderAttributeMinValue->GetValue()/m_sliderAttributeMinValue->GetMax();
	wxString xs;
	xs<<x;
	m_textCtrlAttributeMinValue->SetValue(xs);
	applyColorAttribute();
	refreshScene();
}

void PointCloudSettingsControl::OnSliderAttributeMaxValue(wxCommandEvent& event)
{
	double x=m_attributeCurrentMaxValue-(m_attributeCurrentMaxValue-m_attributeCurrentMinValue)*(m_sliderAttributeMaxValue->GetMax()-m_sliderAttributeMaxValue->GetValue())/m_sliderAttributeMaxValue->GetMax();
	wxString xs;
	xs<<x;
	m_textCtrlAttributeMaxValue->SetValue(xs);
	applyColorAttribute();
	refreshScene();
}

void PointCloudSettingsControl::OnFileChangeAttributeLut(wxFileDirPickerEvent& event)
{
	generateTextureAttribute();
	refreshScene();
}

void PointCloudSettingsControl::refreshScene()
{
	m_parent->refreshScene();
}

void PointCloudSettingsControl::apply()
{
	applyPointSize();
	applySSampling();

	if(m_radioBtnColorSingle->GetValue())
		applyColorSingle();
	else if(m_radioBtnColorAttribute->GetValue())
		applyColorAttribute();
	else if(m_radioBtnColorRGB->GetValue())
		applyColorRGB();

	refreshScene();
}

void PointCloudSettingsControl::applyPointSize()
{
	m_ptCld.pointSize(m_spinCtrlPointSize->GetValue());
}

void PointCloudSettingsControl::applySSampling()
{
	m_ptCld.ssEchantillonnage(m_spinCtrlSSEch->GetValue());
}

void PointCloudSettingsControl::applyColorSingle()
{
	wxColour color=m_colourPickerColorSingle->GetColour();
	m_ptCld.singleColor(TPoint3D<float>(color.Red()/255., color.Green()/255., color.Blue()/255.));
}

void PointCloudSettingsControl::generateTextureAttribute()
{
	//generation de la texture
	m_ptCld.generateTexture(std::string((const char*)m_filePickerAttributeLut->GetPath().mb_str()));
}

void PointCloudSettingsControl::computeTextureMatrixAttribute()
{
	//calcul de la matrice de texture
	double mini, maxi;
	wxString minLabel = m_textCtrlAttributeMinValue->GetValue();
	wxString maxLabel = m_textCtrlAttributeMaxValue->GetValue();
	if ( !minLabel.ToDouble(&mini) )
	{
		::wxMessageBox(_("Bad min value !"));
		return;
	}
	if ( !maxLabel.ToDouble(&maxi) )
	{
		::wxMessageBox(_("Bad max value !"));
		return;
	}
	if(mini>=maxi)
	{
		::wxMessageBox(_("Bad min/max values !"));
		return;
	}

	for (int i = 0; i < 16; i++)
		m_ptCld.m_textureMat[i] = 0;
	m_ptCld.m_textureMat[0] = (1./ (maxi - mini));
	m_ptCld.m_textureMat[12] = ((-mini) / (maxi - mini));
	m_ptCld.m_textureMat[15] = 1;
}

void PointCloudSettingsControl::applyColorAttribute()
{
	computeTextureMatrixAttribute();
}

void PointCloudSettingsControl::applyColorRGB()
{
	m_ptCld.setRedAttributeName(std::string((const char*)m_choiceRGB->GetStringSelection().mb_str()));
}

void PointCloudSettingsControl::initColorAttribute()
{
	std::string attributeName((const char*)m_choiceColorAttributeName->GetStringSelection().mb_str());

	//on indique le nom de la texture
	m_ptCld.setTextureAttributeName(attributeName);

	double mini, maxi;
	m_ptCld.minmax(attributeName, mini, maxi);
	m_attributeCurrentMinValue=mini;
	m_attributeCurrentMaxValue=maxi;

	wxString miniString;
	miniString<<mini;
	wxString maxiString;
	maxiString<<maxi;
	m_textCtrlAttributeMinValue->SetValue(miniString);
	m_textCtrlAttributeMaxValue->SetValue(maxiString);
}



void PointCloudSettingsControl::OnOKButton(wxCommandEvent &event)
{
	// On ne fait que cacher ...
	apply();
	Hide();
}

//void PointCloudSettingsControl::OnCancelButton(wxCommandEvent &event)
//{
//	// On sauvegarde les valeurs des paramètres courants
//}


void PointCloudSettingsControl::OnCloseWindow(wxCloseEvent& event)
{
	Hide();
}
