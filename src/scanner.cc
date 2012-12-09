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

#include "scanner.h"

#include <boost/filesystem.hpp>

#include "file.h"
#include "common.h"
#include "utils/filesystem.h"

#include <iostream>

namespace findd {
  
  Scanner::Scanner () {}
  
  Scanner::~Scanner () {}
  
  void Scanner::scan (const std::string &directory, const bool recursive) {
    using namespace boost::filesystem;
    using namespace std;
    using utils::filesystem::trim_path;
    
    string sdir = trim_path(directory);
    path *pdir = new path(sdir);
    
    if (is_already_scanned(sdir))
      return;
        
    if (!exists(*pdir) || !is_directory(*pdir)) {
      return;
    }
    
    delete pdir;
    list<string> dirs_to_scan;
    dirs_to_scan.push_back(sdir);
    
    while (dirs_to_scan.size() != 0) {
      path *dir = new path(dirs_to_scan.front());
      dirs_to_scan.pop_front();
      
      _scanned_directories.push_back( trim_path(dir->string()) ); // register "dir" as scanned
      
      // read "dir"
      vector<path> contents;
      copy(directory_iterator(*dir), directory_iterator(), back_inserter(contents));
      delete dir;
      
      // process files found from "dir"
      for (int i = 0; i < contents.size(); ++i) {
        const path &p = contents[i];
        
        if (is_directory(p) && recursive) {
          dirs_to_scan.push_back(p.string());
        } else if (is_regular_file(p)) {
          _files.push_back(File(p));
        } else {
          // TODO : what should we do for elements which are not a directory and not a regular file.  
        }
      }
    }
  }

  const std::vector<std::string> &Scanner::scanned_directories () const {
    return _scanned_directories;
  }
  
  file_list Scanner::files () const {
    return _files;
  }
  
  bool Scanner::is_already_scanned (const std::string &dir) {
    for (size_t i = 0; i < _scanned_directories.size(); i++) {
      if (_scanned_directories[i] == dir) return true;
    }
    return false;
  }
  
  long Scanner::totalBytesScanned () const {
    long bytes = 0; int size = _files.size();
    // #pragma omp parallel for reduction(+:bytes)
    // for (int i = 0; i < size; i++) {
    //   bytes += _files[i].size();
    // }
    return bytes;
  }
  
}