/**
 * @file AirReceiver.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRRECEIVER_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRRECEIVER_H

/**
 * Interface class for components that receive air
 */
class AirReceiver
{
private:

public:
	/**
	 * Handles receiving pressure
	 * @param pressure the pressure
	 */
	virtual void ReceivePressure(double pressure) = 0;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRRECEIVER_H
