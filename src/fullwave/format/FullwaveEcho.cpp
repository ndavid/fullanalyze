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

#include "FullwaveEcho.h"

namespace Lidar
{

const std::string FullwaveEchoHelper::m_stringEmissionPulseSequenceFilePointer = "emittedPulseSequence_filePointer";
const std::string FullwaveEchoHelper::m_stringEmissionPulseSequenceRangeBegin = "emittedPulseSequence_rangeBegin";
const std::string FullwaveEchoHelper::m_stringGPSTime = "gpsTime";
const std::string FullwaveEchoHelper::m_stringEmissionAngle = "emissionAngle";
const std::string FullwaveEchoHelper::m_stringOriginX = "originX";
const std::string FullwaveEchoHelper::m_stringOriginY = "originY";
const std::string FullwaveEchoHelper::m_stringOriginZ = "originZ";
const std::string FullwaveEchoHelper::m_stringDirectionX = "directionX";
const std::string FullwaveEchoHelper::m_stringDirectionY = "directionY";
const std::string FullwaveEchoHelper::m_stringDirectionZ = "directionZ";



FullwaveEchoHelper::FullwaveEchoHelper(const FullwaveLidarDataContainer& fwContainer):
	m_drange(fwContainer.fwGlobalParameters().m_rangeStep)
{
	const AttributeMapType& attributeMap = fwContainer.getAttributeMap();

	m_intDirectionX = attributeMap.find(m_stringDirectionX)->second.decalage;
	m_intDirectionY = attributeMap.find(m_stringDirectionY)->second.decalage;
	m_intDirectionZ = attributeMap.find(m_stringDirectionZ)->second.decalage;
	m_intEmissionAngle = attributeMap.find(m_stringDirectionX)->second.decalage;
	m_intEmissionPulseSequenceFilePointer = attributeMap.find(m_stringEmissionPulseSequenceFilePointer)->second.decalage;
	m_intEmissionPulseSequenceRangeBegin = attributeMap.find(m_stringEmissionPulseSequenceRangeBegin)->second.decalage;
	m_intGPSTime = attributeMap.find(m_stringGPSTime)->second.decalage;
	m_intOriginX = attributeMap.find(m_stringOriginX)->second.decalage;
	m_intOriginY = attributeMap.find(m_stringOriginY)->second.decalage;
	m_intOriginZ = attributeMap.find(m_stringOriginZ)->second.decalage;

	m_beginNthSequence = attributeMap.find(stringNthSequenceFilePointer(1))->second.decalage;
}


} //namespace Lidar
