/**
 * @file Cylinder.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H
#define CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H

#include "Component.h"
#include "Polygon.h"
#include "AirSink.h"
#include "AirReceiver.h"

class StruckInstrument;

/**
 * Our cylinder class used to strike instruments
 */
class Cylinder : public Component, public AirReceiver
{
private:
	///The mount of the cylinder
	cse335::Polygon mMount;

	///The cylinder itself
	cse335::Polygon mCylinder;

	///The ram of the cylinder
	cse335::Polygon mRam;

	///The instrument this cylinder strikes
	std::shared_ptr<StruckInstrument> mInstrument;

	///The sink of this cylinder
	AirSink mSink;

	///The current pressure of this cylinder
	double mPressure = 0;

	///The last pressure of this cylinder
	double mLastPressure = 0;

public:
	Cylinder(std::wstring resourcesDir);

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

	/**
	 * Sets the instrument that we strike
	 * @param instrument the instrument
	 */
	void SetMotionSink(std::shared_ptr<StruckInstrument> instrument) { mInstrument = instrument; }

	/**
	 * Getter for our sink
	 * @return the sink pointer
	 */
	AirSink *GetSink() {return &mSink;}

	void ReceivePressure(double pressure) override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H
