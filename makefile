VERSION = `head -1 inc/Version.hpp | cut -f3 -d ' '`
TESTMODULES = Component Button Led Camera Servo Robot I2Cmanager ImageHandler Config ComponentParameters
MODULES = $(TESTMODULES) main


SRCS=$(patsubst %,src/%.cpp,$(MODULES))
INCS=$(patsubst %,inc/%.hpp,$(MODULES)) inc/Constants.hpp
CXXTEST=/home/david/projets/cxxtest
TESTGEN=$(CXXTEST)/bin/cxxtestgen

TESTSRCS=$(patsubst %,src/%.cpp,$(TESTMODULES))

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util -llog4cxx
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: robot$(VERSION)

test: test/runner
	test/runner
	
test/runner: test/runner.cpp
	$(CXX) -o test/runner -I$(CXXTEST) $(TESTSRCS) test/runner.cpp $(LDLIBS)

test/runner.cpp : test/RobotTestSuite.hpp
	$(TESTGEN) --error-printer -o test/runner.cpp test/RobotTestSuite.hpp

.PHONY: docs

docs: Doxyfile
	@doxygen ./Doxyfile

robot$(VERSION): $(OBJS)
	$(CXX) $(CPPFLAGS) -o robot$(VERSION) $(OBJS) $(LDLIBS)

obj/%.o : src/%.cpp
	@echo $<
	$(CXX) $(CPPFLAFS) -c $< -o $@

clean:
	$(RM) $(OBJS) robot$(VERSION) test/runner test/runner.cpp logs/*

cleandocs:
	$(RM) html/search/* html/*.html html/*.css html/*.js html/*.png html/*.svg latex/*

distclean: clean cleandocs
	$(RM)

