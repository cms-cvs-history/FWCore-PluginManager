#ifndef SEAL_BASE_SHARED_LIBRARY_ERROR_H
# define SEAL_BASE_SHARED_LIBRARY_ERROR_H

//<<<<<< INCLUDES                                                       >>>>>>

# include "FWCore/Utilities/interface/Exception.h"

namespace edmplugin {
//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>
//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

/** Error in a shared library operation. */
  class SharedLibraryError : public cms::Exception
{
public:
  SharedLibraryError(const std::string& iCategory):
  cms::Exception(iCategory) {}
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

} // namespace edmplugin
#endif // SEAL_BASE_SHARED_LIBRARY_ERROR_H
