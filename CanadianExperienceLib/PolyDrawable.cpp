/**
 * @file PolyDrawable.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PolyDrawable.h"

/**
 * Constructor
 * @param name The drawable name
 */
PolyDrawable::PolyDrawable(const std::wstring &name) : Drawable(name)
{
}

/**
 * Draw our polygon.
 * @param  graphics The graphics context to draw on
 */
void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(!mPoints.empty()) {

        mPath = graphics->CreatePath();
        mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++)
        {
            mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
        }
        mPath.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(mPath);
    }




//    SolidBrush brush(mColor);
//
//    // Transform the points
//    vector<Point> points;
//    for (auto point : mPoints)
//    {
//        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
//    }
//
//    graphics->FillPolygon(&brush, &points[0], (int)points.size());
}


/** Test to see if we hit this object with a mouse click
 * @param pos Click position
 * @return true it hit
 */
bool PolyDrawable::HitTest(wxPoint pos)
{
    return mPath.Contains(pos.x, pos.y);
}


/**
 * Add a point to the polygon
 * @param point Point to add
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}
