/**
 * @file MachineFrameDlg.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFRAMEDLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFRAMEDLG_H

class MachineDrawable;

class Timeline;

/**
 * Dialog class for setting start frames
 */
class MachineFrameDlg final : public wxDialog
{
private:
	void OnOk(wxCommandEvent& event);

	///Pointer to our first machines drawable
	std::shared_ptr<MachineDrawable> mMachineOne;

	///Pointer to our second machines drawable
	std::shared_ptr<MachineDrawable> mMachineTwo;

	///Pointer to our timeline
	Timeline* mTimeline;

	 ///The start frame of machine one
	int mMachineOneFrame = 0;

	///The start frame for machine two
	int mMachineTwoFrame = 0;

public:
	MachineFrameDlg(wxWindow* parent, std::shared_ptr<MachineDrawable> MachineOne,
					std::shared_ptr<MachineDrawable> MachineTwo, Timeline* timeline);

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFRAMEDLG_H
