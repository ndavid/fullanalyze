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

#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/format/FullwaveEcho.h"

#include "SensorEnergyImage.h"

using namespace boost::gil;

namespace Lidar
{

SensorEnergyImage::SensorEnergyImage(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer):
	m_fwContainer(fwContainer)
{

}

shared_ptr<boost::gil::gray32F_image_t> SensorEnergyImage::run() const
{
	shared_ptr<gray32F_image_t> result_image(new gray32F_image_t(m_fwContainer->getNbCols(), m_fwContainer->getNbRows()));
	gray32F_image_t::view_t sensorImage  = view(*result_image);

	gray32F_image_t::view_t::iterator itSensorImage = sensorImage.begin();
	BasicWaveformConstIteratorType itbW = m_fwContainer->getBasicWaveformContainer().begin();
	LidarConstIteratorEcho itb = m_fwContainer->beginEcho();

	FullwaveEchoHelper fwHelper(*m_fwContainer);

	for(; itSensorImage != sensorImage.end(); ++itSensorImage, ++itbW, ++itb)
	{
		float somme =0;
		for(unsigned int i=1; i<=2; ++i)
		{
			if(fwHelper.hasBackscatteredNthSequence(itb,i))
			{
				std::vector<BasicWaveform::FWAmplitudeType>& data = (*itbW)->data_[i-1];

				for(std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = data.begin(); itAmplitude!=data.end(); ++itAmplitude)
				{
					if(*itAmplitude>6)
						somme+=*itAmplitude;
				}

			}
			else
				break;
		}
		*itSensorImage = somme;
	}

	return result_image;
}


} //namespace Lidar
