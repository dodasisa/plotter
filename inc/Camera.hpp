/*
 * Camera.hpp
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
 
#ifndef __CAMERA__
#define __CAMERA__
#include <string>
#include <raspicam/raspicam.h>

#include "Component.hpp"
#include "log4cxx/logger.h"

/*! \class Camera
 *  \brief Component that controls the raspberry PI camera
 *  \see Component
 *  The constructor calls the base class with the type camera.
 */ 
class Camera : public Component
{
	private:
	raspicam::RaspiCam mCamera;
	static log4cxx::LoggerPtr logger;
	
	public:
	/*! 
	* Default constructor
	* Sets the component type to camera
	*/ 
	Camera();
	
	/*! 
	* Destructor
	*/
	~Camera();
	
	/*! 
	* Tries to open the camera using the raspicam.open() method
	* \param name Name to set as component name
	* 
	* Calls SetName with the given info
	*/
	int InitName(string name);
	
	/*! 
	* Tries to open the camera using the raspicam.open() method
	* \param name Name to set as component name
	* \param pin Pin number. Not required
	* 
	* Calls SetName with the given info
	*/
	int InitNamePin(string name,int pin);

	/*! 
	* Calls the raspicam.grab() method
	*/
	int Shot();
};

#endif
