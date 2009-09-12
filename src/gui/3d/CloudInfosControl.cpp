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

#include "CloudInfosControl.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

BEGIN_EVENT_TABLE(CloudInfosControl, wxFrame)
EVT_BUTTON(wxID_OK,CloudInfosControl::OnOKButton)
END_EVENT_TABLE()

CloudInfosControl::CloudInfosControl(const std::string &infos ,wxWindow* parent, wxWindowID id, const wxString& title, const unsigned long style, const wxPoint& position, const wxSize& size) :
wxFrame(parent,id,title,position,size,style)
{
	wxColour bgcolor( 220, 220, 220);
	SetBackgroundColour(bgcolor);
	ClearBackground();

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *text = new wxStaticText(this,wxID_ANY,wxString(infos.c_str(),*wxConvCurrent));
	sizer->Add( text , 0 , wxALL|wxALIGN_CENTRE , 5);

	wxButton *okButton = new wxButton(this,wxID_OK,_("OK"));
	sizer->Add( okButton , 0 , wxALL|wxALIGN_CENTRE , 5);

	sizer->SetSizeHints(this);
	SetSizer(sizer);
}

CloudInfosControl::~CloudInfosControl()
{
	Destroy();
}

void CloudInfosControl::OnOKButton(wxCommandEvent &event)
{
	Destroy();
}
