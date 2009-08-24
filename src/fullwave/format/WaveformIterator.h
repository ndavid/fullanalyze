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

#ifndef WAVEFORMITERATOR_H_
#define WAVEFORMITERATOR_H_

#include <cassert>
#include <iterator>

#include <boost/shared_ptr.hpp>
#include "fullwave/format/Waveform.h"
#include "LidarFormat/LidarIteratorEcho.h"

namespace Lidar
{


template<class TEchoIterator, class TBasicWaveformIterator, class TWaveform>
class WaveformIteratorModel : public std::iterator< std::random_access_iterator_tag, TWaveform>
{
	public:

		explicit WaveformIteratorModel(const TEchoIterator& echoIterator, const TBasicWaveformIterator& basicWaveformIterator):
			echoIterator_(echoIterator), basicWaveformIterator_(basicWaveformIterator)
		{}

		typedef  WaveformIteratorModel<TEchoIterator, TBasicWaveformIterator, TWaveform> Self;

		WaveformIteratorModel(const Self &rhs):
			echoIterator_(rhs.echoIterator_), basicWaveformIterator_(rhs.basicWaveformIterator_)
		{
		}


		Self &operator=(const Self &rhs)
		{
			echoIterator_ = rhs.echoIterator_;
			basicWaveformIterator_ = rhs.basicWaveformIterator_;
			return *this;
		}


		inline const TWaveform operator*() const
		{
			return TWaveform(*basicWaveformIterator_, *echoIterator_);
		}

		inline const TEchoIterator& echoIterator() const
		{
			return echoIterator_;
		}

		inline const TBasicWaveformIterator& waveformIterator() const
		{
			return basicWaveformIterator_;
		}

		inline Self& operator++()
		{
			++echoIterator_;
			++basicWaveformIterator_;
			return *this;
		}

		inline Self& operator--()
		{
			--echoIterator_;
			--basicWaveformIterator_;
			return *this;
		}

		inline Self& operator+= (const std::size_t index)
		{
			echoIterator_ += index;
			basicWaveformIterator_ += index;
			return *this;
		}

		inline Self& operator-= (const std::size_t index)
		{
			echoIterator_ -= index;
			basicWaveformIterator_ -= index;
			return *this;
		}

		inline friend Self operator+(const Self &lhs, const std::size_t index)
		{
			return Self(lhs) += index;
		}

		inline friend Self operator-(const Self &lhs, const std::size_t index)
		{
			return Self(lhs) -= index;
		}

		inline friend std::ptrdiff_t operator- (const Self &lhs, const Self &rhs)
		{
			assert(lhs.echoIterator_ - rhs.echoIterator_ == lhs.basicWaveformIterator_ - rhs.basicWaveformIterator_);
			return lhs.basicWaveformIterator_ - rhs.basicWaveformIterator_;
		}

		inline friend bool operator== (const Self &lhs, const Self &rhs)
		{
			return (lhs.echoIterator_ == rhs.echoIterator_) && (lhs.basicWaveformIterator_ == rhs.basicWaveformIterator_);
		}

		inline friend bool operator!= (const Self &lhs, const Self &rhs)
		{
			return !(lhs == rhs);
		}

		inline friend bool operator< (const Self &lhs, const Self &rhs)
		{
			assert(lhs.echoIterator_ - rhs.echoIterator_ == lhs.basicWaveformIterator_ - rhs.basicWaveformIterator_);
			return lhs.echoIterator_ < rhs.echoIterator_;
		}

		inline friend bool operator<= (const Self &lhs, const Self &rhs)
		{
			assert(lhs.echoIterator_ - rhs.echoIterator_ == lhs.basicWaveformIterator_ - rhs.basicWaveformIterator_);
			return lhs.echoIterator_ <= rhs.echoIterator_;
		}



	private:
		TEchoIterator echoIterator_;
		TBasicWaveformIterator basicWaveformIterator_;
};

	typedef WaveformIteratorModel<LidarIteratorEcho, BasicWaveformIteratorType, Waveform> WaveformIterator;
	typedef WaveformIteratorModel<LidarConstIteratorEcho, BasicWaveformConstIteratorType, const Waveform> WaveformConstIterator;
} //namespace Lidar


#endif /* WAVEFORMITERATOR_H_ */
