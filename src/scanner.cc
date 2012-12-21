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
#include <errno.h>
#include <stdexcept>

#include "file.h"
#include "global.h"
#include "filesystem.h"

#include <iostream>

namespace findd {
  
  Scanner::Scanner () : _total_bytes_scanned(0) {}
  
  Scanner::~Scanner () {}
  
  void Scanner::scan (const std::string &directory, 
                      const bool inc_hidden, 
                      const bool recursive,
                      const bool force) {
    using namespace std;
    using namespace filesystem;

    string dir = trim_path(real_path(directory)); 
    
    if (is_already_scanned(dir))
      return;
    
    std::list<string> dirs_to_scan;
    dirs_to_scan.push_back(dir);
    
    do {
      dir = dirs_to_scan.front();
      dirs_to_scan.pop_front();
      _scanned_directories.push_back(dir);
      
      DIR *dp;
      struct dirent *entry;
      struct stat statbuf;
      
      if ((dp = opendir(dir.c_str())) == NULL) {
        string error = dir; error += " : "; error += strerror(errno);
        if (!force)
          throw std::logic_error(error);
        else {
          cerr << "WARNING : " << error << endl; 
          continue;
        }
      }
      
      // Read dir content
      while ((entry = readdir(dp)) != NULL) {
        string path = dir_concat(dir, string(entry->d_name));
#ifndef _WIN32
        lstat(path.c_str(), &statbuf);
#else
        stat(path.c_str(), &statbuf);
#endif
        if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
          continue;
        
        if (!inc_hidden)
          if (is_hidden(path)) continue;
        
        if (S_ISDIR(statbuf.st_mode)) {
          dirs_to_scan.push_back(path);
#ifndef _WIN32
        } else if (S_ISLNK(statbuf.st_mode)) {
          // TODO : Follow symbolic links
          // char buf[1024];
          // ssize_t len;
          // cout << path;
          // if ((len = readlink(path.c_str(), buf, sizeof(buf)-1)) != -1) {
          //   buf[len] = '\0';
          //   cout << " -> " <<buf;
          // }
          // cout << endl;
#endif
        } else if (S_ISREG(statbuf.st_mode)) {
          _files.push_back(File(path, statbuf.st_size));
          _total_bytes_scanned += _files.back().size();
        }
      }
      closedir(dp);
    } while (dirs_to_scan.size() != 0 && recursive);
  }
  
  void Scanner::reset () {
    _total_bytes_scanned = 0;
    _scanned_directories.clear();
    _files.clear();
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