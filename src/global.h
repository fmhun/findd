#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>

#include "file.h"

typedef struct std::list<findd::File> file_list;
typedef struct std::vector<findd::File> duplicate;
typedef struct std::vector<duplicate> duplicate_list; 

struct filter_t {
  filter_t () : compare_name(false), compare_size(false), compare_content(false) {}
  
  bool compare_name;
  bool compare_size;
  bool compare_content;
};

struct env_t {
  bool recursive;
  std::vector<std::string> directories;  
  std::string in_scan_file;
  std::string out_scan_file;
  struct filter_t filter;
  bool display_stats;
  bool remove;
};

#endif