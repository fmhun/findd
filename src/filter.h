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

#ifndef FINDD_FILTER_H
#define FINDD_FILTER_H

#include "common.h"

namespace findd {
    
  enum Criteria {
    NONE = 0,
    NAME = 1,
    SIZE = 2,
    CONTENT = 4
  };
  
  class Comparator {
  public:
    Comparator (Criteria mode) : _mode(mode) {}
      
    Comparator (bool cmp_name, bool cmp_size, bool cmp_content) {
      _mode = NONE;
      if (cmp_name)    _mode |= NAME;
      if (cmp_size)    _mode |= SIZE;
      if (cmp_content) _mode |= CONTENT;
    }
      
    bool compare (const File &a, const File &b) const {
      bool equals = false;
        
      if (is_enabled(NAME)) {
        equals = equals || (a.name() == b.name());
      }
        
      return equals;
    }
      
    inline int mode () const {
      return _mode;
    } 
  private:
      
    inline bool is_enabled (Criteria c) const {
      return (c & _mode) == c;
    }
    
    int _mode;
  };
    
  class Engine {
  public:
    Engine () {}
      
    void search (file_list &files, const Comparator &comparator) {
      while (files.size() > 1) {
        duplicate dup;
        File file = files.front();
        files.erase(files.begin());
        dup.push_back(file);
      
        file_list::iterator it = files.begin();
        while (it != files.end()) {
          if (comparator.compare(file, *it)) {
            dup.push_back(*it);
            files.erase(it);
          }
          ++it;
        }
        if (dup.size() > 1) {
          _duplicates.push_back(dup);
        }
      }
    }
  private:
    duplicate_list _duplicates;
  };

}

#endif