MODULES = Component Button Led Camera Servo Robot I2Cmanager ImageHandler Config ComponentParameters main

SRCS=$(patsubst %,src/%.cpp,$(MODULES))
INCS=$(patsubst %,inc/%.hpp,$(MODULES)) inc/Constants.hpp
CXXTEST=/home/david/projets/cxxtest
TESTGEN=$(CXXTEST)/bin/cxxtestgen


CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util -llog4cxx
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

bin: robot

all: robot docs

test: test/runner
	test/runner
	
test/runner: test/runner.cpp
	$(CXX) -o test/runner -I$(CXXTEST) test/runner.cpp

test/runner.cpp : test/RobotTestSuite.hpp
	$(TESTGEN) --error-printer -o test/runner.cpp test/RobotTestSuite.hpp

.PHONY: docs

docs:
	@doxygen ./Doxyfile

robot: $(OBJS)
	$(CXX) $(CPPFLAGS) -o robot $(OBJS) $(LDLIBS)

obj/%.o : src/%.cpp
	@echo $<
	$(CXX) $(CPPFLAFS) -c $< -o $@

clean:
	$(RM) $(OBJS) robot test/runner test/runner.cpp

cleandocs:
	$(RM) html/search/* html/*.html html/*.css html/*.js html/*.png html/*.svg latex/*

distclean: clean
	$(RM)

