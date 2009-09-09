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

#ifdef _WINDOWS
#include <windows.h>

#	undef min
#	undef max
#endif


#include "GL/gl.h"
#include "GL/glu.h"

#include <boost/algorithm/minmax_element.hpp>

#include "tools/ColorLookupTable.h"

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/apply.h"
#include "LidarFormat/geometry/RegionOfInterest2D.h"
#include "LidarFormat/geometry/LidarSpatialIndexation2D.h"

///Debug projection points
#include "gui/PanelManager.h"
#include "layers/VectorLayer.hpp"
#include "layers/ImageLayer.hpp"
#include "layers/VectorLayerContent.hpp"

#include "PointCloud.h"

using namespace Lidar;

PointCloud::PointCloud(const shared_ptr<LidarDataContainer>& lidarContainer, const LidarCenteringTransfo& transfo, const std::string& cloudName):
	m_lidarContainer(lidarContainer),
	m_referenceLidarContainer(m_lidarContainer),
	m_transfo(transfo),
	m_spatialIndexationIsSet(false),
	m_ptSize(1),
	m_ssEchantillonnage(1)
{
	name(cloudName);
	initCentering();

	///debug
//	m_layerPoints = VectorLayer::CreateVectorLayer( "test_crop", SHPT_POINT, CARTOGRAPHIC_COORDINATES , false );

}

void PointCloud::getAttributeList(std::vector<std::string>& liste)
{
	m_lidarContainer->getAttributeList(liste);
}


void PointCloud::updateFromCrop(const RegionOfInterest2D& region)
{
	//calcul de l'indexation si elle n'existe pas encore
	if(!m_spatialIndexationIsSet)
	{
		m_spatialIndexation = shared_ptr<LidarSpatialIndexation2D>(new LidarSpatialIndexation2D(*m_referenceLidarContainer));
		m_spatialIndexation->setResolution(1); //1m //TODO pouvoir ajuster entre aéroporté et terrestre !!
		m_spatialIndexation->indexData();

		m_spatialIndexationIsSet = true;

		///debug
//		PanelManager::Instance()->GetPanelsList()[0]->AddLayer(m_layerPoints);
	}

	m_lidarContainer = region.cropLidarData(*m_referenceLidarContainer, *m_spatialIndexation, m_transfo);

	initCentering();

//	///Projection des points dans le panel pour checker les crops
//	boost::shared_ptr<VectorLayer> vectorLayerPoints = boost::dynamic_pointer_cast<VectorLayer>(m_layerPoints);
//	vectorLayerPoints->Clear();
//
//	LidarConstIteratorXYZ<float> itb = m_lidarContainer->beginXYZ<float>();
//	const LidarConstIteratorXYZ<float> ite = m_lidarContainer->endXYZ<float>();
//
//	for (; itb != ite; ++itb)
//	{
//		const TPoint2D<double> pt = m_transfo.applyTransfo(itb.xy());
//		std::cout << pt << std::endl;
//		vectorLayerPoints->AddPoint(pt.x, pt.y);
//	}
//
//	PanelManager::Instance()->GetPanelsList()[0]->Refresh();
}


template<EnumLidarDataType TAttributeType>
struct FunctorMinMax
{
	typedef typename Lidar::LidarEnumTypeTraits<TAttributeType>::type AttributeType;

	typedef std::pair<LidarConstIteratorAttribute<AttributeType>, LidarConstIteratorAttribute<AttributeType> > ResultType;

	std::pair<double, double> operator()(const LidarDataContainer& lidarContainer, const std::string& name)
	{
		ResultType result=  boost::minmax_element(lidarContainer.beginAttribute<AttributeType>(name), lidarContainer.endAttribute<AttributeType>(name));
		return std::make_pair(*result.first, *result.second);
	}

};

void PointCloud::minmax(const std::string &attributeName, double& mini, double &maxi) const
{
//	FunctorMinMaxParameters p(*m_lidarContainer, attributeName);
	std::pair<double, double> minmax = apply<FunctorMinMax, std::pair<double, double>,  const LidarDataContainer&, const std::string&>(m_lidarContainer->getAttributeType(attributeName), *m_lidarContainer, attributeName);
	mini=minmax.first;
	maxi=minmax.second;
}

