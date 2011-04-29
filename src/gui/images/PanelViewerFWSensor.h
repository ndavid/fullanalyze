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

#ifndef PANELVIEWERFWSENSOR_H_
#define PANELVIEWERFWSENSOR_H_

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "boost/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include "layers/image_types.hpp"
#include "layers/image_layer.hpp"

#include "PanelViewerFW.h"

class RegionOfInterest2D;

class PanelViewerFWSensor : public PanelViewerFW
{
	public:
		virtual ~PanelViewerFWSensor();

		static void Register(wxFrame* parent);
		void addSensorLayer(const shared_ptr<boost::gil::gray32F_image_t>& img);

		void setCropCallback(const boost::function<void(const RegionOfInterest2D&)> cropCallback);
		void setPointCallback(const boost::function<void(const TPoint2D<int>&)> pointCallback);

	protected:
		///Raffraichissement des visus après événements
		virtual void executeModeGeometryMoving();

		PanelViewerFWSensor(wxFrame *parent);
		friend PanelViewerFWSensor* createPanelViewerFWSensor(wxFrame* parent);

		boost::function<void(const RegionOfInterest2D&)> m_cropCallback;
		boost::function<void(const TPoint2D<int>&)> m_pointCallback;
		
};



#endif /*PANELVIEWERFWSENSOR_H_*/
