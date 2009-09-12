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

#include <wx/config.h>
#include <wx/msgdlg.h>

#include "CloudViewGlobalSettingsControl.h"


BEGIN_EVENT_TABLE(CloudViewGlobalSettingsControl, wxDialog)
EVT_CLOSE(CloudViewGlobalSettingsControl::OnCloseWindow)
EVT_BUTTON(wxID_OK, CloudViewGlobalSettingsControl::OnOKButton)
EVT_BUTTON(wxID_APPLY, CloudViewGlobalSettingsControl::OnApplyButton)

EVT_CHECKBOX(ID_CheckBoxDisplayAxes, CloudViewGlobalSettingsControl::OnDisplayAxes)
EVT_CHECKBOX(ID_CheckBoxDisplayBBox, CloudViewGlobalSettingsControl::OnDisplayBBox)
EVT_COLOURPICKER_CHANGED(ID_ColourPickerBackgroundColor, CloudViewGlobalSettingsControl::OnBackgroundColor)
END_EVENT_TABLE()

CloudViewGlobalSettingsControl::CloudViewGlobalSettingsControl(wxWindow* parent, boost::function<void()> notifyRefresh):
	CloudViewGlobalSettingsControlModel(parent),
	m_notifyRefresh(notifyRefresh)
{

	//Chargement à partir du fichier de configuration
	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->Read(_T("/FA/3D/DrawAxes"), &m_drawAxes, false);
	pConfig->Read(_T("/FA/3D/DrawBBox"), &m_drawBBox, false);

	int red, green, blue;
	pConfig->Read(_T("/FA/3D/BackgroundColorRed"), &red, 255);
	pConfig->Read(_T("/FA/3D/BackgroundColorGreen"), &green, 255);
	pConfig->Read(_T("/FA/3D/BackgroundColorBlue"), &blue, 255);
	m_backgroundColor.Set(red, green, blue);

	pConfig->Read(_T("/FA/3D/Far"), &m_far, 10);
	pConfig->Read(_T("/FA/3D/Zoom"), &m_zoom, 1.);
	pConfig->Read(_T("/FA/3D/Translation"), &m_translation, 1.);
	pConfig->Read(_T("/FA/3D/Rotation"), &m_rotation, 45.);


	m_checkBoxDisplayAxes->SetValue(m_drawAxes);
	m_checkBoxDisplayBBox->SetValue(m_drawBBox);
	m_colourPickerBackgroundColor->SetColour(m_backgroundColor);
	m_spinCtrlFar->SetValue(m_far);

	wxString temp;
	temp<<m_zoom;
	m_textCtrlZoom->SetValue(temp);
	temp.Clear(); temp << m_translation;
	m_textCtrlTranslation->SetValue(temp);
	temp.Clear(); temp << m_rotation;
	m_textCtrlRotation->SetValue(temp);
}

CloudViewGlobalSettingsControl::~CloudViewGlobalSettingsControl()
{
	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->Write(_T("/FA/3D/DrawAxes"), m_drawAxes);
	pConfig->Write(_T("/FA/3D/DrawBBox"), m_drawBBox);
	pConfig->Write(_T("/FA/3D/BackgroundColorRed"), m_backgroundColor.Red());
	pConfig->Write(_T("/FA/3D/BackgroundColorGreen"), m_backgroundColor.Green());
	pConfig->Write(_T("/FA/3D/BackgroundColorBlue"), m_backgroundColor.Blue());
	pConfig->Write(_T("/FA/3D/Far"), m_far);
	pConfig->Write(_T("/FA/3D/Zoom"), m_zoom);
	pConfig->Write(_T("/FA/3D/Translation"), m_translation);
	pConfig->Write(_T("/FA/3D/Rotation"), m_rotation);
}

void CloudViewGlobalSettingsControl::OnOKButton(wxCommandEvent &event)
{
	// On ne fait que cacher ...
	Hide();
}

void CloudViewGlobalSettingsControl::apply()
{
	m_far = m_spinCtrlFar->GetValue();

	double zoom, tr, rot;
	wxString zoomLabel = m_textCtrlZoom->GetValue();
	wxString trLabel = m_textCtrlTranslation->GetValue();
	wxString rotLabel = m_textCtrlRotation->GetValue();

	if ( !zoomLabel.ToDouble(&zoom) )
	{
		::wxMessageBox(_("Bad zoom value !"));
		return;
	}
	if ( !trLabel.ToDouble(&tr) )
	{
		::wxMessageBox(_("Bad translation value !"));
		return;
	}
	if ( !rotLabel.ToDouble(&rot) )
	{
		::wxMessageBox(_("Bad rotation value !"));
		return;
	}

	m_zoom = zoom;
	m_translation = tr;
	m_rotation = rot;

	refresh();
}

void CloudViewGlobalSettingsControl::OnApplyButton(wxCommandEvent &event)
{
	apply();
}

void CloudViewGlobalSettingsControl::OnCloseWindow(wxCloseEvent& event)
{
	Hide();
}

void CloudViewGlobalSettingsControl::OnBackgroundColor(wxColourPickerEvent& event)
{
	m_backgroundColor=m_colourPickerBackgroundColor->GetColour();
	refresh();
}

void CloudViewGlobalSettingsControl::OnDisplayAxes(wxCommandEvent &event)
{
	m_drawAxes=m_checkBoxDisplayAxes->GetValue();
	refresh();
}

void CloudViewGlobalSettingsControl::OnDisplayBBox(wxCommandEvent &event)
{
	m_drawBBox=m_checkBoxDisplayBBox->GetValue();
	refresh();
}
