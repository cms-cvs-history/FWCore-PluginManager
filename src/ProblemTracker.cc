

#include "FWCore/PluginManager/interface/ProblemTracker.h"
#include "FWCore/Utilities/interface/EDMException.h"

//#include "SealBase/Error.h"

#include <iostream>
#include <string>
#include <boost/bind.hpp>

using namespace std;

// return true if this is status, false if it is error
static bool codeToName(edmplugin::PluginManager::FeedbackCode code, 
		       string& error_name)
{
  using namespace edmplugin;
  bool rc = true;

  switch(code)
    {
    case PluginManager::ErrorLoadFailure:
      rc=false; error_name="LoadFailure"; break;
    case PluginManager::ErrorEntryFailure: 
      rc=false; error_name="EntryFailure"; break;
    case PluginManager::ErrorBadModule: 
      rc=false; error_name="BadModule"; break;
    case PluginManager::ErrorBadCacheFile: 
      rc=false; error_name="BadCacheFile"; break;
    case PluginManager::ErrorNoFactory: 
      rc=false; error_name="NoFactory";	break;
    case PluginManager::StatusLoading:
      error_name="Loading"; break;
    case PluginManager::StatusUnloading:
      error_name="Unloading";break;
    case PluginManager::StatusEntries: 
      error_name="Entries"; break;
    case PluginManager::StatusAttaching: 
      error_name="Attaching";break;
    case PluginManager::StatusDetaching: 
      error_name="Detaching"; break;
    case PluginManager::StatusQuerying: 
      error_name="Querying"; break;
    default: 
      error_name="NoFeedbackCode"; break;
    }
  
  return rc;
}

namespace edm
{

  void ProblemTracker::feedback(edmplugin::PluginManager::FeedbackData data)
  {
    if(dead_==true) return;

    using namespace edmplugin;
    ProblemTracker* prob = this;
    string name;
    bool is_status = codeToName(data.code,name);

    if(!is_status)
      {
	cerr << "Plugin feedback: Got error " << name 
	     << " in scope " << data.scope
	     << endl;
      }
    
    if(data.error)
      {
	// an exception object is here
	cerr << "The PluginManager has reported an exceptional condition.\n"
	     << "Message:\n" << data.error->what()
	     << endl;
      }

    bool need_throw = name=="NoFactory" ? true: false;

    if(is_status)
      prob->last_status_.swap(name);
    else
      prob->last_error_.swap(name);

    prob->last_scope_.swap(data.scope);

    if(need_throw)
      {
	throw cms::Exception("PluginError","NoFactory")
	  << data.scope
	  << "\nThe library is probably missing.";
      }
  }

  char ProblemTracker::failure(const char* msg)
  {
    if(dead_==true) return 'a';
      //if(old_assert_hook_) return old_assert_hook_(msg);

    ProblemTracker* prob = ProblemTracker::instance();
    cerr << "Got Assertion: message = " << msg << "\n"
	 << "last known PluginManager scope: " << prob->last_scope_ << "\n"
	 << "last known PluginManager status:  " << prob->last_status_ << "\n"
	 << "last known PluginManager error:  " << prob->last_error_
	 << endl;
    
    return 'a';
  }

  // -----------------------------------------------

  bool ProblemTracker::dead_ = true;
  //edmplugin::DebugAids::AssertHook ProblemTracker::old_assert_hook_ = 0;

  ProblemTracker::ProblemTracker():
    last_scope_("Unknown"),
    last_status_("NoStatus"),
    last_error_("NoError")
  {
    dead_ = false;
    //old_assert_hook_ = edmplugin::DebugAids::failHook(&failure);
    edmplugin::PluginManager::Config config;

    //const char *path = getenv ("SEAL_PLUGINS");
    const char *path = getenv ("EDM_PLUGINS");
    if (! path) path = "";
    //LOG (0, trace, LFplugin_manager,
    //    "initialising plugin manager with path <" << path << ">");
    
    std::string spath(path? path: "");
    std::string::size_type last=0;
    std::string::size_type i=0;
    std::vector<std::string> paths;
    while( (i=spath.find_first_of(':',last))!=std::string::npos) {
      paths.push_back(spath.substr(last,i-last));
      last = i+1;
      std::cout <<paths.back()<<std::endl;
    }
    paths.push_back(spath.substr(last,std::string::npos));
    config.searchPath(paths);
    
    edmplugin::PluginManager& db = edmplugin::PluginManager::configure(config);
    db.addFeedback(boost::bind(boost::mem_fn(&ProblemTracker::feedback),this,_1));
    db.initialise();
  }

  ProblemTracker::~ProblemTracker()
  {
    // since this is a singleton, we will not restore the old handle
    dead_ = true;
  }

  ProblemTracker* ProblemTracker::instance()
  {
    static ProblemTracker pt;
    return &pt;
  }

  // ---------------------------------------------

  AssertHandler::AssertHandler():pt_(ProblemTracker::instance())
  {
  }

  AssertHandler::~AssertHandler()
  {
  }


}
