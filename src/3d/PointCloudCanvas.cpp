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

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "GL/gl.h"
#include "GL/glu.h"

#include "boost/bind.hpp"

#include "GLPanel.h"
#include "PointCloudCanvas.h"

#include "gui/3d/CloudControl.h"
#include "3d/Cloud.h"


PointCloudCanvas::PointCloudCanvas(wxWindow *parent) :
	OpenGLCanvas(parent), m_far(10), m_cloudControl( new CloudControl(parent, this, boost::bind( &PointCloudCanvas::update, this))) //, boost::bind(&PointCloudCanvas::setTranslation, this, _1, _2, _3) ))
{

//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(175./255, 175./255, 175./255, 0.0f);
//	glEnable(GL_DEPTH_TEST);
//
////	glShadeModel(GL_SMOOTH); // Permet un joli ombrage
//	glShadeModel(GL_FLAT);
//

	glEnable(GL_DEPTH_TEST); // Mis en place du test de profondeur
	glClearDepth(1.0f); // Mis en place du tampon de profondeur
	glDepthFunc(GL_LEQUAL); // Le type de test de profondeur


//	glEnable(GL_POINT_SMOOTH);
//	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_LINE_SMOOTH);
	//    glEnable(GL_BLEND);
	//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Très jolis calculs de perspective

	glEnableClientState(GL_VERTEX_ARRAY); //pour affichier directement des tableaux de points
//	glEnable(GL_TEXTURE_1D);


//   glEnable(GL_LIGHTING);
//   glEnable(GL_LIGHT0);
//   glEnable(GL_AUTO_NORMAL);
//   glEnable(GL_NORMALIZE);


//    //différents paramètres
 GLfloat ambient[] = {0.15f,0.15f,0.15f,1.0f};
 GLfloat diffuse[] = {0.5f,0.5f,0.5f,1.0f};
 GLfloat light0_position [] = {0.0f, 0.0f, 1000.0f, 0.0f};
 GLfloat specular_reflexion[] = {0.8f,0.8f,0.8f,1.0f};
 GLubyte shiny_obj = 128;
//
//             //positionnement de la lumière avec les différents paramètres
// glEnable(GL_LIGHTING);
 glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
 glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
 glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
 glEnable(GL_LIGHT0);
//
              //spécification de la réflexion sur les matériaux
 glEnable(GL_COLOR_MATERIAL);
 glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
// glColorMaterial(GL_FRONT,GL_DIFFUSE);

 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
 glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
 glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
 glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);



	m_cloudControl->updateFromGlobalViewSettingsControl();

}


void PointCloudCanvas::setFar(const int _far)
{
	m_far = _far;
	DoResize();
}

void PointCloudCanvas::setTranslationScale(const double tr)
{
	TRANSLATION_SCALE = tr;
}

void PointCloudCanvas::setZoom(const double zoom)
{
	ZOOM_SCALE = zoom;
}

void PointCloudCanvas::setRotationScale(const double rotation)
{
	ROTATION_SCALE = rotation;
}


void PointCloudCanvas::DoResize()
{
	int w, h;
	GetClientSize(&w, &h);

	if (h==0)
		h=1;
	if (w==0)
		w=1;

	glViewport(0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(45, (float)w / (float)h, 0.01, 20.);

	gluPerspective(45, (float)w / (float)h, 1., m_sizeOfWorld*m_far);

	//gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
}



void PointCloudCanvas::DrawScene()
{
	// clear color and depth buffers.
	glClearColor(m_cloudControl->backgroundColor().Red()/255., m_cloudControl->backgroundColor().Green()/255., m_cloudControl->backgroundColor().Blue()/255., 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	ApplyTransformation();

	if (m_cloudControl->drawAxes())
		DrawAxes();
	if (m_cloudControl->drawBBox())
		DrawBBox();

	glTranslated(m_sceneTx, m_sceneTy, m_sceneTz);


	for (CloudControl::iterator it = m_cloudControl->begin(); it != m_cloudControl->end(); ++it)
	{
		if ((*it)->isVisible())
		{
			(*it)->draw();
		}
	}

	glFlush();
}
