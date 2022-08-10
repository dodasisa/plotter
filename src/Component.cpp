/*
 * Component.cpp
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


#include "../inc/Component.hpp"

Component::Component(ComponentType type)
{
	SetType(type);
}

Component::Component()
{
	SetType(unknown);
}
Component::~Component()
{
	
}

int Component::GetReady()
{
	return mReady;
}
int Component::GetState()
{
	return mState;
}
string Component::GetName()
{
	return mName;
}
ComponentType Component::GetType()
{
	return mType;
}
int Component::GetPin()
{
	return mPin;
}
void Component::SetReady(int ready)
{
	mReady=ready;
}
void Component::SetState(int state)
{
	mState=state;
}
void Component::SetName(string name)
{
	mName=name;
}
void Component::SetType(ComponentType type)
{
	mType=type;
}
void Component::SetPin(int pin)
{
	mPin=pin;
}

int Component::InitName(std::string name)
{
	mName=name;
	return 0;
}

int Component::InitNamePin(std::string name,int pin)
{
	mName=name;
	mPin=pin;
	return 0;
}

void Component::SetTestMode()
{
	mTest=true;
}

bool Component::IsOnTestMode()
{
	return mTest;
}

