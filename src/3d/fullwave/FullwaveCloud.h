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

#ifndef FULLWAVECLOUD_H_
#define FULLWAVECLOUD_H_

#include <vector>

#include "boost/shared_ptr.hpp"
using boost::shared_ptr;

#include "LidarFormat/extern/matis/tpoint3d.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"
#include "fullwave/format/FullwaveEcho.h"

#include "3d/Cloud.h"


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


		void initCentering();

		void drawCloudSegment() const;
		void drawSpheres() const;
		void drawNormals() const;
};

#endif /* FULLWAVECLOUD_H_ */
