#ifndef FINDD_FILESYSTEM_
#define FINDD_FILESYSTEM_

#include <sys/stat.h>
#include <string>

namespace findd {
  
 /**
  * Lightweight API to manage filesystem
  *
  * @author Florian Mhun <florian.mhun@gmail.com>
  */
  namespace filesystem {
    
    bool exists (const std::string &);
    
    std::string trim_path (const std::string &);
    
    std::string dir_concat (const std::string &, const std::string &);
    
    std::string filename (const std::string &);
    
    std::string extension (const std::string &);
    
    bool is_hidden (const std::string &);
    
    std::string folder (const std::string &);
    
    std::string real_path (const std::string &);
  }

}

#endif