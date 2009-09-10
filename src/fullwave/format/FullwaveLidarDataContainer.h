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

#ifndef FULLWAVELIDARDATACONTAINER_H_
#define FULLWAVELIDARDATACONTAINER_H_


#include <vector>
#include <boost/shared_ptr.hpp>


#include "Waveform.h"
#include "WaveformIterator.h"
#include "LidarFormat/LidarDataContainer.h"

namespace Lidar
{

class LidarCenteringTransfo;

struct FullwaveGlobalParameter
{
	FullwaveGlobalParameter():m_nbMaxSequences(0), m_rangeStep(0), m_nbCol(0){}
	FullwaveGlobalParameter(const unsigned int nbMaxSequences, const double rangeStep, const unsigned int nbCol):
		m_nbMaxSequences(nbMaxSequences), m_rangeStep(rangeStep), m_nbCol(nbCol)
		{}
	unsigned int m_nbMaxSequences;
	double m_rangeStep;
	unsigned int m_nbCol; //Attention ! utilisable seulement pour une géométrie d'acquisition 2D (pas profileur) et un fichier qui contient 1 profil par pixel (sans trou et dans le bon ordre)
};



class FullwaveLidarDataContainer
{
	public:
		typedef BasicWaveform::FWAmplitudeType FWAmplitudeType;

		FullwaveLidarDataContainer(const std::string &xmlFileName); //attention ne charge que les attributs, pas les ondes (=amplitude)
		FullwaveLidarDataContainer(const double rangeStep, const unsigned int nbMaxSequences, const unsigned int nbCol);

		void LoadWaveforms(); //charge les ondes

		void reserve(const std::size_t nbProfilsFW);
		void push_back(const LidarEcho& fwAttributes, const boost::shared_ptr<BasicWaveform> &waveform);
		void clear();
		inline std::size_t size() const;

		void save(const std::string &xmlFileName, const LidarCenteringTransfo& transfo) const;

		///attention
//		FullwaveEcho getFWAttributes(); //permet d'initialiser un écho avec les map d'attributs et de décalage fw, et la taille de l'écho, mais sans valeur des attributs !!

		inline const FullwaveGlobalParameter& fwGlobalParameters() const;
		inline FullwaveGlobalParameter& fwGlobalParameters();


		inline WaveformIterator begin();
		inline WaveformIterator end();
		inline WaveformConstIterator begin() const;
		inline WaveformConstIterator end() const;

		inline LidarIteratorEcho beginEcho();
		inline LidarIteratorEcho endEcho();
		inline LidarConstIteratorEcho beginEcho() const;
		inline LidarConstIteratorEcho endEcho() const;

		void printHeaderAttribut(std::ostream &os);


		///Data accessors
		inline const LidarEcho getAttribute(const unsigned int index) const;
		inline const LidarEcho getAttribute(const unsigned int col, const unsigned int row) const;
		inline const shared_ptr<BasicWaveform> getBasicWaveform(const unsigned int index) const;
		inline const shared_ptr<BasicWaveform> getBasicWaveform(const unsigned int col, const unsigned int row) const;


		///Passage de géométrie 1D/2D : valable seulement pour les acquisitions 2D
		inline void indexToColRow(const unsigned int index, unsigned int& col, unsigned int& row) const;
		inline const unsigned int indexFromColRow(const unsigned int col, const unsigned int row) const;
		inline const unsigned int getNbRows() const;
		inline const unsigned int getNbCols() const;

		inline const double getRangeStep() const;

		const AttributeMapType getAttributeMap() const { return m_attributeData.getAttributeMap(); }

		const LidarDataContainer& getAttributeContainer() const { return m_attributeData; }
		const BasicWaveformContainerType& getBasicWaveformContainer() const { return m_fullwaveData; }

		void setAttributeContainer(const LidarDataContainer& container) { m_attributeData = container; }


	private:
		//non-implemented on purpose for time being
		FullwaveLidarDataContainer(const FullwaveLidarDataContainer&);
		void operator=(const FullwaveLidarDataContainer&);

		std::string m_fileIntensities; //fichier qui contient les données d'amplitude des ondes lidar
		LidarDataContainer m_attributeData;
		BasicWaveformContainerType m_fullwaveData;

		FullwaveGlobalParameter m_fwGlobalParameters;

};



///Implémentations inline

inline WaveformIterator FullwaveLidarDataContainer::begin()
{
	return WaveformIterator(beginEcho(), m_fullwaveData.begin());
}

inline WaveformIterator FullwaveLidarDataContainer::end()
{
	return WaveformIterator(endEcho(), m_fullwaveData.end());
}

inline WaveformConstIterator FullwaveLidarDataContainer::begin() const
{
	return WaveformConstIterator(beginEcho(), m_fullwaveData.begin());
}

inline WaveformConstIterator FullwaveLidarDataContainer::end() const
{
	return WaveformConstIterator(endEcho(), m_fullwaveData.end());
}

inline LidarIteratorEcho FullwaveLidarDataContainer::beginEcho()
{
	return m_attributeData.begin();
}

inline LidarIteratorEcho FullwaveLidarDataContainer::endEcho()
{
	return m_attributeData.end();
}

inline LidarConstIteratorEcho FullwaveLidarDataContainer::beginEcho() const
{
	return m_attributeData.begin();
}

inline LidarConstIteratorEcho FullwaveLidarDataContainer::endEcho() const
{
	return m_attributeData.end();
}

inline FullwaveGlobalParameter& FullwaveLidarDataContainer::fwGlobalParameters()
{
	return m_fwGlobalParameters;
}

inline const FullwaveGlobalParameter& FullwaveLidarDataContainer::fwGlobalParameters() const
{
	return m_fwGlobalParameters;
}

inline void FullwaveLidarDataContainer::indexToColRow(const unsigned int index, unsigned int& col, unsigned int& row) const
{
	col = index % getNbCols();
	row = index / getNbCols();
}

inline const unsigned int FullwaveLidarDataContainer::indexFromColRow(const unsigned int col, const unsigned int row) const
{
	return row * getNbCols() + col;
}

inline const unsigned int FullwaveLidarDataContainer::getNbRows() const
{
	return size() / getNbCols();
}

inline const unsigned int FullwaveLidarDataContainer::getNbCols() const
{
	return m_fwGlobalParameters.m_nbCol;
}

inline const double FullwaveLidarDataContainer::getRangeStep() const
{
	return m_fwGlobalParameters.m_rangeStep;
}

inline std::size_t FullwaveLidarDataContainer::size() const
{
	return m_attributeData.size();
}

inline const shared_ptr<BasicWaveform> FullwaveLidarDataContainer::getBasicWaveform(const unsigned int index) const
{
	return *(m_fullwaveData.begin() + index);
}

inline const shared_ptr<BasicWaveform> FullwaveLidarDataContainer::getBasicWaveform(const unsigned int col, const unsigned int row) const
{
	return getBasicWaveform(indexFromColRow(col, row));
}


//const FullwaveEcho FullwaveLidarDataContainer::getAttribute(const unsigned int index) const
//{
//	return m_attributeData[index];
//}
//
//const FullwaveEcho FullwaveLidarDataContainer::getAttribute(const unsigned int col, const unsigned int row) const
//{
//	return m_attributeData[indexFromColRow(col,row)];
//}



} //namespace Lidar

#endif /* FULLWAVELIDARDATACONTAINER_H_ */
