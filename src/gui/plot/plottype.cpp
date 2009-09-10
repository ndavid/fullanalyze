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
