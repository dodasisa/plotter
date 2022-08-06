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

Camera::~Camera()
{
	std::cerr << "Camera::~Camera" << endl;
	std::cout << "Stopping camera " << GetName() << std::endl;
}

int Camera::Init(string name)
{
	cerr << "Camera::Init" << endl;
	SetName(name);
	std::cout << "Camera named " << GetName()  << std::endl;
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
	return GetReady();
}

int Camera::Shot()
{
	if (!GetReady())
		return FALSE;
	mCamera.grab();
	return true;
}
