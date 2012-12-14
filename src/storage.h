#ifndef FINDD_STORAGE_
#define FINDD_STORAGE_

#include <string>
#include "pugixml.hpp"

#include "global.h"

namespace findd {
  
  class Storage {
  public:
    Storage ();
    ~Storage ();
    void persist (const file_list &, const std::string &);
    file_list restore (const std::string &);
  };
  
}

#endif