#ifndef COMMON_H_
#define COMMON_H_

struct filter_t {
  filter_t () : compare_name(false), compare_size(false), compare_content(false) {}
  
  bool compare_name;
  bool compare_size;
  bool compare_content;
};

#endif