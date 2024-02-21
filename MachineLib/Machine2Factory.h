/**
 * @file Machine2Factory.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H

struct ma_engine;
class Machine;

/**
 * Factory class responsible for second machine
 */
class Machine2Factory
{
private:

	/// Path to the resources directory
	std::wstring mResourcesDir;

	/// The miniaudio engine
	ma_engine* mAudioEngine;

public:
	/// Default constructor (disabled)
	Machine2Factory() = delete;

	/// Copy constructor (disabled)
	Machine2Factory(const Machine2Factory &) = delete;

	/// Assignment operator
	void operator=(const Machine2Factory &) = delete;

	Machine2Factory(std::wstring resourcesDir, ma_engine* audioEngine);

	std::shared_ptr<Machine> Create();


};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
