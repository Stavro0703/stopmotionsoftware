/**
 * @file Cylinder.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Cylinder.h"
#include "StruckInstrument.h"

/// Cylinder base image
const std::wstring CylinderBaseImage = L"/images/cylinder-base.png";

/// Cylinder body image
const std::wstring CylinderBodyImage = L"/images/cylinder.png";

/// Cylinder ram image
const std::wstring CylinderRamImage = L"/images/cylinder-ram.png";

/// The maximum pixels to move the cylinder ram when enabled
const int CylinderMaxExtent = 44;

/// Angle from bottom center of the cylinder to the tubing connector
const double ConnectorAngle = -0.17;

/// Distance from bottom center of the cylinder to the tubing connector
const double ConnectorDistance = 24.5;

/// Rotation for our drum
const double DrumRotation = 0.25;

/// Rotation for our cymbal
const double CymbalRotation = 0.5;

/**
 * Our cylinder constructor
 * @param resourcesDir Resources directory
 */
Cylinder::Cylinder(std::wstring resourcesDir)
{
	mMount.SetImage(resourcesDir + CylinderBaseImage);
	mMount.Rectangle(-mMount.GetImageWidth() / 2, 0);

	mCylinder.SetImage(resourcesDir + CylinderBodyImage);
	mCylinder.Rectangle(-mCylinder.GetImageWidth() / 2, 0);

	mRam.SetImage(resourcesDir + CylinderRamImage);
	mRam.Rectangle(-mCylinder.GetImageWidth() / 2, 0);

	mSink.SetComponent(this);
}

/**
 * Handles drawing our cylinder
 * @param graphics the graphics context
 * @param x X of our machine
 * @param y Y of our machine
 */
void Cylinder::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
	mMount.SetRotation(GetRotation());
	mCylinder.SetRotation(GetRotation());
	mRam.SetRotation(GetRotation());

	mMount.DrawPolygon(graphics, x + GetX(), y + GetY());

	//Handles drawing drum cylinder
	if(GetRotation() <= DrumRotation)
	{
		if(mPressure >= 1 && mLastPressure <= 0 )
		{
			mRam.DrawPolygon(graphics, x + GetX() + 44, y + GetY());
			mInstrument->PlaySound();
		}
		else
		{
			mRam.DrawPolygon(graphics, x + GetX(), y + GetY());
		}
		mLastPressure = mPressure;

	}
	// Handles drawing our cymbal cylinder
	else
	{
		if(mPressure >= 1 && mLastPressure <= 0 )
		{
			mRam.DrawPolygon(graphics, x + GetX(), y + GetY() + 34);
			mInstrument->PlaySound();
		}
		else
		{
			mRam.DrawPolygon(graphics, x + GetX(), y + GetY());
		}
		mLastPressure = mPressure;
	}

	mCylinder.DrawPolygon(graphics, x + GetX(), y + GetY());
}

/**
 * Pressure receiver from our sink
 * @param pressure
 */
void Cylinder::ReceivePressure(double pressure)
{
	mPressure = pressure;
}
