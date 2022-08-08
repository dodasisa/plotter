MODULES = basecomponent Button Led Camera Servo Robot I2Cmanager ImageHandler Config Component main

SRCS=$(patsubst %,src/%.cpp,$(MODULES))
INCS=$(patsubst %,inc/%.hpp,$(MODULES)) inc/Constants.hpp

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util -llog4cxx
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: robot

.PHONY: docs

docs:
	@doxygen ./Doxyfile

robot: $(OBJS)
	$(CXX) $(CPPFLAGS) -o robot $(OBJS) $(LDLIBS)

obj/%.o : src/%.cpp
	@echo $<
	$(CXX) $(CPPFLAFS) -c $< -o $@

clean:
	$(RM) $(OBJS) robot

cleandocs:
	$(RM) html/search/* html/*.html html/*.css html/*.js html/*.png html/*.svg latex/*

distclean: clean
	$(RM)

