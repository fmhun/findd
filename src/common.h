#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <vector>
#include <list>
#include "file.h"
#include <iostream>
#include <sstream>

namespace {
  const char COL_RESET[] = "\x1b[0m";
  const char RED[]     = "\x1b[31m";
  const char GREEN[]   = "\x1b[32m";
  const char YELLOW[]  = "\x1b[33m";
  const char BLUE[]    = "\x1b[34m";
  const char MAGENTA[] = "\x1b[35m";
  const char CYAN[]    = "\x1b[36m";
    
  std::string colorize_filename (const std::string &str, const char* color) {
    size_t found = str.find_last_of("/\\");
      
    std::stringstream colorized;
    colorized << color << str.substr(found+1) << COL_RESET;
      
    std::string cstr(str);
    cstr.replace(found+1, str.length()-1, colorized.str());
      
    return cstr;
  }
}

typedef struct std::vector<findd::File> file_list;
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
  filter_t filter;
  bool display_stats;
};

/** 
 * Overloading of ostream operator<< to print a duplicate
 */
std::ostream& operator<< (std::ostream &out, const duplicate &d) {
  for (int i = 0; i < d.size(); i++) {
    const findd::File &file = d[i];
    out << " #" << i <<" -> " << colorize_filename(file.absolute_path(), RED) << std::endl;
  }
  return out;
}

#endif