#ifndef PluginManager_DebugAids_h
#define PluginManager_DebugAids_h
// -*- C++ -*-
//
// Package:     PluginManager
// Class  :     DebugAids
// 
/**\class DebugAids DebugAids.h FWCore/PluginManager/interface/DebugAids.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Original Author:  Chris Jones
//         Created:  Thu Dec 14 20:59:16 CST 2006
// $Id$
//

// system include files
#include <assert.h>
#include "FWCore/Utilities/interface/Exception.h"
// user include files

// forward declarations
#define ASSERT(condition)  assert(condition)

#define VERIFY(condition) if (!condition) throw cms::Exception("FailVerify")
#endif
