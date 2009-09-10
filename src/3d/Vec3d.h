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
