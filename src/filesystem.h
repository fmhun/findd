#ifndef FINDD_FILESYSTEM_
#define FINDD_FILESYSTEM_

#include <sys/stat.h>
#include <string>

namespace findd {
  
  namespace filesystem {
    
    bool exists (const std::string &);
    
    std::string trim_path (const std::string &);
    
    std::string dir_concat (const std::string &, const std::string &);
    
  }

}

#endif