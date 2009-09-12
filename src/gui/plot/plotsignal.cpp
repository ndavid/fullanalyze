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

#include <limits>
#include <iostream>

#include "plotsignal.h"


PlotSignal::PlotSignal()
{
	m_typeCouleur= PlotType::COULEUR_COURBE;
	m_typeTrace= PlotType::TRACE_COURBE;

	m_miniX = std::numeric_limits<double>::max();
	m_maxiX = -std::numeric_limits<double>::max();
}


void PlotSignal::addCourbe(const std::vector<double>& signal, const double min, const double max, const TPoint3D<int>& couleur, const std::string& title)
{
	//Création de la courbe à partir du tableau
	t_ptrPlotSequenceCourbes ptrSeqCourbes(new PlotSequenceCourbes(1, couleur));
	(*ptrSeqCourbes)[0]=t_ptrPlotCourbe(new PlotCourbe(signal, min, max));
	PlotCourbe& maCourbe = *((*ptrSeqCourbes)[0]);
	m_dataPlot->insert(title,ptrSeqCourbes);

	//définition des bornes
	m_miniX=std::min(min, m_miniX);
	m_maxiX=std::max(max, m_maxiX);
	m_miniY = std::min(m_miniY, maCourbe.GetMiniY());
	m_maxiY = std::max(m_maxiY, maCourbe.GetMaxiY());


	m_notifyPlotFrame();
}
