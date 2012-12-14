#ifndef FINDD_UTILS_FILESYSTEM_
#define FINDD_UTILS_FILESYSTEM_

#include <sys/stat.h>
#include <string>

namespace findd { namespace utils {
  
  namespace filesystem {
    
    bool exists (const std::string &);
    
    std::string trim_path (const std::string &);
    
    std::string dir_concat (const std::string &first, const std::string &second);
    
  }
  
}
}

#endif