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

#include "fullwave/format/FullwaveLidarDataContainer.h"

#include "plotfullwave.h"

using namespace Lidar;

PlotFullwave::PlotFullwave(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer):
	m_fwContainer(fwContainer)
{
	m_typeCouleur= PlotType::COULEUR_COURBE;
	m_typeTrace= PlotType::TRACE_COURBE;
}

void PlotFullwave::checkXY( int &x, int&y ) const
{
	if (y < 0)
		y = 0;
	else if (y >= (int) m_fwContainer->getNbRows())
		y = m_fwContainer->getNbRows() - 1;
	if (x < 0)
		x = 0;
	else if (x >= (int) m_fwContainer->getNbCols())
		x = m_fwContainer->getNbCols() - 1;
}

void PlotFullwave::updatePosition(const TPoint2D<int>& pt)
{
	TPoint2D<int> ptTest(pt);
	checkXY(ptTest.x, ptTest.y);

	if (m_position!=ptTest)
	{
		m_position=ptTest;
		recalcule();
	}
}



void PlotFullwave::recalcule()
{
	//Extraction du profil FW et calcul du fit
	shared_ptr<BasicWaveform> wf = m_fwContainer->getBasicWaveform(m_position.x, m_position.y);

	//Creation du conteneur de données
	m_dataPlot=t_ptrPlotDataContainer(new PlotDataContainer());

	m_miniX = std::numeric_limits<double>::max();
	m_maxiX = -std::numeric_limits<double>::max();

	//Récupération du nombre de courbes dans une sequence :
	const size_t nb_seq = 1 + wf->data_.size();

	//Longueur d'une courbe
	const size_t taille_courbe = wf->emittedPulse_.size();

	///////Remplissage des données :
	const TPoint3D<int> couleur_data(255, 0, 0);

	//Donnees brutes
	{
		t_ptrPlotSequenceCourbes ptrSeqCourbes(new PlotSequenceCourbes(nb_seq, couleur_data));
		(*ptrSeqCourbes)[0]=t_ptrPlotCourbe(new PlotCourbe(wf->emittedPulse_));
		for (size_t i=1; i<nb_seq; ++i)
			(*ptrSeqCourbes)[i]=t_ptrPlotCourbe(new PlotCourbe(wf->data_[i-1]));
		m_dataPlot->insert("Data", ptrSeqCourbes);
	}


	m_miniX=0;
	m_maxiX=taille_courbe; // nb de points d'une courbe
	m_miniY=-100;
	m_maxiY=200;


	m_notifyPlotFrame();
}

PlotFullwave::~PlotFullwave()
{
}



