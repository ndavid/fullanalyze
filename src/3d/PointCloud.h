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

#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include "GL/gl.h"

#include "boost/shared_ptr.hpp"
using boost::shared_ptr;

#include "LidarFormat/extern/matis/tpoint3d.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "Cloud.h"

///debug
#include "layers/VectorLayer.hpp"

namespace Lidar
{
	class LidarDataContainer;
	class LidarSpatialIndexation2D;
}

class RegionOfInterest2D;


class PointCloud: public Cloud
{
	public:

		enum ColorMode
		{
			SINGLE_COLOR,
			ATTRIBUTE,
			RGB
		};

		PointCloud(const shared_ptr<Lidar::LidarDataContainer>& lidarContainer, const Lidar::LidarCenteringTransfo& transfo, const std::string& name="Default point cloud name");
		virtual ~PointCloud();




		virtual void draw();

		void getAttributeList(std::vector<std::string>& liste);

		void minmax(const std::string &attributeName, double& mini, double &maxi) const;


		void setTextureAttributeName(const std::string& name) { m_textureAttributeName = name; }
		void generateTexture(const std::string& fileLUTName);

		void setRedAttributeName(const std::string& name) { m_redAttributeName = name; }

		void colorMode(const ColorMode mode);

		const TPoint3D<float>& singleColor() const { return m_singleColor; }
		void singleColor(const TPoint3D<float>& c) { m_singleColor=c; }

		const unsigned int pointSize() const { return m_ptSize; }
		void pointSize(const unsigned int ptSize) { m_ptSize = ptSize; }

		const unsigned int ssEchantillonnage() const { return m_ssEchantillonnage; }
		void ssEchantillonnage(const unsigned int ssEch) { m_ssEchantillonnage = ssEch; }

		void updateFromCrop(const RegionOfInterest2D& region);

		///Texture matrice
		float m_textureMat[16];

	private:
		shared_ptr<Lidar::LidarDataContainer> m_lidarContainer;
		shared_ptr<Lidar::LidarDataContainer> m_referenceLidarContainer;
		const Lidar::LidarCenteringTransfo m_transfo;

		///debug
		Layer::ptrLayerType m_layerPoints;

		///texture
		GLuint m_texName;

		///Indexation spatiale pour crop
		shared_ptr<Lidar::LidarSpatialIndexation2D> m_spatialIndexation;
		bool m_spatialIndexationIsSet;


		///Texture attribute name
		std::string m_textureAttributeName;
		///Texture data
		GLubyte m_texture1D[3*256]; //3 pour RGB, 256 pour la taille d'une LUT


		///Affichage du point cloud
		ColorMode m_colorMode;
		TPoint3D<float> m_singleColor;
		unsigned int m_ptSize;
		unsigned int m_ssEchantillonnage;

		///RGB red color attribute name
		std::string m_redAttributeName;



		void initCentering();

		void drawPointCloudColor();
		void drawPointCloudTexture();
		void drawPointCloudRGB();
};

#endif /* POINTCLOUD_H_ */
