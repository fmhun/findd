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

#include "engine.h"

#include <iostream>

#include "comparator.h"

namespace findd {
  
  Engine::Engine () {}
  
  void Engine::search (file_list &files, const Comparator &compare) {
    files.sort(compare);
    
    file_list::iterator it = files.begin();
    
    for (;;) {
      const File &current = *it++;
      duplicate dup;
      dup.push_back(current);
      
      // NOTE : the order of parameters of the compare function returns the equality between the current
      //        file and the next one.
      while (it != files.end() && compare(*it, current)) {
        dup.push_back(*it++);
      }
      
      if (dup.size() > 1) _duplicates.push_back(dup);
      
      if (it == files.end()) break;
    }
  }
      
  const duplicate_list &Engine::duplicates() const {
    return _duplicates;
  }
  
  long Engine::getMaxGainOfBytes () {
    long max_gain = 0;
    for (int i = 0 ; i < _duplicates.size(); i++) {

      size_t min_size_file = _duplicates[i][0].size();
      for (int j = 0 ; j<_duplicates[i].size() ; j++) {
        size_t file_size = _duplicates[i][j].size();
        max_gain += file_size;
        if (file_size < min_size_file) min_size_file = file_size;
      }

      max_gain -= min_size_file;
    }
    return max_gain;
  }
  
  long Engine::getMinGainOfBytes () {
    long min_gain = 0;
    for (int i = 0 ; i < _duplicates.size(); i++) {

      size_t max_size_file = _duplicates[i][0].size();
      for (int j = 0 ; j<_duplicates[i].size() ; j++) {
        size_t file_size = _duplicates[i][j].size();
        min_gain += file_size;
        if (file_size > max_size_file) max_size_file = file_size;
      }

      min_gain -= max_size_file;
    }
    return min_gain;
  }
}
