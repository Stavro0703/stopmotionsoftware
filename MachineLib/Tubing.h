/**
 * @file Tubing.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_TUBING_H
#define CANADIANEXPERIENCE_MACHINELIB_TUBING_H

#include "Component.h"
#include "AirReceiver.h"
#include "AirSink.h"
#include "AirSource.h"

/**
 * The tubing class
 */
class Tubing : public Component, public AirReceiver
{
private:
	///The sink of this tubing
	AirSink mSink;

	///The source of this tubing
	AirSource mSource;

public:
	void ReceivePressure(double pressure) override;

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

	/**
	 * Getter for the sink
	 * @return the sink pointer
	 */
	AirSink *GetSink() {return &mSink;}

	/**
	 * Getter for our source
	 * @return the source pointer
	 */
	AirSource *GetSource() { return &mSource; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_TUBING_H
