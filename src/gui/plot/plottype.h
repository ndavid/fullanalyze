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

#ifndef PLOTTYPE_H_
#define PLOTTYPE_H_

#include <set>
#include <vector>
#include <map>

#include <string>

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;
#include <boost/function.hpp>

#include "LidarFormat/extern/matis/tpoint2d.h"
#include "LidarFormat/extern/matis/tpoint3d.h"

///////////Types de donnees de base pour les plots

//Points
class PlotPoint
{
public:
	static const double NO_ATTRIBUT;

	PlotPoint(){}
	PlotPoint(const double& x, const double& y, const double& value = NO_ATTRIBUT): m_x(x), m_y(y), m_value(value){}

	//Accesseurs
	const double GetX() const {return m_x;}
	const double GetY() const {return m_y;}
	const double GetValue() const {return m_value;}
	double &GetValue() { return m_value; }

	PlotPoint &operator*(const double value)
	{
		m_value *= value;
		return *this;
	}


private:
	double m_x;
	double m_y;
	double m_value;
};
//Pointeur sur Point
typedef shared_ptr<PlotPoint> t_ptrPlotPoint;


// Définition du foncteur servant à trier les pointeurs de points
struct SortByAbscisse
{
   bool operator ()(const t_ptrPlotPoint& p1, const t_ptrPlotPoint& p2) const
   {
      return p1->GetX() < p2->GetX();
   }
};

struct SortByOrdonnee
{
   bool operator ()(const t_ptrPlotPoint& p1, const t_ptrPlotPoint& p2) const
   {
      return p1->GetY() < p2->GetY();
   }
};

struct SortByValue
{
   bool operator ()(const t_ptrPlotPoint& p1, const t_ptrPlotPoint& p2) const
   {
      return p1->GetValue() < p2->GetValue();
   }
};


//Courbe = ensemble de PlotPoint(s) (=Courbe ou nuage de points)
class PlotCourbe
{
public:
	typedef std::set<t_ptrPlotPoint, SortByAbscisse> t_PlotCourbeContainer;
	typedef t_PlotCourbeContainer::iterator iterator;
	typedef t_PlotCourbeContainer::const_iterator const_iterator;

	PlotCourbe(){}
	//Création d'une courbe à partir d'un std::vector
	template<typename T>
	PlotCourbe(const std::vector<T> & tab, const double min, const double max)
	{
		double pas;
		if (tab.size()>1)
			pas = (max - min)/(tab.size()-1);
		else
			pas = 0;

		for (std::size_t i=0; i<tab.size(); ++i)
		{
			t_ptrPlotPoint ptrPt(new PlotPoint(min + i*pas,tab[i]));
			m_listePoints.insert(ptrPt);
		}
	}

	template<typename T>
	PlotCourbe(const std::vector<T> & tab)
	{
		for (std::size_t i=0; i<tab.size(); ++i)
		{
			t_ptrPlotPoint ptrPt(new PlotPoint(i,tab[i]));
			m_listePoints.insert(ptrPt);
		}
	}

	void AddPoint(const PlotPoint& pt);

	double GetMiniX() const;
	double GetMaxiX() const;
	double GetMiniY() const;
	double GetMaxiY() const;
	double GetMiniValue() const;
	double GetMaxiValue() const;

	void Normalize(const double maxi = 1.);

	//Iterateurs
	const_iterator begin() const{return m_listePoints.begin();}
	iterator begin() {return m_listePoints.begin();}
	const_iterator end() const{return m_listePoints.end();}
	iterator end() {return m_listePoints.end();}

	size_t size() const { return m_listePoints.size(); }
	bool empty() const { return m_listePoints.empty(); }
private:
	t_PlotCourbeContainer m_listePoints;

};
//Pointeur sur Courbe
typedef shared_ptr<PlotCourbe> t_ptrPlotCourbe;
typedef shared_ptr<const PlotCourbe> t_ptrPlotCourbeConst;

//Sequence de courbes = suite de PlotCourbe(s)
class PlotSequenceCourbes
{
public:
	PlotSequenceCourbes(){}
	PlotSequenceCourbes(const int& taille, const TPoint3D<int>& color = TPoint3D<int>(0,0,0)):m_listeCourbes(taille),m_color(color){}

