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

#ifndef PANELVIEWERFWORTHO_H_
#define PANELVIEWERFWORTHO_H_

#include <string>
#include <vector>
#include "PanelViewerFW.h"

class GLPanel;
class RegionOfInterest2D;

class PanelViewerFWOrtho: public PanelViewerFW
{
	public:
		virtual ~PanelViewerFWOrtho();

		static void Register(wxFrame* parent);

		void AddLayerCarto(const std::string &fileName);

		void showStrip(const std::vector<double>& stripX, const std::vector<double>& stripY, const std::string& stripName);

		void setPointCallback(const boost::function<void(const TPoint2D<double>&)> pointCallback);
		void setCropCallback(const boost::function<void(const RegionOfInterest2D&)> cropCallback);

	protected:
		void OpenCustomFormat(const std::string &filename);

		///Raffraichissement des visus après événements
		virtual void executeModeGeometryMoving();

		PanelViewerFWOrtho(wxFrame *parent);
		friend PanelViewerFWOrtho* createPanelViewerFWOrtho(wxFrame* parent);

		boost::function<void(const RegionOfInterest2D&)> m_cropCallback;
		boost::function<void(const TPoint2D<double>&)> m_pointCallback;


};

#endif /*PANELVIEWERFWORTHO_H_*/
