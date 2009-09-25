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

#ifndef FULLWAVESENSORIMAGE_H_
#define FULLWAVESENSORIMAGE_H_

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "extern/gil/extension/matis/float_images.hpp"

#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/format/FullwaveEcho.h"

namespace Lidar
{


struct FonctorSumBackscatteredEnergy
{
		FonctorSumBackscatteredEnergy(const float noiseThreshold = 6):
			m_noiseThreshold(noiseThreshold)
			{}

		float operator()(const FullwaveEchoHelper& fwHelper, const BasicWaveformConstIteratorType& itbW, const LidarConstIteratorEcho& itb) const
		{
			float somme =0;
			for(unsigned int i=1; i<=2; ++i)
			{
				if(fwHelper.hasBackscatteredNthSequence(itb,i))
				{
					std::vector<BasicWaveform::FWAmplitudeType>& data = (*itbW)->data_[i-1];

					for(std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = data.begin(); itAmplitude!=data.end(); ++itAmplitude)
					{
						if(*itAmplitude > m_noiseThreshold)
							somme+=*itAmplitude;
					}

				}
				else
					break;
			}
			return somme;
		}

	private:
		float m_noiseThreshold;
};


struct FonctorSumEmittedEnergy
{
		FonctorSumEmittedEnergy(const float noiseThreshold = 6):
			m_noiseThreshold(noiseThreshold)
			{}

		float operator()(const FullwaveEchoHelper& fwHelper, const BasicWaveformConstIteratorType& itbW, const LidarConstIteratorEcho& itb) const
		{
			float somme =0;

			std::vector<BasicWaveform::FWAmplitudeType>& data = (*itbW)->emittedPulse_;

			for(std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = data.begin(); itAmplitude!=data.end(); ++itAmplitude)
			{
				if(*itAmplitude > m_noiseThreshold)
					somme+=*itAmplitude;
			}
			return somme;
		}

	private:
		float m_noiseThreshold;
};


using boost::gil::gray32F_image_t;

template<class Image = gray32F_image_t>
struct FullwaveSensorImage
{
		template<class Fonction>
		shared_ptr<Image> operator()(const shared_ptr<const FullwaveLidarDataContainer>& fwContainer, Fonction f) const
		{
			shared_ptr<Image> result_image(new Image(fwContainer->getNbCols(), fwContainer->getNbRows()));
			typename Image::view_t sensorImage  = view(*result_image);

			typename Image::view_t::iterator itSensorImage = sensorImage.begin();
			BasicWaveformConstIteratorType itbW = fwContainer->getBasicWaveformContainer().begin();
			LidarConstIteratorEcho itb = fwContainer->beginEcho();

			FullwaveEchoHelper fwHelper(*fwContainer);

			for(; itSensorImage != sensorImage.end(); ++itSensorImage, ++itbW, ++itb)
			{
				*itSensorImage = f(fwHelper, itbW, itb);
			}

			return result_image;
		}
};





}//namespace Lidar


#endif /* FULLWAVESENSORIMAGE_H_ */
