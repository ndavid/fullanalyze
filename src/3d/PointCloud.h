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

#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include "GL/gl.h"

#include "boost/shared_ptr.hpp"
using boost::shared_ptr;

#include "LidarFormat/extern/matis/tpoint3d.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "Cloud.h"

//debug
//#include "layers/VectorLayer.hpp"

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

//		Layer::ptrLayerType m_layerPoints;

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
