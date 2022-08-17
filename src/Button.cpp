/*
 * Button.cpp
 * 
 * Copyright 2022  <david@raspberrypi>
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


#include "../inc/Button.hpp"
using namespace log4cxx;

LoggerPtr Button::logger(Logger::getLogger("plotter.robot.button"));

Button::Button() : Component(button)
{
	if (IsOnTestMode()) logger->setLevel(Level::getOff());
}

Button::~Button()
{
	LOG4CXX_TRACE(logger, "Button destructor");
}

int Button::InitNamePin(string name,int pin)
{
	SetName(name);	
	SetPin(pin);
	
	gpioSetMode(GetPin(),PI_INPUT);

	LOG4CXX_DEBUG(logger, "Instance button named " << GetName() << ". Using pin " << GetPin() );
	return OK;
}

int Button::InitName(string name)
{
	SetName(name);	

	LOG4CXX_DEBUG(logger, "Instance button named " << GetName() << ". Pin undefined" << GetPin() );
	return OK;
}

ComponentType Button::GetType()
{
	return Component::GetType();
}

bool Button::Read()
{
	return gpioRead(GetPin());
}