	t_ptrPlotCourbe& operator[] (int i){return m_listeCourbes[i];}
	const t_ptrPlotCourbe& operator[] (int i) const {return m_listeCourbes[i];}

	const size_t size() const {return m_listeCourbes.size();}

	const int& GetColorR(){return m_color.x;}
	const int& GetColorG(){return m_color.y;}
	const int& GetColorB(){return m_color.z;}

private:
	std::vector<t_ptrPlotCourbe> m_listeCourbes;
	TPoint3D<int> m_color; //Couleur pour toute la séquence de courbes
};

//Pointeur sur Sequence de courbes
typedef shared_ptr<PlotSequenceCourbes> t_ptrPlotSequenceCourbes;


//Conteneur des donnees de plot (contient les sequences de courbes)
class PlotDataContainer
{
public:
	typedef std::map<std::string , t_ptrPlotSequenceCourbes> t_PlotDataContainer;
	typedef t_PlotDataContainer::iterator iterator;
	typedef t_PlotDataContainer::const_iterator const_iterator;

	PlotDataContainer(){}

	//Fonctions etendues du std::map
	//t_ptrPlotSequenceCourbes& operator[] (int i){return m_listeSequences[i];}
	const size_t size() const {return m_listeSequences.size();}
	bool empty() const {return m_listeSequences.empty();}
	bool insert(const std::string& name, const t_ptrPlotSequenceCourbes& ptrSeq) {return m_listeSequences.insert(t_PlotDataContainer::value_type(name,ptrSeq)).second;}
	const_iterator find(const std::string& courbe) const {return m_listeSequences.find(courbe);}

	//Iterateurs
	const_iterator begin() const{return m_listeSequences.begin();}
	iterator begin() {return m_listeSequences.begin();}
	const_iterator end() const{return m_listeSequences.end();}
	iterator end() {return m_listeSequences.end();}
private:
	std::map<std::string, t_ptrPlotSequenceCourbes> m_listeSequences;
};

typedef shared_ptr<PlotDataContainer> t_ptrPlotDataContainer;
typedef shared_ptr<const PlotDataContainer> t_ptrConstPlotDataContainer;



class PlotType
{
public:
	enum t_TypeCouleur { COULEUR_COURBE, COULEUR_POINTS};
	enum t_TypeTrace {TRACE_COURBE, TRACE_POINTS};

    PlotType():m_dataPlot(new PlotDataContainer()){}
    virtual ~PlotType(){}

    void setPlotNotifier(const boost::function<void()>& notifyPlotFrame)
    {
    	m_notifyPlotFrame = notifyPlotFrame;
    }

    const t_ptrConstPlotDataContainer GetDataPlotContainer() const {return m_dataPlot;}

    //Accesseurs de la config
    const double GetMaxiX() const {return m_maxiX; }
    const double GetMaxiY() const {return m_maxiY; }
    const double GetMiniX() const {return m_miniX; }
    const double GetMiniY() const {return m_miniY; }
    const double GetMiniValue() const {return m_miniValue; }
    const double GetMaxiValue() const {return m_maxiValue; }

    const t_TypeCouleur GetTypeCouleur() const {return m_typeCouleur;}
    const t_TypeTrace GetTypeTrace() const {return m_typeTrace;}

    //Modificateurs de la config
    void SetTypeCouleur(const t_TypeCouleur& color) {m_typeCouleur = color;}
    void SetTypeTrace(const t_TypeTrace& trace) {m_typeTrace = trace;}

protected:
    //donnees du plot
    t_ptrPlotDataContainer m_dataPlot;

    ////////Config du plot

    //Config de mode d'affichage des couleurs : par courbe (tous les points d'une courbe ont la même couleur) ou par points
    t_TypeCouleur m_typeCouleur;

    //Config du mode d'affichage de la courbe : affichage des segments entre chaque point (courbe) ou que les points
    t_TypeTrace m_typeTrace;

    //Bornes de la fenêtre graphique (abscisses, ordonnées, et valeur d'attribut)
    double m_maxiX,m_maxiY;
    double m_miniX,m_miniY;
    double m_miniValue, m_maxiValue;

    boost::function<void()> m_notifyPlotFrame;


};

typedef shared_ptr<PlotType> t_ptrPlotType;

#endif /*PLOTTYPE_H_*/
