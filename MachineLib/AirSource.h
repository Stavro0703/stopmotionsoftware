/**
 * @file AirSource.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H

#include "AirSink.h"

/**
 * The source of our air
 */
class AirSource
{
private:
	///The sink this source provides air to
	AirSink* mSink = nullptr;

public:
	AirSource() { }

	/// Copy constructor (disabled)
	AirSource(const AirSource &) = delete;

	/// Assignment operator (disabled)
	void operator=(const AirSource &) = delete;

	/**
	 * Sends pressure to the sink
	 * @param pressure the pressure to send
	 */
	void SendPressure(double pressure) { mSink->ReceiveAir(pressure); }

	void SetSink(AirSink* sink);

	/**
	 * Getter for our sink
	 * @return the sink
	 */
	AirSink* GetSink() { return mSink; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H
