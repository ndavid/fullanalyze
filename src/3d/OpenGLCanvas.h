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

#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include "wx/glcanvas.h"

#include "Vec3d.h"

class OpenGLCanvas : public wxGLCanvas {

public:

	OpenGLCanvas(wxWindow *parent, double trans_scale = 1, double rot_scale = 45.0);
	~OpenGLCanvas();

	void setTranslation(double x, double y, double z);

	void setSizeOfWorld(const double size);
	void ApplyTransformation();

	void reset();


protected:

	DECLARE_EVENT_TABLE()


	void OnActivate(wxActivateEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnMouse(wxMouseEvent& event);

	void OnMouseWheel(wxMouseEvent& event);

	Vec3d TrackBallMapping(int x, int y);


	void DrawAxes();
	void DrawBBox();

	virtual void DoResize() = 0;


	virtual void DrawScene() = 0;

	//Size of world : cube de la scène
	double m_sizeOfWorld;

	double m_sceneTx, m_sceneTy, m_sceneTz;


	float TRANSLATION_SCALE;
	float ROTATION_SCALE;
	float ZOOM_SCALE;

	double tx, ty, tz;



	//Zoom
	float m_zoom;

	double rotation[16];


	wxGLContext *m_context;


};

#endif // OPENGLCANVAS_H
