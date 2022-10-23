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
using namespace log4cxx;

LoggerPtr Component::logger(Logger::getLogger("plotter.component"));

Component::Component(ComponentType type)
{
	LOG4CXX_TRACE(logger, "Component constructor type = " << type);
	SetType(type);
}

Component::Component()
{
	LOG4CXX_TRACE(logger, "Component constructor()");
	SetType(unknown);
}
Component::~Component()
{
	LOG4CXX_TRACE(logger, "Component destructor. Name=" << mName << ". Type=" << mType);
}

int Component::GetReady()
{
	LOG4CXX_TRACE(logger, "Component GetReady ? " << mReady);
	return mReady;
}
int Component::GetState()
{
	LOG4CXX_TRACE(logger, "Component " << mName << " GetState ? " << mState);
	return mState;
}
string Component::GetName()
{
	LOG4CXX_TRACE(logger, "Component GetName ? " << mName);
	return mName;
}
ComponentType Component::GetType()
{
	LOG4CXX_TRACE(logger, "Component " << mName << " GetType ? " << mType );
	return mType;
}
int Component::GetPin()
{
	LOG4CXX_TRACE(logger, "Component " << mName << " GetPin ? "  << mPin);
	return mPin;
}
void Component::SetReady(int ready)
{
	LOG4CXX_TRACE(logger, "Component " << mName << " SetReady ? " << mReady);
	mReady=ready;
}
void Component::SetState(int state)
{
	LOG4CXX_TRACE(logger, "Component " << mName << ". SetState to " << state);
	mState=state;
}
void Component::SetName(string name)
{
	LOG4CXX_TRACE(logger, "Component SetName to " << name);
	mName=name;
}
void Component::SetType(ComponentType type)
{
	LOG4CXX_TRACE(logger, "Component SetType to " << type);
	mType=type;
}
void Component::SetPin(int pin)
{
	LOG4CXX_TRACE(logger, "Component SetPin to " << pin);
	mPin=pin;
}

int Component::InitName(std::string name)
{
	LOG4CXX_TRACE(logger, "ComponentInitName " << name);
	mName=name;
	return 0;
}

int Component::InitNamePin(std::string name,int pin)
{
	LOG4CXX_TRACE(logger, "Component InitNamePin " << name << ". pin= " << pin);
	mName=name;
	mPin=pin;
	return 0;
}

void Component::SetTestMode()
{
	LOG4CXX_TRACE(logger, "Component " << mName << " SetTestMode");
	mTest=true;
}

bool Component::IsOnTestMode()
{
	LOG4CXX_TRACE(logger, "Component " << mName << " IsOnTestMode ? " << mTest);
	return mTest;
}
