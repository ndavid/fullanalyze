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

#ifndef __FilesPanelBuilder__
#define __FilesPanelBuilder__

#include <wx/string.h>
#include <wx/filepicker.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/treectrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class FilesPanelBuilder
///////////////////////////////////////////////////////////////////////////////
class FilesPanelBuilder : public wxPanel 
{
	private:
	
	protected:
		enum
		{
			ID_DIR_PICKER_IMAGES = 100000,
			ID_DIR_PICKER_LIDAR,
			ID_DIR_PICKER_FULLWAVE,
			ID_TREE_FILES,
		};
		
		wxDirPickerCtrl* m_dirPickerImages;
		wxDirPickerCtrl* m_dirPickerLidar;
		wxDirPickerCtrl* m_dirPickerFullwave;
		wxTreeCtrl* m_treeFiles;
	
	public:
		
		FilesPanelBuilder( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL );
		~FilesPanelBuilder();
	
};

#endif //__FilesPanelBuilder__
