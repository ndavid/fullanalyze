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



