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

#include <boost/bind.hpp>

#include "layers/vector_layer_ghost.hpp"


////si GIL
#include "layers/image_layer.hpp"

//#include "boost/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
//#include <boost/gil/extension/io_new/tiff_all.hpp>

#include "gui/panel_manager.hpp"
#include "layers/image_types.hpp"

#include "LidarFormat/geometry/RegionOfInterest2D.h"

#include "PanelViewerFWSensor.h"

PanelViewerFWSensor::PanelViewerFWSensor(wxFrame *parent) :
	PanelViewerFW(parent)
{
	geometry_add_point(wxPoint(0,0));
}

PanelViewerFWSensor::~PanelViewerFWSensor()
{
}

void PanelViewerFWSensor::addSensorLayer(const shared_ptr<boost::gil::gray32F_image_t>& img)
{
	//boost::gil::any_image<all_image_types> any_sensorFW(img.get() );
        any_image_type any_sensorFW( *img );
	boost::shared_ptr<image_type> sensor_im(new image_type(any_sensorFW) );
	layer::ptrLayerType layerSensor = image_layer::create_image_layer(sensor_im);
	add_layer( layerSensor);
	
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

void PanelViewerFWSensor::execute_mode_geometry_moving()
{
	//position de la souris
	if (m_geometry == GEOMETRY_POINT)
	{
		m_pointCallback(TPoint2D<int>(m_ghostLayer->m_pointPosition.x, m_ghostLayer->m_pointPosition.y));
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
	panel_manager::instance()->Register("PanelViewerFWSensor", boost::bind(createPanelViewerFWSensor, parent));
}




