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

#ifdef _WINDOWS
#include <windows.h>

#	undef min
#	undef max
#endif


#include "GL/gl.h"
#include "GL/glu.h"

#include <boost/algorithm/minmax_element.hpp>

#include "tools/color_lookup_table.hpp"

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/apply.h"
#include "LidarFormat/geometry/RegionOfInterest2D.h"
#include "LidarFormat/geometry/LidarSpatialIndexation2D.h"

///projection points
#include "gui/panel_manager.hpp"
#include "layers/vector_layer.hpp"
#include "layers/simple_vector_layer.hpp"
#include "layers/image_layer.hpp"
//#include "layers/VectorLayerContent.hpp"

#include "core/modules/FAEventHandler.h"

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

	//m_layerPoints = vector_layer::CreateVectorLayer( "point_cloud_" + name(), SHPT_POINT, CARTOGRAPHIC_COORDINATES , false );
	m_layerPoints = layer::ptrLayerType(new simple_vector_layer("point_cloud_" + name() ) );
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
		if(!m_spatialIndexation.get())
		{
			m_spatialIndexation = shared_ptr<LidarSpatialIndexation2D>(new LidarSpatialIndexation2D(*m_referenceLidarContainer));
			m_spatialIndexation->setResolution(0.5); //1m //TODO pouvoir ajuster entre aéroporté et terrestre !!
			m_spatialIndexation->indexData();

			panel_manager::instance()->panels_list()[0]->add_layer(m_layerPoints);
		}

		m_spatialIndexationIsSet = true;

	}

	m_lidarContainer = region.cropLidarData(*m_referenceLidarContainer, *m_spatialIndexation, m_transfo);

	initCentering();

	updateVisuCrop();

}

void PointCloud::updateVisuCrop()
{
	m_layerPoints->clear();

	//	///Projection des points dans le panel pour checker les crops
	if(FAEventHandler::instance()->lidarDisplayProjectedPoints() && isVisible())
	{
		boost::shared_ptr<vector_layer> vectorLayerPoints = boost::dynamic_pointer_cast<vector_layer>(m_layerPoints);

		LidarConstIteratorXYZ<float> itb = m_lidarContainer->beginXYZ<float>();
		const LidarConstIteratorXYZ<float> ite = m_lidarContainer->endXYZ<float>();

		for (; itb != ite; ++itb)
		{
			const TPoint2D<double> pt = m_transfo.applyTransfo(itb.xy());
			vectorLayerPoints->add_point(pt.x, pt.y);
		}
	}

	panel_manager::instance()->panels_list()[0]->Refresh();
}


void PointCloud::resetCrop()
{
	m_spatialIndexationIsSet = false;
	m_lidarContainer = m_referenceLidarContainer;

	initCentering();
	updateVisuCrop();
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

//	std::cout << "generation texture from file : " << fileLUTName << std::endl;


	color_lookup_table cLUT;
	if(fileLUTName!="")
		cLUT.load_from_binary_file(fileLUTName);

	const std::vector<unsigned char>& lutData=cLUT.get_data();

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


//		std::cout<<"min:" << TPoint3D<float>(m_minX, m_minY, m_minZ)<<"\n";
//		std::cout<<"max:" << TPoint3D<float>(m_maxX, m_maxY, m_maxZ)<<"\n";

	}
}

PointCloud::~PointCloud()
{

}
