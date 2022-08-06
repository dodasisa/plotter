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
#include "Constants.hpp"

using namespace std;
using namespace raspicam;

class Camera
{
	private:
	int mReady;
	string mName;
	RaspiCam camera;
	
	public:
	Camera();
	~Camera();
	int Init(string name);

	int Shot();
};

#endif
