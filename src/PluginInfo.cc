//<<<<<< INCLUDES                                                       >>>>>>

#include "FWCore/PluginManager/interface/PluginInfo.h"
#include "FWCore/PluginManager/interface/ModuleDescriptor.h"
#include "FWCore/PluginManager/interface/PluginManager.h"
#include "FWCore/PluginManager/interface/Module.h"
#include "debug.h"
#include "FWCore/PluginManager/interface/DebugAids.h"
#include "FWCore/PluginManager/interface/Log.h"

namespace edmplugin {
//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>
//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

PluginInfo::PluginInfo (Module *module,
			const std::string &name,
			const std::string &category)
    : m_module (module),
      m_name (name),
      m_category (category)
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
    LOG (0, trace, LFplugin_manager, "defining " << m_category
	 << ' ' << m_name << '\n');
}

PluginInfo::~PluginInfo (void)
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
    m_module->detachInfo (this);
}

void
PluginInfo::finish (bool needCache)
{
    // Derived constructor is complete, tell the module I exist.  This
    // adds myself to the module and propagates the notification to
    // the relevant factory.  Note that the factory must already exist, so
    // it will get notified immediately.  However it might still be in
    // the middle of construction, which is why we propagate the
    // notification through the base classes and not directly to the
    // factory from the derived class.
    m_module->addInfo (this, needCache);
}

Module *
PluginInfo::module (void) const
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
    return m_module;
}

const std::string &
PluginInfo::name (void) const
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
    return m_name;
}

const std::string &
PluginInfo::category (void) const
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
    return m_category;
}

void
PluginInfo::cache (ModuleDescriptor *to) const
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
    ASSERT (to);
    new ModuleDescriptor (to, m_category, m_name);
}

void
PluginInfo::detach (void)
{
    ASSERT (m_module);
    ASSERT (! m_name.empty ());
    ASSERT (! m_category.empty ());
}

void
PluginInfo::noFactory (void) const
{
    m_module->manager ()->feedback
	(PluginManager::ErrorNoFactory,
	 //CDJ m_name + " (" + m_module->libraryName ().name () + ")");
	 m_name + " (" + m_module->libraryName ().string() + ")");
    ASSERT (false);
}

} // namespace edmplugin
