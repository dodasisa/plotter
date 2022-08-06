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
#include "Led.hpp"
#include "Constants.hpp"

Led::Led()
{
	std::cerr << "Led::Led" << endl;
	mPin=0;
	mState=OFF;
}

Led::~Led()
{
	std::cerr << "Led::~Led" << endl;
	Off();
	std::cout << "Stopping led " << mName << std::endl;
}

int Led::Init(string name,int pin)
{
	std::cerr << "Led::Init" << endl;
	mName=name;	
	mPin=pin;
	
	gpioSetMode(mPin,PI_OUTPUT);
	mState=Off();
	std::cout << "Led named " << mName << ". Using pin " << mPin << ". State is " << mState << std::endl;
	
	return OK;
}

int Led::On()
{
	std::cerr << "Led::On" << endl;
	mState=ON;
	//std::cout << "Led " << mName <<".ON" << std::endl;
	//gpioWrite(mPin,PI_HIGH);
	return mState;
}
int Led::Off()
{
	std::cerr << "Led::Off" << endl;
	mState=OFF;
	//std::cout << "Led " << mName <<".OFF" << std::endl;
	//gpioWrite(mPin,PI_LOW);
	return mState;
}
int Led::GetState()
{
	return mState;
}

int Led::Toggle()
{
	if (mState==ON)
		return Off();
	else
		return On();
}	

int Led::GetPin()
{
	return mPin;
}

