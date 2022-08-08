/*
 * Servo.hpp
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
 
#ifndef __SERVO__
#define __SERVO__
#include "Component.hpp"
#include "log4cxx/logger.h"

/*! \class Servo
 *  \brief Component that changes the position of a servo
 *  \see BaseComponent
 *  The constructor calls the base class with the type servo.
 */ 
class Servo : public Component
{
	private:
	static log4cxx::LoggerPtr logger;
	
	public:
	/*! 
	* Default constructor
	* Sets the component type to servo
	*/ 
	Servo() : Component(servo)
	{
		SetReady(FALSE);
	};
	
	/*! 
	* Destructor
	*/
	~Servo();
	
	/*! 
	* Sets the name of the servo
	* \param name Name to set as component name
	* 
	* Calls SetName with the given info
	*/
	int InitName(std::string name);
	
	/*! 
	* Sets the name of the servo
	* \param name Name to set as component name
	* \param pin Pin number
	* 
	* Calls SetName with the given info
	* Calls SetPin with the chosen pin
	*/
	int InitNamePin(std::string name,int pin);
};

#endif
