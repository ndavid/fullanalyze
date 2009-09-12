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
// C++ code generated with wxFormBuilder (version Aug  7 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CloudViewGlobalSettingsControlModel.h"

///////////////////////////////////////////////////////////////////////////

CloudViewGlobalSettingsControlModel::CloudViewGlobalSettingsControlModel( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Background settings") ), wxVERTICAL );
	
	m_checkBoxDisplayAxes = new wxCheckBox( this, ID_CheckBoxDisplayAxes, wxT("Display axes"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_checkBoxDisplayAxes, 0, wxALL|wxEXPAND, 5 );
	
	m_checkBoxDisplayBBox = new wxCheckBox( this, ID_CheckBoxDisplayBBox, wxT("Display bounding box"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_checkBoxDisplayBBox, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Background color :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer4->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourPickerBackgroundColor = new wxColourPickerCtrl( this, ID_ColourPickerBackgroundColor, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_USE_TEXTCTRL );
	bSizer4->Add( m_colourPickerBackgroundColor, 1, wxALL|wxEXPAND, 5 );
	
	sbSizer4->Add( bSizer4, 0, wxEXPAND, 5 );
	
	bSizer3->Add( sbSizer4, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("3D settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Far :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer2->Add( m_staticText3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrlFar = new wxSpinCtrl( this, ID_SpinCtrlFar, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 10 );
	fgSizer2->Add( m_spinCtrlFar, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Zoom :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer2->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlZoom = new wxTextCtrl( this, ID_textCtrlZoom, wxT("1."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlZoom, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Translation :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	fgSizer2->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlTranslation = new wxTextCtrl( this, ID_textCtrlTranslation, wxT("1."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlTranslation, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Rotation :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer2->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlRotation = new wxTextCtrl( this, ID_textCtrlRotation, wxT("45."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrlRotation, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	sbSizer2->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	bSizer3->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Apply = new wxButton( this, wxID_APPLY );
	m_sdbSizer2->AddButton( m_sdbSizer2Apply );
	m_sdbSizer2->Realize();
	bSizer3->Add( m_sdbSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
}

CloudViewGlobalSettingsControlModel::~CloudViewGlobalSettingsControlModel()
{
}
