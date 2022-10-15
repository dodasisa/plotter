/*
 * Arm.cpp
 * 
 * Copyright 2022 David <david.lopez.velazquez@gmail.com>
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


#include "../inc/Arm.hpp"


Arm::Arm()
	: Component(arm)
{
	LOG4CXX_TRACE(logger, "Arm constructor");
}


Arm::~Arm()
{
	LOG4CXX_TRACE(logger, "Arm destructor");
}

void Arm::SetNeutral()
{
	LOG4CXX_TRACE(logger, "Arm SetNeutral");
}

void Arm::ReleasePaper()
{
	LOG4CXX_TRACE(logger, "Arm ReleasePaper");
}

int Arm::InitName(string name)
{
	LOG4CXX_TRACE(logger, "Arm InitName");
	SetName(name);	

//	LOG4CXX_DEBUG(logger, "Instance arm named " << GetName()  );
	return OK;
}

