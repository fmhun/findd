#include "crypto.h"

#include <cstddef>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/md5.h>

namespace findd {
  
  namespace crypto {
    
    std::string md5 (char *s, const size_t size) {
      unsigned char result[MD5_DIGEST_LENGTH];
      MD5((unsigned char*) s, size, result);
      
      char str[MD5_DIGEST_LENGTH*2];
      char hexbyte[3];
      sprintf(hexbyte, "%02x", result[0]);
      strcpy(str, hexbyte);
      
      for (int i = 1; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hexbyte, "%02x", result[i]);
        strcat(str, hexbyte);
      }
      
      return std::string(str);
    }

    // int main(int argc, char *argv[]) {
    //     int file_descript;
    //     unsigned long file_size;
    //     char* file_buffer;
    // 
    //     if(argc != 2) { 
    //             printf("Must specify the file\n");
    //             exit(-1);
    //     }
    //     printf("using file:\t%s\n", argv[1]);
    // 
    //     file_descript = open(argv[1], O_RDONLY);
    //     if(file_descript < 0) exit(-1);
    // 
    //     file_size = get_size_by_fd(file_descript);
    //     printf("file size:\t%lu\n", file_size);
    // 
    //     file_buffer = mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0);
    //     MD5((unsigned char*) file_buffer, file_size, result);
    // 
    //     print_md5_sum(result);
    //     printf("  %s\n", argv[1]);
    // 
    //     return 0;
    // }
    
  } // namespace crypto

} // namespace findd