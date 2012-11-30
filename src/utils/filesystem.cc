#include "filesystem.h"

#include <string>

namespace findd { namespace utils {
  
  namespace filesystem {
    
    bool exists (const std::string &dir) {
      struct stat st;
      return stat(dir.c_str(), &st) == 0;
    }
    
    std::string trim_path (const std::string &path) {
      size_t last = path.length()-1;
      std::string p_trim = path;
      while (p_trim[last] == '/') {
        p_trim = path.substr(0, last);
        last -= 1;
      }
      return p_trim;
    }

  }
  
}
}
