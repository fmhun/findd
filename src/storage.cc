/*
This file is part of the Findd project from University of Poitiers (FR).
	
Copyright (C) 2012
	
Florian Mhun <florian.mhun@gmail.com>
Sara Ressam  <sara.ressam@gmail.com>
Bastien Nouhant <bastien.nouhant@gmail.com>
Jérôme Cornet <jerome.cornet@etu.univ-poitiers.fr>
	
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the <organization> nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "storage.h"

#include <iostream>
#include <stdexcept>

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
      throw std::runtime_error("invalid backup");
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
