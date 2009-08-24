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

/*** Display module ***/

REGISTER_MODULE(image_display, "Display", Action::IMAGE)

void Module_image_display::run()
{
	assert(!getSelectedImageData()->m_fileNames.empty());
	FAEventHandler::Instance()->getPanelFWOrtho()->AddLayerCarto(getSelectedImageData()->m_fileNames.front());
}


/*** Shading module ***/

REGISTER_MODULE(image_shading, "Shading", Action::IMAGE)

void Module_image_shading::run()
{
	assert(!getSelectedImageData()->m_fileNames.empty());

	const std::string fileName(getSelectedImageData()->m_fileNames.front());

	shared_ptr<gray32F_image_t> imageIn (new gray32F_image_t);
	tiff_read_image(fileName, *imageIn);

	HillShade img(imageIn);
	shared_ptr<gray32F_image_t> result = img.run();

	wxConfigBase *pConfig = wxConfigBase::Get();
	wxString imagesDir;
	pConfig->Read(_T("/FA/Paths/ImagesWorkingDir"), &imagesDir, _(""));

	tiff_write_view(std::string(imagesDir.fn_str()) + "/" + boost::filesystem::basename(fileName) + "-shaded.tif", view(*result));

	Lidar::Orientation2D ori;
	ori.ReadOriFromImageFile(fileName);
	ori.SaveOriToFile(std::string(imagesDir.fn_str()) + "/" + boost::filesystem::basename(fileName) + "-shaded.ori");
}

