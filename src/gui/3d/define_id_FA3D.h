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

#ifndef __DEFINE_ID__FA3D_HPP__
#define __DEFINE_ID__FA3D_HPP__


#include "gui/define_id.hpp"


enum
{
	ID_FA_INFO,
	ID_FA_DELETE								=	ID_FA_INFO + MAX_LAYERS,
	ID_FA_VISIBILITY							=	ID_FA_DELETE + MAX_LAYERS,
	ID_FA_TRANSFORMATION						=	ID_FA_VISIBILITY + MAX_LAYERS,
	ID_FA_SETTINGS								=	ID_FA_TRANSFORMATION + MAX_LAYERS,
	ID_FA_VISIBILITY_BUTTON					    =	ID_FA_SETTINGS + MAX_LAYERS + 1,
	ID_FA_GLOBAL_SETTINGS_BUTTON,

	ID_FA_SHOW_HIDE_CLOUD_CONTROL,
	ID_FA_LIDAR_DISPLAY_PROJECTED_POINTS,
	ID_FA_ORTHO_NAVIGATE,
	ID_FA_ORTHO_MOVE_SELECTION,
	ID_FA_ORTHO_RECTANGLE_SELECTION,
	ID_FA_ORTHO_CIRCLE_SELECTION,
	ID_FA_ORTHO_NO_SELECTION,

	ID_FA_SENSOR_NAVIGATE,
	ID_FA_SENSOR_MOVE_POINT,

	ID_FA_GLPANEL
};


#endif // __DEFINE_ID__FA3D_HPP__
