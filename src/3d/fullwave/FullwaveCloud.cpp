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

/*!
 * \file FullwaveCloud.cpp
 * \brief
 * \author Adrien Chauve
 * \date 20 févr. 2009
 */

#include <numeric>
#include <algorithm>

#include "GL/gl.h"
#include "GL/glu.h"


#include "tools/ColorLookupTable.h"

#include "LidarFormat/geometry/RegionOfInterest2D.h"

#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/algorithms/FullwaveSpatialIndexation.h"


#include "FullwaveCloud.h"

using namespace Lidar;

FullwaveCloud::FullwaveCloud(const shared_ptr<const Lidar::FullwaveLidarDataContainer>& fwContainer, const LidarCenteringTransfo& transfo, const std::string& cloudName):
	m_fwContainer(fwContainer),
	m_transfo(transfo),
	m_fwHelper(*m_fwContainer),
	m_spatialIndexationIsSet(false),
	m_ssEchantillonnage(1),
	m_ratioAmplitude(0.015),
	m_sphereDetails(10)
{

	name(cloudName);
	initCentering();

}


void FullwaveCloud::colorMode(const ColorMode mode)
{
	m_colorMode = mode;
}

void FullwaveCloud::viewMode(const ViewMode mode)
{
	m_viewMode = mode;
}


void FullwaveCloud::drawCloudSegment() const
{
	glColor3f(m_singleColor.x, m_singleColor.y, m_singleColor.z);

	glBegin(GL_LINES);

	LidarConstIteratorEcho itb = m_fwContainer->beginEcho();
	const LidarConstIteratorEcho itBegin = m_fwContainer->beginEcho();

	const LidarConstIteratorEcho ite = m_fwContainer->endEcho();

	BasicWaveformConstIteratorType itbW = m_fwContainer->getBasicWaveformContainer().begin();


	if(m_spatialIndexationIsSet)
	{

		for(ListePointsType::const_iterator it=m_listPoints.begin(); it < m_listPoints.end(); it += m_ssEchantillonnage)
		{
			itb = itBegin + *it;

			for(unsigned int i=1; i<=2; ++i)
			{
				if(m_fwHelper.hasBackscatteredNthSequence(itb,i))
				{
					glVertex3f(m_fwHelper.originXNthSequence(itb, i), m_fwHelper.originYNthSequence(itb, i), m_fwHelper.originZNthSequence(itb, i));
					glVertex3f(m_fwHelper.endXNthSequence(itb, i), m_fwHelper.endYNthSequence(itb, i), m_fwHelper.endZNthSequence(itb, i));
				}
				else
					break;
			}
		}

	}
	else
	{

		for(;itb<ite; itb += m_ssEchantillonnage)
		{
			for(unsigned int i=1; i<=2; ++i)
			{
				if(m_fwHelper.hasBackscatteredNthSequence(itb,i))
				{
					glVertex3f(m_fwHelper.originXNthSequence(itb, i), m_fwHelper.originYNthSequence(itb, i), m_fwHelper.originZNthSequence(itb, i));
					glVertex3f(m_fwHelper.endXNthSequence(itb, i), m_fwHelper.endYNthSequence(itb, i), m_fwHelper.endZNthSequence(itb, i));
				}
				else
					break;
			}
		}

	}

	glEnd();
}

void FullwaveCloud::drawSpheres() const
{

	glEnable(GL_LIGHTING);

	//New quadric object
	GLUquadric *quadric = gluNewQuadric();
	//Turn on the texture mode for quadrics
	gluQuadricTexture(quadric, true);

	glColor3f(m_singleColor.x, m_singleColor.y, m_singleColor.z);


	const LidarConstIteratorEcho itBegin = m_fwContainer->beginEcho();
	LidarConstIteratorEcho itb = itBegin;

	const BasicWaveformConstIteratorType itWbegin = m_fwContainer->getBasicWaveformContainer().begin();

	BasicWaveformConstIteratorType itbW = m_fwContainer->getBasicWaveformContainer().begin();

	if(m_spatialIndexationIsSet)
	{


		for(ListePointsType::const_iterator it=m_listPoints.begin(); it < m_listPoints.end(); it += m_ssEchantillonnage)
		{
			itb = itBegin + *it;

			itbW = itWbegin + *it;

			for(unsigned int i = 1;i <= 2;++i)
			{
				if(m_fwHelper.hasBackscatteredNthSequence(itb, i))
				{
					std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = (*itbW)->data_[i - 1].begin();
					for(unsigned int pointNb = 0;pointNb < m_fwHelper.nbSamples(itb, i);++pointNb, ++itAmplitude)
					{
						glPushMatrix();
						glTranslated(m_fwHelper.positionXNthSequence(itb, i, pointNb), m_fwHelper.positionYNthSequence(itb, i, pointNb), m_fwHelper.positionZNthSequence(itb, i, pointNb));
						gluSphere(quadric, *itAmplitude * m_ratioAmplitude, m_sphereDetails, m_sphereDetails);
						glPopMatrix();
					}
				}
				else
					break;

			}
		}


	}
	else
	{

		const LidarConstIteratorEcho ite = m_fwContainer->endEcho();

		for(;itb<ite; itb += m_ssEchantillonnage, itbW += m_ssEchantillonnage)
		{

			for(unsigned int i = 1;i <= 2;++i)
			{
				if(m_fwHelper.hasBackscatteredNthSequence(itb, i))
				{
					std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = (*itbW)->data_[i - 1].begin();
					for(unsigned int pointNb = 0;pointNb < m_fwHelper.nbSamples(itb, i);++pointNb, ++itAmplitude)
					{
						glPushMatrix();
						glTranslated(m_fwHelper.positionXNthSequence(itb, i, pointNb), m_fwHelper.positionYNthSequence(itb, i, pointNb), m_fwHelper.positionZNthSequence(itb, i, pointNb));
						gluSphere(quadric, *itAmplitude * m_ratioAmplitude, m_sphereDetails, m_sphereDetails);
						glPopMatrix();
					}
				}
				else
					break;

			}
		}


	}




	glDisable(GL_LIGHTING);

}

