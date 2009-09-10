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
// C++ code generated with wxFormBuilder (version Aug  7 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CloudViewGlobalSettingsControlModel__
#define __CloudViewGlobalSettingsControlModel__

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/clrpicker.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class CloudViewGlobalSettingsControlModel
///////////////////////////////////////////////////////////////////////////////
class CloudViewGlobalSettingsControlModel : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_CheckBoxDisplayAxes = 10000,
			ID_CheckBoxDisplayBBox,
			ID_ColourPickerBackgroundColor,
			ID_SpinCtrlFar,
			ID_textCtrlZoom,
			ID_textCtrlTranslation,
			ID_textCtrlRotation,
		};
		
		wxCheckBox* m_checkBoxDisplayAxes;
		wxCheckBox* m_checkBoxDisplayBBox;
		wxStaticText* m_staticText5;
		wxColourPickerCtrl* m_colourPickerBackgroundColor;
		wxStaticText* m_staticText3;
		wxSpinCtrl* m_spinCtrlFar;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrlZoom;
		wxStaticText* m_staticText41;
		wxTextCtrl* m_textCtrlTranslation;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textCtrlRotation;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Apply;
	
	public:
		
		CloudViewGlobalSettingsControlModel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("3D global settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 335,388 ), long style = wxDEFAULT_DIALOG_STYLE );
		~CloudViewGlobalSettingsControlModel();
	
};

#endif //__CloudViewGlobalSettingsControlModel__
