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

#ifndef CLOUD_H_
#define CLOUD_H_

#include <boost/function.hpp>

#include "LidarFormat/extern/matis/tpoint3d.h"

class RegionOfInterest2D;

class Cloud
{
public:

	Cloud(const boost::function<void()> &notifyCloudControl = boost::function<void()>(), const boost::function<void()> &notifyCloudSettingsControl = boost::function<void()>()):
		m_isEmpty(true), m_isVisible(true), m_name("Default cloud name"), m_filename(""), m_notifyCloudControl(notifyCloudControl), m_notifyCloudSettingsControl(notifyCloudSettingsControl) {}

	virtual ~Cloud() {}

	virtual void draw()=0;

	virtual bool isVisible() const { return m_isVisible;}
	virtual void isVisible(const bool visible) { m_isVisible=visible; } // m_notifyCloudControl(); }

	virtual std::string name() const {return m_name;}
	virtual void name(const std::string &name) {m_name=name;}
	virtual std::string filename() const {return m_filename;}
	virtual void filename(const std::string &filename) {m_filename=filename;}

	virtual std::string getInfos() const {return m_infos;}
	virtual void save(const std::string &name) {}

	void setNotifyCloudControl( const boost::function<void()> &notifier ) { m_notifyCloudControl = notifier; }
	void setNotifyCloudSettingsControl( const boost::function<void()> &notifier ) { m_notifyCloudSettingsControl = notifier; }


	///Callback pour updater la visu des nuages après un crop
	virtual void updateFromCrop(const RegionOfInterest2D& region)=0;
	virtual void updateVisuCrop()=0;
	virtual void resetCrop()=0;



	///// Methodes specifiques PointCloud



	///// Methodes specifiques FullwaveCloud


	virtual void clear() {}

	///BBox de la scène : l'initialisation de ces champs est laissée à la classe fille pour l'instant
	float m_maxX, m_minX, m_maxY, m_minY, m_maxZ, m_minZ;

	bool m_isEmpty;


protected:
	bool m_isVisible;
//	bool m_isTransformable;
	// Le nom du layer
	std::string m_name;
	// Le nom du fichier associe si il existe
	std::string m_filename;

	//infos du layer
	std::string m_infos;

//	static wxColour m_defaultPointColour;

	boost::function<void ()> m_notifyCloudControl;
	boost::function<void ()> m_notifyCloudSettingsControl;


	///Anciennes valeurs de centrages des nuages
	TPoint3D< double > m_ptGold;
	double m_maxiOld;




};

#endif /* CLOUD_H_ */
