/**
 * @file StruckInstrument.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "StruckInstrument.h"

/**
 * Constructor for our struck instrument
 * @param ResourceDir resources directory
 * @param AudioEngine audio engine pointer
 * @param SoundDir the sound directory
 */
StruckInstrument::StruckInstrument(std::wstring ResourceDir, ma_engine *AudioEngine, std::wstring SoundDir) :
	Instrument(AudioEngine, ResourceDir+SoundDir)
{

}
