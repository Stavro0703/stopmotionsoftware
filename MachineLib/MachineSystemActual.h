/**
 * @file MachineSystemActual.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H

#include "MachineSystem.h"
#include "Machine.h"

struct ma_engine;
/**
 * The actual MachineSystem used
 */
class MachineSystemActual : public MachineSystem
{
private:
	///The directory for our images
	std::wstring mResourcesDir;

	///The audio engine for this machine system
	ma_engine* mAudioEngine;

	///The frame rate of this machine system
	double mFrameRate = 30.0;

	///The machine itself
	std::shared_ptr<Machine> mMachine;

	///The location of this machine
	wxPoint mLocation;

	///The current frame we are on
	double mCurrFrame;

public:
	MachineSystemActual(std::wstring resourcesDir, ma_engine* audioEngine);
	void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
	void SetMachineFrame(int frame) override;
	void SetLocation(wxPoint location) override;
	void SetFrameRate(double rate) override;
	void SetMachineNumber(int machine) override;
	int GetMachineNumber() override;
	double GetMachineTime() override;

	/**
	 * Gets the current frame of our machine
	 * @return the frame
	 */
	double GetMachineFame() { return mCurrFrame; }

	/**
	 * Gets the frame rate of our machine
	 * @return the frame rate
	 */
	double GetFrameRate() { return mFrameRate; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEMACTUAL_H
