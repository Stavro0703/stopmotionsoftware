/**
 * @file RotatedBitmap.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "RotatedBitmap.h"



/**
 * Load the image from a file.
 * @param filename File to load
 */
void RotatedBitmap::LoadImage(const std::wstring &filename)
{
    mImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mLoaded = true;
}


/**
 * Draw the bitmap
 * @param graphics The graphics context to draw on
 * @param position The position to draw at
 * @param angle The rotation angle
 */
void RotatedBitmap::DrawImage(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position, double angle)
{
    if(!mBitmapCreated)
    {
        mBitmap = graphics->CreateBitmapFromImage(*mImage);
    }

    graphics->PushState();
    graphics->Translate(position.x, position.y);
    graphics->Rotate(-angle);
    graphics->DrawBitmap(mBitmap, -mCenter.x, -mCenter.y,
            mImage->GetWidth(), mImage->GetHeight());

    graphics->PopState();
}