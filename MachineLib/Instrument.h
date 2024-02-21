/**
 * @file Instrument.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H
#define CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H

#include "Shape.h"
#include <miniaudio.h>

/**
 * Instrument base class
 */
class Instrument : public Shape
{
private:
	/// The miniaudio engine
	ma_engine* mAudioEngine;

	/// The miniaudio sound
	ma_sound mSound;

public:
	void PlaySound();

	~Instrument();

protected:
	Instrument(ma_engine *PEngine, std::wstring sound);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H
