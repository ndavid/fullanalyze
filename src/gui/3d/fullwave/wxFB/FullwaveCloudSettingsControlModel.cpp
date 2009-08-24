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
