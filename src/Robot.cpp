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
Robot::Robot(Config* config)
{
	if (config->IsOnTestMode())
		logger->setLevel(Level::getOff());
	mMode = RunMode::stopped;
	LOG4CXX_TRACE(logger, "Robot constructor");
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
		cerr << "Adding component " << component->GetName() << " of type " << component->GetType() << endl;
		/// Creates an component derived from Component and adds it to its components vector.
		switch (component->GetType())
		{
		case camera:
			errorCount=HandleCamera(component->GetName(),config->GetPhotoFileName(),errorCount);
			break;
		case led:
			errorCount=HandleLed(component->GetName(),component->GetPin(),errorCount);
			break;
		case servo:
			errorCount=HandleServo(component->GetName(),errorCount);
			break;
		case button:
			errorCount=HandleButton(component->GetName(),errorCount);
			break;
		case arm:
			errorCount=HandleArm(component->GetName(),errorCount);
			break;
		case screen:
			errorCount=HandleScreen(component->GetName(),errorCount);
			break;
		case unknown:
		default:
			break;
		}
		cerr << "Component " << component->GetName() << " added. ErrorCount=" << errorCount << endl;
		LOG4CXX_DEBUG(logger, "Component " << component->GetName() << " added. ErrorCount=" << errorCount );
	}
	/// if any of the created components reports an error, the state if the robot is set to 0. Main() must stop.
	if (errorCount == 0) mReady = TRUE;
}

/**
 * Robot main destructor
 */ 
Robot::~Robot()
{
	LOG4CXX_TRACE(logger, "Robot destructor");
	mMode = RunMode::stopping;
	Camera* camera2remove;
	Led* led2remove;
	Servo* servo2remove;
	Button* button2remove;
	Arm* arm2remove;
	Screen* screen2remove;
	/// calls the destructor of every component present in the components vector
	for (vector<Component*>::iterator componentIterator = components.begin(); componentIterator != components.end(); ++componentIterator)
	{
		Component* component = *componentIterator;
		switch (component->GetType())
		{
			case ComponentType::camera:
				camera2remove=(Camera*)component;
				delete(camera2remove);
				break;
			case ComponentType::led:
				led2remove=(Led*)component;
				delete(led2remove);
				break;
			case ComponentType::servo:
				servo2remove=(Servo*)component;
				delete(servo2remove);
				break;
			case ComponentType::button:
				button2remove=(Button*)component;
				delete(button2remove);
				break;
			case ComponentType::arm:
				arm2remove=(Arm*)component;
				delete(arm2remove);
				break;
			case ComponentType::screen:
				screen2remove=(Screen*)component;
				delete(screen2remove);
				break;
			default:
				delete(component);
				break;
		}
	}
	mReady = false;
	mMode = RunMode::stopped;
}
/**
 * Returns the content of mReady. Value 1 means OK, 0 means ERROR.
 */ 
int Robot::GetReady()
{
	return mReady;
}

/**
 * Returns the actual name of the robot.
 * 
 * @return mName;
 */ 
string Robot::GetName()
{
	return mName;
}
/**
 * Main event loop. 
 * If GetReady returns 0 the loop doesn't start.
 * If the loop is already running and GetReady returns 0, the loop stops.
 */ 
int Robot::Run()
{
	// Initialize and enter on ready mode
	if (!GetReady())
		return ERROR;
	cerr << "robot ready" << endl;
	mMode=WaitingMode();
	cerr << "waiting mode done" << endl;
	
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
		cerr << "Running mode done" << endl;

	}
	mReadyIndicator->Off();
	mMode=RunMode::stopped;
	cerr << "stopping mode done" << endl;

	LOG4CXX_INFO(logger, "Enters on mode stopped");
	return OK;
}

// when enter on waiting mode, looks down, close the eyes, put arms in rest
RunMode Robot::WaitingMode()
{
	mReadyIndicator->On();
	mNeck->SetAngle(20.0);
	mFace->SetNeutralFace();
	mRightArm->SetNeutral();
	mLeftArm->SetNeutral();
	return RunMode::waiting;
}

RunMode Robot::DrawingMode()
{
	mWorkingIndicator->On();
	mNeck->SetAngle(60);
	mFace->SetStaringFace();
	
	bool ImageValid=false;
	while (!ImageValid)
	{
		mEyes->Shot();	
		// manipulate image
		// evaluateimage
		ImageValid=true;
	}	
	mFace->Smile();
	mNeck->SetAngle(30);
	mFace->SetNeutralFace();
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
	mNeck->SetAngle(60);
	mFace->Wink();
	mFace->Smile();
	mLeftArm->ReleasePaper();
	return WaitingMode(); // when done
}


/**
 * Opens the camera and stores in the components list. 
 */ 
int Robot::HandleCamera(string name,string fileName,int errorCount)
{
	Camera* cameraHolder=new Camera();
	cameraHolder->SetPhotoFileName(fileName);
	int testState=cameraHolder->InitName(name);
	if (name == "Eyes")
		mEyes=cameraHolder;
	components.push_back(cameraHolder);
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "CAMERA->InitName returns ERROR");
	}
	return errorCount;
}
/**
 * Opens the led and stores in the components list. 
 */ 
int Robot::HandleLed(string name,int pin,int errorCount)
{
	Led* ledHolder=new Led();
	int testState=ledHolder->InitNamePin(name, pin);	
	if (name == "ReadyIndicator")
		mReadyIndicator=ledHolder;
	if (name == "WorkingIndicator")
		mWorkingIndicator=ledHolder;
	components.push_back(ledHolder);
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "LED->InitNamePin returns ERROR");
	}
	return errorCount;
}
/**
 * Opens the servo and stores in the components list. 
 */ 
int Robot::HandleServo(string name,int errorCount)
{
	Servo* servoHolder=new Servo();
	int testState=servoHolder->InitName(name);
	if (name == "Neck")
		mNeck=servoHolder;
	components.push_back(servoHolder);
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "SERVO->InitName returns ERROR");
	}
	return errorCount;
}
/**
 * Opens the button and stores in the components list. 
 */ 
int Robot::HandleButton(string name,int errorCount)
{
	Button* buttonHolder=new Button();
	int testState=buttonHolder->InitName(name);
	if (name=="StartWorking")
		mStartWorking=buttonHolder;
	if (name=="StopWorking")
		mStopWorking=buttonHolder;
	components.push_back(buttonHolder);
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "Button->InitName returns ERROR");
	}
	return errorCount;
}

int Robot::HandleScreen(string name,int errorCount)
{
	Screen* screenHolder=new Screen();
	int testState=screenHolder->InitName(name);
	if (name=="Face")
		mFace=screenHolder;
	components.push_back(screenHolder);
	if (testState==ERROR) 
	{
		errorCount++;
		LOG4CXX_ERROR(logger, "Screen->InitName returns ERROR");
	}
	return errorCount;
}

int Robot::HandleArm(string name,int errorCount)
{
	Arm* armHolder=new Arm();
	int testState=armHolder->InitName(name);
	cerr << "HandleArm, testState=" << testState << endl;
	if (name=="LeftArm")
		mLeftArm=armHolder;
	if (name=="RightArm")
		mRightArm=armHolder;
	components.push_back(armHolder);
	if (testState==ERROR) 
	{
		cerr << "Arm->InitName returns ERROR" << endl;
		errorCount++;
		LOG4CXX_ERROR(logger, "Arm->InitName returns ERROR");
	}
	return errorCount;
}

bool Robot::EvaluatePaperPosition()
{
	return true;
}

bool Robot::FixPaperPosition()
{
	return true;
}

void Robot::DrawVector()
{}
