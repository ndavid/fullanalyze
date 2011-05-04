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

#include <fstream>
#include <iostream>

#include "plot.h"


inline wxString CalculeFormatString(const double& value);
inline double Log10(const double& x)
{
	return std::log(x)/std::log(10.0);
}
inline TPoint3D<int> Palette1(const double& value, const double& min, const double& max);

//Plot::Plot(PlotType* typePlot):
Plot::Plot(wxWindow* parent, const shared_ptr<PlotType>& typePlot, const wxString& title, const wxPoint& pos, const wxSize& size) :
	//    wxFrame(parent, -1, title, pos, size, wxRESIZE_BORDER),
			wxPanel(parent, wxID_ANY, wxDefaultPosition, size, wxWANTS_CHARS, wxPanelNameStr), m_frameConfigCalques(NULL), m_plotType(typePlot)
{

	m_dataPlot = m_plotType->GetDataPlotContainer();

	//Creation de la fen de config
	if (m_frameConfigCalques==NULL)
	{
		m_frameConfigCalques=new PlotCalques(this, m_plotType, _("Calques"));
	}

	m_taille_fenetre=size;

}

void Plot::setPlotType(const shared_ptr<PlotType>& typePlot)
{
	m_plotType = typePlot;
	m_dataPlot = m_plotType->GetDataPlotContainer();
	m_frameConfigCalques->setPlotType(m_plotType);
}

Plot::~Plot()
{
}

void Plot::Redraw()
{
	m_dataPlot=m_plotType->GetDataPlotContainer();
	m_frameConfigCalques->UpdateTableauCalques();

	Refresh();
}

