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
