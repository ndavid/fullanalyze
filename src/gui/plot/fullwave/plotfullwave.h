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

#ifndef PLOTFULLWAVE_H
#define PLOTFULLWAVE_H

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "gui/plot/plottype.h"

namespace Lidar
{
	class FullwaveLidarDataContainer;
	class BasicWaveform;
	class WaveformProcessingMethod;
}

class PlotFullwave : public PlotType
{
public:
    PlotFullwave(const shared_ptr<const Lidar::FullwaveLidarDataContainer>& fwContainer);

    virtual ~PlotFullwave();


    void updatePosition(const TPoint2D<int>& pt);
//    void updateConfig(const ConfigFit & paramConfigFit);

private:
	void recalcule();
	void checkXY( int &x, int&y ) const;

	shared_ptr<const Lidar::FullwaveLidarDataContainer> m_fwContainer;
    TPoint2D<int> m_position;



};

typedef shared_ptr<PlotFullwave> t_ptrPlotFullwave;


#endif // PLOTFULLWAVE_H
