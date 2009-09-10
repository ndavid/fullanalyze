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

#include <vector>
#include <algorithm>

#include "boost/filesystem.hpp"

#include <wx/config.h>
#include <wx/log.h>
#include <wx/menu.h>

#include "tools/Orientation2D.h"

#include "core/modules/FAEventHandler.h"
#include "LidarFormat/LidarFile.h"

#include "FilesPanel.h"

using namespace Lidar;

//helpers
void getFileListExt(std::vector<std::string>& liste, const std::string dirName, const std::string& extensionName)
{
	liste.clear();

	using namespace boost::filesystem;
	using namespace std;

	path dir(dirName);

	if(is_directory(dir))
	{
		for (directory_iterator itr(dir); itr!=directory_iterator(); ++itr)
		{
			if(itr->path().extension() == extensionName)
			{
				liste.push_back(itr->path().filename());
			}
		}

	}

	sort(liste.begin(), liste.end());
}

void FilesPanel::parseImageFiles()
{
	using namespace std;

	std::string dirName (m_dirPickerImages->GetPath().fn_str());

//	std::cout << "Image path : " << dirName << std::endl;


	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->Write(_T("/FA/Paths/ImagesWorkingDir"), m_dirPickerImages->GetPath());

	m_treeFiles->DeleteChildren(m_rootImages);

	vector<string> fileList;
	getFileListExt(fileList, dirName, ".tif");


	if(!fileList.empty())
	{
		for(vector<string>::iterator itr=fileList.begin(); itr!=fileList.end(); ++itr)
		{
			Orientation2D ori;
			try
			{
				ori.ReadOriFromImageFile(dirName+"/"+*itr);
				m_treeFiles->AppendItem(m_rootImages, wxString(itr->c_str(), *wxConvCurrent) );
			}
			catch (const std::logic_error &e)
			{
				wxLogMessage(_("FA : No orientation found for image file ! the file was not loaded !"));
			}
		}

	}
	else
	{
		wxLogMessage(_("FA : Error : selected image directory does not exist !"));
	}

	m_treeFiles->Expand(m_rootImages);
}

#ifdef BUILD_FULLWAVE

#include "fullwave/format/FullwaveFile.h"

void FilesPanel::parseFullwaveFiles()
{
	using namespace boost::filesystem;
	using namespace std;

	string dirName ( m_dirPickerFullwave->GetPath().fn_str());


	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->Write(_T("/FA/Paths/FullwaveWorkingDir"), m_dirPickerFullwave->GetPath());

//	cout << endl << "Fichiers xml du dossier : " << dirFullwave << endl << endl;

	m_treeFiles->DeleteChildren(m_rootFullwave);

	vector<string> fileList;
	getFileListExt(fileList, dirName, ".xml");


	if(!fileList.empty())
	{
		for(vector<string>::iterator itr=fileList.begin(); itr!=fileList.end(); ++itr)
		{
			FullwaveFile fwFile(dirName+"/"+*itr);

			if(fwFile.isValid())
			{
				const wxTreeItemId& fileId = m_treeFiles->AppendItem(m_rootFullwave, wxString(itr->c_str(), *wxConvCurrent) );

				{
					wxString metaData;
					metaData << _("Nb of points : ") << fwFile.getNbPoints();
					m_treeFiles->AppendItem(fileId, metaData );
				}
				{
					wxString metaData;
					metaData << _("Binary data filename : ") << wxString( fwFile.getBinaryDataFileName().c_str(), *wxConvCurrent);
					m_treeFiles->AppendItem(fileId, metaData );
				}
				{
					wxString metaData;
					metaData << _("Binary data file format : ") << wxString( fwFile.getFormat().c_str(), *wxConvCurrent);
					m_treeFiles->AppendItem(fileId, metaData );
				}

			}
		}

	}
	else
	{
		wxLogMessage(_("FA : Error : selected fullwave directory does not exist !"));
	}

	m_treeFiles->Expand(m_rootFullwave);
}

#endif

