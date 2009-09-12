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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 29 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FullwaveCloudSettingsControlModel__
#define __FullwaveCloudSettingsControlModel__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/radiobut.h>
#include <wx/clrpicker.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class FullwaveCloudSettingsControlModel
///////////////////////////////////////////////////////////////////////////////
class FullwaveCloudSettingsControlModel : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_SpinCtrlSSEch = 1000,
			ID_RadioBtnColorSingle,
			ID_ColourPickerColorSingle,
			ID_RadioBtnShapesSegments,
			ID_RadioBtnShapesSpheres,
			ID_SliderSpheresLevelOfDetails,
			ID_SliderSphereRatioAmplitude,
			ID_RadioBtnShapesNormals,
		};
		
		wxStaticText* m_staticText6;
		wxSpinCtrl* m_spinCtrlSSEch;
		wxRadioButton* m_radioBtnColorSingle;
		wxColourPickerCtrl* m_colourPickerColorSingle;
		wxRadioButton* m_radioBtnShapesSegments;
		
		wxRadioButton* m_radioBtnShapesSpheres;
		wxStaticText* m_staticText21;
		wxSlider* m_sliderSpheresLevelOfDetails;
		wxTextCtrl* m_textCtrlSpheresLevelOfDetails;
		wxStaticText* m_staticText31;
		wxSlider* m_sliderSpheresRatioAmplitude;
		wxTextCtrl* m_textCtrlSpheresRatioAmplitude;
		wxRadioButton* m_radioBtnShapesNormals;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Apply;
	
	public:
		FullwaveCloudSettingsControlModel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Fullwave cloud settings control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 487,415 ), long style = wxDEFAULT_DIALOG_STYLE );
		~FullwaveCloudSettingsControlModel();
	
};

#endif //__FullwaveCloudSettingsControlModel__
