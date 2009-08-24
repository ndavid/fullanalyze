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

#include <boost/bind.hpp>

#include "layers/VectorLayerGhost.h"


////si GIL
#include "layers/ImageLayer.hpp"
////si ITK
//#include "layers/NewImageLayer.h"



#include "gui/PanelManager.h"

#include "LidarFormat/geometry/RegionOfInterest2D.h"

#include "PanelViewerFWSensor.h"

PanelViewerFWSensor::PanelViewerFWSensor(wxFrame *parent) :
	PanelViewerFW(parent)
{
}

PanelViewerFWSensor::~PanelViewerFWSensor()
{
}

void PanelViewerFWSensor::addSensorLayer(const shared_ptr<boost::gil::gray32F_image_t>& img)
{
	////si GIL
//	Layer::ptrLayerType layerSensor = ImageLayer::CreateImageLayer(fileName);
	////si ITK
//	Layer::ptrLayerType layerSensor = Layers::NewImageLayer(fileName);

	AddLayer( ImageLayer::CreateImageLayer(*img) );
	Refresh();
}

void PanelViewerFWSensor::setCropCallback(const boost::function<void(const RegionOfInterest2D&)> cropCallback)
{
	m_cropCallback = cropCallback;
}

void PanelViewerFWSensor::setPointCallback(const boost::function<void(const TPoint2D<int>&)> pointCallback)
{
	m_pointCallback = pointCallback;
}

void PanelViewerFWSensor::executeModeGeometryMoving()
{
	//position de la souris
	if (m_geometry == GEOMETRY_POINT)
	{
		m_pointCallback(TPoint2D<int>(m_ghostLayer.m_pointPosition.x, m_ghostLayer.m_pointPosition.y));
	}
//	else if (m_geometry == GEOMETRY_CIRCLE)
//	{
//		//Informe le dock que le point courant a changé
//		Dock *parent = dynamic_cast<Dock*>(m_parent);
//		parent->UpdatePositionVisu2D(TPoint2D<int>(m_ghostLayer.m_circle.first.x, m_ghostLayer.m_circle.first.y));
//	}
//	else if (m_geometry == GEOMETRY_RECTANGLE)
//	{
//		//Informe le dock que le point courant a changé
//		Dock *parent = dynamic_cast<Dock*>(m_parent);
//		parent->UpdatePositionVisuSelection2D(TPoint2D<int>(m_ghostLayer.m_rectangleSelection.first.x, m_ghostLayer.m_rectangleSelection.first.y), TPoint2D<int>(m_ghostLayer.m_rectangleSelection.second.x, m_ghostLayer.m_rectangleSelection.second.y) );
//	}


}





PanelViewerFWSensor* createPanelViewerFWSensor(wxFrame* parent)
{
	return new PanelViewerFWSensor(parent);
}

void PanelViewerFWSensor::Register(wxFrame* parent)
{
	PanelManager::Instance()->Register("PanelViewerFWSensor", boost::bind(createPanelViewerFWSensor, parent));
}




