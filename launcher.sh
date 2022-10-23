#!/bin/sh
unlink logs/robot.log
sudo killall pigpiod
sudo ./robot1.3
