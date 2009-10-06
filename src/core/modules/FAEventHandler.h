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

#ifndef FAEVENTHANDLER_H_
#define FAEVENTHANDLER_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

#include <boost/function.hpp>

#include "tools/PatternSingleton.hpp"

#include "core/modules/Actions.h"

class PanelViewerFWOrtho;
class PanelViewerFWSensor;
class FilesPanel;
class GLPanel;
class Plot;
class wxFrame;

namespace Lidar {
class FullwaveLidarDataContainer;
}

struct SelectedImageData;
struct SelectedLidarData;
struct SelectedFullwaveData;


class FAEventHandler : public PatternSingleton<FAEventHandler>
{
	public:
		friend class PatternSingleton<FAEventHandler>;


		void init(wxFrame* parent);

		void guiParseFiles();

		/// Callbacks
		void setNotifyGLPanelCreated(const boost::function<void()>& notify);
		void setNotifyPlotPanelCreated(const boost::function<void()>& notify);
		void setNotifyShowPanelSensorViewer(const boost::function<void()>& notify);

		////////// GUI
		wxFrame* getMainFrame();
		PanelViewerFWOrtho* getPanelFWOrtho();
		PanelViewerFWSensor* getPanelFWSensor();
		FilesPanel* getFilesPanel();
		GLPanel* getPanel3D();
		Plot* getPlotPanel();

		/// Actions
		void registerAction(const Action& action);
		const std::vector<Action>& getActions() const { return m_actions; }

		/// Selected data provider (gui selection)
		shared_ptr<SelectedImageData> getSelectedImageData() const;
		shared_ptr<SelectedLidarData> getSelectedLidarData() const;

#ifdef BUILD_FULLWAVE
		shared_ptr<SelectedFullwaveData> getSelectedFullwaveData(const bool loadIntensities = false) const;

		void setPlotFullwave(const shared_ptr<Lidar::FullwaveLidarDataContainer>& fwContainer);
#endif









	private:
		FAEventHandler();
		struct Impl;
		boost::shared_ptr<Impl> m_pimpl;

		std::vector<Action> m_actions;
};

#endif /* FAEVENTHANDLER_H_ */
