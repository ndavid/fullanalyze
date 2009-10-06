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
 * \author Frederic Bretar
 */

#include <iostream>
#include <iterator>
#include <vector>

#include <boost/gil/algorithm.hpp>

#include "hillshade.h"


#define NOVALUE -999

using namespace boost::gil;


using namespace std;

const float radiansToDegrees = 180.0 / 3.14159;
const float degreesToRadians = 3.14159 / 180.0;


HillShade::HillShade(const shared_ptr<gray32F_image_t> &mnt, const float az, const float alt, const float z, const float scale) :
	m_img_init(mnt),
	_nb_col(m_img_init->width()),
	_nb_li(m_img_init->height()),
	_z(z), _az(az), _alt(alt), _scale(scale)
{
}



shared_ptr<gray32F_image_t> HillShade::run() {
//	  /* ------------------------------------------
//	     * Move a 3x3 window over each cell
//	     * (where the cell in question is #4)
//	     *
//	     *                 0 1 2
//	     *                 3 4 5
//	     *                 6 7 8
//	    *
//	     */

	//img de sortie
	shared_ptr<gray32F_image_t> pt_img_shade = shared_ptr<gray32F_image_t> (new gray32F_image_t(_nb_col, _nb_li)); //, NOVALUE));
	gray32F_image_t::view_t img_shade = view(*pt_img_shade);

	//initialisation à NOVALUE
	fill_pixels(img_shade, NOVALUE);

	gray32F_image_t::view_t img_init = view(*m_img_init);


//	shared_ptr<Image<float> > pt_img_aspect =
//		shared_ptr<Image<float> > (new Image<float> (_nb_col, _nb_li, NOVALUE));
//	shared_ptr<Image<float> > pt_img_slope =
//		shared_ptr<Image<float> > (new Image<float> (_nb_col, _nb_li, NOVALUE));
	int containsNull = 0;


	float  	x;
	float	y;
    float   aspect;
    float	slope;
    float   cang;

//	ostream_iterator<double> out_it( cout, "  " );
	std::vector<float> win;
	win.reserve(9);

	for ( unsigned int col = 0; col < _nb_col; col++) {
	       for ( unsigned int lig = 0; lig < _nb_li; lig++) {

	            containsNull = 0;
//
	            // Exclude the edges
	            if (col == 0 || lig == 0 || col == _nb_col-1 || lig == _nb_li-1 )
	            {
	                // We are at the edge so write nullValue and move on
	                img_shade(col,lig) = NOVALUE;
	                continue;
	            }

	            // Read in 3x3 window
	            unsigned short cpt=0;
	            for(unsigned int j=0;j<3;++j)//li
	            	for(unsigned int i=0;i<3;++i)//col
	            	{
//	            		std::cout<<cpt<<" "<<(*m_img_init)(col+i-1,lig+j-1)<<std::endl;
	            		win[cpt]=img_init(col+i-1,lig+j-1);
	            		++cpt;
	            	}

//	            std::cout<<"   win size: "<<win.size()<<std::endl;
//
//	    		copy(win.begin(), win.end(), out_it);
//				std::getchar();

				for(unsigned int i=0;i<win.size();++i) {
//	            	std::cout<<"   win siz: "<<win.size()<<std::endl;
	            	if(win[i] == NOVALUE) {
	            		containsNull = 1;
	            		break;
	            	}
	            }

	            if (containsNull == 1) {
	            	// We have nulls so write nullValue and move on
	            	img_shade(col,lig) = NOVALUE;
	            	continue;
	            } else {


		         // We have a valid 3x3 window.

	                /* ---------------------------------------
	                * Compute Hillshade
	                */

	                // First Slope ...
	                x = ((_z*win[0] + _z*win[3] + _z*win[3] + _z*win[6]) -
	                     (_z*win[2] + _z*win[5] + _z*win[5] + _z*win[8])) /
	                    (8.0  * _scale);

	                y = ((_z*win[6] + _z*win[7] + _z*win[7] + _z*win[8]) -
	                     (_z*win[0] + _z*win[1] + _z*win[1] + _z*win[2])) /
	                    (8.0  * _scale);

	                //check values
//	                std::cout<<"x :"<<x<<"  y :"<<y<<std::endl;

					slope = 90.0 - atan(sqrt(x*x + y*y))*radiansToDegrees;
//					(*pt_img_slope)(col,lig) = slope;
	                //check values
//	                std::cout<<"slope :"<<slope<<std::endl;

	                // ... then aspect...
	                aspect = atan2(x,y);
//					(*pt_img_aspect)(col,lig) = aspect*radiansToDegrees;

	                //check values
//	                std::cout<<"aspect :"<<aspect<<std::endl;

	                // ... then the shade value
	                cang = sin(_alt*degreesToRadians) * sin(slope*degreesToRadians) +
	                       cos(_alt*degreesToRadians) * cos(slope*degreesToRadians) *
	                       cos((_az-90.0)*degreesToRadians - aspect);

	                if (cang <= 0.0)
	                    cang = 1.0;
	                else
	                    cang = 1.0 + (254.0 * cang);

	                img_shade(col,lig) = cang;

	            }
	        }


	    }



	return pt_img_shade;
}

