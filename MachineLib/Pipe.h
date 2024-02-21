/**
 * @file Pipe.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PIPE_H
#define CANADIANEXPERIENCE_MACHINELIB_PIPE_H

#include "Instrument.h"
#include "Polygon.h"
#include "AirSink.h"
#include "AirReceiver.h"

struct ma_engine;

/**
 * The pipe class
 */
class Pipe : public Instrument, public AirReceiver
{
private:
	///The pipe itself
	cse335::Polygon mPipe;

	///Top of our pipe
	cse335::Polygon mPipeTop;

	///Puff of smoke from our pipe
	cse335::Polygon mPuff;

	///The current pressure of this pipe
	double mPressure = 0;

	///The last pressure given to this pipe
	double mLastPressure = 0;

	///The AirSink of this pipe
	AirSink mSink;


public:
	/// Default constructor (disabled)
	Pipe() = delete;

	/// Copy constructor (disabled)
	Pipe(const Pipe &) = delete;

	/// Assignment operator
	void operator=(const Pipe &) = delete;

	Pipe(std::wstring resourceDir, ma_engine* audioEngine, std::wstring sound, int length);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

	/**
	 * Getter for our sink
	 * @return the sink pointer
	 */
	AirSink *GetSink() {return &mSink;}

	void ReceivePressure(double pressure) override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_PIPE_H
