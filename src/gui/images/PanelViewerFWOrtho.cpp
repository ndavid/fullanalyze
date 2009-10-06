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

#include <boost/bind.hpp>

#include "gui/PanelManager.h"

#include "boost/shared_ptr.hpp"

#include "layers/VectorLayer.hpp"

////si GIL
#include "layers/ImageLayer.hpp"

#include "extern/gil/extension/matis/float_images.hpp"
#include <boost/gil/extension/io/tiff_io.hpp>
////si ITK
//#include "layers/NewImageLayer.h"


#include "layers/VectorLayerGhost.h"
#include "layers/VectorLayerContent.hpp"
#include "gui/LayerControl.hpp"

#include "LidarFormat/geometry/RegionOfInterest2D.h"

#include "PanelViewerFWOrtho.h"

PanelViewerFWOrtho::PanelViewerFWOrtho(wxFrame *parent) :
	PanelViewerFW(parent)
{

}

PanelViewerFWOrtho::~PanelViewerFWOrtho()
{
}

void PanelViewerFWOrtho::AddLayerCarto(const std::string &fileName)
{
	////si GIL
	Layer::ptrLayerType layerCarto = ImageLayer::CreateImageLayer(fileName);
	////si ITK
//	Layer::ptrLayerType layerCarto = Layers::NewImageLayer(fileName);

	AddLayer( layerCarto );
	Refresh();
}


void PanelViewerFWOrtho::setCropCallback(const boost::function<void(const RegionOfInterest2D&)> cropCallback)
{
	m_cropCallback = cropCallback;
}

void PanelViewerFWOrtho::setPointCallback(const boost::function<void(const TPoint2D<double>&)> pointCallback)
{
	m_pointCallback = pointCallback;
}


void PanelViewerFWOrtho::executeModeGeometryMoving()
{

	Orientation2D ori;
	if (GetLayerControl()->IsOriented())
	{
		ori = GetLayerControl()->GetOrientation();
	}
	else
		throw std::logic_error( "L'ortho ne contient pas d'orientation !! dans PanelViewerFWOrtho::executeModeGeometryMoving \n" );


	//si la sélection est active
	if (m_geometry == GEOMETRY_POINT)
	{
		TPoint2D<double> pt(m_ghostLayer.m_pointPosition.x, m_ghostLayer.m_pointPosition.y);
		pt.x = ori.OriginX() + ori.Step() * pt.x;
		pt.y = ori.OriginY() - ori.Step() * pt.y;

		if(m_pointCallback)
			m_pointCallback(pt);
	}
	else if (m_geometry == GEOMETRY_RECTANGLE)
	{
		std::pair<TPoint2D<double>,TPoint2D<double> > paire = GetSelection();

		//on passe la sélection en coord carto :
		paire.first.x = ori.OriginX() + ori.Step() * paire.first.x;
		paire.first.y = ori.OriginY() - ori.Step() * paire.first.y;
		paire.second.x = ori.OriginX() + ori.Step() * paire.second.x;
		paire.second.y = ori.OriginY() - ori.Step() * paire.second.y;

		//on lance le crop :
		if(m_cropCallback)
			m_cropCallback(RectangularRegionOfInterest2D(paire.first, paire.second));

	}
	else if(m_geometry == GEOMETRY_CIRCLE)
	{
		TPoint2D<double> centre(m_ghostLayer.m_circle.first.x, m_ghostLayer.m_circle.first.y);
		centre.x = ori.OriginX() + ori.Step() * centre.x;
		centre.y = ori.OriginY() - ori.Step() * centre.y;

//		std::cout << "geometry moving cercle : " << centre << " ; rayon = " << m_ghostLayer.m_circle.second << std::endl;

		//on lance le crop :
		if(m_cropCallback)
			m_cropCallback(CircularRegionOfInterest2D(centre, ori.Step() * m_ghostLayer.m_circle.second));

	}
}



void PanelViewerFWOrtho::showStrip(const std::vector<double>& stripX, const std::vector<double>& stripY, const std::string& stripName)
{
	Layer::ptrLayerType layerArc = VectorLayer::CreateVectorLayer( stripName, SHPT_ARC, CARTOGRAPHIC_COORDINATES, false );
	AddLayer( layerArc );

	std::cout << "size x=" << stripX.size() << " ; size y=" << stripY.size() << "\n";

	boost::shared_ptr<VectorLayer> vectorLayerArc = boost::dynamic_pointer_cast<VectorLayer>(layerArc);

	VectorLayer& vect = *vectorLayerArc;
	vect.AddPolyline(stripX, stripY);
//	vect.AddPolygon(stripX, stripY);

	Refresh();
}

