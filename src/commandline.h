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

#ifndef FINDD_COMMANDLINE_H_
#define FINDD_COMMANDLINE_H_

#include <boost/program_options.hpp>
#include <string>
#include <exception>
    
#include "ui.h"

namespace findd {
  
  class App; class Config;
  
  // class CommandLineException : public std::exception {
  // public:
  //   virtual ~CommandLineException () throw() {}
  // 
  //   virtual const char* what () const throw() {
  //     return "command line error";
  //   }
  // };
  // 
  // class ArgumentException : public CommandLineException {
  // public:
  //   ArgumentException () {}
  //   virtual ~ArgumentException() throw() {}
  // 
  //   virtual const char* what() const throw() {
  //     return "findd: illegal option";
  //   }
  // };
  
  class CommandLine : public Ui {
  public:
  	CommandLine ();
    virtual ~CommandLine ();
    
    int run (App &);
  	void parse (Config &, const int &, char **);
    
    void dialog (const std::string &, const UiMessageType) const;
    
    void out (const std::string &) const;
    void err (const std::string &) const;
  private:
  	const std::string help () const;
    const std::string version () const;
    
    int _argc;
    char **_argv;
    boost::program_options::variables_map *_flags;
  };
      
}

#endif	// FINDD_COMMANDLINE_H_