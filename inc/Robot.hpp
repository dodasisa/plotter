/*
 * Robot.hpp
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
 
#ifndef __ROBOT__
#define __ROBOT__
#include <string>
#include <vector>
#include "Component.hpp"
#include "Camera.hpp"
#include "Led.hpp"
#include "Servo.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "log4cxx/logger.h"

using namespace std;

/*! \class Robot
 *  \brief Main class. Holds the components and the event loop.
 *  \param config. A valid Config object.
 * 
 * The constructor gets the configuration, instanciates and initializes 
 * all the components.
 * If no error, Run can be called. Run() holds the event loop.
 */  
class Robot
{
	private:
	static log4cxx::LoggerPtr logger;
	Camera* mEyes;
	int mReady;
	string mName;
	vector<Component*> components;
	
	public:
	Robot(Config* config);				///< Constructor. Takes a pointer to a valid Config object
	~Robot();							///< Destructor. Calls the destructor of every component
	int GetReady();						///< Value is 1 if ready for Run(). If any error value is 0
	int Run();							///< The loop to the main event loop
	string GetName();					///< Returns the actual name of the robot
};

#endif
