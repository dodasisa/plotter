/*
 * Servo.cpp
 * 
 * Copyright 2022  <david.lopez.velazquez@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <iostream>
#include "../inc/Servo.hpp"
#include "../inc/Constants.hpp"

using namespace std;
using namespace log4cxx;

LoggerPtr Servo::logger(Logger::getLogger("plotter.robot.servo"));

Servo::Servo() : Component(servo)
{
	if (IsOnTestMode()) logger->setLevel(Level::getOff());
	LOG4CXX_TRACE(logger, "Servo constructor");
	SetReady(FALSE);
};
	
Servo::~Servo()
{
	LOG4CXX_TRACE(logger, "Servo destructor");
	SetReady(FALSE);
}

int Servo::InitName(string name)
{
	LOG4CXX_TRACE(logger, "Servo InitName");
	SetName(name);
	SetReady(TRUE);
	LOG4CXX_DEBUG(logger, "Instance servo named " << GetName() );
	return GetReady();
}

int Servo::InitNamePin(string name,int pin)
{
	LOG4CXX_TRACE(logger, "Servo InitNamePin");
	SetName(name);
	SetPin(pin);
	SetReady(TRUE);
	LOG4CXX_DEBUG(logger, "Instance servo named " << GetName() );
	return GetReady();
}

void Servo::SetAngle(float angle)
{
	LOG4CXX_TRACE(logger, "Servo SetAngle");
}
