/**
 * @file Instrument.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Instrument.h"

/**
 *Constructor for our instrument
 * @param audioEngine audio engine pointer
 * @param sound the sound of this instrument
 */
Instrument::Instrument(ma_engine *audioEngine, std::wstring sound)
{
	mAudioEngine = audioEngine;
	auto result = ma_sound_init_from_file(audioEngine, wxString(sound), 0, NULL, NULL, &mSound);
	if (result != MA_SUCCESS)
	{
		wxString msg;
		msg.Printf(L"Unable to load audio file %s - %d", sound, result);
		wxMessageBox( msg, wxT("miniaudio failure"), wxICON_ERROR);
	}
}

/**
 * Plays a sound
 */
void Instrument::PlaySound()
{
	// If the sound is already playing, stop it first
	if(ma_sound_is_playing(&mSound))
	{
		ma_sound_stop(&mSound);
	}

	// Always rewind to the beginning before playing
	ma_sound_seek_to_pcm_frame(&mSound, 0);

	// And play the sound!
	ma_sound_start(&mSound);
}

/**
 * Destructor for our instrument
 */
Instrument::~Instrument()
{
	if(ma_sound_is_playing(&mSound))
	{
		ma_sound_stop(&mSound);
	}

	ma_sound_uninit(&mSound);
}