void PanelViewerFWOrtho::OpenCustomFormat( const std::string &filename )
{
//TODO to be cleaned and re implemented
//	///Charger et afficher le nuage de pts en 2D sur l'ortho
//	Layer::ptrLayerType layerPointRoad = VectorLayer::CreateVectorLayer( filename, SHPT_POINT, CARTOGRAPHIC_COORDINATES, false );
//	AddLayer( layerPointRoad );
//	Layer::ptrLayerType layerPointRock = VectorLayer::CreateVectorLayer( filename, SHPT_POINT, CARTOGRAPHIC_COORDINATES, false );
//	AddLayer( layerPointRock );
//	Layer::ptrLayerType layerPointVeget = VectorLayer::CreateVectorLayer( filename, SHPT_POINT, CARTOGRAPHIC_COORDINATES, false );
//	AddLayer( layerPointVeget );
//	Layer::ptrLayerType layerPointLand = VectorLayer::CreateVectorLayer( filename, SHPT_POINT, CARTOGRAPHIC_COORDINATES, false );
//	AddLayer( layerPointLand );
//	Layer::ptrLayerType layerPointAll = VectorLayer::CreateVectorLayer( filename, SHPT_POINT, CARTOGRAPHIC_COORDINATES, false );
////	AddLayer( layerPointAll );
//
//	RecordEcho echo_bin;
//
//	std::cout << "Fichier : " << filename << "\n";
//
//	Chantier monChantierVide;
//	Calculs mesCalculs( monChantierVide );
//
//	//Ouverture du fichier d'echos à charger
//	if (!mesCalculs.OpenReadFileAbsolutePath( filename ))
//		throw std::logic_error( "Erreur a l'ouverture du fichier d'echos en lecture dans PanelViewerFWOrtho::OpenCustomFormat !\n" );
//	else
//		std::cout << "Ouverture du fichier d'echos en lecture OK.\n";
//
//    boost::shared_ptr<VectorLayer> vectorLayerPointRoad = boost::dynamic_pointer_cast<VectorLayer,Layer>(layerPointRoad);
//    boost::shared_ptr<VectorLayer> vectorLayerPointRock = boost::dynamic_pointer_cast<VectorLayer,Layer>(layerPointRock);
//    boost::shared_ptr<VectorLayer> vectorLayerPointVeget = boost::dynamic_pointer_cast<VectorLayer,Layer>(layerPointVeget);
//    boost::shared_ptr<VectorLayer> vectorLayerPointLand = boost::dynamic_pointer_cast<VectorLayer,Layer>(layerPointLand);
//    boost::shared_ptr<VectorLayer> vectorLayerPointAll = boost::dynamic_pointer_cast<VectorLayer,Layer>(layerPointAll);
//
//	while (mesCalculs.FileReadNextStats( echo_bin ))
//	{
//		switch(echo_bin.m_classif)
//		{
//			case 2:
//				vectorLayerPointRoad->AddPoint( echo_bin.m_x, echo_bin.m_y+1.e6);
//				break;
//			case 3:
//				vectorLayerPointRock->AddPoint( echo_bin.m_x, echo_bin.m_y+1.e6);
//				break;
//			case 5:
//				vectorLayerPointLand->AddPoint( echo_bin.m_x, echo_bin.m_y+1.e6);
//				break;
//			case 7:
//				vectorLayerPointVeget->AddPoint( echo_bin.m_x, echo_bin.m_y+1.e6);
//				break;
//		}
//
//		vectorLayerPointAll->AddPoint( echo_bin.m_x, echo_bin.m_y+1.e6);
//
//	}



//	/////Emprise
//
//	///Charger le nuage de pts, calculer son emprise et l'afficher en 2D sur l'ortho
//	Layer::ptrLayerType layerPolygon = VectorLayer::CreateVectorLayer( filename, SHPT_POLYGON, CARTOGRAPHIC_COORDINATES, false );
//	AddLayer( layerPolygon );
//
//	Chantier monChantierVide;
//	Calculs mesCalculs( m_chantier );
//	std::list<RecordEcho> listeBordBande;
//	mesCalculs.Emprise2Shp(filename, listeBordBande);
//
//	std::size_t taille = listeBordBande.size();
////	std::cout<<"liste size"<<taille<<" \n";
//
//	std::vector<double> x,y;
//	x.reserve(taille);
//	y.reserve(taille);
//
//	for(std::list<RecordEcho>::iterator it = listeBordBande.begin(); it != listeBordBande.end(); ++it)
//	{
//		x.push_back(it->m_x);
//		y.push_back(it->m_y+1.e6);
//	}
//
//
//	layerPolygon->AddPolygon(x,y);



}

PanelViewerFWOrtho* createPanelViewerFWOrtho(wxFrame* parent)
{
	return new PanelViewerFWOrtho(parent);
}

void PanelViewerFWOrtho::Register(wxFrame* parent)
{
	PanelManager::Instance()->Register("PanelViewerFWOrtho", boost::bind(createPanelViewerFWOrtho, parent));
}
