#ifndef PLUGIN_MANAGER_PLUGIN_CAPABILITIES_H
# define PLUGIN_MANAGER_PLUGIN_CAPABILITIES_H

//<<<<<< INCLUDES                                                       >>>>>>

# include "FWCore/PluginManager/interface/PluginFactory.h"

namespace edmplugin {
//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>
//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

class PluginCapabilities : public PluginFactory<void>
{
public:
    static PluginCapabilities *get (void);

private:
    PluginCapabilities (void);
    //static PluginCapabilities s_instance;
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

} // namespace edmplugin
#endif // PLUGIN_MANAGER_PLUGIN_CAPABILITIES_H
