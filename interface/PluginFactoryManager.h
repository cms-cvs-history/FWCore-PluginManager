#ifndef PluginManager_PluginFactoryManager_h
#define PluginManager_PluginFactoryManager_h
// -*- C++ -*-
//
// Package:     PluginManager
// Class  :     PluginFactoryManager
// 
/**\class PluginFactoryManager PluginFactoryManager.h FWCore/PluginManager/interface/PluginFactoryManager.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Original Author:  Chris Jones
//         Created:  Thu Mar  8 14:24:50 PST 2007
// $Id$
//

// system include files
#include <list>
#include "sigc++/signal.h"

// user include files
# include "FWCore/PluginManager/interface/PluginFactoryBase.h"

// forward declarations
namespace edmplugin {

class PluginFactoryManager
{

   public:
      friend class PluginManager;
      typedef sigc::signal<void,PluginFactoryBase*>  PluginAddedSignal;

      typedef std::list<PluginFactoryBase *>	FactoryList;
      typedef FactoryList::iterator		FactoryIterator;
      typedef FactoryList::iterator iterator;
      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static PluginFactoryManager* get();

      // ---------- member functions ---------------------------
      void		addFactory (PluginFactoryBase *factory);
      void		removeFactory (PluginFactoryBase *factory);

      PluginAddedSignal pluginAddedSignal_;
      
      iterator begin() {return m_factories.begin();}
      iterator end() {return m_factories.end();}
        
   private:
      PluginFactoryManager();
      virtual ~PluginFactoryManager();
      
      PluginFactoryManager(const PluginFactoryManager&); // stop default

      const PluginFactoryManager& operator=(const PluginFactoryManager&); // stop default

      
      FactoryIterator	beginFactories (void);
      FactoryIterator	endFactories (void);
      PluginFactoryBase *findFactory (const std::string &name);

      // ---------- member data --------------------------------
      FactoryList		m_factories;
};

}
#endif
