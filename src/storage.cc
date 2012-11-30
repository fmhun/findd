#include "storage.h"

namespace findd {
  
  Storage::Storage () {}

  Storage::~Storage () {}

  void Storage::persist (const file_list &fl, const std::string &path) {
    using namespace pugi;
    
    xml_document doc;
    xml_node files = doc.append_child("files");
    
    file_list::const_iterator it;
    for (it = fl.begin(); it != fl.end(); it++) {
      xml_node file = files.append_child("file");
      file.append_attribute("name")           = (*it).name().c_str();
      file.append_attribute("extension")      = (*it).extension().c_str();
      file.append_attribute("absolute-path")  = (*it).absolute_path().c_str();
      file.append_attribute("content-digest") = (*it).content_digest();
      file.append_attribute("size")           = (*it).size();
    }
    
    doc.save_file(path.c_str());
  }

  file_list Storage::restore (const std::string &path) {
    return file_list();
  }

}