void FullwaveCloud::drawNormals() const
{

}

void FullwaveCloud::draw()
{

//	if(!m_spatialIndexationIsSet)
	if(m_viewMode == SEGMENTS)
		drawCloudSegment();
	else if(m_viewMode == SPHERES)
		drawSpheres();
	else
		drawNormals();

//	glColor3f(0, 0, 1);
//
//	glBegin(GL_LINES);
//
//
//
//	LidarConstIteratorEcho itb = m_fwContainer->beginEcho();
//	const LidarConstIteratorEcho ite = m_fwContainer->endEcho();
//
//	BasicWaveformConstIteratorType itbW = m_fwContainer->getBasicWaveformContainer().begin();
//
//	if(!m_spatialIndexationIsSet)
//	{
//		for(;itb<ite; ++itb)
//		{
//			for(unsigned int i=1; i<=2; ++i)
//			{
//				if(m_fwHelper.hasBackscatteredNthSequence(itb,i))
//				{
//					glVertex3f(m_fwHelper.originXNthSequence(itb, i), m_fwHelper.originYNthSequence(itb, i), m_fwHelper.originZNthSequence(itb, i));
//					glVertex3f(m_fwHelper.endXNthSequence(itb, i), m_fwHelper.endYNthSequence(itb, i), m_fwHelper.endZNthSequence(itb, i));
//				}
//				else
//					break;
//			}
//		}
//	}
//	else
//	{
//		const LidarConstIteratorEcho itBegin = m_fwContainer->beginEcho();
//		LidarConstIteratorEcho itb = itBegin;
//
//		const BasicWaveformConstIteratorType itWbegin = m_fwContainer->getBasicWaveformContainer().begin();
//
//		for(ListePointsType::const_iterator it=m_listPoints.begin(); it!= m_listPoints.end(); ++it)
//		{
//			itb = itBegin + *it;
//
//			itbW = itWbegin + *it;
//
//			for(unsigned int i=1; i<=2; ++i)
//			{
//				if(m_fwHelper.hasBackscatteredNthSequence(itb,i))
//				{
//					std::vector<BasicWaveform::FWAmplitudeType>& data = (*itbW)->data_[i-1];
//
//					float somme =0;
//					for(std::vector<BasicWaveform::FWAmplitudeType>::iterator itAmplitude = data.begin(); itAmplitude!=data.end(); ++itAmplitude)
//					{
//						if(*itAmplitude>6)
//							somme+=*itAmplitude;
//					}
//
//					somme/=(255.0*1.2);
//
//					glColor3f(somme, somme, somme);
//
//
//					glVertex3f(m_fwHelper.originXNthSequence(itb, i), m_fwHelper.originYNthSequence(itb, i), m_fwHelper.originZNthSequence(itb, i));
//					glVertex3f(m_fwHelper.endXNthSequence(itb, i), m_fwHelper.endYNthSequence(itb, i), m_fwHelper.endZNthSequence(itb, i));
//				}
//				else
//					break;
//			}
//		}
//	}
//
//
//
//	glEnd();

}

void FullwaveCloud::updateFromCrop(const RegionOfInterest2D& region)
{
	//calcul de l'indexation si elle n'existe pas encore
	if(!m_spatialIndexationIsSet)
	{
		m_spatialIndexation = shared_ptr<FullwaveSpatialIndexation>(new FullwaveSpatialIndexation(m_fwContainer));
		m_spatialIndexation->setResolution(0.5); //1m //TODO arranger ça !
		m_spatialIndexation->indexData();

		m_spatialIndexationIsSet = true;
	}

	region.getListNeighborhood(m_listPoints, *m_spatialIndexation, m_transfo);
	std::sort(m_listPoints.begin(), m_listPoints.end());
	m_listPoints.erase( std::unique(m_listPoints.begin(), m_listPoints.end()), m_listPoints.end());

	initCentering();
}


