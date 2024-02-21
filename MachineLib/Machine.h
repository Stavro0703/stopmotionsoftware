/**
 * @file Machine.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

class Component;

class MachineSystemActual;

/**
 * Machine base class
 */
class Machine
{
private:

	///The current time we are on
	double mTime = 0;

	///This machines number
	int mMachineNumber;

	///The collection of our machines components
	std::vector<std::shared_ptr<Component>> mComponents;

	///The system this machine belongs to
	MachineSystemActual* mMachineSystem;

public:

	Machine(int number);
	
	/// Default constructor (disabled)
	Machine() = delete;
	
	/// Copy constructor (disabled)
	Machine(const Machine &) = delete;
	
	/// Assignment operator
	void operator=(const Machine &) = delete;

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

	/**
	 * Getter for our machine number
	 * @return the number
	 */
	int GetMachineNumber() { return mMachineNumber; }

	/**
	 * Returns the time of our machine
	 * @return the time
	 */
	double GetMachineTime() { return mTime; }

	void SetMachineTime();

	/**
	 * Setter for machine number
	 * @param number the number of the machine
	 */
	void SetMachineNumber(int number) { mMachineNumber = number; }


	void AddComponent(std::shared_ptr<Component> component);

	/**
	 * Setter for our machine system
	 * @param system
	 */
	void SetMachineSystem(MachineSystemActual* system) { mMachineSystem = system; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
