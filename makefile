CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -I/usr/local/include
LDLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util
SRCS=Led.cpp Camera.cpp Servo.cpp Robot.cpp Config.cpp Component.cpp main.cpp 
OBJS=$(subst .cpp,.0,$(SRCS))

all: plotter

plotter: $(OBJS)
	$(CXX) $(CPPFLAGS) -o plotter $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAFS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) plotter

distclean: clean
	$(RM) *~ .depend

include .depend