void PointCloud::generateTexture(const std::string& fileLUTName)
{
	glGenTextures(1, &m_texName);
	glBindTexture(GL_TEXTURE_1D, m_texName);

	std::cout << "generation texture from file : " << fileLUTName << std::endl;


	ColorLookupTable cLUT;
	if(fileLUTName!="")
		cLUT.LoadFromBinaryFile(fileLUTName);

	const std::vector<unsigned char>& lutData=cLUT.getData();

   for (int j = 0; j < 256; j++) {
	   m_texture1D[3*j] = lutData[j];
	   m_texture1D[3*j+1] = lutData[256+j];
	   m_texture1D[3*j+2] = lutData[256*2+j];
	   //m_texture1D[4*j+3] = (GLubyte) 255;

//	   std::cout << (int) lutData[j] << "\t" << (int) lutData[256+j] << "\t" << (int) lutData[256*2+j] << std::endl;
   }


	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, m_texture1D);


	glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

	glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_WRAP_S,GL_CLAMP);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);



//	float border={0,0,0,0};
//	glTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_BORDER_COLOR,border);


}

void PointCloud::colorMode(const ColorMode mode)
{
	m_colorMode = mode;
}

void PointCloud::draw()
{
	//taille des points
	glPointSize( m_ptSize );

	switch(m_colorMode)
	{
		case SINGLE_COLOR:
			drawPointCloudColor();
			break;
		case ATTRIBUTE:
			drawPointCloudTexture();
			break;
		case RGB:
			drawPointCloudRGB();
	}
}


const GLenum SwitchGL(const EnumLidarDataType type)
{
	GLenum result;
	switch (type) {
		case LidarDataType::int8:
			result=GL_BYTE;
			break;
		case LidarDataType::uint8:
			result=GL_UNSIGNED_BYTE;
			break;
		case LidarDataType::int16:
			result=GL_SHORT;
			break;
		case LidarDataType::uint16:
			result=GL_UNSIGNED_SHORT;
			break;
		case LidarDataType::int32:
			result=GL_INT;
			break;
		case LidarDataType::uint32:
			result=GL_UNSIGNED_INT;
			break;
		case LidarDataType::float32:
			result=GL_FLOAT;
			break;
		case LidarDataType::float64:
			result=GL_DOUBLE;
			break;
		default:
			result=0;
	}

	return result;
}


template<EnumLidarDataType TAttributeType>
struct FunctorDisplayAttribute
{
	typedef typename Lidar::LidarEnumTypeTraits<TAttributeType>::type AttributeType;

	void operator()(const LidarDataContainer& lidarContainer, const std::string& name, const unsigned int lod)
	{
		GLenum attribType = SwitchGL(lidarContainer.getAttributeType(name));
		glTexCoordPointer(1, attribType, lidarContainer.pointSize() * lod, &*lidarContainer.beginAttribute<AttributeType>(name));
	}

};


void PointCloud::drawPointCloudTexture()
{
	//GL_SHORT,	GL_INT,	GL_FLOAT, or GL_DOUBLE are accepted

	glEnable(GL_TEXTURE_1D);

	glColor3d(1, 1, 1);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glMatrixMode(GL_TEXTURE); /* enter texture matrix mode */
	glLoadIdentity();
	glMultMatrixf(m_textureMat);
	glMatrixMode(GL_MODELVIEW); /* back to modelview mode */

	glBindTexture(GL_TEXTURE_1D, m_texName);

	GLenum coordType = SwitchGL(m_lidarContainer->getAttributeType("x"));

	if(coordType!=0)
		glVertexPointer(3, coordType, m_lidarContainer->pointSize()*m_ssEchantillonnage, &*m_lidarContainer->beginAttribute<float>("x"));
	//double mais pas grave car convertit en voir !! (marche aussi en float)

	//Coord de textures :
	if(SwitchGL(m_lidarContainer->getAttributeType(m_textureAttributeName)))
	{
		apply<FunctorDisplayAttribute, void, const LidarDataContainer&, const std::string&, const unsigned int>(m_lidarContainer->getAttributeType(m_textureAttributeName), *m_lidarContainer, m_textureAttributeName, m_ssEchantillonnage);

		const unsigned int taille = m_lidarContainer->size() / m_ssEchantillonnage;
		glDrawArrays( GL_POINTS, 0, taille);
	}
	else
	{
		std::cout<<"Warning : type d'attribut non affichable !"<<std::endl;
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_1D);
}

