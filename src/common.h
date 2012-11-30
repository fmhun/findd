#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <vector>
#include <list>
#include "file.h"
#include <iostream>

typedef struct std::vector<findd::File> file_list;
typedef struct std::vector<findd::File*> duplicate;
typedef struct std::list<duplicate> duplicate_list; 

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


// void filter_files (file_list *fl, duplicate_list *dups) {
//   using namespace std;
//   file_list::const_iterator it;
//   
//   for (it = fl->begin(); it != fl->end(); ++it) {
//     cout << (*it).name() << endl;
//   }
// }

#endif