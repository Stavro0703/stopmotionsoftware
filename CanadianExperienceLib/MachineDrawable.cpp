/**
 * @file MachineDrawable.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "Timeline.h"

/**
 * Constructor for our drawable Machine
 * @param resourcesDir
 * @param audioEngine
 * @param name the name of our machine
 * @param numMachine the number of our machine
 */
MachineDrawable::MachineDrawable(std::wstring resourcesDir, ma_engine *audioEngine, const std::wstring &name, int numMachine) :
		Drawable(name)
{
	MachineSystemFactory factory(resourcesDir, audioEngine);
	mMachineSystem = factory.CreateMachineSystem();
	mMachineSystem->SetMachineNumber(numMachine);
	mMachineSystem->SetFrameRate(30);
	mMachineSystem->SetLocation(wxPoint(500,200));
	mStartFrame = 0;
}

/**
 * Draw function for our machine drawable
 * @param graphics
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	if(mTimeline->GetCurrentFrame() > mStartFrame)
	{
		double scale = 0.75f;
		mMachineSystem->SetMachineFrame(mTimeline->GetCurrentFrame() - mStartFrame);
		graphics->PushState();
		graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
		graphics->Scale(scale, scale);
		mMachineSystem->DrawMachine(graphics);
		graphics->PopState();
	}
	else
	{
		double scale = 0.75f;
		mMachineSystem->SetMachineFrame(0);
		graphics->PushState();
		graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
		graphics->Scale(scale, scale);
		mMachineSystem->DrawMachine(graphics);
		graphics->PopState();
	}

}

/**
 * HitTest for our  machine drawable
 * @param pos
 * @return hit or not?
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
	return false;
}

/**
 *Sets the timeline of this drawable
 * @param timeline the timeline
 */
void MachineDrawable::SetTimeline(Timeline *timeline)
{
	Drawable::SetTimeline(timeline);
	mTimeline = timeline;
}
