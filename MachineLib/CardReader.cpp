/**
 * @file CardReader.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "CardReader.h"
#include "AirSource.h"

///Maximum number of sources
const int NumAirSources = 10;

/// Image for the back of the card reader
const std::wstring CardReaderBackImage = L"/images/card-reader-back.png";

/// Image for the front of the card reader
const std::wstring CardReaderFrontImage = L"/images/card-reader-front.png";

// The card actual dimensions are 847 by 379 pixels,
// a size chosen to make the column spacing exactly
// 10 pixels. We draw it much smaller than that on the screen

/// Width to draw the card on the screen in pixels
const int CardWidth = 132;

/// Height to draw the card on the screen in pixels
const int CardLength = 297;

/// Amount of offset the center of the card so it will
/// appear at the right place relative to the card reader.
const int CardOffsetX = 126;

/// Y dimension of the offset
const int CardOffsetY = 65;

// These values are all for the underlying image. They
// can be used for find the punches.

/// Width of a card column in pixels
const int CardColumnWidth = 10;

/// Height of a card row in pixels
const int CardRowHeight = 29;

/// X offset for the first column (left side)
const int CardColumn0X = 24;

/// Y offset to the first row (0's)
/// There are actually two rows above this that can be used
const int CardRow0Y = 78;

/// Width of a punched hole
const int CardPunchWidth = 8;

/// Height of a punched hole
const int CardPunchHit = 20;

/// Any average luminance below this level is considered a punched hole
const double CardPunchLuminance = 0.1;

//
// These values are for the outputs of the card reader,
// where the tubing attaches.
//

/// Y offset to the first card reader output in pixels
const int OutputOffsetY = -92;

/// X offset to the first card reader output in pixels
const int OutputOffsetX = -35;

/// X spacing for the outputs
const double OutputSpacingX = 10.7;

/**
 *CardReader constructor
 * @param resourcesDir our resources directory
 */
CardReader::CardReader(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
	mBack.SetImage(mResourcesDir + CardReaderBackImage);
	mBack.Rectangle(-mBack.GetImageWidth() / 2, 0);

	mFront.SetImage(mResourcesDir + CardReaderFrontImage);
	mFront.Rectangle(-mFront.GetImageWidth() / 2, 0);

	mColumn = 0;

	for (int i = 0; i < NumAirSources; i++)
	{
		auto source = std::make_shared<AirSource>();
		mSources.push_back(source);
	}
}

/**
 * Determine if a hole is punched in the card.
 * @param column Column on the card, from 0 (left of first column) to 80 (last column)
 * @param row Row on the card, -2 to 9.
 * @return True if hole is punched at column, row
*/
bool CardReader::IsPunched(int column, int row)
{
	auto luminance = mCard.AverageLuminance(CardColumn0X + (column - 1) * CardColumnWidth,
											CardRow0Y + CardRowHeight * row, CardPunchWidth, CardPunchHit);
	return luminance < CardPunchLuminance;
}

/**
 *Draw function for our full card reader
 * @param graphics the context to be drawn to
 * @param x X position of our card reader
 * @param y Y position of our card reader
 */
void CardReader::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
	x = 175;
	mBack.DrawPolygon(graphics, x, y);


	auto cardScale = (double)CardLength / mCard.GetImageWidth();
	if(mColumn > 80)
	{
		mColumn = 80;
	}
	mCard.DrawPolygon(graphics, x, y + (mColumn-1) * cardScale * CardColumnWidth);
	mFront.DrawPolygon(graphics, x, y);

}

/**
 * Intializes card polygon object
 * @param path the card path
 */
void CardReader::SetCard(std::wstring path)
{
	mCard.SetImage(path);
	mCard.Rectangle(CardOffsetX, CardOffsetY, CardLength, CardWidth);
	mCard.SetRotation(-0.25);
}

/**
 * Sets the time of CardReader and handles sending Air
 * @param time the time
 */
void CardReader::SetTime(double time)
{
	double beat = time * mBeatsPerMinute / 60.0;
	double remainder = fmod(beat, 1);
	mColumn = (int)beat;

	if(remainder < 0.5)
	{
		// Determine what is punched in this row
		for (int row = 0; row < mSources.size(); row++)
		{
			bool punched = IsPunched(mColumn , row);
			if(mColumn >= 80)
			{
				punched = false;
			}
			if (punched && mSources[row]->GetSink() != nullptr)
			{
				mSources[row]->SendPressure(1);
			}
		}
	}
	else
	{
		for (int row = 0; row < mSources.size(); row++)
		{

			if (mSources[row]->GetSink() != nullptr)
			{
				mSources[row]->SendPressure(0);
			}

		}
	}
}

