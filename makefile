MODULES = basecomponent Led Camera Servo Robot Config Component main

SRCS=$(patsubst %,src/%.cpp,$(MODULES))
INCS=$(patsubst %,inc/%.hpp,$(MODULES)) inc/Constants.hpp

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: robot

robot: $(OBJS)
	$(CXX) $(CPPFLAGS) -o robot $(OBJS) $(LDLIBS)

obj/%.o : src/%.cpp
	@echo $<
	$(CXX) $(CPPFLAFS) -c $< -o $@

clean:
	$(RM) $(OBJS) robot

distclean: clean
	$(RM)

