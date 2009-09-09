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

#include <cmath>

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "wx/wx.h"

#include "GL/gl.h"
#include "GL/glu.h"



#include "OpenGLCanvas.h"



int attrib_list[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER };

OpenGLCanvas::OpenGLCanvas(wxWindow *parent, double trans_scale, double rot_scale) :
	wxGLCanvas(parent, -1, attrib_list), m_sizeOfWorld(1), TRANSLATION_SCALE(trans_scale), ROTATION_SCALE(rot_scale), ZOOM_SCALE(1)
{

	m_context = new wxGLContext(this);

	m_sceneTx = m_sceneTy = m_sceneTz =0;

	reset();

	SetCurrent(*m_context);

}

OpenGLCanvas::~OpenGLCanvas()
{
}


void OpenGLCanvas::reset()
{
	tx = ty = tz = 0.0;

	m_zoom = 10;

	// Initialize rotation matrix to indentity.
	for (int i = 0; i < 16; i++)
		rotation[i] = 0.0;
	rotation[0] = rotation[5] = rotation[10] = rotation[15] = 1.0;
}

BEGIN_EVENT_TABLE(OpenGLCanvas, wxGLCanvas)
EVT_SIZE(OpenGLCanvas::OnSize)
EVT_PAINT(OpenGLCanvas::OnPaint)
EVT_ERASE_BACKGROUND(OpenGLCanvas::OnEraseBackground)
EVT_MOUSE_EVENTS(OpenGLCanvas::OnMouse)
//EVT_MOUSEWHEEL(OpenGLCanvas::OnMouseWheel)
END_EVENT_TABLE()

void OpenGLCanvas::OnPaint(wxPaintEvent& event)
{

	wxPaintDC dc(this);
	SetCurrent(*m_context);
	DrawScene();
	SwapBuffers();
}

void OpenGLCanvas::OnSize(wxSizeEvent& event)
{

	wxGLCanvas::OnSize(event);
	SetCurrent(*m_context);
	DoResize();
	Refresh();
}

void OpenGLCanvas::setSizeOfWorld(const double size)
{
	bool toBeResized = std::fabs(m_sizeOfWorld-size)/m_sizeOfWorld > 0.5;
	m_sizeOfWorld = size;

	if(toBeResized)
		DoResize();
}

void OpenGLCanvas::OnEraseBackground(wxEraseEvent& event)
{
}

void OpenGLCanvas::OnMouse(wxMouseEvent& event)
{
	static Vec3d lastPoint, curPoint;
	static int lastX, lastY;

	if (event.LeftDown())
	{
		lastPoint = TrackBallMapping(event.GetX(), event.GetY());
	}
	else if (event.RightDown())
	{
		lastX = event.GetX();
		lastY = event.GetY();
	}
	else if (event.MiddleDown())
	{
		lastX = event.GetX();
		lastY = event.GetY();
	}
	else if (event.Dragging())
	{
		if (event.LeftIsDown())
		{
			curPoint = TrackBallMapping(event.GetX(), event.GetY());
			Vec3d direction = curPoint - lastPoint;
			double velocity = direction.Length();
			if (velocity > 0.0001)
			{

				Vec3d rotAxis;
				rotAxis.crossProd(lastPoint, curPoint);
				double rot_angle = velocity * ROTATION_SCALE;

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glRotated(rot_angle, rotAxis.x, rotAxis.y, rotAxis.z);
				glMultMatrixd(rotation);

				glGetDoublev(GL_MODELVIEW_MATRIX, rotation);


				Refresh();

				lastPoint = curPoint;
			}
		}
		else if (event.RightIsDown())
		{
			tx += (event.GetX() - lastX) * TRANSLATION_SCALE;
			ty += (lastY - event.GetY()) * TRANSLATION_SCALE;

			Refresh();

			lastX = event.GetX();
			lastY = event.GetY();
		}
		else if (event.MiddleIsDown())
		{
			tx += (event.GetX() - lastX) * TRANSLATION_SCALE;
			tz += (event.GetY() - lastY) * TRANSLATION_SCALE;

			Refresh();

			lastX = event.GetX();
			lastY = event.GetY();
		}
	}

	int deltaMouseWheel = event.GetWheelRotation();
	if (event.GetWheelDelta())
	{
		if (deltaMouseWheel<0)
		{
			m_zoom += ZOOM_SCALE;

		}
		else
		{
			m_zoom -= ZOOM_SCALE;

		}
		Refresh();
	}


	event.Skip();
}


void OpenGLCanvas::setTranslation(double x, double y, double z)
{
	m_sceneTx = x;
	m_sceneTy = y;
	m_sceneTz = z;


}

Vec3d OpenGLCanvas::TrackBallMapping(int x, int y)
{
	Vec3d v;
	double d;

	int w, h;
	GetSize(&w, &h);

	v.x = (2.0*x - w) / w;
	v.y = (h - 2.0*y) / h;
	v.z = 0.0;
	d = v.Length();
	d = (d < 1.0) ? d : 1.0;
	v.z = sqrtf(1.001 - d*d);

	v.Normalize();

	return v;
}

void OpenGLCanvas::ApplyTransformation()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(tx, ty, tz);

	glTranslated(0., 0., m_zoom*-0.05*m_sizeOfWorld);

	glMultMatrixd(rotation);

}

void OpenGLCanvas::DrawAxes()
{
	glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_LINES);
	//dessin des axes
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(m_sizeOfWorld, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, m_sizeOfWorld, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, m_sizeOfWorld);
	glColor3f(1.0, 1.0, 1.0);

	glEnd();

}

void OpenGLCanvas::DrawBBox()
{
	glBegin(GL_LINES);

	glColor3f(1.0, 1.0, 1.0);

	//dessin du cube
	glVertex3f(-m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, +m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, -m_sizeOfWorld);
	glVertex3f(+m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, +m_sizeOfWorld, +m_sizeOfWorld);
	glVertex3f(-m_sizeOfWorld, -m_sizeOfWorld, +m_sizeOfWorld);
	glEnd();
}


