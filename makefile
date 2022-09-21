VERSION = `head -1 inc/Version.hpp | cut -f3 -d ' '`
TESTMODULES = Component Button Led Camera Servo Screen Robot I2Cmanager ImageHandler Config ComponentParameters Options Arm
TESTSUITES = ConfigTest RobotTest ButtonTest LedTest OptionsTest
MODULES = $(TESTMODULES) main

SRCS=$(patsubst %,src/%.cpp,$(MODULES))
INCS=$(patsubst %,inc/%.hpp,$(MODULES)) inc/Constants.hpp
CXXTEST=/home/david/projets/cxxtest

TESTDEFS=$(patsubst %,test/%.hpp,$(TESTSUITES))
TESTSRCS=$(patsubst %,src/%.cpp,$(TESTMODULES))
GRAMMAR_OUT=ConfigParser.cpp ConfigParser.hpp ConfigParser.output ConfigScanner.cpp location.h
GRAMMAR_OUT_FILES=$(patsubst %,grammar/%,$(GRAMMAR_OUT))

CC=gcc
CXX=g++
TESTGEN=$(CXXTEST)/bin/cxxtestgen
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util -llog4cxx
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: robot$(VERSION)

parser: grammar/ConfigParser.yy
	bison --debug --defines=grammar/ConfigParser.hpp --verbose --output=grammar/ConfigParser.cpp --file-prefix=CP_ grammar/ConfigParser.yy
	$(CXX) $(CPPFLAGS) -c -o grammar/parserConfig.o mc_parser.tab.cc

lexer: grammar/ConfigScanner.l
	flex --outfile=grammar/ConfigScanner.cpp $<
	$(CXX) $(CPPFLAGS) -c grammar/ConfigScanner.cpp -o grammar/ConfigScanner.o

testLed: test/runnerLed
	sudo test/runnerLed
	
testButton: test/runner test/ButtonTest.hpp test/mode
	sudo test/runner ButtonTest

test/runnerLed: test/runnerLed.cpp src/Led.cpp src/Component.cpp inc/Led.hpp inc/Component.hpp
	$(CXX) -o test/runnerLed -I$(CXXTEST) src/Led.cpp src/Component.cpp inc/Led.hpp inc/Component.hpp test/runnerLed.cpp $(LDLIBS)
	
test/runnerLed.cpp : src/Led.cpp src/Component.cpp inc/Led.hpp inc/Component.hpp test/LedTest.hpp
	$(TESTGEN) --error-printer -o test/runnerLed.cpp src/Led.cpp src/Component.cpp inc/Led.hpp inc/Component.hpp test/LedTest.hpp

test: test/runner
	test/runner
	
test/runner: test/runner.cpp
	$(CXX) -o test/runner -I$(CXXTEST) $(TESTSRCS) test/runner.cpp $(TESTDEFS) $(LDLIBS)

test/runner.cpp : $(TESTDEFS)
	$(TESTGEN) --error-printer -o test/runner.cpp $(TESTSRCS) $(TESTDEFS)

.PHONY: docs

docs: Doxyfile
	@doxygen ./Doxyfile

robot$(VERSION): $(OBJS)
	$(CXX) $(CPPFLAGS) -o robot$(VERSION) $(OBJS) $(LDLIBS)

obj/%.o : src/%.cpp
	@echo $<
	$(CXX) $(CPPFLAFS) -c $< -o $@

clean:
	$(RM) $(OBJS) robot$(VERSION) test/runner* logs/* $(GRAMMAR_OUT_FILES)

cleandocs:
	$(RM) html/search/* html/*.html html/*.css html/*.js html/*.png html/*.svg latex/*

distclean: clean cleandocs
	$(RM)

