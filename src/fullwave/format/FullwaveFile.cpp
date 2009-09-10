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
