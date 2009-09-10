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

#include "FilesPanelBuilder.h"

///////////////////////////////////////////////////////////////////////////

FilesPanelBuilder::FilesPanelBuilder( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 3 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Image directory") ), wxVERTICAL );
	
	m_dirPickerImages = new wxDirPickerCtrl( this, ID_DIR_PICKER_IMAGES, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	sbSizer1->Add( m_dirPickerImages, 0, wxALL|wxEXPAND, 10 );
	
	fgSizer1->Add( sbSizer1, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Lidar data directory") ), wxVERTICAL );
	
	m_dirPickerLidar = new wxDirPickerCtrl( this, ID_DIR_PICKER_LIDAR, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	sbSizer3->Add( m_dirPickerLidar, 0, wxALL|wxEXPAND, 10 );
	
	fgSizer1->Add( sbSizer3, 1, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Fullwave directory") ), wxVERTICAL );
	
	m_dirPickerFullwave = new wxDirPickerCtrl( this, ID_DIR_PICKER_FULLWAVE, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	sbSizer11->Add( m_dirPickerFullwave, 0, wxALL|wxEXPAND, 10 );
	
	fgSizer1->Add( sbSizer11, 1, wxALL|wxEXPAND, 5 );
	
	m_treeFiles = new wxTreeCtrl( this, ID_TREE_FILES, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_FULL_ROW_HIGHLIGHT|wxTR_HAS_BUTTONS|wxTR_HIDE_ROOT );
	fgSizer1->Add( m_treeFiles, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( fgSizer1 );
	this->Layout();
}

FilesPanelBuilder::~FilesPanelBuilder()
{
}
