/**
 * @file Machine.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "MachineSystemActual.h"

/**
 *Our machine constructor
 * @param number the machine number
 */
Machine::Machine(int number) : mMachineNumber(number)
{

}

/**
 * Draw function for our machine
 * @param graphics the context to be drawn to
 * @param x machines x coordinate
 * @param y machines y coordinate
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
	for (auto components : mComponents)
	{
		components->SetTime(mTime);
		components->Draw(graphics, x, y);
	}
}

/**
 * Establishes link between machine and component
 * @param component the component to link
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
	mComponents.push_back(component);
	component->SetMachine(this);
}

/**
 * Calculates the time of our machine and sets it
 */
void Machine::SetMachineTime()
{
	double currentFrame = mMachineSystem->GetMachineFame();
	double frameRate = mMachineSystem->GetFrameRate();

	mTime = currentFrame/frameRate;
}

