/**
 * @file MachineDrawable.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include "Drawable.h"
#include <machine-api.h>

/**
 * Adapter class for our machine in the CanadianExperience
 */
class MachineDrawable : public Drawable
{
private:
	///The machine system of this drawable
	std::shared_ptr<MachineSystem> mMachineSystem;

	///The timeline
	Timeline* mTimeline;

	///The starting frame of this drawable
	int mStartFrame = 0;

public:
	MachineDrawable(std::wstring resourcesDir, ma_engine *audioEngine, const std::wstring &name, int numMachine);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	bool HitTest(wxPoint pos) override;

	/**
	 * Getter for our system
	 * @return the system
	 */
	std::shared_ptr<MachineSystem> GetSystem() { return mMachineSystem; }

	void SetTimeline(Timeline* timeline) override;

	/**
	 * Sets the start frame
	 * @param frame the frame to start on
	 */
	void SetStartFrame(int frame) { mStartFrame = frame; }

	/**
	 * Gets the starting frame
	 * @return the starting frame
	 */
	int GetStartFrame() { return mStartFrame; }

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
