#include "crypto.h"

#include <cstddef>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

namespace findd {
  
  namespace crypto {
    
    std::string md5 (char *s, const size_t len) {
      MD5_CTX context;
      unsigned char digest[MD5_DIGEST_LENGTH];

      MD5Init (&context);
      MD5Update (&context, (POINTER)s, len);
      MD5Final (digest, &context);

      char str[MD5_DIGEST_LENGTH*2];
      char hexbyte[3];
      sprintf(hexbyte, "%02x", digest[0]);
      strcpy(str, hexbyte);
      
      for (int i = 1; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hexbyte, "%02x", digest[i]);
        strcat(str, hexbyte);
      }
      
      return std::string(str);
    }
    
  } // namespace crypto

} // namespace findd