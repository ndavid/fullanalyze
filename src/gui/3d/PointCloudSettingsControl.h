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

#ifndef __POINT_CLOUD_SETTINGS_CONTROL_HPP__
#define __POINT_CLOUD_SETTINGS_CONTROL_HPP__

#include <vector>
//#include <wx/filepicker.h>
#include <wx/panel.h>

#include "CloudSettingsControl.h"
#include "wxFB/PointCloudSettingsControlModel.h"

class CloudControl;
class PointCloud;
class wxSlider;
class wxTextCtrl;
class wxCheckBox;
class wxFilePickerCtrl;

class PointCloudSettingsControl : public PointCloudSettingsControlModel, public CloudSettingsControl
{
public:
	PointCloudSettingsControl(unsigned int index, CloudControl *parent, wxWindowID id = wxID_ANY, const wxString& title = _("Point cloud settings"),
		long style = wxDEFAULT_FRAME_STYLE , const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );


//	void OnGetFocus(wxFocusEvent &event);

	virtual void show(const bool toBeShown);
	virtual void destroy();
	virtual bool isVisible() const;


private:
	void OnOKButton(wxCommandEvent &event);
//	void OnCancelButton(wxCommandEvent &event);
	void OnApplyButton(wxCommandEvent &event);
	void OnCloseWindow(wxCloseEvent& event);
	void OnSingleColorColourPickerChanged(wxColourPickerEvent& event);
	void OnPointSize(wxSpinEvent& event);
	void OnSSampling(wxSpinEvent& event);

	void OnRadioBtnColorSingle(wxCommandEvent& event);
	void OnRadioBtnColorAttribute(wxCommandEvent& event);
	void OnRadioBtnColorRGB(wxCommandEvent& event);

	void OnChoiceColorAttributeName(wxCommandEvent& event);
	void OnChoiceColorRedName(wxCommandEvent& event);

	void OnSliderAttributeMinValue(wxCommandEvent& event);
	void OnSliderAttributeMaxValue(wxCommandEvent& event);

	void OnFileChangeAttributeLut(wxFileDirPickerEvent& event);

	void apply();
	void applyPointSize();
	void applySSampling();
	void applyColorSingle();
	void applyColorAttribute();
	void applyColorRGB();

	void initColorAttribute();
	void generateTextureAttribute();
	void computeTextureMatrixAttribute();

	void refreshScene();


	DECLARE_EVENT_TABLE();

	CloudControl *m_parent;
	PointCloud& m_ptCld;


	//pour l'affichage selon un attribut :
	double m_attributeCurrentMinValue, m_attributeCurrentMaxValue;

};

#endif // __POINT_CLOUD_SETTINGS_CONTROL_HPP__
