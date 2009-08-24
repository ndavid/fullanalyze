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

#include <functional>
#include <algorithm>

#include "plottype.h"

const double PlotPoint::NO_ATTRIBUT=0;



void PlotCourbe::AddPoint(const PlotPoint& pt)
{
	t_ptrPlotPoint ptrPt(new PlotPoint(pt));
	m_listePoints.insert(ptrPt);
}

double PlotCourbe::GetMiniX() const
{
	const_iterator mini = std::min_element(m_listePoints.begin(), m_listePoints.end(), SortByAbscisse() );
	return (*mini)->GetX();
}

double PlotCourbe::GetMaxiX() const
{
	const_iterator maxi = std::max_element(m_listePoints.begin(), m_listePoints.end(), SortByAbscisse() );
	return (*maxi)->GetX();
}

double PlotCourbe::GetMiniY() const
{
	const_iterator mini = std::min_element(m_listePoints.begin(), m_listePoints.end(), SortByOrdonnee() );
	return (*mini)->GetY();
}

double PlotCourbe::GetMaxiY() const
{
	const_iterator maxi = std::max_element(m_listePoints.begin(), m_listePoints.end(), SortByOrdonnee() );
	return (*maxi)->GetY();
}

double PlotCourbe::GetMiniValue() const
{
	const_iterator mini = std::min_element(m_listePoints.begin(), m_listePoints.end(), SortByValue() );
	return (*mini)->GetValue();
}

double PlotCourbe::GetMaxiValue() const
{
	const_iterator maxi = std::max_element(m_listePoints.begin(), m_listePoints.end(), SortByValue() );
	return (*maxi)->GetValue();
}

struct NormalizeValue : public std::unary_function<t_ptrPlotPoint, void>
{
		NormalizeValue(const double value) :
			m_value(value)
		{
		}
		void operator ()(t_ptrPlotPoint p1) const
		{
			p1->GetValue() *= m_value;
		}
	private:
		double m_value;
};

void PlotCourbe::Normalize(const double maxi)
{
	//using namespace std;

	double max = ( *max_element(m_listePoints.begin(), m_listePoints.end()) )->GetValue();

	for_each(m_listePoints.begin(), m_listePoints.end(), NormalizeValue(maxi / max));

}