void PointCloud::drawPointCloudColor()
{
	glColor3f(m_singleColor.x, m_singleColor.y, m_singleColor.z);

	GLenum coordType = SwitchGL(m_lidarContainer->getAttributeType("x"));

	if(coordType!=0)
		glVertexPointer(3, coordType, m_lidarContainer->pointSize() * m_ssEchantillonnage, &*m_lidarContainer->beginAttribute<float>("x"));

	const unsigned int taille = m_lidarContainer->size() / m_ssEchantillonnage;
	glDrawArrays( GL_POINTS, 0, taille);

}


template<EnumLidarDataType TAttributeType>
struct FunctorDisplayRGB
{
	typedef typename Lidar::LidarEnumTypeTraits<TAttributeType>::type AttributeType;

	void operator()(const LidarDataContainer& lidarContainer, const std::string& name, const unsigned int lod)
	{
		GLenum attribType = SwitchGL(lidarContainer.getAttributeType(name));
		glColorPointer(3, attribType, lidarContainer.pointSize() * lod, &*lidarContainer.beginAttribute<AttributeType>(name));
	}

};



void PointCloud::drawPointCloudRGB()
{
	glEnable(GL_COLOR_ARRAY);

	GLenum coordType = SwitchGL(m_lidarContainer->getAttributeType("x"));
	if(coordType!=0)
		glVertexPointer(3, coordType, m_lidarContainer->pointSize()*m_ssEchantillonnage, &*m_lidarContainer->beginAttribute<float>("x"));

	//Coord de textures :
	if(SwitchGL(m_lidarContainer->getAttributeType(m_redAttributeName)))
	{
		apply<FunctorDisplayRGB, void, const LidarDataContainer&, const std::string&, const unsigned int>(m_lidarContainer->getAttributeType(m_redAttributeName), *m_lidarContainer, m_redAttributeName, m_ssEchantillonnage);

		const unsigned int taille = m_lidarContainer->size() / m_ssEchantillonnage;
		glDrawArrays(GL_POINTS, 0, taille);
	}
	else
	{
		std::cout<<"Warning : type de couleur non affichable !"<<std::endl;
	}


	glDisable(GL_COLOR_ARRAY);
}


void PointCloud::initCentering()
{
	m_maxX = -std::numeric_limits<float>::max();
	m_maxY = -std::numeric_limits<float>::max();
	m_maxZ = -std::numeric_limits<float>::max();
	m_minX = std::numeric_limits<float>::max();
	m_minY = std::numeric_limits<float>::max();
	m_minZ = std::numeric_limits<float>::max();

	LidarIteratorXYZ<float> itb=m_lidarContainer->beginXYZ<float>();
	const LidarIteratorXYZ<float> ite=m_lidarContainer->endXYZ<float>();


	if(itb==ite)
	{
		m_isEmpty = true;
	}
	else
	{
		m_isEmpty = false;

		for(;itb!=ite; ++itb)
		{
			m_maxX = std::max( m_maxX, itb.x() );
			m_maxY = std::max( m_maxY, itb.y() );
			m_maxZ = std::max( m_maxZ, itb.z() );
			m_minX = std::min( m_minX, itb.x() );
			m_minY = std::min( m_minY, itb.y() );
			m_minZ = std::min( m_minZ, itb.z() );
		}


		std::cout<<"min:" << TPoint3D<float>(m_minX, m_minY, m_minZ)<<"\n";
		std::cout<<"max:" << TPoint3D<float>(m_maxX, m_maxY, m_maxZ)<<"\n";

	}
}

PointCloud::~PointCloud()
{

}
