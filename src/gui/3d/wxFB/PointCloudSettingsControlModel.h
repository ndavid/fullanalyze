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

///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PointCloudSettingsControlModel__
#define __PointCloudSettingsControlModel__

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
#include <wx/choice.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PointCloudSettingsControlModel
///////////////////////////////////////////////////////////////////////////////
class PointCloudSettingsControlModel : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_SpinCtrlPointSize = 1000,
			ID_SpinCtrlSSEch,
			ID_RadioBtnColorSingle,
			ID_ColourPickerColorSingle,
			ID_RadioBtnColorAttribute,
			ID_ChoiceColorAttributeName,
			ID_SliderAttributeMinValue,
			ID_SliderAttributeMaxValue,
			ID_FilePickerAttributeLut,
			ID_RadioBtnColorRGB,
			ID_ChoiceRGB,
			ID_RadioBtnColorTexture,
			ID_RadioBtnColorClassification,
		};
		
		wxStaticText* m_staticText5;
		wxSpinCtrl* m_spinCtrlPointSize;
		wxStaticText* m_staticText6;
		wxSpinCtrl* m_spinCtrlSSEch;
		wxRadioButton* m_radioBtnColorSingle;
		wxColourPickerCtrl* m_colourPickerColorSingle;
		wxRadioButton* m_radioBtnColorAttribute;
		wxStaticText* m_staticText1;
		wxChoice* m_choiceColorAttributeName;
		wxStaticText* m_staticText2;
		wxSlider* m_sliderAttributeMinValue;
		wxTextCtrl* m_textCtrlAttributeMinValue;
		wxStaticText* m_staticText3;
		wxSlider* m_sliderAttributeMaxValue;
		wxTextCtrl* m_textCtrlAttributeMaxValue;
		wxStaticText* m_staticText4;
		wxFilePickerCtrl* m_filePickerAttributeLut;
		wxRadioButton* m_radioBtnColorRGB;
		wxChoice* m_choiceRGB;
		wxRadioButton* m_radioBtnColorTexture;
		wxFilePickerCtrl* m_filePicker2;
		wxRadioButton* m_radioBtnColorClassification;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Apply;
	
	public:
		
		PointCloudSettingsControlModel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Point cloud settings control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 487,520 ), long style = wxDEFAULT_DIALOG_STYLE );
		~PointCloudSettingsControlModel();
	
};

#endif //__PointCloudSettingsControlModel__
