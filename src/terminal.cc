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

#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>

#include "app.h"
#include "global.h"

using namespace boost;
using std::logic_error;
using std::string;

void validate(boost::any& v, const std::vector<std::string >& values, filter_t* /* target_type */, int) {
  using namespace boost::program_options;
  
  filter_t f;
  
  validators::check_first_occurrence(v);
  std::string in = validators::get_single_string(values);
  std::transform(in.begin(), in.end(), in.begin(), ::tolower);
  
  for (unsigned int i = 0; i < in.length(); i++) {
    if (in.at(i) == 'n') {
      f.compare_name = true;
    } else if (in.at(i) == 's') {
      f.compare_size = true;
    } else if (in.at(i) == 'c') {
      f.compare_content = true;
    } else {
      throw logic_error(string("The filter combinasion '") 
              + in + "' is not valid. run with --help to see available modes.");
    }
  }
  
  v = f;
}

namespace { // Auxiliary functions for checking input for validity.
    
  using namespace boost::program_options;
    
  // Function used to check that 'opt1' and 'opt2' are not specified at the same time.
  void conflicting_options(const variables_map& vm, 
                           const char* opt1, const char* opt2) {
      if (vm.count(opt1) && !vm[opt1].defaulted() 
          && vm.count(opt2) && !vm[opt2].defaulted())
          throw logic_error(string(opt1) + " and " + opt2 + " options can not be used together.");
  }

  // Function used to check that of 'for_what' is specified, then 'required_option' is specified too.
  void option_dependency(const variables_map& vm,
                          const char* for_what, const char* required_option){
      if (vm.count(for_what) && !vm[for_what].defaulted())
          if (vm.count(required_option) == 0 || vm[required_option].defaulted())
              throw logic_error(string("option ") + for_what 
                                + " requires option '" + required_option + "'.");
  }
    
}

namespace findd {
  
  namespace po = boost::program_options;
  
  Terminal::Terminal () {
    _options = new boost::program_options::options_description();
  }

  Terminal::~Terminal () {
    delete _options;
  }
  
  bool Terminal::parse (env_t &env, const int &argc, char **argv) {
    _argc = argc;
    _argv = argv;
    
    po::options_description general("General options");
    general.add_options()
      ("help,h", "produce help message")
      ("version,v", "produce version message")  
    ;
      
    po::options_description scanning("Scanning options");
    scanning.add_options()
      ("recursive,r", po::bool_switch(&env.recursive)->default_value(false), "scan directories recursively if specified")
      ("scan,s", po::value< std::vector<std::string> >(&env.directories)->multitoken(), "list of directories to scan")
      ("restore,i", po::value<std::string>(&env.in_scan_file), "restore a scan from a backup")
      ("save,o", po::value<std::string>(&env.out_scan_file), "save scanned files")
      ("include-hidden", po::bool_switch(&env.include_hidden)->default_value(false), "include hidden files for searching")
    ;
      
    po::options_description filtering("Filtering options");
    scanning.add_options()
      ("filter,f", po::value<filter_t>(&env.filter)->required(), "apply filter to search duplicates")
      ("remove", po::bool_switch(&env.remove)->default_value(false), "do not ask for duplicates removal");
    ;
    
    _options->add(general).add(filtering).add(scanning);
    
    
    try {
      po::store(po::parse_command_line(_argc, _argv, *_options), _flags);
      
      if (_flags.count("help")) {
        help();
      } else if (_flags.count("version")) {
        version();
      } else {
        conflicting_options(_flags, "scan", "restore");
        conflicting_options(_flags, "restore", "save");
        conflicting_options(_flags, "filter", "nofilter");
        option_dependency(_flags, "scan", "filter");
        option_dependency(_flags, "restore", "filter");
        
        po::notify(_flags);
      }
    } catch (std::exception &e) { 
      std::cerr << e.what() << std::endl;
      return false;
    }
    return true;
  }
    
}