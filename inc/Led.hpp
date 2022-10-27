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
#include "Component.hpp"
#include "log4cxx/logger.h"

/*! \class Led
 *  \brief Component that sets a led On and Off
 *  \see BaseComponent
 *  The constructor calls the base class with the type led.
 */ 
class Led : public Component
{
	private:
	static log4cxx::LoggerPtr logger;
	
	public:
	/*! 
		* Default constructor
		* Sets the component type to led
		*/ 
	Led();
	
	/*! 
	* Destructor
	*/
	~Led();

	/*! 
	* Defines the name and the pin where the led is connected
	* \param name Name to set as component name
	* \param pin Pin number
	* 
	* Calls SetName with the given info
	* Calls pigpio::gpioSetMode with the chosen pin and the mode pigpio.PI_OUTPUT
	*/
	bool InitNamePin(std::string name,int pin);
	
	/*! 
	* Set the led ON
	* Calls pigpio::gpioWrite with the component pin and pigpio::PI_HIGH
	*/
	int On();
	
	/*! 
	* Set the led OFF
	* Calls pigpio::gpioWrite with the component pin and pigpio::PI_LOW
	*/
	int Off();
	
	/*! 
	* Set the led OFF if if state is ON, and ON if it is OFF
	* Calls pigpio::gpioWrite with the component pin and pigpio::PI_LOW
	* \see On()
	* \see Off()
	*/
	int Toggle();
};

#endif
