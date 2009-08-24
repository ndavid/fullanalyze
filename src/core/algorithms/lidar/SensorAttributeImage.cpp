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

#include "LidarFormat/LidarDataContainer.h"
#include "core/algorithms/lidar/SensorIndexation.h"

#include "SensorAttributeImage.h"


using namespace boost::gil;

namespace Lidar
{

SensorAttributeImage::SensorAttributeImage(const shared_ptr<const Lidar::LidarDataContainer>& lidarContainer, const unsigned int nbCols):
	m_lidarContainer(lidarContainer),
	m_nbCols(nbCols)
{

}


shared_ptr<gray32F_image_t>  SensorAttributeImage::run(const char* attributeName)
{

	SensorIndexation sensorIndexation(m_lidarContainer, m_nbCols);
	sensorIndexation.setResolution(1);
	sensorIndexation.indexData();


	const SensorIndexation::GriddedDataType& grid = sensorIndexation.getSpatialIndexation();

	shared_ptr<gray32F_image_t> result_image(new gray32F_image_t(grid.GetTaille().x, grid.GetTaille().y));
	gray32F_image_t::view_t sensorImage  = view(*result_image);

	const LidarConstIteratorAttribute<float> beginAttribute = m_lidarContainer->beginAttribute<float>(attributeName);

	for(int col = 0; col < sensorImage.width(); ++col)
	{
		for(int lig = 0; lig < sensorImage.height(); ++lig)
		{
			if(!grid(col,lig).empty())
			{
				sensorImage(col,lig) = *(beginAttribute + *grid(col,lig).begin());
			}
		}
	}


	return result_image;
}


} //namespace Lidar
