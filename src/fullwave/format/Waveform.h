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

#ifndef WAVEFORM_H_
#define WAVEFORM_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

#include <boost/shared_ptr.hpp>

#include "LidarFormat/LidarEcho.h"

namespace Lidar
{



struct FunctorCout
{
	FunctorCout(std::ostream& os, const char * sep):os_(os), sep_(sep){}
	std::ostream& operator()(const unsigned char i)
	{
		os_ << static_cast<int>(i) << sep_;
		return os_;
	}
	private:
		std::ostream& os_;
		const char * sep_;
};

struct BasicWaveform
{
		typedef unsigned char FWAmplitudeType;
		typedef std::vector<std::vector<FWAmplitudeType> > AmplitudeContainerType;
		AmplitudeContainerType data_;
		typedef std::vector<FWAmplitudeType> EmittedPulseContainerType;
		EmittedPulseContainerType emittedPulse_;

		inline friend std::ostream& operator<<( std::ostream& os, const BasicWaveform& basicWaveform )
		{
			using namespace std;
			FunctorCout it_outputEmittedPulse( cout, "\t" );
			cout << "Emitted Pulse " << endl;
			for_each(basicWaveform.emittedPulse_.begin(), basicWaveform.emittedPulse_.end(), it_outputEmittedPulse);
			cout << endl;

			for(unsigned int i = 0; i<basicWaveform.data_.size(); ++i)
			{
				std::ostringstream oss;
				oss << i;
				cout << "Backscattered  sequence " << oss.str() << endl;
				for_each(basicWaveform.data_[i].begin(), basicWaveform.data_[i].end(), it_outputEmittedPulse);
				cout << endl;
			}

			return os;
		}
};

typedef std::vector<boost::shared_ptr<BasicWaveform> > BasicWaveformContainerType;
typedef BasicWaveformContainerType::iterator BasicWaveformIteratorType;
typedef BasicWaveformContainerType::const_iterator BasicWaveformConstIteratorType;

class Waveform
{
	public:
		Waveform(const boost::shared_ptr<BasicWaveform>& waveform, const LidarEcho &echo):
			waveform_(waveform), echo_(echo){}

		inline const BasicWaveform& waveform() const { return *waveform_; }
		//inline BasicWaveform& waveform() { return *waveform_; }

		inline const LidarEcho& echo() const { return echo_; }
//		inline FullwaveEcho& echo() { return *echo_; }

		inline friend std::ostream& operator<<( std::ostream& os, const Waveform& waveform )
		{
			using namespace std;
			os << endl << endl;
			os << "Waveform : " << endl;
			os << "Attributs : " << endl;
			os << waveform.echo_ << endl;
			os << "Intensités : " << endl;
			os << *waveform.waveform_ << endl;

			return os;
		}

	private:
		boost::shared_ptr<BasicWaveform> waveform_;
		LidarEcho echo_;
};




} //namespace Lidar

#endif /* WAVEFORM_H_ */
