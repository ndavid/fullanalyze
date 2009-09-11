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


#include <wx/config.h>
#include <boost/filesystem.hpp>

//register modules
#include "core/modules/Module.h"

//get image data
#include "core/modules/SelectedFullwaveData.h"

//gui access
#include "gui/files/FilesPanel.h"
#include "3d/GLPanel.h"
#include "gui/3d/CloudControl.h"
#include "gui/images/PanelViewerFWSensor.h"
#include "gui/images/PanelViewerFWOrtho.h"

//algorithms
#include "fullwave/algorithms/SensorEnergyImage.h"
#include "fullwave/algorithms/FullwaveTools.h"

//images
#include "extern/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/io/tiff_io.hpp>
namespace gil = boost::gil;

//3d
#include "3d/fullwave/FullwaveCloud.h"




/*** Display 3d module ***/

REGISTER_MODULE(fullwave_display3d, "Display waveforms in 3D", Action::FULLWAVE)

void Module_fullwave_display3d::run()
{
	shared_ptr<SelectedFullwaveData> selectedData = getSelectedFullwaveData(true);
	const SelectedFullwaveData::FullwaveData& fwData = selectedData->front();

	FAEventHandler::Instance()->getPanel3D()->getCloudControl()->AddCloud( shared_ptr<Cloud>(new FullwaveCloud(fwData.m_container, fwData.m_transfo, fwData.m_basename )));
}



/*** Display 1d module ***/

REGISTER_MODULE(fullwave_display1d, "Display waveforms as 1D signals", Action::FULLWAVE)

void Module_fullwave_display1d::run()
{
	shared_ptr<SelectedFullwaveData> selectedData = getSelectedFullwaveData(true);
	const SelectedFullwaveData::FullwaveData& fwData = selectedData->front();

	Lidar::SensorEnergyImage sensorImageMaker(fwData.m_container);

	shared_ptr<gil::gray32F_image_t> sensorImage = sensorImageMaker.run();
	FAEventHandler::Instance()->getPanelFWSensor()->addSensorLayer(sensorImage);

	FAEventHandler::Instance()->setPlotFullwave(fwData.m_container);
}



/*** Centering module ***/

REGISTER_MODULE(fullwave_center, "Center waveforms", Action::FULLWAVE)

void Module_fullwave_center::run()
{
	shared_ptr<SelectedFullwaveData> selectedData = getSelectedFullwaveData(true);
	const SelectedFullwaveData::FullwaveData& fwData = selectedData->front();

	double x=0, y=0;
	wxTextEntryDialog dialogX(FAEventHandler::Instance()->getMainFrame(), _("Transfo x"), _("Please enter text"), _("0."));
	if (dialogX.ShowModal() == wxID_OK)
	{
		wxString result = dialogX.GetValue();
		if(!result.ToDouble(&x))
		{
			wxMessageBox(_("Bad transfo value !"));
			return;
		}
	}
	wxTextEntryDialog dialogY(FAEventHandler::Instance()->getMainFrame(), _("Transfo y"), _("Please enter text"), _("0."));
	if (dialogY.ShowModal() == wxID_OK)
	{
		wxString result = dialogY.GetValue();
		if(!result.ToDouble(&y))
		{
			wxMessageBox(_("Bad transfo value !"));
			return;
		}
	}

	LidarCenteringTransfo transfo;
	transfo.setTransfo(x,y);

	shared_ptr<Lidar::LidarDataContainer> centeredContainer = transfo.centerLidarDataContainer(fwData.m_container->getAttributeContainer(), "originX", "originY", "originZ");
	fwData.m_container->setAttributeContainer(*centeredContainer);

	std::string fileNameXML = ( boost::filesystem::path(fwData.m_path) / (fwData.m_basename + "-centering.xml") ).string();

	FullwaveFile::save(*fwData.m_container, fileNameXML, transfo);

	std::cout << "Fin centrage fw" << std::endl;
}



/*** Display strip module ***/

REGISTER_MODULE(fullwave_display_strip, "Display strip", Action::FULLWAVE)

void Module_fullwave_display_strip::run()
{
	shared_ptr<SelectedFullwaveData> selectedData = getSelectedFullwaveData();
	const SelectedFullwaveData::FullwaveData& fwData = selectedData->front();

	std::vector<double> stripX, stripY;
	FullwaveTools::calculeEmprise(*fwData.m_container, stripX, stripY, fwData.m_transfo);
	FAEventHandler::Instance()->getPanelFWOrtho()->showStrip(stripX, stripY, fwData.m_basename);
}



/*** Print waveforms module ***/

REGISTER_MODULE(fullwave_print, "Print first waveforms", Action::FULLWAVE)

void Module_fullwave_print::run()
{


	try{
		shared_ptr<SelectedFullwaveData> selectedData = getSelectedFullwaveData(true);
		const SelectedFullwaveData::FullwaveData& fwData = selectedData->front();

		fwData.m_container->printHeaderAttribut(std::cout);

		std::cout << "Printing first 10 waveforms: " << std::endl;
		std::ostream_iterator<const Lidar::Waveform> it_output( std::cout, "\n\n" );
		std::copy(fwData.m_container->begin(), fwData.m_container->begin()+10, it_output);
	}

	catch(std::exception &e)
	{
		std::cout << "Exception ! \n";
		std::cout << e.what() << std::endl;
	}
}

