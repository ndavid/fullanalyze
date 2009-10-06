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
