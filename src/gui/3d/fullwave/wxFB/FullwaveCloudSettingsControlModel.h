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
