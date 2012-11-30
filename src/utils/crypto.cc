#include "crypto.h"

#include <boost/crc.hpp>
#include <boost/uuid/sha1.hpp>
#include <sstream>
#include <cstddef>
#include <string>

namespace findd { namespace utils {
  
  namespace crypto {
    
    std::string sha1 (const std::string &str) {
      boost::uuids::detail::sha1 hasher;
      hasher.process_bytes(str.c_str(), str.length());
      
      unsigned int digest[5];
      hasher.get_digest(digest);
      
      char hash[20];
      for(int i = 0; i < 5; ++i) {
        const char *tmp = reinterpret_cast<char *>(digest);
        hash[i * 4] = tmp[i * 4 + 3];
        hash[i * 4 + 1] = tmp[i * 4 + 2];
        hash[i * 4 + 2] = tmp[i * 4 + 1];
        hash[i * 4 + 3] = tmp[i * 4];
      }
      
      std::stringstream res;
      res << std::hex;
      for(int i = 0; i < 20; ++i) {
          res << ((hash[i] & 0x000000F0) >> 4)
             <<  (hash[i] & 0x0000000F);
      }
      
      return res.str();
    }
    
    int crc32(char *data, unsigned int size) {
      boost::crc_32_type result;
      result.process_bytes(data, size);
      return result.checksum();
    }
    
  } // namespace crypto

} // namespace utils

} // namespace findd