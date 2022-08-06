CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util
SRCS=src/Led.cpp src/Camera.cpp src/Servo.cpp src/Robot.cpp src/Config.cpp src/Component.cpp src/main.cpp 
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

