/**
 * @file MachineSystemFactory.h
 *
 * @author Charles Owen
 *
 * MachineSystem factory class. Creates MachineSystem objects
 *
 * You should not have any reason to change this header file!
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H
#define CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H

#include <memory>

class MachineSystem;
struct ma_engine;

/**
 * MachineSystem factory class. Creates MachineSystem objects
 */
class MachineSystemFactory
{
private:
    /// The resources directory
    std::wstring mResourcesDir;

    /// The miniaudio engine
    ma_engine* mAudioEngine;

public:
    MachineSystemFactory(std::wstring resourcesDir, ma_engine* audioEngine);

    // Do not change the return type for CreateMachineSystem!
    std::shared_ptr<MachineSystem> CreateMachineSystem();
};

#endif //CANADIANEXPERIENCE_MACHINESYSTEMFACTORY_H