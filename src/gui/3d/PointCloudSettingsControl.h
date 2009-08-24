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

class PointCloudSettingsControl : public CloudSettingsControl, public PointCloudSettingsControlModel
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
