/*
 * Robot.cpp
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
#include "../inc/Robot.hpp"
#include "../inc/Constants.hpp"
using namespace log4cxx;
using namespace std;

LoggerPtr Robot::logger(Logger::getLogger("plotter.robot"));

/**
 * Robot main constructor
 * @param config A pointer to a valid Config
 */ 
Robot::Robot(Config* config)
{
	if (config->IsOnTestMode())
		logger->setLevel(Level::getOff());
	LOG4CXX_TRACE(logger, "Robot constructor");
	int errorCount = 0;
	mReady = FALSE;
	mName = config->GetValue("Name");
	LOG4CXX_INFO(logger, "Starting Robot " << mName);
	LOG4CXX_DEBUG(logger, "Found " << config->components.size() << " components in the config file");
	vector<ComponentParameters*>::iterator componentIterator;
	/// Loops every Component defined in the Config class.
	for (componentIterator = config->components.begin(); componentIterator != config->components.end(); ++componentIterator)
	{
		ComponentParameters* component = *componentIterator;
		/// Creates an component derived from Component and adds it to its components vector.
		Led* ledHolder;
		Camera* cameraHolder;
		Servo* servoHolder;
		int testState;
		switch (component->GetType())
		{
		case camera:
			cameraHolder=new Camera();
			testState=cameraHolder->InitName(component->GetName());
			mEyes=cameraHolder;
			components.push_back(cameraHolder);
			
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "CAMERA>InitName returns ERROR");
			}
			break;
		case led:
			ledHolder=new Led();
			testState=ledHolder->InitNamePin(component->GetName(), component->GetPin());	
					
			components.push_back(ledHolder);
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "LED>InitNamePin returns ERROR");
			}
			break;
		case servo:
			servoHolder=new Servo();
			testState=servoHolder->InitName(component->GetName());
			components.push_back(servoHolder);
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "SERVO>InitName returns ERROR");
			}
			break;
		case unknown:
		default:
			break;
		}
		LOG4CXX_DEBUG(logger, "Component " << component->GetName() << " added. ErrorCount=" << errorCount );
	}
	/// if any of the created components reports an error, the state if the robot is set to 0. Main() must stop.
	if (errorCount == 0) mReady = TRUE;
}

/**
 * Robot main destructor
 */ 
Robot::~Robot()
{
	LOG4CXX_TRACE(logger, "Robot destructor");
	/// calls the destructor of every component present in the components vector
	for (vector<Component*>::iterator componentIterator = components.begin(); componentIterator != components.end(); ++componentIterator)
	{
		Component* component = *componentIterator;
		delete(component);
	}
	mReady = false;
}
/**
 * Returns the content of mReady. Value 1 means OK, 0 means ERROR.
 */ 
int Robot::GetReady()
{
	return mReady;
}
/**
 * Main event loop. 
 * If GetReady returns 0 the loop doesn't start.
 * If the loop is already running and GetReady returns 0, the loop stops.
 */ 
int Robot::Run()
{
	if (!GetReady())
		return ERROR;
	mEyes->Shot();
	return OK;
}
