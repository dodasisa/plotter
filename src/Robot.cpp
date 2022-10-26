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
Robot::Robot()
{
}

bool Robot::Configure(Config* config)
{
	mReady=false;
	if (config->IsOnTestMode())
		logger->setLevel(Level::getOff());
	mMode = RunMode::stopped;
	LOG4CXX_TRACE(logger, "Robot Configure");
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
		//cerr << "Adding component " << component->GetName() << " of type " << component->GetType() << endl;
		/// Creates an component derived from Component and adds it to its components vector.
		switch (component->GetType())
		{
		case camera:
			errorCount=HandleCamera(component->GetName(),config->GetPhotoFileName(),errorCount,config->IsOnTestMode());
			break;
		case led:
			errorCount=HandleLed(component->GetName(),component->GetPin(),errorCount,config->IsOnTestMode());
			break;
		case servo:
			errorCount=HandleServo(component->GetName(),errorCount,config->IsOnTestMode());
			break;
		case button:
			errorCount=HandleButton(component->GetName(),component->GetPin(),errorCount,config->IsOnTestMode());
			break;
		case arm:
			errorCount=HandleArm(component->GetName(),errorCount,config->IsOnTestMode());
			break;
		case screen:
			errorCount=HandleScreen(component->GetName(),errorCount,config->IsOnTestMode());
			break;
		case unknown:
		default:
			break;
		}
		if (errorCount>0)
			return false;
		LOG4CXX_DEBUG(logger, "Component " << component->GetName() << " added. ErrorCount=" << errorCount );
	}
	/// if any of the created components reports an error, the state if the robot is set to 0. Main() must stop.
	if (errorCount == 0) mReady = TRUE;
	return mReady;
}

/**
 * Robot main destructor
 */ 
Robot::~Robot()
{
	LOG4CXX_TRACE(logger, "Robot destructor");
	mMode = RunMode::stopping;
	
	mReady = false;
	mMode = RunMode::stopped;
}
/**
 * Returns the content of mReady. Value 1 means OK, 0 means ERROR.
 */ 
bool Robot::GetReady()
{
	LOG4CXX_TRACE(logger, "Robot GetReady? " << (mReady? "Yes":"No"));
	return mReady;
}

/**
 * Returns the actual name of the robot.
 * 
 * @return mName;
 */ 
string Robot::GetName()
{
	LOG4CXX_TRACE(logger, "Robot GetName " << mName);
	return mName;
}
/**
 * Main event loop. 
 * If GetReady returns 0 the loop doesn't start.
 * If the loop is already running and GetReady returns 0, the loop stops.
 */ 
bool Robot::Run()
{
	LOG4CXX_TRACE(logger, "Robot Run");
	mMode=WaitingMode();
	//cerr << "waiting mode done" << endl;
	
	// mode changes on interruptios, when a button is pressed.
	// We have two buttons: STOP and START
	// STOP changes the mode to stopping, unless current mode is drawing; in this case the mode should be aborting
	// START changes the mode to drawing
	while (mMode != RunMode::stopping){
		if (mMode == RunMode::drawing)
		{
			// returns only when the drawing is done, or aborted
			mMode=DrawingMode();
		}
		sleep(3);
		
		mMode=RunMode::stopping;
		//cerr << "Running mode done" << endl;

	}
	mReadyIndicator.Off();
	mMode=RunMode::stopped;
	//cerr << "stopping mode done" << endl;

	LOG4CXX_INFO(logger, "Enters on mode stopped");
	return OK;
}

// when enter on waiting mode, looks down, close the eyes, put arms in rest
RunMode Robot::WaitingMode()
{
	LOG4CXX_TRACE(logger, "Robot WaitingMode");
	LOG4CXX_DEBUG(logger, mReadyIndicator.GetName());
	mReadyIndicator.On();
	mNeck.SetAngle(20.0);
	mFace.SetNeutralFace();
	mRightArm.SetNeutral();
	mLeftArm.SetNeutral();
	return RunMode::waiting;
}

