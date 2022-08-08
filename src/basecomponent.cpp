/*
 * basecomponent.cpp
 * 
 * Copyright 2022  <david@raspberrypi>
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


#include "../inc/basecomponent.hpp"


BaseComponent::BaseComponent(ComponentType type)
{
	SetType(type);
}

BaseComponent::BaseComponent()
{
	SetType(unknown);
}
BaseComponent::~BaseComponent()
{
	
}

int BaseComponent::GetReady()
{
	return mReady;
}
int BaseComponent::GetState()
{
	return mState;
}
string BaseComponent::GetName()
{
	return mName;
}
ComponentType BaseComponent::GetType()
{
	return mType;
}
int BaseComponent::GetPin()
{
	return mPin;
}
void BaseComponent::SetReady(int ready)
{
	mReady=ready;
}
void BaseComponent::SetState(int state)
{
	mState=state;
}
void BaseComponent::SetName(string name)
{
	mName=name;
}
void BaseComponent::SetType(ComponentType type)
{
	mType=type;
}
void BaseComponent::SetPin(int pin)
{
	mPin=pin;
}

int BaseComponent::InitName(std::string name)
{
	mName=name;
	return 0;
}

int BaseComponent::InitNamePin(std::string name,int pin)
{
	mName=name;
	mPin=pin;
	return 0;
}


