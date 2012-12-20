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

#include "filesystem.h"

#ifndef _WIN32
#include <cstdlib>
#else
#include "win/realpath.h"
#endif
#include <string>

namespace findd {
  
  namespace filesystem {
    
    const char* SEPARATORS = "/\\";
    
#ifdef _WIN32
    
    const char SEPARATOR = '\\';

#else
    
    const char SEPARATOR = '/';

#endif
    
    bool exists (const std::string &path) {
      struct stat st;
      return stat(path.c_str(), &st) == 0;
    }
    
    std::string trim_path (const std::string &path) {
      size_t last = path.length()-1;
      std::string p_trim = path;
      while (p_trim[last] == SEPARATOR) {
        p_trim = path.substr(0, last);
        last -= 1;
      }
      return p_trim;
    }

    std::string dir_concat (const std::string &first, const std::string &second) {
      return first + SEPARATOR + second;
    }
    
    std::string filename (const std::string &path) {
      return path.substr( path.find_last_of(SEPARATORS) + 1 );
    }
    
    std::string extension (const std::string &path) {
      std::string fn = filename(path);
      if (fn[0] == '.')
        return fn;
      else {
        std::string ext = fn.substr( fn.find_last_of(".") + 1 );
        return fn == ext ? "" : ext;
      }
    }
    
    bool is_hidden (const std::string &path) {
#ifdef _WIN32
        // TODO : implement it for windows system
        // @see GetFileAttributes http://msdn.microsoft.com/en-us/library/aa364944%28VS.85%29.aspx
      return false;
#else
      std::string fn = filename(path);
      return fn == extension(fn);
#endif
    }
    
    std::string real_path (const std::string &path) {
      char resolved[1024];
      realpath(path.c_str(), resolved);
      return resolved; 
    }
    
  } // end namespace filesystem
 
} // end namespace findd
