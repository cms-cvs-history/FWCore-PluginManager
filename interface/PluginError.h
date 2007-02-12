#ifndef PLUGIN_MANAGER_PLUGIN_ERROR_H
# define PLUGIN_MANAGER_PLUGIN_ERROR_H

//<<<<<< INCLUDES                                                       >>>>>>

# include "FWCore/PluginManager/interface/config.h"
# include "FWCore/Utilities/interface/Exception.h"

namespace edmplugin {
//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>
//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

/** Error object for the plug-in manager.  All lower-level errors
    are chained to this type before being passed upwards.  */
  class PluginError : public cms::Exception
{
public:
  PluginError (const std::string& iMessage): cms::Exception("PluginError",iMessage) {}
  PluginError(const std::string& iMessage,
              const cms::Exception& iOther): cms::Exception("PluginError",iMessage,iOther) {}
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

} // namespace edmplugin
#endif // PLUGIN_MANAGER_PLUGIN_ERROR_H
