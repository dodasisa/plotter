/*
 * Button.hpp
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


#ifndef ___BUTTON___
#define ___BUTTON___

#include <string>
#include <pigpio.h>
#include "Component.hpp"
#include "log4cxx/logger.h"

/*! \class Button
 *  \brief Component that listen the status of a physical button
 *  \see BaseComponent
 *  The constructor calls the base class with the type button.
 */ 
class Button: public Component
{
	private:
		static log4cxx::LoggerPtr logger;
		
	public:
		/*! 
		* Default constructor
		* Sets the component type to button
		*/ 
		Button();
		
		/*! 
		* Destructor
		*/
		~Button();
		
		/*! 
		* @brief Initializes the button setting its name
		* @param name Name of the button
		*/
		int InitName(std::string name);
		
		/*! 
		* @brief Initializes the button setting its name and its pin
		* @param name Name of the button
		* @param pin Pin number
		*/
		int InitNamePin(std::string name,int pin);
		

};

#endif /* ___BUTTON___ */ 
