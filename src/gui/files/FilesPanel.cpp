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

#include <vector>
#include <algorithm>
#include <iostream>

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
				liste.push_back(itr->path().filename().string());
			}
		}

	}

	sort(liste.begin(), liste.end());
}

void getFileListExts(std::vector<std::string>& liste, const std::string dirName, const std::vector<std::string>& extensionNames)
{
        liste.clear();

        using namespace boost::filesystem;
        using namespace std;

        path dir(dirName);

        if(is_directory(dir))
        {
                for (directory_iterator itr(dir); itr!=directory_iterator(); ++itr)
                {
                    unsigned int i;
                    for(i=0;i<extensionNames.size();++i)
                    {
                        if(itr->path().extension() == extensionNames[i])
                        {
                              #if BOOST_FILESYSTEM_VERSION < 3  
                              liste.push_back(itr->path().filename());
                              #else
                              liste.push_back(itr->path().filename().string() );
                              #endif
                        }
                    }
                }

        }

        sort(liste.begin(), liste.end());
}

void FilesPanel::parseImageFiles()
{
	using namespace std;

	std::string dirName ((const char*)m_dirPickerImages->GetPath().mb_str());

        std::cout << "Image path : " << dirName << std::endl;


	wxConfigBase *pConfig = wxConfigBase::Get();
	pConfig->Write(_T("/FA/Paths/ImagesWorkingDir"), m_dirPickerImages->GetPath());

	m_treeFiles->DeleteChildren(m_rootImages);

        vector<string> fileList, extensionList;
        extensionList.push_back(".tif");
        extensionList.push_back(".jpg");
        extensionList.push_back(".png");
        //        getFileListExt(fileList, dirName, ".tif");
        getFileListExts(fileList, dirName, extensionList);

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
			catch (const std::logic_error &)
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

	string dirName ( (const char*)m_dirPickerFullwave->GetPath().mb_str());


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

	string dirName ( (const char*)m_dirPickerLidar->GetPath().mb_str());


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
	wxTreeItemId id_select = event.GetItem();
	if(!m_treeFiles->IsSelected(id_select))
		m_treeFiles->SelectItem(id_select);

	const wxTreeItemId& parent = m_treeFiles->GetItemParent(id_select);
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

	//Menu Lidar
	m_popupMenuLidar = new wxMenu;

	//Menu Fullwave
	m_popupMenuFullwave = new wxMenu;

	std::vector<Action> actions = FAEventHandler::instance()->getActions();

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
				;//nothing yet!

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
	const Action& action = FAEventHandler::instance()->getActions()[event.GetId()];

	action.m_callback();
}


std::string FilesPanel::getSelectedItemName() const
{
	std::string selected_item_name =((const char*)m_treeFiles->GetItemText(m_treeFiles->GetSelection()).mb_str());
	return selected_item_name;
}

std::string FilesPanel::getFullwaveSelectedItemName() const
{
	std::string fw_selected_item_name = ( boost::filesystem::path((const char*)m_dirPickerFullwave->GetPath().mb_str()) / getSelectedItemName()).string();
	return fw_selected_item_name;
}

std::string FilesPanel::getLidarSelectedItemName() const
{
	std::string lidar_selected_item_name= ( boost::filesystem::path((const char*)m_dirPickerLidar->GetPath().mb_str()) / getSelectedItemName()).string();
	return lidar_selected_item_name;
}

std::string FilesPanel::getImagesSelectedItemName() const
{
	std::string im_selected_image_name = ( boost::filesystem::path((const char*)m_dirPickerImages->GetPath().mb_str()) / getSelectedItemName()).string();
	return im_selected_image_name;
}


BEGIN_EVENT_TABLE(FilesPanel, wxPanel)
	///dir picker
	EVT_DIRPICKER_CHANGED(ID_DIR_PICKER_IMAGES, FilesPanel::OnDirChangeImages)
	EVT_DIRPICKER_CHANGED(ID_DIR_PICKER_LIDAR, FilesPanel::OnDirChangeLidar)
	EVT_DIRPICKER_CHANGED(ID_DIR_PICKER_FULLWAVE, FilesPanel::OnDirChangeFullwave)
	///Popup menu display
	EVT_TREE_ITEM_MENU(ID_TREE_FILES, FilesPanel::OnPopupMenu)
END_EVENT_TABLE()
