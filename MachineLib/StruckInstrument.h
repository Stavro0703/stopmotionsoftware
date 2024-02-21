/**
 * @file StruckInstrument.h
 * @author Stavro Polis
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H
#define CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H

#include "Instrument.h"

/**
 * Struck instrument base class
 */
class StruckInstrument : public Instrument
{
private:

public:
	StruckInstrument(std::wstring ResourceDir, ma_engine *AudioEngine, std::wstring SoundDir);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H
