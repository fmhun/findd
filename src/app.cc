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

#include "app.h"

#include "common.h"
#include "filelist.h"
#include "duplicate.h"
#include "file.h"
#include "scanner.h"

#include <iostream>

namespace findd {
  
  using std::vector;
  using std::string;
  
  App::App () {}
  
  App::~App () {}

  int App::execute () {
    // try {
    //   load_file_list();
    //   search_duplicates();
    // } catch FinddException &e {
    //   _term_message = e.what();
    //   return -1;
    // }
    load_file_list();
    //search_duplicates();
    
    return 0;
  }
  
  void App::load_file_list () {
    if (_env.in_scan_file != "") {
      // load filelist from the backup
    } else {
      if (!_env.directories.empty()) {  // perform new scan
        Scanner scanner;
        const std::vector<std::string> &dir = _env.directories;
        
        for (unsigned int i = 0; i < dir.size(); i++) {
          scanner.scan(dir[i]);
        }
        
        std::cout << scanner.file_list().size() * sizeof(File) << std::endl;
      } else {
        //throw ArgumentException("no input directories to scan");
      }
    }
  }
  
  void App::search_duplicates () {
    // FileList files;
    // File f1("/f1", 1), f2("/f2", 1), f3("/f2 bis", f4("/f1 bis") 1);
    // 
    // files.push_back(f1); files.push_back(f2); files.push_back(f3);
    // 
    // // Display file addresses
    // list<string>::iterator i = files.begin();
    // for (i = files.begin(); i != files.end(); ++i) {
    //   cout << &(*i) << endl;
    // }
    //   
    // vector<vector<string*> > duplicates;
    // list<string>::iterator it = files.begin();
    //   
    // // main loop to iterate over each non-identical file
    // while (it != files.end()) {
    //   vector<string*> dup;
    //   dup.push_back(&(*it));
    //   string file = *it;
    // 
    //   cout << "|__ searching duplicates for " << file << endl;
    //   it++; // point to the next element
    // 
    //   // iterate over the file list while we found that the next element is identical with the file we are processing
    //   while (it != files.end()) {
    //     if (file == *it) {   
    //       cout << "   |__ found " << *it << endl;
    //       dup.push_back(&(*it));
    //       it++; // process the next element
    //     } else {
    //       cout << "   |__ done " << file << endl;
    //       break;
    //     }
    //   }
    // 
    //   if (dup.size() != 1) {
    //     duplicates.push_back(dup);
    //   }
    // }
    
  }
  
  env_t & App::env () { return _env; }
}