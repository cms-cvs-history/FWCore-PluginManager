// -*- C++ -*-
//
// Package:     PluginManager
// Class  :     PluginFactoryManager
// 
// Implementation:
//     <Notes on implementation>
//
// Original Author:  Chris Jones
//         Created:  Thu Mar  8 14:24:57 PST 2007
// $Id$
//

// system include files
#include "sigc++/signal.h"

// user include files
#include "FWCore/PluginManager/interface/PluginFactoryManager.h"
#include "FWCore/Utilities/interface/Exception.h"

using namespace edmplugin;
//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PluginFactoryManager::PluginFactoryManager()
{
}

// PluginFactoryManager::PluginFactoryManager(const PluginFactoryManager& rhs)
// {
//    // do actual copying here;
// }

PluginFactoryManager::~PluginFactoryManager()
{
}

//
// assignment operators
//
// const PluginFactoryManager& PluginFactoryManager::operator=(const PluginFactoryManager& rhs)
// {
//   //An exception safe implementation is
//   PluginFactoryManager temp(rhs);
//   swap(rhs);
//
//   return *this;
// }

//
// member functions
//
/** Add the @a factory to the plugin manager.  This makes the factory
participate in the internal cache management scheme to allow data
about modules and plug-ins to to be cached and restored.  This
method is called by the #PluginFactoryBase constructor.  */
void
PluginFactoryManager::addFactory (PluginFactoryBase *factory)
{
  // FIXME: allow factories to be registered to the database, then
  // notify them on each refresh (and when they are added).  The
  // factories should be accessed via XyzDB::get () which gets the
  // global database and registers an instance of the factory into it.
  m_factories.push_back (factory);
  
  pluginAddedSignal_(factory);
}

/** Remove a @a factory from the plug-in manager.  This method is
be called from the #PluginFactoryBase destructor so that the
manager will not try to notify factories that have already been
unloaded from the program.  */
void
PluginFactoryManager::removeFactory (PluginFactoryBase *factory)
{
  FactoryIterator pos = std::find (m_factories.begin (), m_factories.end (), factory);
  if(pos == m_factories.end ()) {
    throw cms::Exception("PluginFactoryRemoveFactory")<<"asked to remove a plugin factory which was never registered";
  }
  m_factories.erase (pos);
}

/** Find a factory that matches category label @a name.  Internal
method used to match info item categories to factories.  Returns
pointer to the matching factory, or null if none is found.  */
PluginFactoryBase *
PluginFactoryManager::findFactory (const std::string &name)
{
  FactoryIterator pos = m_factories.begin ();
  while (pos != m_factories.end () && (*pos)->category () != name)
    ++pos;
  
  return pos != m_factories.end () ? *pos : 0;
}

//
// const member functions
//

//
// static member functions
//
PluginFactoryManager*
PluginFactoryManager::get() {
  static PluginFactoryManager* s_pfm=0;
  if (0 == s_pfm) {
    s_pfm=new PluginFactoryManager();
  }
  return s_pfm;
}
