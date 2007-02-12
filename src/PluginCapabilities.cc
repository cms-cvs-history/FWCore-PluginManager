//<<<<<< INCLUDES                                                       >>>>>>

#include "FWCore/PluginManager/interface/PluginCapabilities.h"

namespace edmplugin {
//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>

PluginCapabilities PluginCapabilities::s_instance;

//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

PluginCapabilities::PluginCapabilities (void)
    : PluginFactory<void> ("Capability")
{}

PluginCapabilities *
PluginCapabilities::get (void)
{ return &s_instance; }

} // namespace edmplugin
