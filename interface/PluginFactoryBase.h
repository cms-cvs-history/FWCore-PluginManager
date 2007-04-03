#ifndef PLUGIN_MANAGER_PLUGIN_DBVIEW_BASE_H
# define PLUGIN_MANAGER_PLUGIN_DBVIEW_BASE_H

//<<<<<< INCLUDES                                                       >>>>>>

# include "FWCore/PluginManager/interface/config.h"
# include <string>

namespace edmplugin {
//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>

class Module;
class PluginInfo;
class ModuleDescriptor;

//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

/** Abstract base class to bridge #PluginManager and #PluginFactory.  */
class PluginFactoryBase
{
public:
    PluginFactoryBase (const std::string &tag);
    virtual ~PluginFactoryBase (void);

    // Category tag
    const std::string &	category (void) const;

    // Notifications from PluginManager.
    virtual void	restore (Module *module, ModuleDescriptor *info) =0;
    virtual void	addInfo (PluginInfo *info) = 0;
    virtual void	removeInfo (PluginInfo *info) = 0;

protected:
    friend class PluginManager;
    // Notifications from derived class
    virtual void	rebuild (void);
    void finishedConstruction();

private:
    std::string	m_tag;

    // undefined, no semantics
    PluginFactoryBase (const PluginFactoryBase &);
    PluginFactoryBase &operator= (const PluginFactoryBase &);
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

} // namespace edmplugin
#endif // PLUGIN_MANAGER_PLUGIN_DBVIEW_BASE_H
