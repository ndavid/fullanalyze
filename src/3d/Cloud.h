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
