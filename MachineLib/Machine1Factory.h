/**
 * @file Machine1Factory.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE1FACTORY_H

class Machine;
struct ma_engine;

/**
 * Factory for creating Machine #1
 */
class Machine1Factory
{
private:
	/// Path to the resources directory
	std::wstring mResourcesDir;

	/// The miniaudio engine
	ma_engine* mAudioEngine;

public:
	Machine1Factory(std::wstring resourcesDir, ma_engine* audioEngine);
	
	/// Default constructor (disabled)
	Machine1Factory() = delete;
	
	/// Copy constructor (disabled)
	Machine1Factory(const Machine1Factory &) = delete;
	
	/// Assignment operator
	void operator=(const Machine1Factory &) = delete;

	std::shared_ptr<Machine> Create();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE1FACTORY_H
