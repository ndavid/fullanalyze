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

#include <string>
#include <sstream>
#include <stdexcept>

#include "boost/filesystem.hpp"

#include "LidarFormat/extern/matis/tpoint3d.h"

#include "LidarFormat/LidarFile.h"

#include "FullwaveEcho.h"

#include "FullwaveLidarDataContainer.h"


namespace Lidar
{


void FullwaveLidarDataContainer::printHeaderAttribut(std::ostream &os)
{
	m_attributeData.printHeader(os);
}

void FullwaveLidarDataContainer::save(const std::string &xmlFileName, const LidarCenteringTransfo& transfo) const
{
	using namespace boost::filesystem;

	//récupération de l'arbre xml du container lidar
	shared_ptr<cs::LidarDataType> xmlLidarData = LidarFile::createXMLStructure(m_attributeData, xmlFileName, transfo);

	//ajout des méta-données fw dans l'arbre xml
	const std::string fullwaveFileName = basename(xmlFileName) + ".bin-fw";

	cs::FullwaveMetaDataType fwMetaData(fullwaveFileName, m_fwGlobalParameters.m_nbMaxSequences, m_fwGlobalParameters.m_rangeStep, m_fwGlobalParameters.m_nbCol);
	xmlLidarData->fullwaveMetaData(fwMetaData);

	//sauvegarde des données fw
	//TODO réécrire pour prendre en compte jq à nbSeqMax
	//fait que pour nbMaxSeq = 2

	///ATENTION le fichier fullwave contient un pointeur vers la FIN de chacune des séquences de waveform
	std::ofstream fileOut( (path(xmlFileName).branch_path().string() + "/" + fullwaveFileName).c_str(), std::ios::binary);
	if(fileOut.is_open())
	{
		//pur chaque waveform...
		for(BasicWaveformContainerType::const_iterator itWaveform = m_fullwaveData.begin(); itWaveform != m_fullwaveData.end(); ++itWaveform)
		{
			//on parcourt les séquences

			//séquence d'émission du pulse
			fileOut.write( reinterpret_cast<char*>( &( (*itWaveform)->emittedPulse_.front()) ), (*itWaveform)->emittedPulse_.size() );

			///TODO amélioration possible si on sait que toutes les séquences ont la même longueur -> au moins écrire toutes les séquences d'une même waveform d'un coup
			for(unsigned int i = 0; i<(*itWaveform)->data_.size(); ++i) // = itWaveform->data_.begin(); itSequence != itWaveform->data_.end(); ++itSequence)
			{
				fileOut.write( reinterpret_cast<char*>( &( (*itWaveform)->data_[i].front()) ), (*itWaveform)->data_[i].size() );
			}


//Chargement brutal du fichier ? test de l'emprise avec juste le premier point de la séquence ? (mais nécessite indexation)
//Ou test directement dans affichage 3D...

		}

	}

	std::cout << "taille du tableau de waveforms : " << m_fullwaveData.size() << std::endl;

	//sauvegarde du fichier xml et container d'attributs
	LidarFile::save(m_attributeData, xmlFileName, *xmlLidarData);

}

void FullwaveLidarDataContainer::clear()
{
	m_attributeData.clear();
	m_fullwaveData.clear();
}

void FullwaveLidarDataContainer::push_back(const LidarEcho& fwAttributes, const boost::shared_ptr<BasicWaveform> &waveform)
{
	m_attributeData.push_back(fwAttributes);
	m_fullwaveData.push_back(waveform);
}

//FullwaveEcho FullwaveLidarDataContainer::getFWAttributes()
//{
//	return m_attributeData.getEchoAttributes();
//}


void FullwaveLidarDataContainer::reserve(const std::size_t nbProfilsFW)
{
	m_attributeData.reserve(nbProfilsFW);
	m_fullwaveData.reserve(nbProfilsFW);
}


FullwaveLidarDataContainer::FullwaveLidarDataContainer(const double rangeStep, const unsigned int nbMaxSequences, const unsigned int nbCol):
	m_fwGlobalParameters(nbMaxSequences, rangeStep, nbCol)
{
	//génération des attributs nécessaires pour le FW
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringGPSTime, LidarTypeTraits<FWGPSTimeType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringEmissionAngle, LidarTypeTraits<FWEmissionAngleType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringOriginX, LidarTypeTraits<FWOriginType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringOriginY, LidarTypeTraits<FWOriginType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringOriginZ, LidarTypeTraits<FWOriginType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringDirectionX, LidarTypeTraits<FWDirectionType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringDirectionY, LidarTypeTraits<FWDirectionType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringDirectionZ, LidarTypeTraits<FWDirectionType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringEmissionPulseSequenceFilePointer, LidarTypeTraits<FWFilePointerType>::enum_type);
	m_attributeData.addAttribute(FullwaveEchoHelper::m_stringEmissionPulseSequenceRangeBegin, LidarTypeTraits<FWRangeBeginType>::enum_type);


