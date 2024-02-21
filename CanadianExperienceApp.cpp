/**
 * @file CanadianExperienceApp.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "CanadianExperienceApp.h"
#include "MainFrame.h"

/**
 * Initialize the application.
 * @return True if successful
 */
bool CanadianExperienceApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Initialize the audio engine
    auto result = ma_engine_init(NULL, &mAudioEngine);
    if (result != MA_SUCCESS)
    {
        wxString msg;
        msg.Printf(L"Unable to initialize miniaudio engine - %d", result);
        wxMessageBox( msg, wxT("miniaudio failure"), wxICON_ERROR);
        return false;
    }

    // Do not remove this line...
    wxSetWorkingDirectory(L"..");

    // Get pointer to XML resource system
    auto xmlResource = wxXmlResource::Get();

    // Initialize XRC handlers
    xmlResource->InitAllHandlers();

    // Load all XRC resources from the program resources
    auto standardPaths = wxStandardPaths::Get();
    if (!wxXmlResource::Get()->LoadAllFiles(standardPaths.GetResourcesDir() + "/xrc"))
    {
        return false;
    }

    auto frame = new MainFrame(standardPaths.GetResourcesDir().ToStdWstring(), &mAudioEngine);
    frame->Initialize();
    frame->Show(true);

    return true;
}

/**
 * Exit the application. Time to shut down services such as miniaudio
 * @return
 */
int CanadianExperienceApp::OnExit()
{
    ma_engine_uninit(&mAudioEngine);
    return wxAppBase::OnExit();
}