void Plot::OnPaint(wxPaintEvent &WXUNUSED(event))
{
	using namespace std;

	wxPaintDC dc(this);
	//Doc wx :
	//This should normally be constructed as a temporary stack object; don't store a wxClientDC object.
	//wxClientDC : en dehors de la fonction OnPaint ; et wxPaintDC : dans la fonction OnPaint

	dc.SetPen(*wxRED);
	//TODO Option background
	dc.SetBackground(*wxBLACK_BRUSH); //pour le fond, en noir
//	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

//	dc.SetBrush(*wxBLACK_BRUSH); //pour le fond, en noir
	//TODO Option
	dc.SetTextForeground(*wxWHITE);
//	dc.SetTextForeground(*wxBLACK);


	//    dc.SetBackgroundMode(wxSOLID);
	//    dc.SetBackground(*wxBLACK_BRUSH);
	//    dc.FloodFill(50,50,*wxBLACK);

	//Y a-t-il des donnees a tracer ?
	if (!m_dataPlot->empty())
	{
		//Alias sur la premiere sequence de courbe

		PlotSequenceCourbes& premiereSeqCourbe=*m_dataPlot->begin()->second;

		//Recuperation du nombre de sequences (par calque) a afficher dans la fenetre de plot
		const int nb_seq=premiereSeqCourbe.size();

		//Recuperation de la longueur des courbes
		int longueur=premiereSeqCourbe[0]->size();

		const int OFFSET_GAUCHE=40;
		const int OFFSET_DROITE=10;
		const int OFFSET_LIG=10;//+m_ToolBar->GetSize().GetHeight();
		const int OFFSET_BOTTOM=10;

		const double miniY=m_plotType->GetMiniY();
		const double maxiY=m_plotType->GetMaxiY();
		const double miniX=m_plotType->GetMiniX();
		const double maxiX=m_plotType->GetMaxiX()*nb_seq;//60*3;


		const int LONG_AXE_ORDO=std::max(1, dc.GetSize().GetHeight()-OFFSET_LIG-OFFSET_BOTTOM);
		const int LONG_AXE_ABSC=std::max(1, dc.GetSize().GetWidth()-OFFSET_GAUCHE-OFFSET_DROITE);

		//      const float echelle_y=LONG_AXE_ORDO/maxiY; //m_frameConfigCalques->GetMaxiY();
		const float echelle_x=LONG_AXE_ABSC/maxiX;

		TPoint2D<int> pt_origine(OFFSET_GAUCHE, m_taille_fenetre.GetHeight()-OFFSET_LIG-OFFSET_BOTTOM);
		TPoint2D<int> pt_ordonnee=pt_origine+TPoint2D<int>(0, -LONG_AXE_ORDO);
		TPoint2D<int> pt_abscisse=pt_origine+TPoint2D<int>(LONG_AXE_ABSC, 0);

		// Axe des abscisses
		//TODO Option
		dc.SetPen(*wxWHITE);
		dc.DrawLine(pt_origine.x, pt_origine.y, pt_abscisse.x, pt_abscisse.y);

		//Pour chaque courbe (ex Data, DataFiltre, FitG, ...) : plot !
		for (PlotDataContainer::const_iterator it=m_dataPlot->begin(); it!=m_dataPlot->end(); ++it)
		{
			const PlotSequenceCourbes& tab_seq=*it->second; //alias bien pratique pour le coeur de la boucle

			pt_origine=TPoint2D<int>(OFFSET_GAUCHE, m_taille_fenetre.GetHeight()-OFFSET_LIG-OFFSET_BOTTOM);
			pt_ordonnee=pt_origine+TPoint2D<int>(0, -LONG_AXE_ORDO);
			pt_abscisse=pt_origine+TPoint2D<int>(LONG_AXE_ABSC, 0);

			TPoint2D<int> pt_initial=pt_origine;//+TPoint2D<float>(0,-temp);//motion.y));
			TPoint2D<int> pt_courant=pt_initial;
			TPoint2D<int> pt_suivant=pt_initial;

			double abscisse=0;
			double ordonnee=0;

			//Pour chaque seq de la courbe : plot !
			for (std::size_t i=0; i<tab_seq.size(); ++i)
			{
				const PlotCourbe& courbe=*tab_seq[i]; //encore un alias

				//                std::cout<<"\tlongueur="<<longueur<<"\n";

				//axe des ordonnees
				//TODO Option
				dc.SetPen(*wxWHITE);
				dc.DrawLine(pt_origine.x, pt_origine.y, pt_ordonnee.x, pt_ordonnee.y);

				//Affichage de la courbe
				if (m_frameConfigCalques->AfficheCourbe(it->first) && !courbe.empty())
				{
					data2plot(abscisse, (*courbe.begin())->GetX(), miniX, maxiX, (double) LONG_AXE_ABSC);
					data2plot(ordonnee, (*courbe.begin())->GetY(), miniY, maxiY, (double) LONG_AXE_ORDO);
					pt_initial=pt_origine+TPoint2D<int>((int) floor(abscisse), (int) -floor(ordonnee));
					pt_courant=pt_initial;
					pt_suivant=pt_initial;

					wxColour couleur(m_frameConfigCalques->GetColour(it->first));
					wxPen pen(couleur);
					//TODO Option épaisseur traits
					pen.SetWidth(1); //5 -> demo videoproj
//					pen.SetWidth(5);
					dc.SetPen(pen);
					for (PlotCourbe::const_iterator it_pt=++courbe.begin(); it_pt!=courbe.end(); ++it_pt)
					{
						data2plot(abscisse, (*it_pt)->GetX(), miniX, maxiX, (double) LONG_AXE_ABSC);
						data2plot(ordonnee, (*it_pt)->GetY(), miniY, maxiY, (double) LONG_AXE_ORDO);
						pt_suivant=pt_origine+TPoint2D<int>((int) floor(abscisse), (int) -floor(ordonnee));
						dc.DrawLine(pt_courant.x, pt_courant.y, pt_suivant.x, pt_suivant.y);
						pt_courant=pt_suivant;
					}
				}

				//Affichage des points
				if (m_frameConfigCalques->AffichePoints(it->first))
				{
					wxColour couleur(m_frameConfigCalques->GetColour(it->first));
					wxPen pen(couleur);
					//TODO Option épaisseur points
//					pen.SetWidth(2); //5 -> demo videoproj
					pen.SetWidth(1);
					dc.SetPen(pen);
					dc.SetBrush(couleur);
					for (PlotCourbe::const_iterator it_pt=courbe.begin(); it_pt!=courbe.end(); ++it_pt)
					{
						//Si la couleur est définie pour chaque point on la récupère
						if (m_plotType->GetTypeCouleur()==PlotType::COULEUR_POINTS)
						{
							double min=m_frameConfigCalques->GetMinValue(it->first);
							double max=m_frameConfigCalques->GetMaxValue(it->first);
							TPoint3D<int> coul=Palette1((*it_pt)->GetValue(), min, max);
							couleur.Set(coul.x, coul.y, coul.z);
							dc.SetPen(couleur);
						}
						data2plot(abscisse, (*it_pt)->GetX(), miniX, maxiX, (double) LONG_AXE_ABSC);
						data2plot(ordonnee, (*it_pt)->GetY(), miniY, maxiY, (double) LONG_AXE_ORDO);
						pt_courant=pt_origine+TPoint2D<int>((int) floor(abscisse), (int) -floor(ordonnee));
						dc.DrawCircle(pt_courant.x, pt_courant.y, (int) max(float(1), sqrt(float(LONG_AXE_ABSC)*LONG_AXE_ORDO)/350));

					}
				}

				//Affichage des graduations
				// tous les 10 en x/bins et tous les 25 en y/intensite

				//                wxPen PenGrad;
				//                PenGrad.SetWidth(1);
				//                PenGrad.SetColour(*wxWHITE);
				//                dc.SetPen(PenGrad);

				//Ajustement du nombre de chiffres significatifs affichés pour la légende
				dc.SetPen(*wxWHITE);
				wxString format_x = CalculeFormatString(plot2data(std::floor(1.*LONG_AXE_ABSC/nb_seq), miniX, maxiX, double(LONG_AXE_ABSC)));
				for (int grad_x=0; grad_x<std::floor(1.*LONG_AXE_ABSC/nb_seq); ++grad_x)
				{
					if ((grad_x%80)==0)
					{
						pt_courant=pt_origine+TPoint2D<int>((int) floor(1.*grad_x), 0);
						wxString txt_grad_x = wxString::Format(format_x, plot2data(double(grad_x), miniX, maxiX, double(LONG_AXE_ABSC)));
						dc.DrawLine(pt_courant.x, pt_courant.y, pt_courant.x, pt_courant.y+5);
						dc.DrawText(txt_grad_x, pt_courant.x-txt_grad_x.length()*4, pt_courant.y+4);
					}
					else if ((grad_x%40)==0)
					{
						pt_courant=pt_origine+TPoint2D<int>((int) floor(1.*grad_x), 0);
						dc.DrawLine(pt_courant.x, pt_courant.y, pt_courant.x, pt_courant.y+2);
					}
				}

				wxString format_y = CalculeFormatString(plot2data(float(LONG_AXE_ORDO), miniY, maxiY, double(LONG_AXE_ABSC)));
				for (unsigned int grad_y=0; grad_y< float(LONG_AXE_ORDO); ++grad_y)
				{
					if ((grad_y%80)==0)
					{
						pt_courant=pt_origine+TPoint2D<int>(0, -(int) floor((float)grad_y));
						wxString txt_grad_y = wxString::Format(format_y, plot2data(double(grad_y), miniY, maxiY, double(LONG_AXE_ORDO)));
						dc.DrawLine(pt_courant.x, pt_courant.y, pt_courant.x-5, pt_courant.y);
						dc.DrawText(txt_grad_y, pt_courant.x-OFFSET_GAUCHE+5, pt_courant.y-10);
					}
					else if ((grad_y%40)==0)
					{
						pt_courant=pt_origine+TPoint2D<int>(0, -(int) floor((float)grad_y));
						dc.DrawLine(pt_courant.x, pt_courant.y, pt_courant.x-2, pt_courant.y);
					}
				}

				//Mise a jour de la nouvelle origine pour le trace de la sequence suivante
				pt_origine.x+=(int) floor(longueur*echelle_x);
				pt_ordonnee.x+=(int) floor(longueur*echelle_x);

			}
		}

	}

}

