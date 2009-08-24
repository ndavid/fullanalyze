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

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include <wx/frame.h>

#include "gui/PanelManager.h"


#include "3d/GLPanel.h"

#include "gui/3d/CloudControl.h"

#include "gui/images/PanelViewerFWOrtho.h"
#include "gui/images/PanelViewerFWSensor.h"
#include "gui/files/FilesPanel.h"
#include "gui/plot/plotsignal.h"
#include "gui/plot/plot.h"

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/LidarFile.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"
#include "LidarFormat/tools/Orientation2D.h"



#ifdef BUILD_FULLWAVE
#include "gui/plot/fullwave/plotfullwave.h"
#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/algorithms/FullwaveTools.h"
#include "fullwave/format/FullwaveFile.h"
#endif


#include "FAEventHandler.h"


using boost::shared_ptr;

struct FAEventHandler::Impl
{
	Impl();

	///Interface
	void init(wxFrame* parent);
	void setNotifyGLPanelCreated(const boost::function<void()>& notify);
	void setNotifyPlotPanelCreated(const boost::function<void()>& notify);
	void setNotifyShowPanelSensorViewer(const boost::function<void()>& notify);

	void createPanel3d();

	///DATA
	wxFrame* m_parent;

	PanelViewerFWOrtho *m_panelViewerMain;
	PanelViewerFWSensor *m_panelViewerSensor;
	FilesPanel *m_panelMainFiles;
	GLPanel *m_panel3D;
	Plot* m_plotPanel;

	//pour une création du panel3D sans bug (démarrage de l'appli)
	boost::function<void()> m_notifyGLPanelCreated;
	boost::function<void()> m_notifyPlotPanelCreated;
	boost::function<void()> m_notifyShowPanelSensorViewer;

#ifdef BUILD_FULLWAVE
	shared_ptr<PlotFullwave> m_plotFW;
#endif
	shared_ptr<PlotSignal> m_plotSignal;
};

FAEventHandler::Impl::Impl():
m_parent(0), m_panelViewerMain(0), m_panelViewerSensor(0),m_panelMainFiles(0), m_panel3D(0), m_plotPanel(0)
{

}

void FAEventHandler::Impl::setNotifyGLPanelCreated(const boost::function<void()>& notify)
{
	m_notifyGLPanelCreated=notify;
}

void FAEventHandler::Impl::setNotifyPlotPanelCreated(const boost::function<void()>& notify)
{
	m_notifyPlotPanelCreated=notify;
}

void FAEventHandler::Impl::setNotifyShowPanelSensorViewer(const boost::function<void()>& notify)
{
	m_notifyShowPanelSensorViewer=notify;
}

void FAEventHandler::Impl::init(wxFrame* parent)
{
	m_parent = parent;

	///registering panels
	PanelViewerFWOrtho::Register(m_parent);
	PanelViewerFWSensor::Register(m_parent);


	///creating panels
	m_panelViewerMain = static_cast<PanelViewerFWOrtho*>(PanelManager::Instance()->createObject("PanelViewerFWOrtho"));
	m_panelViewerSensor = static_cast<PanelViewerFWSensor*>(PanelManager::Instance()->createObject("PanelViewerFWSensor"));
	m_panelMainFiles = new FilesPanel(m_parent);
}




void FAEventHandler::Impl::createPanel3d()
{
	m_panel3D = new GLPanel(m_parent);
	m_panelViewerMain->setCropCallback(boost::bind(&CloudControl::updateFromCrop, m_panel3D->getCloudControl(), _1));
	m_notifyGLPanelCreated();
}






PanelViewerFWOrtho* FAEventHandler::getPanelFWOrtho()
{
	return m_pimpl->m_panelViewerMain;
}

PanelViewerFWSensor* FAEventHandler::getPanelFWSensor()
{
	return m_pimpl->m_panelViewerSensor;
}



FilesPanel* FAEventHandler::getFilesPanel()
{
	return m_pimpl->m_panelMainFiles;
}

GLPanel* FAEventHandler::getPanel3D()
{
	if(!m_pimpl->m_panel3D)
		m_pimpl->createPanel3d();
	return m_pimpl->m_panel3D;
}

wxFrame* FAEventHandler::getMainFrame()
{
	return m_pimpl->m_parent;
}

Plot* FAEventHandler::getPlotPanel()
{
	return m_pimpl->m_plotPanel;
}

void FAEventHandler::init(wxFrame* parent)
{
	m_pimpl->init(parent);
}

void FAEventHandler::setNotifyGLPanelCreated(const boost::function<void()>& notify)
{
	m_pimpl->setNotifyGLPanelCreated(notify);
}

void FAEventHandler::setNotifyPlotPanelCreated(const boost::function<void()>& notify)
{
	m_pimpl->setNotifyPlotPanelCreated(notify);
}

void FAEventHandler::setNotifyShowPanelSensorViewer(const boost::function<void()>& notify)
{
	m_pimpl->setNotifyShowPanelSensorViewer(notify);
}


FAEventHandler::FAEventHandler():
	m_pimpl(new Impl)
{

}

void FAEventHandler::guiParseFiles()
{
	m_pimpl->m_panelMainFiles->parseAllFiles();
}

void FAEventHandler::registerAction(const Action& action)
{
	m_actions.push_back(action);
}


#include "core/modules/SelectedImageData.h"
#include "core/modules/SelectedLidarData.h"
#include "core/modules/SelectedFullwaveData.h"

shared_ptr<SelectedImageData> FAEventHandler::getSelectedImageData() const
{
	shared_ptr<SelectedImageData> data(new SelectedImageData);
	data->m_fileNames.push_back(m_pimpl->m_panelMainFiles->getImagesSelectedItemName());
	return data;
}

shared_ptr<SelectedLidarData> FAEventHandler::getSelectedLidarData() const
{
	using namespace Lidar;
	const std::string fileName(m_pimpl->m_panelMainFiles->getLidarSelectedItemName());
	LidarFile file(fileName);
	shared_ptr<LidarDataContainer> lidarData(new LidarDataContainer);
	file.loadData(*lidarData);

	LidarCenteringTransfo transfo;
	file.loadTransfo(transfo);


	SelectedLidarData::LidarData data;
	data.m_container = lidarData;
	data.m_transfo = transfo;
	data.m_path = boost::filesystem::path(fileName).branch_path().string();
	data.m_basename = boost::filesystem::basename(fileName);
	data.m_extension = boost::filesystem::extension(fileName);

	shared_ptr<SelectedLidarData> selectedData(new SelectedLidarData);
	selectedData->m_data.push_back(data);
	return selectedData;
}


#ifdef BUILD_FULLWAVE
shared_ptr<SelectedFullwaveData> FAEventHandler::getSelectedFullwaveData() const
{
	using namespace Lidar;
	const std::string fileName(m_pimpl->m_panelMainFiles->getFullwaveSelectedItemName());
	FullwaveFile file(fileName);
	shared_ptr<FullwaveLidarDataContainer> fwData(new FullwaveLidarDataContainer(fileName));

	LidarCenteringTransfo transfo;
	file.loadTransfo(transfo);


	SelectedFullwaveData::FullwaveData data;
	data.m_container = fwData;
	data.m_transfo = transfo;
	data.m_path = boost::filesystem::path(fileName).branch_path().string();
	data.m_basename = boost::filesystem::basename(fileName);
	data.m_extension = boost::filesystem::extension(fileName);

	shared_ptr<SelectedFullwaveData> selectedData(new SelectedFullwaveData);
	selectedData->m_data.push_back(data);
	return selectedData;

}
#endif










