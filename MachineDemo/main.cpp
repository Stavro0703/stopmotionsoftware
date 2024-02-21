/**
 * @file main.cpp
 * @author Charles B. Owen
 *
 * Main entry point for machine demonstrator program
 *
 * Do not modify this file!
 */
#include "pch.h"
#include <MachineDemoBaseApp.h>
#include "MachineSystemIsolator.h"

//<editor-fold desc="MachineDemoApp">
/**
 * MachineDemo main application class.
 * Most of the work is actually done in the base class.
 */
class MachineDemoApp : public MachineDemoBaseApp {
public:
    /**
     * Create the machine isolator, which contains the machine we are displaying.
     * @param resourcesDir Directory containing the resources for the program
     * @param audioEngine The miniaudio engine
     * @return MachineSystemIsolator object
     */
    std::shared_ptr<IMachineSystemIsolator> CreateMachineIsolator(std::wstring resourcesDir, ma_engine *audioEngine) override
    {
        return std::make_shared<MachineSystemIsolator>(resourcesDir, audioEngine);
    }

};
//</editor-fold>

wxIMPLEMENT_APP(MachineDemoApp);

