/**
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

#include "terminal.h"

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include <cstdio>
#include <getopt.h>

namespace findd {

  namespace commandline {
    
    using std::cout;
    using std::cerr;
    using std::endl;
    
#ifdef _WIN32
    const char *DIR_ARG_SEPARATOR = ";";
#endif
    const char *DIR_ARG_SEPARATOR = ":";
    
    void parse_command_line (const int argc, char **argv, env_t *env) {
      
      const char *short_options = "hvrNSCs:i:o:";
      
      static struct option long_options[] = 
      {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        
        // scan option
        {"recursive", no_argument, 0, 'r'},
        {"include-hidden", no_argument, (int*)&env->include_hidden, 1},
        
        // scan params
        {"scan", required_argument, 0, 's'},
        {"restore", required_argument, 0, 'i'},
        {"save", required_argument, 0, 'o'},
        
        // duplicates searching option
        {"remove", no_argument, (int*)&env->remove, 1},
        
        // duplicates searching params
        {"compare-name", no_argument, 0, 'N'},
        {"compare-size", no_argument, 0, 'S'},
        {"compare-content", no_argument, 0, 'C'},
        
          // TODO : verbosity
        {0,0,0,0}
      };
      
      // parse commandline
      int c;
      for(;;) {
        
        int option_index = 0;
        c = getopt_long (argc, argv, short_options, long_options, &option_index);
        
        if (c == -1) break;
        else if (c == 0) c = *(long_options[option_index].flag);
        
        char *dir;
        switch (c) {
        case 1:
          break;
        case 'h':
          help();
          exit(EXIT_FAILURE);
          break;
        case 'v':
          version();
          exit(EXIT_FAILURE);
          break;
        case 'r':
          env->recursive = true;
          break;
        case 'N':
          env->comparator.enable(NAME);
          break;
        case 'S':
          env->comparator.enable(SIZE);
          break;
        case 'C':
          env->comparator.enable(CONTENT);
          break;
        case 's':
          dir = strtok(optarg, DIR_ARG_SEPARATOR);
          while (dir != 0) {
            env->directories.push_back(dir);
            dir = strtok (0, DIR_ARG_SEPARATOR);
          }
          break;
        case 'i':
          env->in_scan_file = optarg;
          break;
        case 'o':
          env->out_scan_file = optarg;
          break;
        case '?':
          usage();
          exit(EXIT_FAILURE);
          break;
        default:
          break;
        }
      }
      
      // analyse options semantic
      if (env->directories.empty() && env->in_scan_file.empty())
        throw std::logic_error("missing option --scan or --restore");
      else if (!env->directories.empty() && !env->in_scan_file.empty())
        throw std::logic_error("--scan and --restore options can not be used together");
      else if (!env->in_scan_file.empty() && env->comparator.mode() == 0)
        throw std::logic_error("--restore option requires one filter criteria at least [-NSC]");
    }
    
  }

}