void FilesPanel::parseLidarFiles()
{
	using namespace boost::filesystem;
	using namespace std;

	string dirName ( m_dirPickerLidar->GetPath().fn_str());


	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->Write(_T("/FA/Paths/LidarWorkingDir"), m_dirPickerLidar->GetPath());

//	cout << endl << "Lidar path : " << dirName << endl << endl;

	m_treeFiles->DeleteChildren(m_rootLidar);


	vector<string> fileList;
	getFileListExt(fileList, dirName, ".xml");


	if(!fileList.empty())
	{
		for(vector<string>::iterator itr=fileList.begin(); itr!=fileList.end(); ++itr)
		{
			LidarFile lidarFile(dirName+"/"+*itr);

			if(lidarFile.isValid())
			{
				const wxTreeItemId& fileId = m_treeFiles->AppendItem(m_rootLidar, wxString(itr->c_str(), *wxConvCurrent) );

				{
					wxString metaData;
					metaData << _("Nb of points : ") << lidarFile.getNbPoints();
					m_treeFiles->AppendItem(fileId, metaData );
				}
				{
					wxString metaData;
					metaData << _("Binary data filename : ") << wxString( lidarFile.getBinaryDataFileName().c_str(), *wxConvCurrent);
					m_treeFiles->AppendItem(fileId, metaData );
				}
				{
					wxString metaData;
					metaData << _("Binary data file format : ") << wxString( lidarFile.getFormat().c_str(), *wxConvCurrent);
					m_treeFiles->AppendItem(fileId, metaData );
				}

			}
		}

	}
	else
	{
		wxLogMessage(_("FA : Error : selected lidar directory does not exist !"));
	}

	m_treeFiles->Expand(m_rootLidar);
}

void FilesPanel::parseAllFiles()
{
	parseImageFiles();
	parseLidarFiles();
#ifdef BUILD_FULLWAVE
	parseFullwaveFiles();
#endif

}

void FilesPanel::OnDirChangeLidar(wxFileDirPickerEvent& event)
{
	parseLidarFiles();
}

void FilesPanel::OnDirChangeFullwave(wxFileDirPickerEvent& event)
{
#ifdef BUILD_FULLWAVE
	parseFullwaveFiles();
#endif
}

void FilesPanel::OnDirChangeImages(wxFileDirPickerEvent& event)
{
	parseImageFiles();
}

void FilesPanel::OnPopupMenu(wxTreeEvent& event)
{
	const wxTreeItemId& parent = m_treeFiles->GetItemParent(event.GetItem());
	wxMenu *menuToBeDisplayed = 0;

	if(parent == m_rootImages)
	{
		menuToBeDisplayed = m_popupMenuImages;
	}
	else if(parent == m_rootLidar)
	{
		menuToBeDisplayed = m_popupMenuLidar;
	}
	else if(parent == m_rootFullwave)
	{
		menuToBeDisplayed = m_popupMenuFullwave;
	}

	if(menuToBeDisplayed)
	{
		PopupMenu(menuToBeDisplayed);
	}
}

FilesPanel::FilesPanel( wxWindow* parent ):
	FilesPanelBuilder( parent )
{
	///bases du treeCtrl
	m_root = m_treeFiles->AddRoot(_("Data"));
	m_rootImages = m_treeFiles->AppendItem(m_root, _("Images"));
	m_rootLidar = m_treeFiles->AppendItem(m_root, _("Lidar files"));
	m_rootFullwave = m_treeFiles->AppendItem(m_root, _("Fullwave files"));

	///Dossiers des dirPickerCrl
	wxConfigBase *pConfig = wxConfigBase::Get();
	wxString lidarDir, imagesDir, fullwaveDir;
	pConfig->Read(_T("/FA/Paths/LidarWorkingDir"), &lidarDir, _(""));
	pConfig->Read(_T("/FA/Paths/ImagesWorkingDir"), &imagesDir, _(""));
	pConfig->Read(_T("/FA/Paths/FullwaveWorkingDir"), &fullwaveDir, _(""));

	if(lidarDir != _(""))
	{
		m_dirPickerLidar->SetPath(lidarDir);
	}

	if(fullwaveDir != _(""))
	{
		m_dirPickerFullwave->SetPath(fullwaveDir);
	}

	if(imagesDir != _(""))
	{
		m_dirPickerImages->SetPath(imagesDir);
	}


	parseImageFiles();
	parseLidarFiles();
#ifdef BUILD_FULLWAVE
	parseFullwaveFiles();
#endif

	initPopupMenu();
}