void FullwaveCloud::initCentering()
{
	m_maxX = -std::numeric_limits<float>::max();
	m_maxY = -std::numeric_limits<float>::max();
	m_maxZ = -std::numeric_limits<float>::max();
	m_minX = std::numeric_limits<float>::max();
	m_minY = std::numeric_limits<float>::max();
	m_minZ = std::numeric_limits<float>::max();


	LidarConstIteratorEcho itb = m_fwContainer->beginEcho();
	const LidarConstIteratorEcho ite = m_fwContainer->endEcho();

	if(!m_spatialIndexationIsSet)
	{
		if(itb==ite)
		{
			m_isEmpty = true;
		}
		else
		{
			m_isEmpty = false;

			for(;itb<ite; ++itb)
			{
				for(unsigned int i=1; i<=2; ++i)
				{
					if(m_fwHelper.hasBackscatteredNthSequence(itb,i))
					{
						m_maxX = std::max( m_maxX, m_fwHelper.originXNthSequence(itb, i) );
						m_maxY = std::max( m_maxY, m_fwHelper.originYNthSequence(itb, i) );
						m_maxZ = std::max( m_maxZ, m_fwHelper.originZNthSequence(itb, i) );
						m_minX = std::min( m_minX, m_fwHelper.originXNthSequence(itb, i) );
						m_minY = std::min( m_minY, m_fwHelper.originYNthSequence(itb, i) );
						m_minZ = std::min( m_minZ, m_fwHelper.originZNthSequence(itb, i) );

						m_maxX = std::max( m_maxX, m_fwHelper.endXNthSequence(itb, i) );
						m_maxY = std::max( m_maxY, m_fwHelper.endYNthSequence(itb, i) );
						m_maxZ = std::max( m_maxZ, m_fwHelper.endZNthSequence(itb, i) );
						m_minX = std::min( m_minX, m_fwHelper.endXNthSequence(itb, i) );
						m_minY = std::min( m_minY, m_fwHelper.endYNthSequence(itb, i) );
						m_minZ = std::min( m_minZ, m_fwHelper.endZNthSequence(itb, i) );

					}
					else
						break;
				}
			}
		}
	}
	else
	{
		const LidarConstIteratorEcho itBegin = m_fwContainer->beginEcho();
		LidarConstIteratorEcho itb = itBegin;

//		std::cout << "nb de points dans FullwaveCloud : " << m_listPoints.size() << std::endl;


		if(m_listPoints.empty())
			m_isEmpty = true;
		else
		{
			m_isEmpty = false;

			for(ListePointsType::const_iterator it=m_listPoints.begin(); it!= m_listPoints.end(); ++it)
			{
				itb = itBegin + *it;

				for(unsigned int i=1; i<=2; ++i)
				{
					if(m_fwHelper.hasBackscatteredNthSequence(itb,i))
					{
						m_maxX = std::max( m_maxX, m_fwHelper.originXNthSequence(itb, i) );
						m_maxY = std::max( m_maxY, m_fwHelper.originYNthSequence(itb, i) );
						m_maxZ = std::max( m_maxZ, m_fwHelper.originZNthSequence(itb, i) );
						m_minX = std::min( m_minX, m_fwHelper.originXNthSequence(itb, i) );
						m_minY = std::min( m_minY, m_fwHelper.originYNthSequence(itb, i) );
						m_minZ = std::min( m_minZ, m_fwHelper.originZNthSequence(itb, i) );

						m_maxX = std::max( m_maxX, m_fwHelper.endXNthSequence(itb, i) );
						m_maxY = std::max( m_maxY, m_fwHelper.endYNthSequence(itb, i) );
						m_maxZ = std::max( m_maxZ, m_fwHelper.endZNthSequence(itb, i) );
						m_minX = std::min( m_minX, m_fwHelper.endXNthSequence(itb, i) );
						m_minY = std::min( m_minY, m_fwHelper.endYNthSequence(itb, i) );
						m_minZ = std::min( m_minZ, m_fwHelper.endZNthSequence(itb, i) );
					}
					else
						break;
				}
			}

		}


	}


//	std::cout << "\n\nBBox du nuage FW à afficher : \n";
//	std::cout<<"min:" << TPoint3D<float>(m_minX, m_minY, m_minZ)<<"\n";
//	std::cout<<"max:" << TPoint3D<float>(m_maxX, m_maxY, m_maxZ)<<"\n";
}

FullwaveCloud::~FullwaveCloud()
{

}
