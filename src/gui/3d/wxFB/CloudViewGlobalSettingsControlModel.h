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