	//génération des attributs de séquences
	for(unsigned int i=1; i<= nbMaxSequences; ++i)
	{
		m_attributeData.addAttribute(FullwaveEchoHelper::stringNthSequenceFilePointer(i), LidarTypeTraits<FWFilePointerType>::enum_type);
		m_attributeData.addAttribute(FullwaveEchoHelper::stringNthSequenceRangeBegin(i), LidarTypeTraits<FWRangeBeginType>::enum_type);
	}
}





void FullwaveLidarDataContainer::LoadWaveforms()
{
	//chargement des données fw
	//TODO réécrire pour prendre en compte jq à nbSeqMax
	//fait que pour nbMaxSeq = 2

	m_fullwaveData.reserve(m_attributeData.size());

	///ATENTION le fichier fullwave contient un pointeur vers la FIN de chacune des séquences de waveform
	std::ifstream fileIn( m_fileIntensities.c_str(), std::ios::binary );
	std::size_t fileLastPosition = 0;
	unsigned int taille = 0;
	if(fileIn.is_open())
	{
		LidarIteratorAttribute<FWFilePointerType> itSeqEmission = m_attributeData.beginAttribute<FWFilePointerType>(FullwaveEchoHelper::m_stringEmissionPulseSequenceFilePointer);
		LidarIteratorAttribute<FWFilePointerType> itSeq1 = m_attributeData.beginAttribute<FWFilePointerType>(FullwaveEchoHelper::stringNthSequenceFilePointer(1));
		LidarIteratorAttribute<FWFilePointerType> itSeq2 = m_attributeData.beginAttribute<FWFilePointerType>(FullwaveEchoHelper::stringNthSequenceFilePointer(2));

//		std::cout << "pour chaque waveform " << std::endl;

		//pour chaque waveform...
		const LidarIteratorAttribute<FWFilePointerType> ite = m_attributeData.endAttribute<FWFilePointerType>(FullwaveEchoHelper::m_stringEmissionPulseSequenceFilePointer);
		for(; itSeqEmission != ite; ++itSeqEmission, ++itSeq1, ++itSeq2)
		{
			boost::shared_ptr<Lidar::BasicWaveform> uneWaveform( new Lidar::BasicWaveform );

			//lecture de la séquence d'émission du pulse
			taille = *itSeqEmission - fileLastPosition;
//			std::cout << "*itSeqEmission " << *itSeqEmission << std::endl;

			uneWaveform->emittedPulse_.resize(taille);
//			std::cout << "taille émission : " << taille << std::endl;
			fileIn.read( reinterpret_cast<char*>( &( uneWaveform->emittedPulse_.front()) ), taille );
			fileLastPosition += taille;

			//lecture de la première séquence si présente
			if( *itSeq1 > fileLastPosition )
			{
				uneWaveform->data_.resize(1);
//				std::cout << "*itSeq1 " << *itSeq1 << std::endl;
				taille = *itSeq1 - fileLastPosition;
				uneWaveform->data_[0].resize(taille);
//				std::cout << "taille seq1 : " << taille << std::endl;
				fileIn.read( reinterpret_cast<char*>( &( uneWaveform->data_[0].front()) ), taille );
				fileLastPosition += taille;
			}

			//lecture de la deuxième séquence si présente
			if( *itSeq2 > fileLastPosition )
			{
				uneWaveform->data_.resize(2);
//				std::cout << "*itSeq2 " << *itSeq2 << std::endl;
				taille = *itSeq2 - fileLastPosition;
				uneWaveform->data_[1].resize(taille);
//				std::cout << "taille seq2 : " << taille << std::endl;
				fileIn.read( reinterpret_cast<char*>( &( uneWaveform->data_[1].front()) ), taille );
				fileLastPosition += taille;
			}

			m_fullwaveData.push_back(uneWaveform);

		}

	}

}


FullwaveLidarDataContainer::FullwaveLidarDataContainer(const std::string &xmlFileName)
{
	///chargement des attributs
	LidarFile fichierLidar(xmlFileName);
	fichierLidar.loadData(m_attributeData);


	//récupération des méta données fw
	std::auto_ptr<cs::LidarDataType> xmlLidarData( cs::lidarData( xmlFileName, xml_schema::Flags::dont_validate ) );

	if(	!xmlLidarData->fullwaveMetaData().present() )
		throw std::logic_error("Wrong FW format ! No fw meta data !\n");

	cs::FullwaveMetaDataType fwMetaData = xmlLidarData->fullwaveMetaData().get();
	m_fwGlobalParameters.m_nbCol = fwMetaData.nbCol();
	m_fwGlobalParameters.m_nbMaxSequences = fwMetaData.nbMaxSequences();
	m_fwGlobalParameters.m_rangeStep = fwMetaData.rangeStep();

	using namespace boost::filesystem;
	m_fileIntensities = path(xmlFileName).branch_path().string() + "/" + fwMetaData.fullwaveFileName();

}


} //namespace LidarDataFormat


