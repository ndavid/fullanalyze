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

#include "boost/filesystem.hpp"
using namespace boost::filesystem;

#include "LidarFormat/LidarDataContainer.h"
#include "LidarFormat/LidarIOFactory.h"
#include "LidarFormat/geometry/LidarCenteringTransfo.h"

#include "fullwave/format/FullwaveLidarDataContainer.h"
#include "fullwave/format/FullwaveEcho.h"

#include "FullwaveFile.h"


namespace Lidar
{

FullwaveFile::FullwaveFile(const std::string &xmlFileName):
	LidarFile(xmlFileName)
{
	if(m_isValid)
	{
		if(!m_xmlData->fullwaveMetaData().present())
			m_isValid = false;
	}

}



void FullwaveFile::save(const FullwaveLidarDataContainer& fwContainer, const std::string& xmlFileName, const LidarCenteringTransfo& transfo)
{
	const LidarDataContainer& lidarContainer = fwContainer.getAttributeContainer();
	const cs::DataFormatType format=cs::DataFormatType::binary;

	//génération du fichier xml
	const std::string dataFileName = basename(xmlFileName) + ".bin";
	cs::LidarDataType::AttributesType attributes(dataFileName, lidarContainer.size(), format);

	//insertion des attributs dans le xml (avec leur nom et leur type)
	const AttributeMapType& attributeMap = lidarContainer.getAttributeMap();
	for(AttributeMapType::const_iterator it=attributeMap.begin(); it!=attributeMap.end(); ++it)
	{
		attributes.attribute().push_back(cs::AttributeType(it->second.type, it->first));
	}

	//cas de la transfo
	if(transfo.isSet())
	{
		attributes.centeringTransfo(cs::CenteringTransfoType(transfo.x(), transfo.y()));
	}

	//sauvegarde du xml
	xml_schema::NamespaceInfomap map;
	map[""].name = "cs";
	//map[""].schema = "/src/LidarFormat/models/xsd/format_me.xsd";


	cs::LidarDataType xmlLidarData(attributes);

	const FullwaveGlobalParameter& fwGlobalParam = fwContainer.fwGlobalParameters();
	const std::string fullwaveFileName = basename(xmlFileName) + ".bin-fw";
	cs::FullwaveMetaDataType fwMetaData(fullwaveFileName, fwGlobalParam.m_nbMaxSequences, fwGlobalParam.m_rangeStep, fwGlobalParam.m_nbCol);
	xmlLidarData.fullwaveMetaData(fwMetaData);


	std::ofstream ofs (xmlFileName.c_str());
	cs::lidarData (ofs, xmlLidarData, map);

	//création du writer approprié au format grâce à la factory
	boost::shared_ptr<LidarFileIO> writer = LidarIOFactory::instance().createObject(format);
	writer->save(lidarContainer, path(xmlFileName).branch_path().string() + "/" + dataFileName);


	//sauvegarde des données fw
	//TODO réécrire pour prendre en compte jq à nbSeqMax
	//fait que pour nbMaxSeq = 2

	///ATENTION le fichier fullwave contient un pointeur vers la FIN de chacune des séquences de waveform
	std::ofstream fileOut( (path(xmlFileName).branch_path().string() + "/" + fullwaveFileName).c_str(), std::ios::binary );
	if(fileOut.is_open())
	{
		//pur chaque waveform...
		for(BasicWaveformContainerType::const_iterator itWaveform = fwContainer.getBasicWaveformContainer().begin(); itWaveform != fwContainer.getBasicWaveformContainer().end(); ++itWaveform)
		{
			//séquence d'émission du pulse
			fileOut.write( reinterpret_cast<char*>( &( (*itWaveform)->emittedPulse_.front()) ), (*itWaveform)->emittedPulse_.size() );

			///TODO amélioration possible si on sait que toutes les séquences ont la même longueur -> au moins écrire toutes les séquences d'une même waveform d'un coup
			for(unsigned int i = 0; i<(*itWaveform)->data_.size(); ++i) // = itWaveform->data_.begin(); itSequence != itWaveform->data_.end(); ++itSequence)
			{
				fileOut.write( reinterpret_cast<char*>( &( (*itWaveform)->data_[i].front()) ), (*itWaveform)->data_[i].size() );
			}


		}

	}


}



FullwaveFile::~FullwaveFile()
{

}


} // namespace Lidar
