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

#include <wx/config.h>
#include <boost/filesystem.hpp>

//register modules
#include "core/modules/Module.h"

//get image data
#include "core/modules/SelectedFullwaveData.h"

//gui access
#include "gui/files/FilesPanel.h"
#include "3d/GLPanel.h"
#include "gui/3d/CloudControl.h"

//3d
#include "3d/fullwave/FullwaveCloud.h"




/*** Display 3d module ***/

REGISTER_MODULE(fullwave_display3d, "Display waveforms in 3D", Action::FULLWAVE)

void Module_fullwave_display3d::run()
{
	shared_ptr<SelectedFullwaveData> selectedData = getSelectedFullwaveData();
	const SelectedFullwaveData::FullwaveData& fwData = selectedData->front();

	FAEventHandler::Instance()->getPanel3D()->getCloudControl()->AddCloud( shared_ptr<Cloud>(new FullwaveCloud(fwData.m_container, fwData.m_transfo, fwData.m_basename )));
}


//void FAEventHandler::fullwaveCenter(const std::string &fileName)
//{
//	FullwaveLidarDataContainer fwContainer(fileName);
//
//	double x=0, y=0;
//	wxTextEntryDialog dialogX(m_pimpl->m_parent, _("Transfo x"), _("Please enter text"), _("0."));
//	if (dialogX.ShowModal() == wxID_OK)
//	{
//		wxString result = dialogX.GetValue();
//		if(!result.ToDouble(&x))
//		{
//			wxMessageBox(_("Bad transfo value !"));
//			return;
//		}
//	}
//	wxTextEntryDialog dialogY(m_pimpl->m_parent, _("Transfo y"), _("Please enter text"), _("0."));
//	if (dialogY.ShowModal() == wxID_OK)
//	{
//		wxString result = dialogY.GetValue();
//		if(!result.ToDouble(&y))
//		{
//			wxMessageBox(_("Bad transfo value !"));
//			return;
//		}
//	}
//
//	LidarCenteringTransfo transfo;
//	transfo.setTransfo(x,y);
//
//	shared_ptr<LidarDataContainer> centeredContainer = transfo.centerLidarDataContainer(fwContainer.getAttributeContainer(), "originX", "originY", "originZ");
//	fwContainer.setAttributeContainer(*centeredContainer);
//
//	fwContainer.LoadWaveforms();
//
//	std::string fileNameXML = boost::filesystem::path(fileName).branch_path().string() + "/" + boost::filesystem::basename(fileName) + "-centered.xml";
//	FullwaveFile::save(fwContainer, fileNameXML, transfo);
//
//	std::cout << "Fin centrage fw" << std::endl;
//}



//void FAEventHandler::fullwaveDisplay1d(const std::string &fileName)
//{
//	//TODO généraliser
////	const std::string sensorImageFileName("/home/achauve/Documents/data_test/images/brusquet_bande6_parc-centered-capteur.tif");
//
//	shared_ptr<FullwaveLidarDataContainer> fwContainer(new FullwaveLidarDataContainer(fileName));
//	fwContainer->LoadWaveforms();
//
//	SensorEnergyImage sensorImageMaker(fwContainer);
//
//	shared_ptr<gil::gray32F_image_t> sensorImage = sensorImageMaker.run();
//	m_pimpl->m_panelViewerSensor->addSensorLayer(sensorImage);
//
//	m_pimpl->m_plotFW = shared_ptr<PlotFullwave>(new PlotFullwave(fwContainer));
//
//	if(!m_pimpl->m_plotPanel)
//	{
//		m_pimpl->m_plotPanel = new Plot(m_pimpl->m_parent,m_pimpl-> m_plotFW);
//		m_pimpl->m_panelViewerSensor->setPointCallback(boost::bind(&PlotFullwave::updatePosition, m_pimpl->m_plotFW, _1));
//		m_pimpl->m_notifyPlotPanelCreated();
//	}
//
//	m_pimpl->m_plotFW->setPlotNotifier(boost::bind(&Plot::Redraw, m_pimpl->m_plotPanel));
//
//	m_pimpl->m_notifyShowPanelSensorViewer();
//
//}


//void FAEventHandler::fullwaveShowStrip(const std::string &fileName)
//{
//	FullwaveLidarDataContainer fwContainer(fileName);
//	FullwaveFile file(fileName);
//
//	LidarCenteringTransfo transfo;
//	file.loadTransfo(transfo);
//
//	std::vector<double> stripX, stripY;
//	FullwaveTools::calculeEmprise(fwContainer, stripX, stripY, transfo);
//	m_pimpl->m_panelViewerMain->showStrip(stripX, stripY, boost::filesystem::basename(fileName));
//}

//void FAEventHandler::fullwavePrintWaveforms(const std::string &fileName)
//{
//	using namespace std;
//	cout << "Chargement des données fw (échos): " << fileName << endl;
//	FullwaveLidarDataContainer fwContainer(fileName);
//
////	m_pimpl->createPanel3d();
//
//	try{
//		cout << "Chargement des données fw (intensités): " << fileName << endl;
//		fwContainer.LoadWaveforms();
//		cout << "Fin Chargement " << endl << endl;
//
//		fwContainer.printHeaderAttribut(cout);
//
//		cout << "Affichage dix premiers échos : " << endl;
//		ostream_iterator<const Waveform> it_output( cout, "\n\n" );
////		cout << "Emitted Pulse " << endl;
//		copy(fwContainer.begin(), fwContainer.begin()+10, it_output);
////		cout << *fwContainer.begin() << std::endl;
//
//	}
//
//	catch(std::exception &e)
//	{
//		cout << "Exception ! \n";
//		cout << e.what() << endl;
//	}
//}
