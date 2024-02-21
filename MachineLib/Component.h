/**
 * @file Component.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include "Machine.h"

/**
 * Base class for all machine components
 */
class Component
{
private:
	///Components position relative to machine
	wxPoint mRelativeLocation;

	///Rotation of our component
	double mRotation;

	///The machine this component belongs to
	Machine* mMachine;

public:
	virtual ~Component() { }

	/**
	 * Handles drawing for all components
	 * @param graphics the context to be drawn to
	 * @param x X position of our machine
	 * @param y Y position of our machine
	 */
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) = 0;

	/**
	 * Setter for our relative position
	 * @param x X to be set
	 * @param y Y to be set
	 */
	void SetPosition(int x, int y) { mRelativeLocation.x = x; mRelativeLocation.y = y; }

	/**
	 * Getter for our relative position
	 * @return our position
	 */
	wxPoint GetPosition() { return mRelativeLocation; }

	/**
	 * Setter for our components rotation
	 * @param rotation the rotation
	 */
	void SetRotation(double rotation) { mRotation = rotation; }

	/**
	 * Getter for our component rotation
	 * @return the rotation
	 */
	double GetRotation() { return mRotation; }

	/**
	 * Setter for mMachine
	 * @param machine the machine to be set
	 */
	void SetMachine(Machine* machine) { mMachine = machine; }

	/**
	 * Getter for our machine member
	 * @return mMachine
	 */
	Machine* GetMachine() { return mMachine; }

	/**
	 * Gets the X coordinate of our position
	 * @return X
	 */
	int GetX() { return mRelativeLocation.x; }

	/**
	 * Gets the Y coordinate of our position
	 * @return Y
	 */
	int GetY() { return mRelativeLocation.y; }

	virtual void SetTime(double time);


protected:
	//Component();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
