# Copyright (c) 2010-2014, Tamir Atias
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Author: Caleb Stewart
# Date: 5/1/2012 (M/D/Y)

CFILES:=$(shell find ./TmxParser/ -maxdepth 1 -type f -name *.c) $(shell find ./TmxParser/base64 -maxdepth 1 -type f -name *.c)
CPPFILES:=$(shell find ./TmxParser/ -maxdepth 1 -type f -name *.cpp) $(shell find ./TmxParser/base64 -maxdepth 1 -type f -name *.cpp)
COBJECTS:=$(CFILES:.c=.o)
CPPOBJECTS:=$(CPPFILES:.cpp=.o)
SOURCES:= $(CFILES) $(CPPFILES)
OBJECTS:= $(COBJECTS) $(CPPOBJECTS)
TMXHEADERS:= $(shell find ./TmxParser/ -maxdepth 1 -type f -name *.h)

LDFLAGS:=
CFLAGS:=
CPPFLAGS:=
CXXFLAGS:=

.PHONY: all clean install uninstall

all: libtmxparser.a

libtmxparser.a: $(OBJECTS)
	@echo ar libtmxparser.a
	@ar rcs libtmxparser.a $(OBJECTS)

.c.o: $(SOURCES) $(TMXHEADERS)
	@echo gcc $<
	@gcc $(CFLAGS) $(CXXFLAGS) -o $(<:.c=.o) -c $< $(LDFLAGS)

.cpp.o: $(SOURCES) $(TMXHEADERS)
	@echo g++ $<
	@g++ $(CPPFLAGS) $(CXXFLAGS) -o $(<:.cpp=.o) -c $< $(LDFLAGS)

clean:
	@echo "removing -- objects"
	@rm $(OBJECTS)
	@echo "removing -- library"
	@rm libtmxparser.a

install:
	@echo "installing -- headers"
	@install -d $(DESTDIR)/usr/include/TmxParser
	@install $(TMXHEADERS) $(DESTDIR)/usr/include/TmxParser/
	@echo "installing -- library"
	@install -d $(DESTDIR)/usr/lib/
	@install libtmxparser.a $(DESTDIR)/usr/lib/
ifeq ($(strip $(DESTDIR)),)
	@echo "installing -- running ldconfig"
	@ldconfig
endif

uninstall:
	@echo "uninstalling -- headers"
	@rm /usr/include/TmxParser/*
	@rmdir /usr/include/TmxParser
	@echo "uninstalling -- library"
	@rm /usr/lib/libtmxparser.a
	@echo "uninstalling -- running ldconfig"
	@ldconfig
