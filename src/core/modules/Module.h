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

#ifndef MODULE_H_
#define MODULE_H_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

#include "core/modules/FAEventHandler.h"
#include "core/modules/Actions.h"

#ifdef BUILD_FULLWAVE

#define REGISTER_MODULE(ModuleName, ModuleTitle, ModuleType)\
	class Module_ ## ModuleName\
	{\
		static bool m_registerModule;\
		static void run();\
		static bool registerModule()\
		{\
			Action action(ModuleTitle, ModuleType, boost::function<void()>(&Module_ ## ModuleName ::preRun));\
			FAEventHandler::Instance()->registerAction(action);\
			return true;\
		}\
		static void preRun()\
		{\
			run();\
			FAEventHandler::Instance()->guiParseFiles();\
		}\
		static shared_ptr<SelectedImageData> getSelectedImageData()\
		{\
			return FAEventHandler::Instance()->getSelectedImageData();\
		}\
		static shared_ptr<SelectedLidarData> getSelectedLidarData()\
		{\
			return FAEventHandler::Instance()->getSelectedLidarData();\
		}\
		static shared_ptr<SelectedFullwaveData> getSelectedFullwaveData(const bool loadIntensities = false)\
		{\
			return FAEventHandler::Instance()->getSelectedFullwaveData(loadIntensities);\
		}\
	};\
	bool Module_ ## ModuleName::m_registerModule = Module_ ## ModuleName ::registerModule();

#else

#define REGISTER_MODULE(ModuleName, ModuleTitle, ModuleType)\
	class Module_ ## ModuleName\
	{\
		static bool m_registerModule;\
		static void run();\
		static bool registerModule()\
		{\
			Action action(ModuleTitle, ModuleType, boost::function<void()>(&Module_ ## ModuleName ::preRun));\
			FAEventHandler::Instance()->registerAction(action);\
			return true;\
		}\
		static void preRun()\
		{\
			run();\
			FAEventHandler::Instance()->guiParseFiles();\
		}\
		static shared_ptr<SelectedImageData> getSelectedImageData()\
		{\
			return FAEventHandler::Instance()->getSelectedImageData();\
		}\
		static shared_ptr<SelectedLidarData> getSelectedLidarData()\
		{\
			return FAEventHandler::Instance()->getSelectedLidarData();\
		}\
	};\
	bool Module_ ## ModuleName::m_registerModule = Module_ ## ModuleName ::registerModule();


#endif



#endif /* MODULE_H_ */
