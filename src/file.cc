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

#include "file.h"

#include <unistd.h>

#include <string>
#include <iostream>
#include <fstream>

#include "utils/crypto.h"

namespace findd {
  
  using utils::crypto::md5;
  
  File::File (const string &name, const string &extension, const string &absolute_path, unsigned int size) 
      : _name(name), _extension(extension), _absolute_path(absolute_path), _size(size) 
  {}
  
  File::File (const fs::path &p) {
    _name = p.filename().string();
    _extension = p.extension().string();
    _absolute_path = fs::canonical(p).string();
    _size = fs::file_size(p);
  }
  
  File::File (const File &f) {
    _name = f._name;
    _extension = f._extension;
    _absolute_path = f._absolute_path;
    _size = f._size;
  }

  bool File::drop () const {
  	return ::unlink(_absolute_path.c_str());
  }
  
  void File::compute_checksum () {
    FILE* f = fopen(_absolute_path.c_str(), "r");
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    
    char *fcontent = new char[fsize];
    rewind(f);
    fread(fcontent, sizeof(char), fsize, f);
    fclose(f);
    
    _content_digest = md5(fcontent, fsize);
    delete [] fcontent;
  }

  string File::name () const {
  	return _name;
  }
  
  string File::extension () const {
  	return _extension;
  }

  string File::absolute_path () const {
  	return _absolute_path;
  }

  string File::content_digest () {
    if (_content_digest.empty()) compute_checksum();
  	return _content_digest;
  }

  unsigned int File::size () const {
  	return _size;
  }
  
}