void Plot::OnClickCalques(wxCommandEvent& event)
{
	if (m_frameConfigCalques->IsShown())
		m_frameConfigCalques->Show(false);
	else
	{
		m_frameConfigCalques->UpdateTableauCalques();
		m_frameConfigCalques->Show();
	}
}

void Plot::OnClickSaveAs(wxCommandEvent& WXUNUSED(event))
{
        #if wxMINOR_VERSION <9
	wxString file = wxFileSelector(_("Enregistrer les courbes sous (format ASCII)"), _(""), _(""), _(""), _("*.*"), wxSAVE, this);
	#else
	wxString file = wxFileSelector(_("Enregistrer les courbes sous (format ASCII)"), _(""), _(""), _(""), _("*.*"), wxFD_SAVE, this);
        #endif
        std::cout<<"\tFichier choisi : "<<file<<"\n";

	if (!file.empty())
	{
		//Pour chaque courbe (ex Data, DataFiltre, FitG, ...) : plot !
		for (PlotDataContainer::const_iterator it=m_dataPlot->begin(); it!=m_dataPlot->end(); ++it)
		{
			const PlotSequenceCourbes& tab_seq=*it->second; //alias bien pratique pour le coeur de la boucle

			if (m_frameConfigCalques->AfficheCourbe(it->first) || m_frameConfigCalques->AffichePoints(it->first))
			{
				std::string fic((const char*)file.mb_str());
				fic += "_" + it->first;
				std::ofstream fic_ecriture(fic.c_str());
				fic_ecriture.precision(10);

				//Pour chaque seq de la courbe : plot !
				int sautAbscisse=0;
				if (tab_seq.size()>0)
					sautAbscisse=tab_seq[0]->size();
				for (std::size_t i=0; i<tab_seq.size(); ++i)
				{
					const PlotCourbe& courbe=*tab_seq[i]; //alias
					for (PlotCourbe::const_iterator it_pt=courbe.begin(); it_pt!=courbe.end(); ++it_pt)
						fic_ecriture<<(*it_pt)->GetX() + i*sautAbscisse<<"\t"<<(*it_pt)->GetY()<<"\n";
				}

			}
		}
	}
}

