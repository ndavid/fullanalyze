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
// C++ code generated with wxFormBuilder (version Oct 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PointCloudSettingsControlModel.h"

///////////////////////////////////////////////////////////////////////////

PointCloudSettingsControlModel::PointCloudSettingsControlModel( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 487,493 ), wxDefaultSize );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 5, 5 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Geometry") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableRow( 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Point size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer4->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_spinCtrlPointSize = new wxSpinCtrl( this, ID_SpinCtrlPointSize, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 20, 1 );
	fgSizer4->Add( m_spinCtrlPointSize, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Sub sampling"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer4->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_spinCtrlSSEch = new wxSpinCtrl( this, ID_SpinCtrlSSEch, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100, 0 );
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
	fgSizer2->Add( m_radioBtnColorSingle, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourPickerColorSingle = new wxColourPickerCtrl( this, ID_ColourPickerColorSingle, wxColour( 40, 144, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_USE_TEXTCTRL );
	fgSizer2->Add( m_colourPickerColorSingle, 0, wxALL|wxEXPAND, 5 );
	
	m_radioBtnColorAttribute = new wxRadioButton( this, ID_RadioBtnColorAttribute, _("Attribute"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_radioBtnColorAttribute, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Attribute color settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Attribute name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer3->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choiceColorAttributeNameChoices;
	m_choiceColorAttributeName = new wxChoice( this, ID_ChoiceColorAttributeName, wxDefaultPosition, wxDefaultSize, m_choiceColorAttributeNameChoices, 0 );
	m_choiceColorAttributeName->SetSelection( 0 );
	fgSizer3->Add( m_choiceColorAttributeName, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Min value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderAttributeMinValue = new wxSlider( this, ID_SliderAttributeMinValue, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer1->Add( m_sliderAttributeMinValue, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAttributeMinValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_textCtrlAttributeMinValue, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer3->Add( bSizer1, 1, wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Max value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_sliderAttributeMaxValue = new wxSlider( this, ID_SliderAttributeMaxValue, 100, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer11->Add( m_sliderAttributeMaxValue, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textCtrlAttributeMaxValue = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer11->Add( m_textCtrlAttributeMaxValue, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fgSizer3->Add( bSizer11, 1, wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("LUT"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_filePickerAttributeLut = new wxFilePickerCtrl( this, ID_FilePickerAttributeLut, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer3->Add( m_filePickerAttributeLut, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer3->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	fgSizer2->Add( sbSizer3, 1, wxEXPAND|wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_radioBtnColorRGB = new wxRadioButton( this, ID_RadioBtnColorRGB, _("RGB"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_radioBtnColorRGB, 0, wxALL, 5 );
	
	wxArrayString m_choiceRGBChoices;
	m_choiceRGB = new wxChoice( this, ID_ChoiceRGB, wxDefaultPosition, wxDefaultSize, m_choiceRGBChoices, 0 );
	m_choiceRGB->SetSelection( 0 );
	fgSizer2->Add( m_choiceRGB, 0, wxALL|wxEXPAND, 5 );
	
	m_radioBtnColorTexture = new wxRadioButton( this, ID_RadioBtnColorTexture, _("Texture"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_radioBtnColorTexture, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_filePicker2 = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, _("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	fgSizer2->Add( m_filePicker2, 0, wxALL|wxEXPAND, 5 );
	
	m_radioBtnColorClassification = new wxRadioButton( this, ID_RadioBtnColorClassification, _("Classification"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_radioBtnColorClassification, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	fgSizer1->Add( sbSizer2, 1, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Apply = new wxButton( this, wxID_APPLY );
	m_sdbSizer2->AddButton( m_sdbSizer2Apply );
	m_sdbSizer2->Realize();
	fgSizer1->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
}

PointCloudSettingsControlModel::~PointCloudSettingsControlModel()
{
}
