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
// C++ code generated with wxFormBuilder (version Dec 29 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "FullwaveCloudSettingsControlModel.h"

///////////////////////////////////////////////////////////////////////////

FullwaveCloudSettingsControlModel::FullwaveCloudSettingsControlModel( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 487,415 ), wxDefaultSize );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 5, 5 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("General settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableRow( 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Sub sampling"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer4->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_spinCtrlSSEch = new wxSpinCtrl( this, ID_SpinCtrlSSEch, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10000, 0 );
	fgSizer4->Add( m_spinCtrlSSEch, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	fgSizer1->Add( sbSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Cloud color") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 5, 5 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_radioBtnColorSingle = new wxRadioButton( this, ID_RadioBtnColorSingle, _("Single"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtnColorSingle->SetValue( true ); 
	fgSizer2->Add( m_radioBtnColorSingle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourPickerColorSingle = new wxColourPickerCtrl( this, ID_ColourPickerColorSingle, wxColour( 40, 144, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_USE_TEXTCTRL );
	fgSizer2->Add( m_colourPickerColorSingle, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer2->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	fgSizer1->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Shapes") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 2, 2, 5, 5 );
	fgSizer21->AddGrowableCol( 1 );
	fgSizer21->AddGrowableRow( 2 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_radioBtnShapesSegments = new wxRadioButton( this, ID_RadioBtnShapesSegments, _("Segments"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_radioBtnShapesSegments->SetValue( true ); 
	fgSizer21->Add( m_radioBtnShapesSegments, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer21->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_radioBtnShapesSpheres = new wxRadioButton( this, ID_RadioBtnShapesSpheres, _("Spheres"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_radioBtnShapesSpheres, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Sphere settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer31;
	fgSizer31 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer31->AddGrowableCol( 1 );
	fgSizer31->SetFlexibleDirection( wxBOTH );
	fgSizer31->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, _("Level of details"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer31->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderSpheresLevelOfDetails = new wxSlider( this, ID_SliderSpheresLevelOfDetails, 10, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer12->Add( m_sliderSpheresLevelOfDetails, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSpheresLevelOfDetails = new wxTextCtrl( this, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_textCtrlSpheresLevelOfDetails, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer31->Add( bSizer12, 1, wxEXPAND, 5 );
	
	m_staticText31 = new wxStaticText( this, wxID_ANY, _("Ratio amplitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer31->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderSpheresRatioAmplitude = new wxSlider( this, ID_SliderSphereRatioAmplitude, 15, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer111->Add( m_sliderSpheresRatioAmplitude, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlSpheresRatioAmplitude = new wxTextCtrl( this, wxID_ANY, _("0.015"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer111->Add( m_textCtrlSpheresRatioAmplitude, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer31->Add( bSizer111, 1, wxEXPAND, 5 );
	
	sbSizer31->Add( fgSizer31, 1, wxEXPAND, 5 );
	
	fgSizer21->Add( sbSizer31, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_radioBtnShapesNormals = new wxRadioButton( this, ID_RadioBtnShapesNormals, _("Normals"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_radioBtnShapesNormals, 0, wxALL, 5 );
	
	sbSizer4->Add( fgSizer21, 1, wxEXPAND, 5 );
	
	fgSizer1->Add( sbSizer4, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Apply = new wxButton( this, wxID_APPLY );
	m_sdbSizer2->AddButton( m_sdbSizer2Apply );
	m_sdbSizer2->Realize();
	fgSizer1->Add( m_sdbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
}

FullwaveCloudSettingsControlModel::~FullwaveCloudSettingsControlModel()
{
}
