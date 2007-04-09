//<<<<<< INCLUDES                                                       >>>>>>

#include "FWCore/PluginManager/interface/PluginManager.h"
#include "FWCore/Utilities/interface/Exception.h"

#include <iostream>
#include <utility>
#include <cstdlib>
#include <string>
#include <set>

using namespace edmplugin;


int main (int, char **argv)
{
  int returnValue = EXIT_SUCCESS;
  try {
  }catch(std::exception& iException) {
    std::cout <<"Caught exception "<<iException.what()<<std::endl;
    returnValue = 1;
  }

    return returnValue;
}
