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

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdexcept>

#include "file.h"
#include "global.h"
#include "filesystem.h"

#include <iostream>

namespace findd {
  
  Scanner::Scanner () : _total_bytes_scanned(0) {}
  
  Scanner::~Scanner () {}
  
  void Scanner::scan (const std::string &directory, const bool inc_hidden, const bool recursive) {
    using namespace std;
    using namespace filesystem;
    
    string dir = trim_path(directory); 
    
    if (is_already_scanned(dir))
      return;
    
    std::list<string> dirs_to_scan;
    dirs_to_scan.push_back(directory);
    
    do {
      dir = dirs_to_scan.front();
      dirs_to_scan.pop_front();
      _scanned_directories.push_back(dir);
      
      DIR *dp;
      struct dirent *entry;
      struct stat statbuf;
      
      if ((dp = opendir(dir.c_str())) == NULL) {
        string error = "can not open "; error += dir;
        throw std::logic_error(error);
      }
      
      // Read dir content
      while((entry = readdir(dp)) != NULL) {
        string path = dir_concat(dir, string(entry->d_name));
        stat(path.c_str(), &statbuf);
        
        if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
          continue;
        
        if (!inc_hidden)
          if (is_hidden(path)) continue;
        
        if (S_ISDIR(statbuf.st_mode)) {
          dirs_to_scan.push_back(path);
        } else {
          _files.push_back(File(path, statbuf.st_size));
          _total_bytes_scanned += _files.back().size();
        }
      }
      closedir(dp);
    } while (dirs_to_scan.size() != 0 && recursive);
  }
  
  void Scanner::reset () const {
    // TODO : reset the scanned directories and scanned files
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
  
  long Scanner::total_bytes_scanned () const {
    return _total_bytes_scanned;
  }
  
}