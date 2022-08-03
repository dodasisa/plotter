CC = g++
CFLAGS  = -g -Wall -I/usr/local/include
CLIBS = -lpthread -lpigpio -lrt -lraspicam -lmmal -lmmal_core -lmmal_util

plotter: main.o Led.o Camera.o Servo.o Robot.o Config.o Component.o
	$(CC) $(CFLAGS) -o plotter main.o Led.o Camera.o Servo.o Robot.o Config.o Component.o $(CLIBS)

main.o: main.cpp Led.hpp Camera.hpp Servo.hpp Robot.hpp Component.hpp
	$(CC) $(CFLAGS) -c main.cpp
	
Led.o: Led.hpp Led.cpp
	$(CC) $(CFLAGS) -c Led.cpp
	
Camera.o: Camera.hpp Camera.cpp
	$(CC) $(CFLAGS) -c Camera.cpp
	
Servo.o: Servo.hpp Servo.cpp
	$(CC) $(CFLAGS) -c Servo.cpp
	
Robot.o: Robot.hpp Robot.cpp
	$(CC) $(CFLAGS) -c Robot.cpp
	
Config.o: Config.hpp Config.cpp
	$(CC) $(CFLAGS) -c Config.cpp

Component.o: Component.hpp Component.cpp
	$(CC) $(CFLAGS) -c Component.cpp
