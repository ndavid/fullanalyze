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

#ifndef FULLWAVECLOUD_H_
#define FULLWAVECLOUD_H_

#include <vector>

#include "boost/shared_ptr.hpp"
using boost::shared_ptr;

#include "LidarFormat/extern/matis/tpoint3d.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"
#include "fullwave/format/FullwaveEcho.h"

#include "3d/Cloud.h"

#include "layers/VectorLayer.hpp"


namespace Lidar
{
	class FullwaveLidarDataContainer;
	class FullwaveSpatialIndexation;

}

class RegionOfInterest2D;


class FullwaveCloud : public Cloud
{
	public:
		enum ViewMode
		{
			SEGMENTS,
			NORMALS,
			SPHERES
		};

		enum ColorMode
		{
			SINGLE_COLOR,
			ATTRIBUTE
		};

		FullwaveCloud(const shared_ptr<const Lidar::FullwaveLidarDataContainer>& fwContainer, const Lidar::LidarCenteringTransfo& transfo, const std::string& name="Default fulwave cloud name");
		virtual ~FullwaveCloud();

		virtual void draw();
		virtual void updateFromCrop(const RegionOfInterest2D& region);
		virtual void updateVisuCrop();


		void colorMode(const ColorMode mode);
		void viewMode(const ViewMode mode);

		const TPoint3D<float>& singleColor() const { return m_singleColor; }
		void singleColor(const TPoint3D<float>& c) { m_singleColor=c; }


		unsigned int ssEchantillonnage() const { return m_ssEchantillonnage; }
		void ssEchantillonnage(const unsigned int ssEch) { m_ssEchantillonnage = ssEch; }

		double ratioAmplitude() const { return m_ratioAmplitude; }
		void ratioAmplitude(const double ratio) { m_ratioAmplitude = ratio; }

		unsigned char sphereDetails() const { return m_sphereDetails; }
		void sphereDetails(const unsigned char details) { m_sphereDetails = details; }


	private:
		shared_ptr<const Lidar::FullwaveLidarDataContainer> m_fwContainer;
		const Lidar::LidarCenteringTransfo m_transfo;

		Lidar::FullwaveEchoHelper m_fwHelper;

		///Indexation spatiale pour crop
		shared_ptr<Lidar::FullwaveSpatialIndexation> m_spatialIndexation;
		bool m_spatialIndexationIsSet;

		typedef std::vector<unsigned int> ListePointsType;
		ListePointsType m_listPoints;


		///Affichage du fw cloud
		ViewMode m_viewMode;

		ColorMode m_colorMode;
		TPoint3D<float> m_singleColor;
		unsigned int m_ssEchantillonnage;

		////spheres settings
		//ratio amplitude de l'onde/taille suivant la (une) normale
		double m_ratioAmplitude;
		unsigned char m_sphereDetails;

		///FW cloud footprints
		Layer::ptrLayerType m_layerFootprints;


		void initCentering();

		void drawCloudSegment() const;
		void drawSpheres() const;
		void drawNormals() const;
};

#endif /* FULLWAVECLOUD_H_ */