void Plot::OnClickZoomAll(wxCommandEvent& event)
{
	//calcul du zoom adapte, seq par seq...
}

void Plot::OnResize(wxSizeEvent& event)
{
	m_taille_fenetre=event.GetSize();
	Refresh();
}

void Plot::OnMouse(wxMouseEvent& event)
{
	if(event.MiddleIsDown())
	{
		m_frameConfigCalques->Show(!m_frameConfigCalques->IsVisible());
	}
	else if(event.LeftDClick())
	{
		wxCommandEvent e;
		OnClickSaveAs(e);
	}

	event.Skip();
}




PlotCalques::PlotCalques(wxWindow* parent, const shared_ptr<PlotType>& typePlot, const wxString& title) :
	wxMiniFrame(parent, -1, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX), m_plotType(typePlot)
{
	this->CentreOnScreen();
	m_parent=parent;

	//création des sizer pour la disposition de la fenêtre :
	m_Sizer=new wxFlexGridSizer(wxHORIZONTAL);
	m_Sizer->SetCols(5);

	SetSizer(m_Sizer);

	//Initialisation du gestionnaire de calques
	const t_ptrConstPlotDataContainer ptrData =((Plot*) m_parent)->GetDataPlotContainer();

	UpdateTableauCalques();
}


void PlotCalques::setPlotType(const shared_ptr<PlotType>& typePlot)
{
	m_plotType = typePlot;
	UpdateTableauCalques();
}

void PlotCalques::UpdateTableauCalques()
{
	unsigned char couleur=0;
	const t_ptrConstPlotDataContainer ptrData =((Plot*) m_parent)->GetDataPlotContainer();

	//Création de la configuration par défaut des sizers
	wxSizerFlags sizerFlag(1); //0 pour que les contrôles gardent leur taille, 1 pour qu'ils se mettent à l'échelle et d'autres valeurs relatives entre contrôles pour définir des proportions différentes
	sizerFlag.Expand().Border(5); //bordure de 5 entre le contrôle et le sizer

	//parcours des differents calques a gerer
	for (PlotDataContainer::const_iterator it=ptrData->begin(); it!=ptrData->end(); ++it)
	{
		bool existe=m_configCalque.find(it->first)!=m_configCalque.end();
		if (!existe) //si le calque n'est pas dans encore dans la liste
		{
			ElementConfigCalque& element=*m_configCalque.insert(t_MapConfigCalques::value_type(it->first,new ElementConfigCalque)).first->second;
			element.m_checkBoxAfficheTrait=new wxCheckBox(this,-1,wxString(it->first.c_str(), *wxConvCurrent).Truncate(40)+_(" : Courbe"));
			element.m_checkBoxAffichePoints=new wxCheckBox(this,-1,_("Points"));

			//Réglage du tracé trait/points
			if (m_plotType->GetTypeTrace()==PlotType::TRACE_COURBE)
			{
				element.m_checkBoxAffichePoints->SetValue(false);
				element.m_checkBoxAfficheTrait->SetValue(true);
			}
			else if (m_plotType->GetTypeTrace()==PlotType::TRACE_POINTS)
			{
				element.m_checkBoxAffichePoints->SetValue(true);
				element.m_checkBoxAfficheTrait->SetValue(false);
			}

			//Réglage des couleurs
			if (m_plotType->GetTypeCouleur()==PlotType::COULEUR_COURBE)
			{
				PlotSequenceCourbes& Seq = *(it->second);
				wxColour couleur(Seq.GetColorR(), Seq.GetColorG(), Seq.GetColorB());
				element.m_ColourPickerCtrlCouleur=new wxColourPickerCtrl(this, -1, couleur);

				element.m_textCtrlMinValueAttribut = new wxTextCtrl(this, -1, _("Min"));
				element.m_textCtrlMinValueAttribut->Disable();
				element.m_textCtrlMaxValueAttribut = new wxTextCtrl(this, -1, _("Max"));
				element.m_textCtrlMaxValueAttribut->Disable();
			}
			else if (m_plotType->GetTypeCouleur()==PlotType::COULEUR_POINTS)
			{
				element.m_ColourPickerCtrlCouleur=new wxColourPickerCtrl(this, -1, wxColour(0,0,0));
				element.m_ColourPickerCtrlCouleur->Disable();
				wxString minValue;
				minValue<<m_plotType->GetMiniValue();
				element.m_textCtrlMinValueAttribut = new wxTextCtrl(this, -1,minValue);
				wxString maxValue;
				maxValue<<m_plotType->GetMaxiValue();
				element.m_textCtrlMaxValueAttribut = new wxTextCtrl(this, -1, maxValue);
			}

			m_Sizer->Add(element.m_checkBoxAfficheTrait, sizerFlag);
			m_Sizer->Add(element.m_checkBoxAffichePoints, sizerFlag);
			m_Sizer->Add(element.m_ColourPickerCtrlCouleur, sizerFlag);
			m_Sizer->Add(element.m_textCtrlMinValueAttribut, sizerFlag);
			m_Sizer->Add(element.m_textCtrlMaxValueAttribut, sizerFlag);
			couleur+=50;
		}
	}

	//Supression des calques qui ne sont plus a afficher
	for (t_MapConfigCalques::const_iterator it=m_configCalque.begin(); it!=m_configCalque.end(); ++it)
	{
		bool existe=ptrData->find(it->first)!=ptrData->end();
		if (!existe) //si le calque n'est pas dans la liste des data a afficher
		{
			it->second->m_checkBoxAfficheTrait->Destroy();
			it->second->m_checkBoxAffichePoints->Destroy();
			it->second->m_ColourPickerCtrlCouleur->Destroy();
			it->second->m_textCtrlMinValueAttribut->Destroy();
			it->second->m_textCtrlMaxValueAttribut->Destroy();
			delete it->second;
			m_configCalque.erase(it->first);
		}
	}


	m_Sizer->Layout();
	m_Sizer->Fit(this);
	m_Sizer->SetSizeHints(this);
}

