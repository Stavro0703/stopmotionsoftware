/**
 * @file MachineFactory.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFACTORY_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFACTORY_H

#include "Actor.h"
#include "MachineDrawable.h"

struct ma_engine;

/**
 * Class for creating a machine drawable
 */
class MachineFactory
{
private:
	///The machine drawable of this factory
	std::shared_ptr<MachineDrawable> mMachineDrawable;

public:
	std::shared_ptr<Actor> Create(std::wstring resourcesDir, ma_engine* audioEngine, int machineNum);

	/**
	 * Sets the machine drawable
	 * @param machine
	 */
	void SetMachineDrawable(std::shared_ptr<MachineDrawable> machine) { mMachineDrawable = machine; }

	/**
	 * Gets the machine drawable
	 * @return our MachineDrawable
	 */
	std::shared_ptr<MachineDrawable> GetMachineDrawable() { return mMachineDrawable; }

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEFACTORY_H
