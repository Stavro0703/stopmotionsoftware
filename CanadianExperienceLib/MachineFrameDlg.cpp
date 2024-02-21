/**
 * @file MachineFrameDlg.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>

#include "MachineFrameDlg.h"
#include "MachineDrawable.h"
#include "Timeline.h"

/**
 * Constructor for our machine frame dialog
 * @param parent the parent window
 * @param MachineOne the first machines drawable
 * @param MachineTwo the second machines drawable
 * @param timeline the timeline
 */
MachineFrameDlg::MachineFrameDlg(wxWindow *parent,std::shared_ptr<MachineDrawable> MachineOne,
								 std::shared_ptr<MachineDrawable> MachineTwo, Timeline* timeline) :
								 mMachineOne(MachineOne), mMachineTwo(MachineTwo), mTimeline(timeline)
{
	wxXmlResource::Get()->LoadDialog(this, parent, L"MachineFrameDlg");

	mMachineOneFrame = MachineOne->GetStartFrame();
	mMachineTwoFrame = MachineTwo->GetStartFrame();

	Bind(wxEVT_BUTTON, &MachineFrameDlg::OnOk, this, wxID_OK);

	auto machineOneCtrl = XRCCTRL(*this, "Machine1StartFrame", wxTextCtrl);
	wxIntegerValidator<int> machineOneValidator(&mMachineOneFrame);
	machineOneValidator.SetRange(0, mTimeline->GetNumFrames());
	machineOneCtrl->SetValidator(machineOneValidator);

	auto machineTwoCtrl = XRCCTRL(*this, "Machine2StartFrame", wxTextCtrl);
	wxIntegerValidator<int> machineTwoValidator(&mMachineTwoFrame);
	machineTwoValidator.SetRange(0, mTimeline->GetNumFrames());
	machineTwoCtrl->SetValidator(machineTwoValidator);
}

/**
 * When OK is pressed in the dialog this function validates and sets
 * @param event the event
 */
void MachineFrameDlg::OnOk(wxCommandEvent& event)
{
	if ( Validate() && TransferDataFromWindow() )
	{
		// Success! Set values in the class
		mMachineOne->SetStartFrame(mMachineOneFrame);
		mMachineTwo->SetStartFrame(mMachineTwoFrame);

		EndModal(wxID_OK);
	}
}
