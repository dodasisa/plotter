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

LoggerPtr Robot::logger(Logger::getLogger("plotter.robot"));

/**
 * Robot main constructor
 * @param config A pointer to a valid Config
 */ 
Robot::Robot(Config* config)
{
	if (config->IsOnTestMode())
		logger->setLevel(Level::getOff());
	mMode = RunMode::stopped;
	LOG4CXX_TRACE(logger, "Robot constructor");
	int errorCount = 0;
	mReady = FALSE;
	mName = config->GetName();
	LOG4CXX_INFO(logger, "Starting Robot " << mName);
	LOG4CXX_DEBUG(logger, "Found " << config->components.size() << " components in the config file");
	vector<ComponentParameters*>::iterator componentIterator;
	mMode = RunMode::starting;
	/// Loops every Component defined in the Config class.
	for (componentIterator = config->components.begin(); componentIterator != config->components.end(); ++componentIterator)
	{
		ComponentParameters* component = *componentIterator;
		/// Creates an component derived from Component and adds it to its components vector.
		Led* ledHolder;
		Camera* cameraHolder;
		Servo* servoHolder;
		Button* buttonHolder;
		int testState;
		switch (component->GetType())
		{
		case camera:
			// HandleCamera(component->GetName(),config->GetPhotoFileName()); // This should replace the whole case code
			cameraHolder=new Camera();
			cameraHolder->SetPhotoFileName(config->GetPhotoFileName());
			testState=cameraHolder->InitName(component->GetName());
			if (component->GetName()== "Eyes")
				mEyes=cameraHolder;
			components.push_back(cameraHolder);
			
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "CAMERA->InitName returns ERROR");
			}
			break;
		case led:
			// HandleLed(component->GetName(),component->GetPin()); // This should replace the whole case code
			ledHolder=new Led();
			testState=ledHolder->InitNamePin(component->GetName(), component->GetPin());	
			if (component->GetName() == "ReadyIndicator")
				mReadyIndicator=ledHolder;
			if (component->GetName() == "WorkingIndicator")
				mWorkingIndicator=ledHolder;
			components.push_back(ledHolder);
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "LED->InitNamePin returns ERROR");
			}
			break;
		case servo:
			// HandleServo(component->GetName()); // This should replace the whole case code
			servoHolder=new Servo();
			testState=servoHolder->InitName(component->GetName());
			components.push_back(servoHolder);
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "SERVO->InitName returns ERROR");
			}
			break;
		case button:
			// HandleButton(component->GetName()); // This should replace the whole case code
			buttonHolder=new Button();
			testState=buttonHolder->InitName(component->GetName());
			components.push_back(buttonHolder);
			if (testState==ERROR) 
			{
				errorCount++;
				LOG4CXX_ERROR(logger, "Button->InitName returns ERROR");
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
	mMode = RunMode::stopping;
	Camera* camera2remove;
	Led* led2remove;
	Servo* servo2remove;
	Button* button2remove;
	/// calls the destructor of every component present in the components vector
	for (vector<Component*>::iterator componentIterator = components.begin(); componentIterator != components.end(); ++componentIterator)
	{
		Component* component = *componentIterator;
		switch (component->GetType())
		{
			case ComponentType::camera:
				camera2remove=(Camera*)component;
				delete(camera2remove);
				break;
			case ComponentType::led:
				led2remove=(Led*)component;
				delete(led2remove);
				break;
			case ComponentType::servo:
				servo2remove=(Servo*)component;
				delete(servo2remove);
				break;
			case ComponentType::button:
				button2remove=(Button*)component;
				delete(button2remove);
				break;
			default:
				delete(component);
				break;
		}
	}
	mReady = false;
	mMode = RunMode::stopped;
}
/**
 * Returns the content of mReady. Value 1 means OK, 0 means ERROR.
 */ 
int Robot::GetReady()
{
	return mReady;
}

/**
 * Returns the actual name of the robot.
 * 
 * @return mName;
 */ 
string Robot::GetName()
{
	return mName;
}
/**
 * Main event loop. 
 * If GetReady returns 0 the loop doesn't start.
 * If the loop is already running and GetReady returns 0, the loop stops.
 */ 
int Robot::Run()
{
	// Initialize and enter on ready mode
	if (!GetReady())
		return ERROR;
	
	LOG4CXX_INFO(logger, "Enters on mode waiting");
	mMode = RunMode::waiting;	
	mReadyIndicator->On();
	while (mMode != RunMode::stopping){
		while (mMode == RunMode::waiting)
		{		
			sleep(3);
			// check buttons status
			// if buttonStop is ON, change the mode to stopping
			// if buttonWakeUp is ON, change the mode to looking
			// TODO: Remove this. It is just to avoid running forever, while debuging
			mMode = RunMode::looking;
			LOG4CXX_INFO(logger, "Enters on mode looking");
		}
		
		if (mMode==RunMode::looking)
		{
			mWorkingIndicator->On();
			mEyes->Shot();
			sleep(1);
			mWorkingIndicator->Off();
			sleep(1);
			mWorkingIndicator->On();
			sleep(1);
			mWorkingIndicator->Off();
			sleep(1);
			mWorkingIndicator->On();
			sleep(1);
			// TODO: Remove this. It is just to avoid running forever, while debuging
			mMode = RunMode::stopping;
			LOG4CXX_INFO(logger, "Enters on mode stopping");
			mWorkingIndicator->Off();
		}
	}
	mReadyIndicator->Off();
	mMode=RunMode::stopped;
	LOG4CXX_INFO(logger, "Enters on mode stopped");
	return OK;
}
