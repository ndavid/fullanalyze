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

#ifndef __CLOUD_SETTINGS_CONTROL_HPP__
#define __CLOUD_SETTINGS_CONTROL_HPP__

#include <wx/dialog.h>

class CloudControl;

class CloudSettingsControl //: public wxDialog
{
public:
	CloudSettingsControl(CloudControl *parent){} //: wxDialog( (wxWindow*)parent, wxID_ANY, _("Cloud settings control")){}
	virtual ~CloudSettingsControl() {}


	virtual void show(const bool toBeShown)=0;
	virtual void destroy()=0;
	virtual bool isVisible() const=0 ;

	unsigned int index() { return m_index; }
	void index(const unsigned int index){  m_index = index; }

protected:
	unsigned int m_index;
};

#endif // __CLOUD_SETTINGS_CONTROL_HPP__
