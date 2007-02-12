#ifndef PLUGIN_MANAGER_PLUGIN_DB_H
# define PLUGIN_MANAGER_PLUGIN_DB_H

//<<<<<< INCLUDES                                                       >>>>>>

# include "FWCore/PluginManager/interface/config.h"
# include "FWCore/PluginManager/interface/Filename.h"
# //include "FWCore/PluginManager/interface/MapIterator.h"
# //include "FWCore/PluginManager/interface/SearchPath.h"
# //include "FWCore/PluginManager/interface/Callback.h"
# include <string>
# include <list>
# include <map>
# include <vector>
#include <boost/iterator/transform_iterator.hpp>
#include "sigc++/signal.h"

namespace cms {
  class Exception;
}

namespace edmplugin {
//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>

class Module;
class ModuleCache;
class ModuleDescriptor;
class PluginFactoryBase;
class PluginInfo;
//class Error;

//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
template <typename T, typename U> struct GetSecond : public std::unary_function<const std::pair<T,U>&, const U&>{
  const U& operator()(const std::pair<T,U>& iPair) const { return iPair.second; }
};
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

/** Catalog of dynamically available components in the system.

    #PluginManager maintains a catalog of objects that can be
    created dynamically.  Most of the objects are provided by plug-in
    modules: dynamically loaded shared libraries.  Subclasses of
    #PluginFactoryBase provided concrete views of the catalog.

    There is only one instance of this type, provided by #get().  */
class PluginManager
{
public:
    typedef std::list<ModuleCache *>		DirectoryMap;
    typedef DirectoryMap::const_iterator	DirectoryIterator;

    typedef std::map<Filename, Module *>	ModuleMap;
    //typedef MapValueIterator<ModuleMap>		ModuleIterator;
    typedef boost::transform_iterator<GetSecond<Filename,Module*>, ModuleMap::const_iterator> ModuleIterator;
    typedef std::vector<std::string> SearchPath;

    /// Types of information passed as feedback.
    enum FeedbackCode
    {
	// Status feedback: no error object
	StatusLoading,		//< About to load a module library
	StatusUnloading,	//< About to unload a module library
	StatusEntries,		//< About to check for entry points
	StatusAttaching,	//< About to attach a module library
	StatusDetaching,	//< About to detach a module library
	StatusQuerying,		//< About to query a module library

	// Error feedback: see the passed error object
	ErrorLoadFailure,	//< Module library failed to load
	ErrorEntryFailure,	//< Missing entry points in the module
	ErrorBadModule,		//< Module is being marked bad
	ErrorBadCacheFile,	//< Bad or inaccessible cache file
	ErrorNoFactory,		//< Missing factory for a plug-in

	// Fallback
	Other			//< Something else
    };

    /// Simple tuple of data passed to feedback clients.
    struct FeedbackData
    {
      FeedbackData (FeedbackCode code, const std::string &s, cms::Exception *err = 0);

	FeedbackCode	code;	//< Feedback code.
	std::string	scope;	//< Subject, e.g. module or file name.
        cms::Exception		*error;	//< Possible error object.
    };

    /// Feedback callback type
    //CDJ typedef Callback1<FeedbackData> FeedbackCB;
    typedef sigc::signal<void,const FeedbackData&>::slot_type FeedbackCB;
    static PluginManager *get (void);
    static void		destroyOnExit (bool destroy);

    // cache management interface
    void		initialise (void);
    void		refresh (void);

    // feedback management
    void		addFeedback (FeedbackCB callback);
    void		removeFeedback (FeedbackCB callback);
    void		feedback (FeedbackData data);
    void		feedback (FeedbackCode code,
		    		  const Filename &scope,
				  cms::Exception *error = 0); 
    void		feedback (FeedbackCode code,
		    		  const std::string &scope,
				  cms::Exception *error = 0);
 
    // access to db structure
    DirectoryIterator	beginDirectories (void) const;
    DirectoryIterator	endDirectories (void) const;
    DirectoryIterator	locateDirectory (const Filename &name) const;
    ModuleCache *	directory (const Filename &name) const;

    ModuleIterator	beginModules (void) const;
    ModuleIterator	endModules (void) const;
    ModuleIterator	locateModule (const Filename &libraryName) const;
    Module *		module (const Filename &libraryName) const;

    // interface for factory management; mainly private to implementation
    void		addInfo (PluginInfo *info);
    void		removeInfo (PluginInfo *info);
    void		restore (Module *module, ModuleDescriptor *from);

    void		addFactory (PluginFactoryBase *factory);
    void		removeFactory (PluginFactoryBase *factory);

private:
    typedef std::list<PluginFactoryBase *>	FactoryList;
    typedef FactoryList::iterator		FactoryIterator;

    typedef sigc::signal<void,const FeedbackData&>  FeedbackList;
    //typedef FeedbackList::iterator		FeedbackIterator;

    friend class PluginManagerDestructor;
    PluginManager (const SearchPath &path);
    ~PluginManager (void);

    void		rebuild (void);
    FactoryIterator	beginFactories (void);
    FactoryIterator	endFactories (void);
    PluginFactoryBase *findFactory (const std::string &name);

    bool		m_initialised;
    SearchPath		m_searchPath;
    DirectoryMap	m_directories;
    ModuleMap		m_modules;
    FactoryList		m_factories;
    FeedbackList	m_feedbacks;

    // undefined semantics
    PluginManager (const PluginManager &);
    PluginManager &operator= (const PluginManager &);
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

inline
PluginManager::FeedbackData::FeedbackData (FeedbackCode c,
					   const std::string &s,
					   cms::Exception *err /* = 0 */)
    : code (c),
      scope (s),
      error (err)
{}

} // namespace edmplugin
#endif // PLUGIN_MANAGER_PLUGIN_DB_H
