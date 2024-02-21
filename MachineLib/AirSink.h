/**
 * @file AirSink.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H

#include "Component.h"

class AirReceiver;

class AirSource;

/**
 * Class for an AirSink which is designed to receive pressure
 */
class AirSink
{
private:
	///The source of this air sink
	AirSource* mSource = nullptr;

	///The component this AirSink is tied to
	AirReceiver* mComponent = nullptr;

public:
	AirSink() { }

	/// Copy constructor (disabled)
	AirSink(const AirSink &) = delete;

	/// Assignment operator
	void operator=(const AirSink &) = delete;

	/**
	 * Setter for our AirSource
	 * @param source the source
	 */
	void SetSource(AirSource* source) { mSource = source; }

	/**
	 * Setter for our component
	 * @param component the component
	 */
	void SetComponent(AirReceiver* component) { mComponent = component; }

	void ReceiveAir(double pressure);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H
