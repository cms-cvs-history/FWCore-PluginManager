#ifndef PluginManager_Filename_h
#define PluginManager_Filename_h
// -*- C++ -*-
//
// Package:     PluginManager
// Class  :     Filename
// 
/**\class Filename Filename.h FWCore/PluginManager/interface/Filename.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Original Author:  Chris Jones
//         Created:  Thu Dec 14 21:10:26 CST 2006
// $Id$
//

// system include files
#include <boost/filesystem/path.hpp>

// user include files

// forward declarations

namespace edmplugin {
  typedef boost::filesystem::path Filename;
}

#endif
