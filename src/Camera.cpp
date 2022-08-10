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
#include <fstream>

#include "../inc/Camera.hpp"

using namespace std;
using namespace log4cxx;
using namespace raspicam;

LoggerPtr Camera::logger(Logger::getLogger("plotter.robot.camera"));

Camera::Camera() : Component(camera)
{
	if (IsOnTestMode()) logger->setLevel(Level::getOff());
		SetReady(FALSE);
}

Camera::~Camera()
{
	LOG4CXX_TRACE(logger, "Camera destructor");
}

int Camera::InitName(string name)
{
	SetName(name);
	LOG4CXX_DEBUG(logger, "Instance Camera named " << GetName() );

	try{
		SetReady(mCamera.open());
	}
	catch (int e)
	{
		SetReady(false);
	}
	if (!GetReady()) LOG4CXX_ERROR(logger, "Error opening the camera " << GetName() );
	
	SetReady(OK);
	return GetReady();
}

int Camera::InitNamePin(string name, int pin)
{
	return InitName(name);
}

int Camera::Shot()
{
	if (!GetReady())
		return FALSE;
	mCamera.grab();
	unsigned char *data=new unsigned char[  mCamera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
	
	string outimage=ImagesFolder + "/" + PhotoName + ".ppm";
	LOG4CXX_DEBUG(logger, "Saving the photo to " << outimage );
	
	mCamera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );
	//mCamera.retrieve ( data,raspicam::RASPICAM_FORMAT_IGNORE );
	ofstream outFile (outimage,ios::binary );
	outFile<<"P6\n"<<mCamera.getWidth() <<" "<<mCamera.getHeight() <<" 255\n";
	outFile.write ( ( char* ) data, mCamera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
	
	delete data;
	return true;
}

void Camera::SetParameters(string folder,string photo)
{
	ImagesFolder=folder;
	PhotoName=photo;
}
