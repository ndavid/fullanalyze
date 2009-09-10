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

#ifndef CLOUDVIEWGLOBALSETTINGSCONTROL_H_
#define CLOUDVIEWGLOBALSETTINGSCONTROL_H_

#include <boost/function.hpp>

#include "wxFB/CloudViewGlobalSettingsControlModel.h"

class CloudViewGlobalSettingsControl : public CloudViewGlobalSettingsControlModel
{
	public:
		CloudViewGlobalSettingsControl(wxWindow* parent, boost::function<void()> notifyRefresh);
		virtual ~CloudViewGlobalSettingsControl();

		bool drawAxes() const { return m_drawAxes; }
		bool drawBBox() const { return m_drawBBox; }
		wxColour backgroundColor() const { return m_backgroundColor; }

		int far() const { return m_far; }
		double zoom() const { return m_zoom; }
		double translation() const { return m_translation; }
		double rotation() const { return m_rotation; }

	private:
		boost::function<void()> m_notifyRefresh;

		void OnOKButton(wxCommandEvent &event);
		void OnApplyButton(wxCommandEvent &event);
		void OnCloseWindow(wxCloseEvent& event);

		void OnBackgroundColor(wxColourPickerEvent& event);
		void OnDisplayAxes(wxCommandEvent &event);
		void OnDisplayBBox(wxCommandEvent &event);

		void refresh() { m_notifyRefresh(); }
		void apply();


		bool m_drawAxes;
		bool m_drawBBox;
		wxColour m_backgroundColor;

		int m_far;
		double m_zoom;
		double m_translation;
		double m_rotation;

		DECLARE_EVENT_TABLE();

};

#endif /* CLOUDVIEWGLOBALSETTINGSCONTROL_H_ */