RunMode Robot::DrawingMode()
{
	LOG4CXX_TRACE(logger, "Robot DrawingMode");
	mWorkingIndicator.On();
	mNeck.SetAngle(60);
	mFace.SetStaringFace();
	
	bool ImageValid=false;
	while (!ImageValid)
	{
		mEyes.Shot();	
		// manipulate image
		// evaluateimage
		ImageValid=true;
	}	
	mFace.Smile();
	mNeck.SetAngle(30);
	mFace.SetNeutralFace();
	bool PaperReady=false;
	while (!PaperReady)
	{
		PaperReady=EvaluatePaperPosition();
		if (!PaperReady) FixPaperPosition();	
		PaperReady=true;	
	}
	int Vector=0;
	int TotVectors=0;
	while (Vector < TotVectors)
	{
		DrawVector();
	}
	mNeck.SetAngle(60);
	mFace.Wink();
	mFace.Smile();
	mLeftArm.ReleasePaper();
	return WaitingMode(); // when done
}


/**
 * Opens the camera and stores in the components list. 
 */ 
int Robot::HandleCamera(string name,string fileName,int errorCount,bool testMode)
{
	LOG4CXX_TRACE(logger, "Robot HandleCamera " << fileName);
	int testState=ERROR;
	if (name == "Eyes")
	{
		mEyes.SetPhotoFileName(fileName);
		testState=mEyes.InitName(name);
		mEyes.SetTestMode(testMode);
	}
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "CAMERA.InitName returns ERROR");
	}
	return errorCount;
}
/**
 * Opens the led and stores in the components list. 
 */ 
int Robot::HandleLed(string name,int pin,int errorCount,bool testMode)
{
	LOG4CXX_TRACE(logger, "Robot HandleLed " << name);
	int testState=ERROR;
	if (name == "ReadyIndicator")
	{
		if (testState=mReadyIndicator.InitNamePin(name, pin) == ERROR)
			errorCount++;
		mReadyIndicator.SetTestMode(testMode);
	}
	if (name == "WorkingIndicator")
	{
		if (testState=mWorkingIndicator.InitNamePin(name, pin) == ERROR)
			errorCount++;
		mWorkingIndicator.SetTestMode(testMode);
	}
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "LED.InitNamePin returns ERROR. Name=" << name << ". Pin=" << pin);
	}
	return errorCount;
}
/**
 * Opens the servo and stores in the components list. 
 */ 
int Robot::HandleServo(string name,int errorCount,bool testMode)
{
	LOG4CXX_TRACE(logger, "Robot HandleServo " << name);
	int testState=ERROR;
	if (name == "Neck")
	{
		testState=mNeck.InitName(name);
		mNeck.SetTestMode(testMode);
	}
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "SERVO.InitName returns ERROR");
	}
	return errorCount;
}
/**
 * Opens the button and stores in the components list. 
 */ 
int Robot::HandleButton(string name,int pin,int errorCount,bool testMode)
{
	LOG4CXX_TRACE(logger, "Robot HandleButton " << name);
	int testState=ERROR;
	if (name=="StartWorking")
	{
		if (testState=mStartWorking.InitNamePin(name,pin) == ERROR)
			errorCount++;
		mStartWorking.SetTestMode(testMode);
	}
	if (name=="StopWorking")
	{
		if (testState=mStopWorking.InitNamePin(name,pin) == ERROR)
			errorCount++;
		mStopWorking.SetTestMode(testMode);
	}

	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "Button.InitName returns ERROR");
	}
	return errorCount;
}

int Robot::HandleScreen(string name,int errorCount,bool testMode)
{
	LOG4CXX_TRACE(logger, "Robot HandleScreen " << name);
	int testState=ERROR;
	if (name=="Face")
	{
		testState=mFace.InitName(name);
		mFace.SetTestMode(testMode);
	}
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "Screen.InitName returns ERROR");
	}
	return errorCount;
}

int Robot::HandleArm(string name,int errorCount,bool testMode)
{
	LOG4CXX_TRACE(logger, "Robot HandleArm " << name);
	int testState=ERROR;
	
	if (name=="LeftArm")
	{
		if (testState=mLeftArm.InitName(name) == ERROR)
			errorCount++;
		mLeftArm.SetTestMode(testMode);
	}

	if (name=="RightArm")
	{
		if (testState=mRightArm.InitName(name) == ERROR)
			errorCount++;
		mRightArm.SetTestMode(testMode);
	}

	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "Arm.InitName returns ERROR");
	}
	return errorCount;
}

bool Robot::EvaluatePaperPosition()
{
	LOG4CXX_TRACE(logger, "Robot EvaluatePaperPosition ");
	return true;
}

bool Robot::FixPaperPosition()
{
	LOG4CXX_TRACE(logger, "Robot FixPaperPosition ");
	return true;
}

void Robot::DrawVector()
{
	LOG4CXX_TRACE(logger, "Robot DrawVector ");
}
