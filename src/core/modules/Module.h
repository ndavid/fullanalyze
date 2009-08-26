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
			Action action(ModuleTitle, ModuleType, boost::function<void()>(&Module_ ## ModuleName ::run));\
			FAEventHandler::Instance()->registerAction(action);\
			return true;\
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
