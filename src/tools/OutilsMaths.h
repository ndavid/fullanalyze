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

#ifndef OUTILSMATHS_H_
#define OUTILSMATHS_H_

#include <cmath>

#define PI 3.141592653589793238462643383279

inline double ROUND(double x)
{
	return std::floor(x+0.5);
}

inline int iROUND(double x)
{
	return static_cast<int>(ROUND(x));
}

template<typename T> inline
T sqr(const T x)
{
	return x*x;
}

template<typename T> inline
T D2R(const T x)
{
	return x/180*M_PI;
}

#endif /*OUTILSMATHS_H_*/