void FilesPanel::initPopupMenu()
{

	//Menu images
	m_popupMenuImages = new wxMenu;
//	m_popupMenuImages->Append(ID_IMAGE_OPEN, _("Display") );
//	m_popupMenuImages->Append(ID_IMAGE_SHADED, _("Shading") );

	//Menu Lidar
	m_popupMenuLidar = new wxMenu;
//	m_popupMenuLidar->Append(ID_LIDAR_SHOW_STRIP, _("Show strip") );
//	m_popupMenuLidar->Append(ID_LIDAR_PRINT_ECHOES, _("Print echoes"));
//	m_popupMenuLidar->Append(ID_LIDAR_SAVE_AS_BINARY, _("Save in binary format"));
//	m_popupMenuLidar->Append(ID_LIDAR_SAVE_AS_ASCII, _("Save in ascii format"));
//	m_popupMenuLidar->Append(ID_LIDAR_CENTER, _("Center point cloud"));
//	m_popupMenuLidar->Append(ID_LIDAR_CENTER_CUSTOM, _("Custom center point cloud"));
//	m_popupMenuLidar->Append(ID_LIDAR_MAKE_MNS, _("Compute MNS"));

	//Menu Fullwave
	m_popupMenuFullwave = new wxMenu;
//	m_popupMenuFullwave->Append(ID_FULLWAVE_DISPLAY_3D, _("Display waveforms in 3D") );
//	m_popupMenuFullwave->Append(ID_FULLWAVE_SHOW_STRIP, _("Show strip") );
//	m_popupMenuFullwave->Append(ID_FULLWAVE_PRINT_WAVEFORMS, _("Print waveforms") );
//	m_popupMenuFullwave->Append(ID_FULLWAVE_SHOW_SENSOR_1D, _("Display waveforms in sensor geometry") );
//	m_popupMenuFullwave->Append(ID_FULLWAVE_CENTER, _("Center waveforms") );


	std::vector<Action> actions = FAEventHandler::Instance()->getActions();

	for(std::vector<Action>::const_iterator it = actions.begin(); it != actions.end(); ++it)
	{
		wxMenu* menuTemp = 0;
		switch(it->m_type)
		{
			case Action::IMAGE:
				menuTemp = m_popupMenuImages;
				break;
			case Action::LIDAR:
				menuTemp = m_popupMenuLidar;
				break;
			case Action::FULLWAVE:
				menuTemp = m_popupMenuFullwave;
				break;
			case Action::MULTIPLE:
				;//nothing !

		}

		if(menuTemp)
		{
			menuTemp->Append(it - actions.begin(), wxString(it->m_title.c_str(), *wxConvCurrent));

			Connect(it - actions.begin(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FilesPanel::OnClickPopupMenu), NULL, this);
		}
	}

}

void FilesPanel::OnClickPopupMenu(wxCommandEvent &event)
{
	const Action& action = FAEventHandler::Instance()->getActions()[event.GetId()];

	action.m_callback();
}


std::string FilesPanel::getSelectedItemName() const
{
	return std::string(m_treeFiles->GetItemText(m_treeFiles->GetSelection()).fn_str());
}

std::string FilesPanel::getFullwaveSelectedItemName() const
{
	return std::string((m_dirPickerFullwave->GetPath() + _("/")).fn_str())   + getSelectedItemName();
}

std::string FilesPanel::getLidarSelectedItemName() const
{
	return std::string((m_dirPickerLidar->GetPath() + _("/")).fn_str())   + getSelectedItemName();
}

std::string FilesPanel::getImagesSelectedItemName() const
{
	return std::string((m_dirPickerImages->GetPath() + _("/")).fn_str())   + getSelectedItemName();
}


BEGIN_EVENT_TABLE(FilesPanel, wxPanel)
	///dir picker
	EVT_DIRPICKER_CHANGED(ID_DIR_PICKER_IMAGES, FilesPanel::OnDirChangeImages)
	EVT_DIRPICKER_CHANGED(ID_DIR_PICKER_LIDAR, FilesPanel::OnDirChangeLidar)
	EVT_DIRPICKER_CHANGED(ID_DIR_PICKER_FULLWAVE, FilesPanel::OnDirChangeFullwave)
	///Popup menu display
	EVT_TREE_ITEM_MENU(ID_TREE_FILES, FilesPanel::OnPopupMenu)
END_EVENT_TABLE()
