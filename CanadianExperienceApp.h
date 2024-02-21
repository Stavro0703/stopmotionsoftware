/**
 * @file CanadianExperienceApp.h
 * @author Charles B. Owen
 *
 * Main application class
 */

#ifndef CANADIANEXPERIENCEAPP_H
#define CANADIANEXPERIENCEAPP_H

#include <miniaudio.h>

/**
 * Main application class
 */
class CanadianExperienceApp : public wxApp {
private:
    /// The audio engine for miniaudio
    ma_engine mAudioEngine;

public:
    bool OnInit() override;
    int OnExit() override;
};

#endif //CANADIANEXPERIENCEAPP_H
