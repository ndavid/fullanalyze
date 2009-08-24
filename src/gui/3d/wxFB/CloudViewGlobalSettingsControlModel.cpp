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
