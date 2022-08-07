/*
 * Camera.cpp
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
#include "../inc/Camera.hpp"

using namespace std;
using namespace log4cxx;
using namespace raspicam;

LoggerPtr Camera::logger(Logger::getLogger("plotter.robot.camera"));

Camera::~Camera()
{
	LOG4CXX_TRACE(logger, "Camera destructor");
}

int Camera::Init(string name)
{
	SetName(name);
	LOG4CXX_DEBUG(logger, "Instance Camera named " << GetName() );
/*
	try{
		mReady=mCamera.open();
	}
	catch (int e)
	{
		mReady=false;
	}
	if (!mReady) std::cerr << "Error opening the camera " << mName << std::endl;
	*/
	SetReady(OK);
	return GetReady();
}

int Camera::Shot()
{
	if (!GetReady())
		return FALSE;
	mCamera.grab();
	return true;
}
