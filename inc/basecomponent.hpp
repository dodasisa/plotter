/*
 * basecomponent.hpp
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


#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP
#include <string>
#include "Constants.hpp"
using namespace std;

/*! \class BaseComponent
 *  \brief Base class for components managed by the robot
 * 
 * The constructor stores the component type if given.
 * If no type given, sets to unknown.
 */ 
class BaseComponent
{
	public:
		/*! 
		* Default constructor
		* Sets the component type to unknown
		*/ 
		BaseComponent();
		/*! Constructor konwing the type
		 * @param type The type of component, a value of the enum ComponentType
		 */ 		 
		BaseComponent(ComponentType type);
		/*! 
		* Destructor
		*/
		virtual ~BaseComponent();
		/*! 
		* Initializes the Component setting its name
		* @param name Name of the component, left side of the line in the configuration file
		*/
		int InitName(std::string name);
		/*! 
		* Initializes the Component setting its name and its pin number
		* @param name Name of the component, left side of the line in the configuration file
		* @param pin Pin number where this component is connected
		*/
		int InitNamePin(std::string name,int pin);
		/*! 
		* Returns the state of the component. If ok 0, if error 1.
		*/
		int GetReady();
		/*! 
		* Sets the status of the component
		* @param ready State to set, if ok 0, if not 1
		*/
		void SetReady(int ready);
		/*! 
		* Returns the name of the component.
		*/
		string GetName();
		/*! 
		* Sets the name of the component
		* @param name Name to assign
		*/
		void SetName(string name);
		/*! 
		* Returns the state of the component; ON or OFF.
		*/
		int GetState();
		/*! 
		* Sets the state of the component
		* @param state State to set, ON or OFF
		*/
		void SetState(int state);
		/*! 
		* Returns the type of the component; led, servo, camera, button or unknown.
		*/
		ComponentType GetType();
		/*! 
		* Sets the type of the component; led, servo, camera, button or unknown.
		* @param type One of the values of the enum ComponentType
		*/
		void SetType(ComponentType type);
		/*! 
		* Returns the pin number of the component.
		*/
		int GetPin();
		/*! 
		* Sets the pin number of the component
		* @param pin Pin number
		*/
		void SetPin(int pin);
	
	private:
		int mReady;
		int mState;
		int mPin;
		string mName;
		ComponentType mType;
};

#endif /* BASECOMPONENT_HPP */ 
