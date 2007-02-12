#ifndef PluginManager_Log_h
#define PluginManager_Log_h
// -*- C++ -*-
//
// Package:     PluginManager
// Class  :     Log
// 
/**\class Log Log.h FWCore/PluginManager/interface/Log.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Original Author:  Chris Jones
//         Created:  Thu Dec 14 20:52:46 CST 2006
// $Id$
//

// system include files
enum { LFplugin_manager };
// user include files
#include "FWCore/MessageLogger/interface/MessageLogger.h"

// forward declarations
#define LOG(level,what,mode,v) LogDebug( #mode ) <<v

static const char* const indent = "";
static const char* const undent = "";

#endif
