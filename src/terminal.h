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

#ifndef FINDD_TERMINAL_H_
#define FINDD_TERMINAL_H_

#include <iostream>
    
#include "global.h"

namespace findd {
  
  namespace commandline {
  
    using std::cout;
    using std::cerr;
    using std::endl;
  
    inline void version () {
      cerr << "findd version 1.0.0, University of Poitiers © 2012" << endl;
    }

    inline void usage () {
      cerr << "usage: findd --scan <DIRS> [--recursive] [--include-hidden] [--save <PATH>] [-NSC] [--remove]" << endl
           << "       findd --restore <PATH> [--save <PATH>] [-NSC] [--remove]" << endl;
    }
    
    inline void help () {
      cerr << "findd help :" << endl << endl;
      usage();
      cerr << endl << "Options" << endl
           << endl
           << "\t--version, -v :" << endl
           << "\t\tPrint what version you use." << endl << endl
           << "\t--help, -h :" << endl
           << "\t\tPrint the help message." << endl << endl
           << "\t--scan <DIRS>, -s :" << endl
           << "\t\tSpecify directories to scan separated by colon symbol (:). Ex : --scan /foo/bar:/bar/foo." << endl << endl
           << "\t--recursive, -r :" << endl
           << "\t\tScan directories contained into directories you specified for --scan." << endl << endl
           << "\t--include-hidden :" << endl
           << "\t\tInclude hidden files when you scan directories." << endl << endl
           << "\t--follow-symlink :" << endl
           << "\t\tFollow symbolic links. It requires that the -r option is set." << endl << endl
           << "\t--restore <PATH>, -i :" << endl
           << "\t\tfind duplicates from a file previously saved by the program." << endl << endl
           << "\t--save <PATH>, -o :" << endl
           << "\t\tStore the result of the file list built from input parameters as xml. Use it to store a scan result." << endl << endl
           << "\t--remove :" << endl
           << "\t\tEnable dialog to delete duplicates." << endl << endl
           << "\t--compare-name, -N :" << endl
           << "\t\tsearch duplicates by name" << endl << endl
           << "\t--compare-size, -S :" << endl
           << "\t\tsearch duplicates by size." << endl << endl
           << "\t--compare-content, -C :" << endl
           << "\t\tsearch duplicates by content" << endl << endl;
    }
    
    void parse_command_line (const int argc, char **argv, env_t *env);
  
  }
      
}

#endif // FINDD_TERMINAL_H_