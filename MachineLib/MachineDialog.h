/**
 * @file MachineDialog.h
 * @author Charles Owen
 *
 * Class that implements a dialog box for machine selection
 *
 * You are not allowed to change this class in any way!
 */

#ifndef CANADIANEXPERIENCE_MACHINEDIALOG_H
#define CANADIANEXPERIENCE_MACHINEDIALOG_H

class MachineSystem;

/**
 * Exported dialog box class for selecting a machine
 *
 * You are not allowed to change this class in any way!
 */
class MachineDialog : public wxDialog {
private:
    void OnOK(wxCommandEvent& event);
    void OnInitDialog(wxInitDialogEvent& event);

    /// MachineSystem we are editing
    std::shared_ptr<MachineSystem> mMachine;

    /// The machine number as used by the validator
    int mMachineNumber;

    /// The machine number control
    wxTextCtrl* mMachineNumberCtrl;

public:
    MachineDialog(wxWindow *parent, std::shared_ptr<MachineSystem> machineSystem);

};

#endif //CANADIANEXPERIENCE_MACHINEDIALOG_H
