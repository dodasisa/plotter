/*
 * Led.hpp
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
 
#ifndef __LED__
#define __LED__
#include <string>
#include <pigpio.h>
#include "basecomponent.hpp"
#include "log4cxx/logger.h"

class Led : public BaseComponent
{
	private:
	int mPin;
	static log4cxx::LoggerPtr logger;
	
	public:
	Led() : BaseComponent(led)
	{
		mPin=0;
		SetState(OFF);
	};
	~Led();

	int Init(std::string name,int pin);
	int On();
	int Off();
	int Toggle();	
	int GetPin();
};

#endif
