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
