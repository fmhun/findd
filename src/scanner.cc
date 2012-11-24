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

namespace findd {
  
  Scanner::Scanner () {
    _file_list = new std::list<File>();
    _scanned_directories = new std::vector<std::string>();
  }
  
  Scanner::~Scanner () {
    delete _file_list;
    delete _scanned_directories;
  }
  
  void Scanner::scan (const std::string &directory) {
    using namespace fs;
    using namespace std;
		
		path p(directory);
    
    if (!exists(p) || !is_directory(p)) {
      return;
    }
  
    list<path> dirs_to_scan;
    dirs_to_scan.push_back(p);

    while (dirs_to_scan.size() != 0) {
      path dir = dirs_to_scan.front();
      dirs_to_scan.pop_front();
      _scanned_directories->push_back(dir.string());

      vector<path> contents;
      copy(directory_iterator(dir), directory_iterator(), back_inserter(contents));

      for (vector<path>::const_iterator it(contents.begin()); it != contents.end(); ++it) {
        if (is_directory(*it)) {
          dirs_to_scan.push_back(*it);
        } else if (is_regular_file(*it)) {
          _file_list->push_back(File(*it));
        } else {
          // TODO : what should we do for elements which are not a directory and not a regular file.  
        }
      }
    }
	}

  const std::vector<std::string> &Scanner::scanned_directories () const {
    return *_scanned_directories;
  }
  
  const std::list<File> &Scanner::file_list () const {
    return *_file_list;
  }
  
}