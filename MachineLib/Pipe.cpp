/**
 * @file Pipe.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Pipe.h"
#include "AirSink.h"

/// The pipe base image
const std::wstring PipeBaseImage = L"/images/pipe-base.png";

/// The pipe image
const std::wstring PipeImage = L"/images/pipe.png";

/// The pipe top image
const std::wstring PipeTopImage = L"/images/pipe-top.png";

/// The pipe puff image
const std::wstring PuffImage = L"/images/puff.png";

/// Pipe images width in pixels
const int PipeWidth = 20;

/// Pipe base height
const int PipeBaseHeight = 20;

/// Puff image width in pixels
const int PuffWidth = 65;

///Base offset
const int BaseOffset = 5;

/**
 * Constructor for our pipe
 * @param resourcesDir resources directory
 * @param audioEngine audio engine pointer
 * @param sound directory the the sound
 * @param length length of the pipe
 */
Pipe::Pipe(std::wstring resourcesDir, ma_engine *audioEngine, std::wstring sound, int length) :
	Instrument(audioEngine, resourcesDir+sound)
{
	// Instrument base class polygon
	SetImage(resourcesDir + PipeBaseImage);
	Rectangle(-PipeWidth / 2, 0, PipeWidth, PipeWidth);

	// Polygons for the other components
	mPipe.SetImage(resourcesDir + PipeImage);
	mPipe.Rectangle(-PipeWidth / 2, -PipeBaseHeight, PipeWidth, length);

	mPipeTop.SetImage(resourcesDir + PipeTopImage);
	mPipeTop.Rectangle(-PipeWidth / 2, -PipeBaseHeight - length, PipeWidth);

	mPuff.SetImage(resourcesDir + PuffImage);
	mPuff.Rectangle(-PuffWidth / 2, -PipeBaseHeight - length, PuffWidth);

	mSink.SetComponent(this);
}

/**
 * Draw function for our pipe
 * @param graphics the context to be drawn to
 * @param x X position of our machine
 * @param y Y position of our machine
 */
void Pipe::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
	if (mPressure >= 1 && mLastPressure <= 0 )
	{
		mPuff.DrawPolygon(graphics, x + GetX(), y + GetY());
		PlaySound();
	}
	mLastPressure = mPressure;
	Shape::Draw(graphics, x , y-BaseOffset);
	mPipe.DrawPolygon(graphics, x + GetX(), y + GetY());
	mPipeTop.DrawPolygon(graphics, x + GetX(), y + GetY());
}

/**
 *Handles receiving pressure for our pipe
 * @param pressure
 */
void Pipe::ReceivePressure(double pressure)
{
	mPressure = pressure;
}
