/**
 * @file MachineSystemActual.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "MachineSystemActual.h"
#include "Machine.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

/**
 * Constructor for our actual machine system
 * @param resourcesDir our resources directory
 * @param audioEngine the engine for our audio
 */
MachineSystemActual::MachineSystemActual(std::wstring resourcesDir, ma_engine *audioEngine) :
				mAudioEngine(audioEngine), mResourcesDir(resourcesDir)
{
	SetMachineNumber(1);
}

/**
 *Handles drawing the machine itself
 * @param graphics the context to be drawn to
 */
void MachineSystemActual::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
	mMachine->SetMachineTime();
	mMachine->Draw(graphics, mLocation.x, mLocation.y);
}

/**
 *Sets the current frame of the machine
 * @param frame the current frame
 */
void MachineSystemActual::SetMachineFrame(int frame)
{
	mCurrFrame = frame;
}

/**
 *Sets the location of our machine
 * @param location location we wish to set
 */
void MachineSystemActual::SetLocation(wxPoint location)
{
	mLocation = location;
}

/**
 *Sets the frame rate our machine
 * @param rate the frame rate
 */
void MachineSystemActual::SetFrameRate(double rate)
{
	mFrameRate = rate;
}

/**
 *Sets the number of our machine
 * @param machine the machine number
 */
void MachineSystemActual::SetMachineNumber(int machine)
{
	//If machine 1 is needed it is created and set
	if(machine == 1)
	{
		Machine1Factory machine1Factory(mResourcesDir, mAudioEngine);
		mMachine = machine1Factory.Create();
		mMachine->SetMachineNumber(machine);
		mMachine->SetMachineSystem(this);
	}
	//If machine 2 is needed it is created and set
	else if(machine == 2)
	{
		Machine2Factory machine2Factory(mResourcesDir, mAudioEngine);
		mMachine = machine2Factory.Create();
		mMachine->SetMachineNumber(machine);
		mMachine->SetMachineSystem(this);
	}

}

/**
 *Gets the machines number
 * @return the machine number
 */
int MachineSystemActual::GetMachineNumber()
{
	return mMachine->GetMachineNumber();
}

/**
 *Gets the current time of the machine
 * @return the time
 */
double MachineSystemActual::GetMachineTime()
{
	return mMachine->GetMachineTime();
}

