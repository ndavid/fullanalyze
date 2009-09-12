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

#ifndef __CLOUD_INFOS_CONTROL_HPP__
#define __CLOUD_INFOS_CONTROL_HPP__

#include <wx/frame.h>

class CloudInfosControl : public wxFrame
{
public:
	CloudInfosControl(const std::string &infos ,wxWindow* parent, wxWindowID id, const wxString& title, const unsigned long style, const wxPoint& position=wxDefaultPosition, const wxSize& size=wxDefaultSize);
	virtual ~CloudInfosControl();

	void OnOKButton(wxCommandEvent &event);

	DECLARE_EVENT_TABLE();
};

#endif // __CLOUD_INFOS_CONTROL_HPP__
