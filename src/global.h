#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>

#include "file.h"
#include "comparator.h"

namespace findd {

  typedef struct std::list<findd::File> file_list;
  typedef struct std::vector<findd::File> duplicate;
  typedef struct std::vector<duplicate> duplicate_list; 

  struct env_t {
    env_t () : recursive(false), remove(false), include_hidden(false), in_scan_file(""), out_scan_file("") {}
  
    bool recursive;
    std::vector<std::string> directories;
    std::string in_scan_file;
    std::string out_scan_file;
    Comparator comparator;
    bool remove;
    bool include_hidden;
  };

}

#endif