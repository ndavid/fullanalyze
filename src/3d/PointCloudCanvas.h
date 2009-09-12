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

#ifndef POINTCLOUDCANVAS_H
#define POINTCLOUDCANVAS_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include "LidarFormat/extern/matis/tpoint3d.h"

#include "OpenGLCanvas.h"

class CloudControl;


class PointCloudCanvas : public OpenGLCanvas
{

	public:

		PointCloudCanvas(wxWindow *parent);

		CloudControl* getCloudControl() { return m_cloudControl; }

		void update() { Refresh(); }

		void setFar(const int far);
		void setTranslationScale(const double tr);
		void setZoom(const double zoom);
		void setRotationScale(const double rotation);

	protected:

		virtual void DoResize();
		virtual void DrawScene();


	private:

		int m_far;

		CloudControl* m_cloudControl;


};

#endif // POINTCLOUDCANVAS_H
