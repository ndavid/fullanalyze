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

#ifndef VEC3D_H
#define VEC3D_H

#include <math.h>

class Vec3d {

public:

	Vec3d() : x(0.0), y(0.0), z(0.0) {}
	Vec3d(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

	inline void crossProd(Vec3d &v1, Vec3d &v2) {
		x = v1.y*v2.z - v1.z*v2.y;
		y = v1.z*v2.x - v1.x*v2.z;
		z = v1.x*v2.y - v1.y*v2.x;
		Normalize();
	}

	inline double Length() {
		return sqrtf(x*x + y*y + z*z);
	}

	inline void Normalize() {
		double length = Length();
		x /= length;
		y /= length;
		z /= length;
	}
	
	inline Vec3d operator*(const double scale) {
		return Vec3d(x * scale, y * scale, z * scale);
	}

	inline Vec3d operator+(const Vec3d& v) {
		return Vec3d(x + v.x, y + v.y, z + v.z);
	}

	inline Vec3d operator-(const Vec3d& v) {
		return Vec3d(x - v.x, y - v.y, z - v.z);
	}

	inline Vec3d& operator*=(const double scale) {
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	inline Vec3d& operator+=(const Vec3d& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline Vec3d& operator-=(const Vec3d& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	double x;
	double y;
	double z;

};

inline Vec3d operator*(double scale, const Vec3d& v) {
	return Vec3d(scale * v.x, scale * v.y, scale * v.z);
}

#endif // VEC3D_H
