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

#include <string>
#include <iostream>

#include "common.h"
#include "scanner.h"
#include "terminal.h"
#include "utils/timer.h"
#include "file.h"
#include "storage.h"

namespace findd {
  
  using std::vector;
  using std::string;
  using std::cout; using std::cerr; using std::endl;
  using utils::Timer;
  
  App::App () {}
  
  App::~App () {}

  void App::execute () {
    file_list files;
    Storage storage;
    
    if (_env.in_scan_file.empty() == false) {
      // load filelist from the backup
      files = storage.restore(_env.in_scan_file);
    } else {
      if (_env.directories.empty() == false) {  // perform new scan
        Scanner scanner;
        Timer t; t.start();
        
        for (unsigned int i = 0; i < _env.directories.size(); i++)
          scanner.scan(_env.directories[i], _env.recursive);
        t.stop();
        
        files = scanner.files();
        
        if (_env.out_scan_file.empty() == false) {
          storage.persist(files, _env.out_scan_file);
        }
        
        cout << "size of file list : " << (sizeof(File) * files.size()) << " bytes" << endl;
        cout << "scanned " << files.size() << " files (" << scanner.totalBytesScanned() << " bytes) in " << t.elapsed() << " seconds" << endl;
        
        if (_env.filter.compare_content) {
          cout << "processing files content..." << endl;
          #pragma omp parallel for
          for (int i = 0; i < files.size(); ++i) 
            files[i].compute_checksum();
        }
      } else {
        //throw ArgumentException("no input directories to scan");
      }
    }
    
    /* Search for duplicates */
  }
   
  env_t & App::env () { return _env; }
}