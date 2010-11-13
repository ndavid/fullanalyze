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

#include <stdexcept>
#include <wx/wx.h>
#include <wx/statusbr.h>

#include "gui/MainFrame.h"

#ifdef _WINDOWS
#include "LidarFormat/file_formats/StaticRegisterFormats.cpp"
#endif


#ifdef __LINUX__
#include <locale.h>
#endif

class MyApp : public wxApp
{
public:
private:
	bool OnInit();
	bool InitFrame();

	MainFrame *m_mainFrameDock;

};

IMPLEMENT_APP(MyApp)


bool MyApp::InitFrame()
{

	wxInitAllImageHandlers();

#ifdef _WINDOWS
	registerAllFileFormats();
#endif

	m_mainFrameDock = new MainFrame;

	return true;
}

bool MyApp::OnInit()
{
#ifdef __LINUX__
setlocale (LC_ALL,"POSIX");
#endif

	try
	{
		if ( InitFrame() )
			m_mainFrameDock->Show();
		else
			exit(0);


	}
	catch( std::exception &e )
	{
		wxString message;
		message << wxString(e.what(), *wxConvCurrent);
		wxMessageBox( message );
	}
	catch( ... )
	{
		wxMessageBox( _("Unhandled exception ...") );
	}

	return true;
}

