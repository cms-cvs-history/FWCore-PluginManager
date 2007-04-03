//<<<<<< INCLUDES                                                       >>>>>>

#include "FWCore/PluginManager/interface/PluginManager.h"
#include "FWCore/PluginManager/interface/ModuleDescriptor.h"
#include "FWCore/PluginManager/interface/ModuleCache.h"
#include "FWCore/PluginManager/interface/Module.h"
//#include "SealBase/StringOps.h"
//#include "SealBase/Signal.h"
//#include "SealBase/Error.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "boost/thread/thread.hpp"
#include "FWCore/MessageService/interface/MessageLoggerScribe.h"

#include "FWCore/MessageService/interface/MessageServicePresence.h"
#include "FWCore/MessageLogger/interface/MessageDrop.h"

#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <string>
#include <set>

//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>
//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

using namespace edmplugin;

void feedback (PluginManager::FeedbackData data)
{
    std::string explanation;
    if (data.error) {
      explanation=data.error->what();
      std::string::size_type last=0;
      std::string::size_type i=0;
      while(std::string::npos != (i=explanation.find_first_of('\n',last))){
        explanation.insert(i+1,"\t",1);
        last = i+2;
      }
    }
    if (data.code == PluginManager::StatusLoading)
	std::cerr << "Note: Loading " << data.scope << "\n";

    else if (data.code == PluginManager::ErrorLoadFailure)
	std::cerr << "  *** WARNING: module `" << data.scope
		  << "' failed to load for the following reason\n\t"
		  << explanation << "\n";

    else if (data.code == PluginManager::ErrorBadModule)
	std::cerr << "  *** WARNING: module `" << data.scope
		  << "' ignored until problems with it are fixed.\n\n";

    else if (data.code == PluginManager::ErrorBadCacheFile)
	std::cerr << "  *** WARNING: cache file " << data.scope
		  << " is corrupted.\n";

    else if (data.code == PluginManager::ErrorEntryFailure)
	std::cerr << "  *** WARNING: module `" << data.scope
		  << "' does not have the required entry point, reason was\n\t"
		  << explanation << "\n";

    // This cannot actually trigger in SealPlugin* utility, for example only
    else if (data.code == PluginManager::ErrorNoFactory)
	std::cerr << "  *** WARNING: module `" << data.scope
		  << "' missing one or more factories for plug-ins\n";
}

/*
namespace  {
  void
  runMessageLoggerScribe()
  {
    edm::service::MessageLoggerScribe  m;
    m.run();
  }
}  // namespace
*/
int main (int argc, char **argv)
{
  int returnValue = EXIT_SUCCESS;
  edm::service::MessageServicePresence presence;
  edm::MessageDrop::instance()->debugEnabled=false;

  try {
    std::string spath;
    const char* kSearchPath = 0;
    if(argc >1) {
      kSearchPath = argv[1];
      spath = std::string(kSearchPath);
      if (not boost::filesystem::is_directory(kSearchPath) ) {
        //at the moment, we can't handle an individual file
        spath = boost::filesystem::path(kSearchPath).branch_path().string();
      }
    } else {
      kSearchPath = getenv("EDM_PLUGINS");
      if( 0 == kSearchPath ) {
        std::cerr <<"The environment variable 'EDM_PLUGINS' has not been set"<<std::endl;
        return 1;
      }
      spath = std::string(kSearchPath);
    }
    std::string::size_type last=0;
    std::string::size_type index=0;
    std::vector<std::string> paths;
    while( (index=spath.find_first_of(':',last))!=std::string::npos) {
      paths.push_back(spath.substr(last,index-last));
      last = index+1;
      std::cout <<paths.back()<<std::endl;
    }
    paths.push_back(spath.substr(last,std::string::npos));
    
    edmplugin::PluginManager& rdb = edmplugin::PluginManager::configure(PluginManager::Config().searchPath(paths));

    // List all categories and items in them.  Set avoids duplicates.
    typedef std::pair<std::string,std::string>	Seen;
    typedef std::set<Seen>			SeenSet;
    typedef SeenSet::iterator			SeenSetIterator;

    PluginManager			*db = PluginManager::get ();

    db = &rdb;
    db->addFeedback (&feedback);
    db->initialise ();
  }catch(std::exception& iException) {
    std::cout <<"Caught exception "<<iException.what()<<std::endl;
    returnValue = 1;
  }

    return returnValue;
}
