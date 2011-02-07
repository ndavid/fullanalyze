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

#include <wx/config.h>
#include <boost/filesystem.hpp>

//register modules
#include "core/modules/Module.h"

//get image data
#include "core/modules/SelectedImageData.h"

//gui access
#include "gui/images/PanelViewerFWOrtho.h"
#include "gui/files/FilesPanel.h"

//shading algorithm
#include "core/algorithms/image/hillshade.h"

#include "LidarFormat/tools/Orientation2D.h"

#include <boost/gil/extension/io_new/tiff_all.hpp>

/*** Display module ***/

REGISTER_MODULE(image_display, "Display", Action::IMAGE)

void Module_image_display::run()
{
	assert(!getSelectedImageData()->m_fileNames.empty());
	FAEventHandler::instance()->getPanelFWOrtho()->AddLayerCarto(getSelectedImageData()->m_fileNames.front());
}


/*** Shading module ***/

REGISTER_MODULE(image_shading, "Shading", Action::IMAGE)

void Module_image_shading::run()
{
	assert(!getSelectedImageData()->m_fileNames.empty());

	const std::string fileName(getSelectedImageData()->m_fileNames.front());

	shared_ptr<gray32F_image_t> imageIn (new gray32F_image_t);
        read_image(fileName,
                   *imageIn,
                   tiff_tag());

	HillShade img(imageIn);
	shared_ptr<gray32F_image_t> result = img.run();

	wxConfigBase *pConfig = wxConfigBase::Get();
	wxString imagesDir;
	pConfig->Read(_T("/FA/Paths/ImagesWorkingDir"), &imagesDir, _(""));

        write_view(std::string((const char*)imagesDir.mb_str()) + "/" + boost::filesystem::basename(fileName) + "-shaded.tif",
                   view(*result),
                   tiff_tag());

	Lidar::Orientation2D ori;
	ori.ReadOriFromImageFile(fileName);
	ori.SaveOriToFile(std::string((const char*)imagesDir.mb_str()) + "/" + boost::filesystem::basename(fileName) + "-shaded.ori");
}