const wxColour PlotCalques::GetColour(const std::string& dataName)
{
	return (m_configCalque[dataName])->m_ColourPickerCtrlCouleur->GetColour();
}
const bool PlotCalques::AfficheCourbe(const std::string& dataName)
{
	return m_configCalque[dataName]->m_checkBoxAfficheTrait->GetValue();
}
const bool PlotCalques::AffichePoints(const std::string& dataName)
{
	return m_configCalque[dataName]->m_checkBoxAffichePoints->GetValue();
}

const double PlotCalques::GetMinValue(const std::string& dataName)
{
	double d;
	m_configCalque[dataName]->m_textCtrlMinValueAttribut->GetValue().ToDouble(&d);
	return d;
}

const double PlotCalques::GetMaxValue(const std::string& dataName)
{
	double d;
	m_configCalque[dataName]->m_textCtrlMaxValueAttribut->GetValue().ToDouble(&d);
	return d;
}

void PlotCalques::OnCheckBox(wxCommandEvent& event)
{
	m_parent->Refresh();
}

void PlotCalques::OnPickColour(wxColourPickerEvent& event)
{
	m_parent->Refresh();
}

void PlotCalques::OnTextChange(wxCommandEvent& event)
{
	m_parent->Refresh();
}

void PlotCalques::OnClickQuitter(wxCloseEvent& event)
{
	this->Show(false);
}

TPoint3D<int> Palette1(const double& value, const double& min, const double& max)
{
	if (value<min || value>max) return TPoint3D<int>(0,0,0);
	if(min<max) return TPoint3D<int>(223,(int) std::floor((value-min)/(max-min)*255),20);
	else return TPoint3D<int>(0,0,0);
	//	if(min<max) return TPoint3D<int>(std::floor((value-min)/(max-min)*255),0,0);
	//	else return TPoint3D<int>(255,0,0);
}

wxString CalculeFormatString(const double& value)
{
	int nb_chiffres = (int) std::floor(Log10(value));
	nb_chiffres = std::max(0, 2 - nb_chiffres);
	wxString format= _("%.");
	format<<nb_chiffres<<_("f");
	return format;
}

BEGIN_EVENT_TABLE(Plot, wxPanel)
EVT_SIZE (Plot::OnResize)
EVT_PAINT (Plot::OnPaint)
EVT_MOUSE_EVENTS(Plot::OnMouse)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(PlotCalques, wxFrame)
EVT_CHECKBOX(-1, PlotCalques::OnCheckBox)
EVT_COLOURPICKER_CHANGED(-1, PlotCalques::OnPickColour)
EVT_CLOSE(PlotCalques::OnClickQuitter)
EVT_TEXT(-1,PlotCalques::OnTextChange)
END_EVENT_TABLE()

