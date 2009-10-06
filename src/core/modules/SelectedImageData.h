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

#ifndef SELECTEDIMAGEDATA_H_
#define SELECTEDIMAGEDATA_H_

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>
#include "boost/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/io/tiff_dynamic_io.hpp>

using boost::shared_ptr;
using namespace boost::gil;

struct SelectedImageData
{
	typedef any_image< boost::mpl::vector<rgb8_image_t, gray8_image_t , gray16_image_t , gray32_image_t, gray32F_image_t> > usable_images_t;
	typedef std::vector<shared_ptr<usable_images_t> > DataContainerType;

	DataContainerType m_data;

	std::vector<std::string> m_fileNames;
};

#endif /* SELECTEDIMAGEDATA_H_ */
