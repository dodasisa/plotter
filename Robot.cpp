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
#include "Robot.hpp"
#include "Constants.hpp"

Robot::Robot(Config &config)
{
	cerr << "Robot::Robot" << endl;
	int errorCount=0;
	mReady=FALSE;
	mName=config.GetValue("Name");
	std::cout << "Starting Robot " << mName << std::endl;
	std::cout << "Found " << config.components.size() << " components in the config file" << endl;
	vector<Component>::iterator componentIterator;
	for (componentIterator = config.components.begin(); componentIterator != config.components.end(); ++componentIterator)
	{
		Component component = *componentIterator;
		switch (component.GetType())
		{
			case camera:
				cameras.push_back(new Camera());
				if (cameras.back()->Init(component.GetName()) == ERROR) errorCount++;
				break;
			case led:
				leds.push_back(new Led());
				if (leds.back()->Init(component.GetName(), component.GetPin()) == ERROR) errorCount++;
			break;
			case servo:
				servos.push_back(new Servo());
				if (servos.back()->Init(component.GetName()) == ERROR) errorCount++;
				break;
			break;
			case unknown:
			default:
			break;
		}
	}
	
//	if (!eye.Init("Eyes")) errorCount++;
//	if (!led.Init("ReadyIndicator",5)) errorCount++;
//	if (!shoulder.Init("Shoulder")) errorCount++;
//	if (!elbow.Init("Elbow")) errorCount++;
	if (errorCount==0) mReady=TRUE;
}
Robot::~Robot()
{
	cerr << "Robot::~Robot" << endl;
	for (vector<Camera*>::iterator cameraIterator = cameras.begin(); cameraIterator != cameras.end(); ++cameraIterator)
	{
		Camera *camera = *cameraIterator;
		delete(camera);
	}
	for (vector<Led*>::iterator ledIterator = leds.begin(); ledIterator != leds.end(); ++ledIterator)
	{
		Led *led = *ledIterator;
		delete(led);
	}
	for (vector<Servo*>::iterator servoIterator = servos.begin(); servoIterator != servos.end(); ++servoIterator)
	{
		Servo *servo = *servoIterator;
		delete(servo);
	}
	mReady=false;
}
int Robot::IsReady()
{
	return mReady;
}
int Robot::Run()
{
	if (!IsReady())
		return ERROR;
	return OK;
}
