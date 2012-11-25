#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <vector>
#include <list>
#include "file.h"

typedef struct std::list<findd::File> file_list;

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
  filter_t filter;
  bool display_stats;
};

#endif