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
LIB_DIR = lib
INCLUDES = -Ilib/pugixml/src
CFLAGS = -ansi -pendic $(INCLUDES) -fopenmp

SRC_DIR = src
SRCOBJS = common.o crypto.o logger.o file.o duplicate.o filter.o scanner.o app.o commandline.o
DEPS_LIB = -lboost_program_options -lboost_system -lboost_filesystem
PROG_MAIN_SRC = main.cc

TEST_DIR = unittest
TEST_OBJS = filetest.o filelisttest.o duplicatetest.o filtertest.o scannertest.o configtest.o apptest.o commandlinetest.o
TEST_LIB = -lcppunit
TEST_PROG_SRC = testrunner.cc

all: findd clean

findd: $(SRCOBJS) $(PROG_MAIN_SRC:.cc=.o)
	$(CXX) $(CFLAGS) $^ -o $@ $(DEPS_LIB) $(OMPFLAGS)

pugixml.o: $(LIB_DIR)/pugixml/src/pugixml.cpp
	$(CXX) -c $^ -o $@

check: test
	@./test

test: $(SRCOBJS) $(TEST_OBJS) $(TEST_PROG_SRC:.cc=.o)
	$(CXX) $(CFLAGS) $^ -o $@ $(DEPS_LIB) $(TEST_LIB)

$(PROG_MAIN_SRC:.cc=.o): $(SRC_DIR)/$(PROG_MAIN_SRC)
	$(CXX) $(CFLAGS) -c $< -o $@

$(TEST_PROG_SRC:.cc=.o): $(TEST_DIR)/$(TEST_PROG_SRC)
	$(CXX) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

common.o: $(SRC_DIR)/common.h
	$(CXX) $(CFLAGS) -c $< -o $@

%.o: $(SRC_DIR)/utils/%.cc $(SRC_DIR)/utils/%.h
	$(CXX) $(CFLAGS) -c $< -o $@

%.o: $(SRC_DIR)/%.cc $(SRC_DIR)/%.h
	$(CXX) $(CFLAGS) -c $< -o $@

%.o: $(TEST_DIR)/%.cc $(TEST_DIR)/%.h
	$(CXX) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

.PHONY: clean

clean:
	rm -rf *.o

properclean: .PHONY
	rm -rf findd test
	
doc: .PHONY
	dioxygen