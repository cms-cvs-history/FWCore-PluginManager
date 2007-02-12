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
int main (int, char **argv)
{
  int returnValue = EXIT_SUCCESS;
  edm::service::MessageServicePresence presence;
/*  boost::thread  scribe( ((void) edm::MessageLoggerQ::instance() // ensure Q's static data init'd
                          , runMessageLoggerScribe  // start a new thread
                          ));*/


    //Signal::handleFatal (argv [0]);
  try {
    // List all categories and items in them.  Set avoids duplicates.
    typedef std::pair<std::string,std::string>	Seen;
    typedef std::set<Seen>			SeenSet;
    typedef SeenSet::iterator			SeenSetIterator;

    PluginManager			*db = PluginManager::get ();
    PluginManager::DirectoryIterator	dir;
    ModuleCache::Iterator		plugin;
    ModuleDescriptor			*cache;
    SeenSet				seen;
    unsigned				i;

    db->addFeedback (&feedback);
    db->initialise ();
    for (dir = db->beginDirectories (); dir != db->endDirectories (); ++dir)
	for (plugin = (*dir)->begin (); plugin != (*dir)->end (); ++plugin)
	    for (cache=(*plugin)->cacheRoot(), i=0; i < cache->children(); ++i)
		seen.insert (Seen (cache->child (i)->token (0),
				   cache->child (i)->token (1)));

    SeenSetIterator cat = seen.begin ();
    SeenSetIterator current; 
    while (cat != seen.end ())
    {
	std::cout << "Category " << cat->first << ":\n";
	current = cat;
	while (current != seen.end () && current->first == cat->first)
	{
	    std::cout << "  " << current->second << std::endl;
	    ++current;
	}
	cat = current;
    }

  }catch(std::exception& iException) {
    std::cout <<"Caught exception "<<iException.what()<<std::endl;
    returnValue = 1;
  }

    return returnValue;
}
