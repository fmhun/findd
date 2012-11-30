#include <string>

namespace findd { namespace utils {
  
  namespace crypto {

    std::string sha1 (const std::string &);
    
    int crc32(char *, unsigned int);
    
  } // namespace crypto
  
} // namespace utils

} // namespace findd