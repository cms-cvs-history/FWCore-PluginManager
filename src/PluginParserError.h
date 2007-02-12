#ifndef PLUGIN_MANAGER_PLUGIN_PARSER_ERROR_H
# define PLUGIN_MANAGER_PLUGIN_PARSER_ERROR_H

//<<<<<< INCLUDES                                                       >>>>>>

//# include "FWCore/PluginManager/interface/config.h"
# //include "FWCore/PluginManager/interface/Error.h"
#include "FWCore/Utilities/interface/Exception.h"
namespace edmplugin {
//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>
//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

  class  PluginParserError : public cms::Exception
{
public:
    PluginParserError (const std::string &reason);
    // implicit copy constructor
    // implicit assignment operator
    // implicit destructor

//    virtual std::string	explainSelf (void) const;
//    virtual Error *	clone (void) const;
//    virtual void	rethrow (void);

//private:
//    std::string		m_reason;
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

} // namespace edmplugin
#endif // PLUGIN_MANAGER_PLUGIN_PARSER_ERROR_H
