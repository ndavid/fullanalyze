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

/*!
 * \class HillShade
 * \brief Generate a shaded view of a DTM from http://perrygeo.googlecode.com/svn/trunk/demtools/hillshade.cpp
 * \author Frederic Bretar
 */

#ifndef HILLSHADE_H_
#define HILLSHADE_H_
//BOOST
#include <boost/shared_ptr.hpp>
#include "extern/gil/extension/matis/float_images.hpp"

using boost::shared_ptr;






class HillShade {
public:

	HillShade(const shared_ptr<boost::gil::gray32F_image_t> &, const float az = 315., const float alt = 45., const float z = 1., const float scale = 1.);

	shared_ptr<boost::gil::gray32F_image_t> run();

private:
	const std::string _name_mnt;
	shared_ptr<boost::gil::gray32F_image_t> m_img_init;
	unsigned int _nb_col, _nb_li;
	float _z;
	float _az,_alt, _scale;

};

#endif /* HILLSHADE_H_ */
