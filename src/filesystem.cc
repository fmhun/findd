#include "filesystem.h"

#include <string>

namespace findd {
  
  namespace filesystem {
    
    const char* SEPARATORS = "/\\";
    
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
    
    std::string filename (const std::string &path) {
      return path.substr( path.find_last_of(SEPARATORS) + 1 );
    }
    
    std::string extension (const std::string &path) {
      std::string fn = filename(path);
      if (fn[0] == '.')
        return fn;
      else {
        std::string ext = fn.substr( fn.find_last_of(".") + 1 );
        return fn == ext ? "" : ext;
      }
    }
    
    bool is_hidden (const std::string &path) {
#ifdef _WIN32
        // TODO : implement it for windows system
        // @see GetFileAttributes http://msdn.microsoft.com/en-us/library/aa364944%28VS.85%29.aspx
      return false;
#else
      std::string fn = filename(path);
      return fn == extension(fn);
#endif
    }
    
    std::string folder (const std::string &path) {
      return path.substr( 0, path.find_last_of(SEPARATORS) );
    }
    
  } // end namespace filesystem
 
} // end namespace findd
