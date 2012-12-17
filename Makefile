# This file is part of the Findd project from University of Poitiers (FR).
# 	
# Copyright (C) 2012
# 	
# Florian Mhun <florian.mhun@gmail.com>
# Sara Ressam  <sara.ressam@gmail.com>
# Bastien Nouhant <bastien.nouhant@gmail.com>
# Jérôme Cornet <jerome.cornet@etu.univ-poitiers.fr>
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#   * Neither the name of the <organization> nor the
#     names of its contributors may be used to endorse or promote products
#     derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

CXX = g++
CC = gcc

LIB_DIR = lib
SRC_DIR = src

LIB_INCLUDE_DIR = ./include
INCLUDES = -I$(LIB_INCLUDE_DIR)
CFLAGS = $(INCLUDES)
OMPFLAGS = -fopenmp

SRC_OBJS = crypto.o filesystem.o utils.o storage.o file.o duplicate.o comparator.o engine.o scanner.o app.o terminal.o
DEPS_OBJS = pugixml.o md5.o
PROG_MAIN_SRC = main.cc

TEST_DIR = unittest
TEST_OBJS = filetest.o filesystemtest.o scannertest.o enginetest.o comparatortest.o
TEST_LIB = -lcppunit
TEST_PROG_SRC = testrunner.cc

INSTALL = /usr/bin/install -c

PREFIX = /usr/local
BIN_PREFIX = 
BIN_DIR = $(PREFIX)/bin

all: findd changelog

findd: $(SRC_OBJS) $(DEPS_OBJS) $(PROG_MAIN_SRC:.cc=.o)
	$(CXX) $(CFLAGS) $^ -o $@

pugixml.o: $(LIB_DIR)/pugixml/src/pugixml.cpp
	$(CXX) -c $^ -o $@
	@cp $(LIB_DIR)/pugixml/src/pugiconfig.hpp $(LIB_DIR)/pugixml/src/pugixml.hpp $(LIB_INCLUDE_DIR)

md5.o: $(LIB_DIR)/md5/md5c.c
	$(CC) -c $^ -o $@
	@cp $(LIB_DIR)/md5/md5.h $(LIB_INCLUDE_DIR)

dist: .PHONY
	@mkdir -p dist
	ARCH=32 MINGWCXX=/usr/local/mingw32/bin/i686-w64-mingw32-g++ MINGWCC=/usr/local/mingw32/bin/i686-w64-mingw32-gcc $(MAKE) dist-win
	ARCH=64 MINGWCXX=/usr/local/mingw64/bin/x86_64-w64-mingw32-g++ MINGWCC=/usr/local/mingw64/bin/x86_64-w64-mingw32-gcc $(MAKE) dist-win
	
dist-win:
	@mkdir -p dist/win$(ARCH)
	$(MINGWCC) -c $(LIB_DIR)/md5/md5c.c -o md5-win$(ARCH).o
	$(MINGWCXX) -c $(LIB_DIR)/pugixml/src/pugixml.cpp -o pugixml-win$(ARCH).o
	$(MINGWCXX) $(CFLAGS) $(addprefix $(SRC_DIR)/,$(subst .o,.cc,$(SRC_OBJS))) $(SRC_DIR)/$(PROG_MAIN_SRC) md5-win$(ARCH).o pugixml-win$(ARCH).o -o dist/win$(ARCH)/findd.exe
	@rm -f md5-win$(ARCH).o pugixml-win$(ARCH).o

install: all
	$(INSTALL) findd $(BIN_DIR)/$(BIN_PREFIX)findd
	
check: test
	@./test

test: $(SRC_OBJS) $(TEST_OBJS) $(DEPS_OBJS) $(TEST_PROG_SRC:.cc=.o)
	$(CXX) $(CFLAGS) $^ -o $@ -I$(SRC_DIR) $(TEST_LIB)

$(PROG_MAIN_SRC:.cc=.o): $(SRC_DIR)/$(PROG_MAIN_SRC)
	$(CXX) $(CFLAGS) -c $< -o $@

$(TEST_PROG_SRC:.cc=.o): $(TEST_DIR)/$(TEST_PROG_SRC)
	$(CXX) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

%.o: $(SRC_DIR)/%.cc $(SRC_DIR)/%.h
	$(CXX) $(CFLAGS) -c $< -o $@

%.o: $(TEST_DIR)/%.cc $(TEST_DIR)/%.h
	$(CXX) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

.PHONY:

clean:
	rm -f *.o *~

properclean: .PHONY
	rm -f findd test

changelog:
	@git log --stat --name-only --date=short --abbrev-commit > ChangeLog

doc: .PHONY
	dioxygen