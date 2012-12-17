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

#ifndef FINDD_FILESYSTEM_H_
#define FINDD_FILESYSTEM_H_

#include <sys/stat.h>
#include <string>

namespace findd {
  
 /**
  * Lightweight API to manage filesystem
  */
  namespace filesystem {
    
    bool exists (const std::string &);
    
    std::string trim_path (const std::string &);
    
    std::string dir_concat (const std::string &, const std::string &);
    
    std::string filename (const std::string &);
    
    std::string extension (const std::string &);
    
    bool is_hidden (const std::string &);
    
    std::string folder (const std::string &);
    
    std::string real_path (const std::string &);
  }

}

#endif // FINDD_FILESYSTEM_H_