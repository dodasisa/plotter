/*
 * Led.cpp
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
#include "../inc/Led.hpp"
#include "../inc/Constants.hpp"

using namespace std;
using namespace log4cxx;

LoggerPtr Led::logger(Logger::getLogger("plotter.robot.led"));

Led::Led() : Component(led)
{
	if (IsOnTestMode()) logger->setLevel(Level::getOff());
	SetPin(0);
	SetState(OFF);
}

Led::~Led()
{
	LOG4CXX_TRACE(logger, "Led destructor");
	Off();
}

int Led::InitNamePin(string name,int pin)
{
	
	SetName(name);	
	SetPin(pin);
	SetReady(OK);
	
	//gpioSetMode(GetPin(),PI_OUTPUT);
	SetState(Off());

	LOG4CXX_DEBUG(logger, "Instance led named " << GetName() << ". Using pin " << GetPin() << ". State is " << GetState() );
	return GetReady();
}

int Led::InitName(string name)
{
	
	SetName(name);	
	LOG4CXX_ERROR(logger, "Instance led named " << GetName() << ". No pin defined");
	return ERROR;
}

int Led::On()
{
	LOG4CXX_TRACE(logger, "Led ON");
	SetState(ON);
	//gpioWrite(mPin,PI_HIGH);
	return GetState();
}
int Led::Off()
{
	LOG4CXX_TRACE(logger, "Led OFF");
	SetState(OFF);
	//gpioWrite(mPin,PI_LOW);
	return GetState();
}

int Led::Toggle()
{
	if (GetState()==ON)
		return Off();
	else
		return On();
}	


