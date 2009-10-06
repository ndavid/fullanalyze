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

#include <numeric>

#include "FullwaveSensorImage.h"

#include "boost/gil/extension/matis/float_images.hpp"
#include <boost/gil/gil_all.hpp>

namespace gil = boost::gil;

#include "FullwaveCorrectEnergy.h"

namespace Lidar
{


void fullwaveCorrectEnergy(const shared_ptr<FullwaveLidarDataContainer>& fwContainer, float normalisationEnergy)
{

	shared_ptr<gil::gray32F_image_t> sensorImageEmittedEnergy = FullwaveSensorImage<>()(fwContainer, Lidar::FonctorSumEmittedEnergy());
	gil::gray32F_view_t sensorImageEmittedEnergyView = gil::view(*sensorImageEmittedEnergy);

	if(normalisationEnergy == 0)
	{
		//the normalisation energy is then the mean emitted energy
		normalisationEnergy = std::accumulate(sensorImageEmittedEnergyView.begin(), sensorImageEmittedEnergyView.end(), 0.) / (sensorImageEmittedEnergyView.width() * sensorImageEmittedEnergyView.height());
	}

	BasicWaveformConstIteratorType itbW = fwContainer->getBasicWaveformContainer().begin();
	LidarConstIteratorEcho itb = fwContainer->beginEcho();

	FullwaveEchoHelper fwHelper(*fwContainer);

	gil::gray32F_view_t::iterator itSensorImage = sensorImageEmittedEnergyView.begin();
	for(; itSensorImage != sensorImageEmittedEnergyView.end(); ++itSensorImage, ++itbW, ++itb)
	{
		for(unsigned int i=1; i<=2; ++i)
		{
			if(fwHelper.hasBackscatteredNthSequence(itb,i))
			{
				std::vector<BasicWaveform::FWAmplitudeType>& data = (*itbW)->data_[i-1];

				for(std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = data.begin(); itAmplitude!=data.end(); ++itAmplitude)
				{
					*itAmplitude *= normalisationEnergy / *itSensorImage;
				}

			}
			else
				break;
		}
	}

}


}//namespace Lidar

