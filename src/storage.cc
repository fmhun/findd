#include "storage.h"
#include <iostream>
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
      file.append_attribute("absolute-path")  = (*it).path().c_str();
      file.append_attribute("size")           = (int) (*it).size();
    }
    
    doc.save_file(path.c_str());
  }

  file_list Storage::restore (const std::string &path) {
    using namespace pugi;
    
    file_list fl;
    xml_document doc;
    xml_parse_result result = doc.load_file(path.c_str());
    
    if (!result) {
      throw 1;
    }
    
    xml_node files = doc.child("files");
    for (pugi::xml_node file = files.first_child(); file; file = file.next_sibling()) {
      fl.push_back(File(
        file.attribute("name").as_string(),
        file.attribute("extension").as_string(),
        file.attribute("absolute-path").as_string(),
        file.attribute("size").as_uint()
      ));
    }
    
    return fl;
  }

}
