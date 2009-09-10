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

#include <boost/filesystem.hpp>

#include <wx/config.h>
#include <wx/textdlg.h>

//register modules
#include "core/modules/Module.h"

//get image data
#include "core/modules/SelectedLidarData.h"

//algorithms
#include "core/algorithms/lidar/MNS.h"

//images
#include <boost/gil/extension/matis/float_images.hpp>
#include <boost/gil/extension/io/tiff_io.hpp>
namespace gil = boost::gil;

//gui access
#include "gui/files/FilesPanel.h"
#include "3d/GLPanel.h"
#include "gui/3d/CloudControl.h"

//3d
#include "3d/PointCloud.h"




/*** Display 3d module ***/

REGISTER_MODULE(lidar_display3d, "Display 3D", Action::LIDAR)

void Module_lidar_display3d::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

	FAEventHandler::Instance()->getPanel3D()->getCloudControl()->AddCloud( shared_ptr<Cloud>(new PointCloud(lidarData.m_container, lidarData.m_transfo, lidarData.m_basename )));
}



/*** Print first echoes module ***/

REGISTER_MODULE(lidar_print_echoes, "Print first 10 echoes", Action::LIDAR)

void Module_lidar_print_echoes::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

	lidarData.m_container->printHeader(std::cout);
	std::cout.precision(12);

	for(Lidar::LidarIteratorEcho it = lidarData.m_container->begin(); it != lidarData.m_container->begin()+10 && it < lidarData.m_container->end(); ++it)
		std::cout << LidarEcho(*it) << std::endl;
}



/*** Save as binary module ***/

REGISTER_MODULE(lidar_save_as_binary, "Save as binary", Action::LIDAR)

void Module_lidar_save_as_binary::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

	lidarData.m_container->printHeader(std::cout);
	std::cout.precision(12);

	std::string fileNameXML = ( boost::filesystem::path(lidarData.m_path) / (lidarData.m_basename + "-binary.xml") ).string();
	LidarFile::save(*lidarData.m_container, fileNameXML);
}



/*** Save as ascii module ***/

REGISTER_MODULE(lidar_save_as_ascii, "Save as ascii", Action::LIDAR)

void Module_lidar_save_as_ascii::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

	lidarData.m_container->printHeader(std::cout);
	std::cout.precision(12);

	std::string fileNameXML = ( boost::filesystem::path(lidarData.m_path) / (lidarData.m_basename + "-ascii.xml") ).string();
	LidarFile::save(*lidarData.m_container, fileNameXML, cs::DataFormatType::ascii);
}



/*** Centering module ***/

REGISTER_MODULE(lidar_centering, "Point cloud centering", Action::LIDAR)

void Module_lidar_centering::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

	LidarCenteringTransfo transfo;
	shared_ptr<LidarDataContainer> centeredContainer = transfo.centerLidarDataContainer(*lidarData.m_container);

	std::string fileNameXML = ( boost::filesystem::path(lidarData.m_path) / (lidarData.m_basename + "-centering.xml") ).string();
	LidarFile::save(*centeredContainer, fileNameXML, transfo);
}



/*** Custom centering module ***/
//TODO fusionner le code avec le module precedent

REGISTER_MODULE(lidar_custom_centering, "Custom point cloud centering", Action::LIDAR)

void Module_lidar_custom_centering::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

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

	shared_ptr<LidarDataContainer> centeredContainer = transfo.centerLidarDataContainer(*lidarData.m_container);

	std::string fileNameXML = ( boost::filesystem::path(lidarData.m_path) / (lidarData.m_basename + "-centering.xml") ).string();
	LidarFile::save(*centeredContainer, fileNameXML, transfo);
}



/*** MNS module ***/

REGISTER_MODULE(lidar_mns, "Compute MNS", Action::LIDAR)

void Module_lidar_mns::run()
{
	shared_ptr<SelectedLidarData> selectedData = getSelectedLidarData();
	const SelectedLidarData::LidarData& lidarData = selectedData->front();

	double r=1.;
	wxTextEntryDialog dialogResolution(FAEventHandler::Instance()->getMainFrame(), _("Raster resolution"), _("Please enter the raster resolution (m)"), _("1."));
	if (dialogResolution.ShowModal() == wxID_OK)
	{
		wxString result = dialogResolution.GetValue();
		if(!result.ToDouble(&r))
		{
			wxMessageBox(_("Bad resolution value !"));
			return;
		}
	}

	Lidar::MNS mns(*lidarData.m_container, lidarData.m_transfo, r);

	wxConfigBase *pConfig = wxConfigBase::Get();
	wxString imagesDir;
	pConfig->Read(_T("/FA/Paths/ImagesWorkingDir"), &imagesDir, _(""));


	shared_ptr<gil::gray32F_image_t> result = mns.run();

	using namespace boost::filesystem;
	gil::tiff_write_view( (path(imagesDir.fn_str()) / (lidarData.m_basename + "-mns.tif")).string() , gil::view(*result));

	Lidar::Orientation2D ori = mns.getOri();
	ori.SaveOriToFile( (path(imagesDir.fn_str()) / (lidarData.m_basename + "-mns.ori")).string() );

}

