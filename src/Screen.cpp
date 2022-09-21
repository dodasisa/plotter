/*
 * Screen.cpp
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
#include "../inc/Screen.hpp"
#include "../inc/Constants.hpp"

using namespace std;
using namespace log4cxx;

LoggerPtr Screen::logger(Logger::getLogger("plotter.robot.screen"));

Screen::Screen() : Component(screen)
{
	if (IsOnTestMode()) logger->setLevel(Level::getOff());
	SetReady(FALSE);
};
	
Screen::~Screen()
{
	LOG4CXX_TRACE(logger, "Screen destructor");
	SetReady(FALSE);
}

int Screen::InitName(string name)
{
	SetName(name);
	SetReady(TRUE);
	LOG4CXX_DEBUG(logger, "Instance screen named " << GetName() );
	return GetReady();
}

int Screen::InitNamePin(string name,int pin)
{
	SetName(name);
	SetPin(pin);
	SetReady(TRUE);
	LOG4CXX_DEBUG(logger, "Instance screen named " << GetName() );
	return GetReady();
}
void Screen::SetNeutralFace()
{
}

void Screen::SetStaringFace()
{}

void Screen::Smile()
{}
void Screen::Wink()
{}
