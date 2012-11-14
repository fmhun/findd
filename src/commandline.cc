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

#include "commandline.h"

#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include <exception>

#include "app.h"
#include "ui.h"
#include "config.h"

namespace po = boost::program_options;

namespace findd {
  
  CommandLine::CommandLine () {}

  CommandLine::~CommandLine () { delete _flags; }
  
  int CommandLine::run (App &app) {
    app.bind(const_cast<CommandLine *>(this));
        
    if (_flags->count("help")) {
      out(help());
    } else if (_flags->count("version")) {
      out(version());
    } else {
      try {
        return app.execute();
      } catch (std::exception &e) {
        err(e.what());
        return -1;
      }
    }
    
    return 0;
  }
  
  void CommandLine::parse (Config &cnf, const int &argc, char **argv) {
    _argc = argc;
    _argv = argv;
    _flags = new po::variables_map();
    
    try {
      po::options_description general("General options");
      general.add_options()
        ("help,h", "produce help message")
        ("version,v", "produce version message")  
      ;
    
      po::options_description scanning("Scanning options");
      scanning.add_options()
        ("recursive,r", po::bool_switch(&cnf.recursive), "scan directories recursively")
          //("input-scan", po::value(), "scan backup")
      ;
    
      po::options_description all("All options");
      all.add(general).add(scanning);

      po::store(po::parse_command_line(_argc, _argv, all), *_flags);
      po::notify(*_flags);
    } catch (std::exception &e) {
      out(e.what());
    }
  }
  
  void CommandLine::dialog (const std::string &msg, const UiMessageType type) const {
    switch (type) {
      case INFO:
        out(msg);
      break;
      case ERROR:
        err(msg);
      break;
    }
  }
  
  void CommandLine::out (const std::string &msg) const {
    std::cout << msg << std::endl;
  }
  
  void CommandLine::err (const std::string &msg) const {
    std::cerr << msg << std::endl;    
  }
  
  const std::string CommandLine::help () const {
    return "findd help : \
      test";
  }
  
  const std::string CommandLine::version () const {
    return "findd version 1.0.0, University of Poitiers © 2012";
  }
  
}