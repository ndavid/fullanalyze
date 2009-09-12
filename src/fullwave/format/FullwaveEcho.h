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

#ifndef FULLWAVEECHO_H_
#define FULLWAVEECHO_H_


#include "FullwaveLidarDataContainer.h"

namespace Lidar
{

typedef unsigned int FWFilePointerType;
typedef float FWRangeBeginType;
typedef double FWGPSTimeType;
typedef float FWEmissionAngleType;
typedef float FWOriginType;
typedef float FWDirectionType;

class FullwaveEchoHelper
{
	public:
		FullwaveEchoHelper(const FullwaveLidarDataContainer& fwContainer);


		template<class EchoOrIteratorEcho>
		const bool hasBackscatteredSequences(const EchoOrIteratorEcho& echo) const
		{
			return echo.template value<FWFilePointerType>(intNthSequenceFilePointer(1)) > echo.template value<FWFilePointerType>(intEmissionPulseSequenceFilePointer());
		}

		template<class EchoOrIteratorEcho>
		const bool hasBackscatteredNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			if(seqNb>1)
				return echo.template value<FWFilePointerType>(intNthSequenceFilePointer(seqNb)) > echo.template value<FWFilePointerType>(intNthSequenceFilePointer(seqNb-1));

			return hasBackscatteredSequences(echo);
		}

		template<class EchoOrIteratorEcho>
		const unsigned int nbSamples(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			if(seqNb>1)
				return echo.template value<FWFilePointerType>(intNthSequenceFilePointer(seqNb)) - echo.template value<FWFilePointerType>(intNthSequenceFilePointer(seqNb-1));

			return echo.template value<FWFilePointerType>(intNthSequenceFilePointer(1)) - echo.template value<FWFilePointerType>(intEmissionPulseSequenceFilePointer());
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType originXNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			return echo.template value<FWOriginType>(intOriginX()) +  echo.template value<FWDirectionType>(intDirectionX()) * echo.template value<FWRangeBeginType>(intNthSequenceRangeBegin(seqNb));
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType originYNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			return echo.template value<FWOriginType>(intOriginY()) +  echo.template value<FWDirectionType>(intDirectionY()) * echo.template value<FWRangeBeginType>(intNthSequenceRangeBegin(seqNb));
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType originZNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			return echo.template value<FWOriginType>(intOriginZ()) +  echo.template value<FWDirectionType>(intDirectionZ()) * echo.template value<FWRangeBeginType>(intNthSequenceRangeBegin(seqNb));
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType endXNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			return originXNthSequence(echo, seqNb) + m_drange * echo.template value<FWDirectionType>(intDirectionX()) * (nbSamples(echo, seqNb) -1);
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType endYNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			return originYNthSequence(echo, seqNb) + m_drange * echo.template value<FWDirectionType>(intDirectionY()) * (nbSamples(echo, seqNb) -1);
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType endZNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb) const
		{
			return originZNthSequence(echo, seqNb) + m_drange * echo.template value<FWDirectionType>(intDirectionZ()) * (nbSamples(echo, seqNb) -1);
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType positionXRange(const EchoOrIteratorEcho& echo, const float range, const unsigned int seqNb) const
		{
			return originXNthSequence(echo, seqNb) + range * m_drange * echo.template value<FWDirectionType>(intDirectionX());
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType positionYRange(const EchoOrIteratorEcho& echo, const float range, const unsigned int seqNb) const
		{
			return originYNthSequence(echo, seqNb) + range * m_drange * echo.template value<FWDirectionType>(intDirectionY());
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType positionZRange(const EchoOrIteratorEcho& echo, const float range, const unsigned int seqNb) const
		{
			return originZNthSequence(echo, seqNb) + range * m_drange * echo.template value<FWDirectionType>(intDirectionZ());
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType positionXNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb, const unsigned int i) const
		{
			return originXNthSequence(echo, seqNb) + m_drange * echo.template value<FWDirectionType>(intDirectionX()) * i;
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType positionYNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb, const unsigned int i) const
		{
			return originYNthSequence(echo, seqNb) + m_drange * echo.template value<FWDirectionType>(intDirectionY()) * i;
		}

		template<class EchoOrIteratorEcho>
		const FWOriginType positionZNthSequence(const EchoOrIteratorEcho& echo, const unsigned int seqNb, const unsigned int i) const
		{
			return originZNthSequence(echo, seqNb) + m_drange * echo.template value<FWDirectionType>(intDirectionZ()) * i;
		}


		const unsigned int intDirectionX() const {return m_intDirectionX;}
		const unsigned int intDirectionY() const {return m_intDirectionY;}
		const unsigned int intDirectionZ() const {return m_intDirectionZ;}
		const unsigned int intEmissionAngle() const {return m_intEmissionAngle;}
		const unsigned int intEmissionPulseSequenceFilePointer() const {return m_intEmissionPulseSequenceFilePointer;}
		const unsigned int intEmissionPulseSequenceRangeBegin() const {return m_intEmissionPulseSequenceRangeBegin;}
		const unsigned int intGPSTime() const {return m_intGPSTime;}
		const unsigned int intOriginX() const {return m_intOriginX;}
		const unsigned int intOriginY() const {return m_intOriginY;}
		const unsigned int intOriginZ() const {return m_intOriginZ;}

		inline const unsigned int intNthSequenceFilePointer(const unsigned int nbSeq) const
		{
			return m_beginNthSequence + (nbSeq - 1)*(sizeof(FWFilePointerType) + sizeof(FWRangeBeginType));
		}

		inline const unsigned int intNthSequenceRangeBegin(const unsigned int nbSeq) const
		{
			return m_beginNthSequence + sizeof(FWFilePointerType) + (nbSeq - 1)*(sizeof(FWFilePointerType) + sizeof(FWRangeBeginType));
		}


		static const std::string m_stringEmissionPulseSequenceFilePointer;
		static const std::string m_stringEmissionPulseSequenceRangeBegin;
		static const std::string m_stringGPSTime;
		static const std::string m_stringEmissionAngle;
		static const std::string m_stringOriginX;
		static const std::string m_stringOriginY;
		static const std::string m_stringOriginZ;
		static const std::string m_stringDirectionX;
		static const std::string m_stringDirectionY;
		static const std::string m_stringDirectionZ;

		static const std::string stringNthSequenceFilePointer(const unsigned int nbSeq)
		{
			std::ostringstream oss;
			oss << "sequence" << nbSeq << "_";
			return oss.str() + "filePointer";
		}

		static const std::string stringNthSequenceRangeBegin(const unsigned int nbSeq)
		{
			std::ostringstream oss;
			oss << "sequence" << nbSeq << "_";
			return oss.str() + "rangeBegin";
		}


	private:
		unsigned int m_intDirectionX;
		unsigned int m_intDirectionY;
		unsigned int m_intDirectionZ;
		unsigned int m_intEmissionAngle;
		unsigned int m_intEmissionPulseSequenceFilePointer;
		unsigned int m_intEmissionPulseSequenceRangeBegin;
		unsigned int m_intGPSTime;
		unsigned int m_intOriginX;
		unsigned int m_intOriginY;
		unsigned int m_intOriginZ;

		unsigned int m_beginNthSequence;

		double m_drange;

};

} //namespace Lidar

#endif /* FULLWAVEECHO_H_ */
