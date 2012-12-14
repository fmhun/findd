#include "filesystem.h"

#include <string>

namespace findd {
  
  namespace filesystem {

#ifdef _WIN32
    
    const char SEPARATOR = '\\';

#else
    
    const char SEPARATOR = '/';

#endif
    
    bool exists (const std::string &path) {
      struct stat st;
      return stat(path.c_str(), &st) == 0;
    }
    
    std::string trim_path (const std::string &path) {
      size_t last = path.length()-1;
      std::string p_trim = path;
      while (p_trim[last] == SEPARATOR) {
        p_trim = path.substr(0, last);
        last -= 1;
      }
      return p_trim;
    }

    std::string dir_concat (const std::string &first, const std::string &second) {
      return first + SEPARATOR + second;
    }
    
  } // end namespace filesystem
 
} // end namespace findd
