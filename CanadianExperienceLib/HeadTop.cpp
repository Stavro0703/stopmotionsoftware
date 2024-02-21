/**
 * @file HeadTop.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <sstream>
#include <iomanip>

#include "HeadTop.h"
#include "Actor.h"
#include "Timeline.h"

using namespace std;

/**
 * Constructor
 * @param name Drawable name
 * @param filename File to load for the head
 */
HeadTop::HeadTop(const std::wstring& name, const std::wstring& filename)
        : ImageDrawable(name, filename)
{

}


/**
 * Set the actor. This is where we set the channel name
 * @param actor Actor to set
 */
void HeadTop::SetActor(Actor *actor)
{
    ImageDrawable::SetActor(actor);

    // Set the channel name
    mPositionChannel.SetName(actor->GetName() + L":" + GetName() + L":position");
}


/**
 * Set the timeline. The tells the channel the timeline
 * @param timeline Timeline to set
 */
void HeadTop::SetTimeline(Timeline *timeline)
{
    ImageDrawable::SetTimeline(timeline);

    timeline->AddChannel(&mPositionChannel);
}

/**
 * Set the keyframe based on the current status.
*/
void HeadTop::SetKeyframe()
{
    ImageDrawable::SetKeyframe();

    mPositionChannel.SetKeyframe(GetPosition());
}

/**
 * Get the current channel from the animation system.
*/
void HeadTop::GetKeyframe()
{
    ImageDrawable::GetKeyframe();

    if (mPositionChannel.IsValid())
    {
        SetPosition(mPositionChannel.GetPoint());
    }
}



/**
 * Draw the head top
 * @param graphics
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);

//    wxPoint eb1 = TransformPoint(wxPoint(32, 63));
//    wxPoint eb2 = TransformPoint(wxPoint(46, 61));
//
//    wxPen eyebrowPen(*wxBLACK, 2);
//    graphics->SetPen(eyebrowPen);
//    graphics->StrokeLine(eb1.x, eb1.y, eb2.x, eb2.y);

//    DrawEyebrow(graphics, wxPoint(32, 63), wxPoint(46, 61));
//    DrawEyebrow(graphics, wxPoint(64, 59), wxPoint(77, 61));
//
//    DrawEye(graphics, wxPoint(42, 79));
//    DrawEye(graphics, wxPoint(69, 79));


    // Distance horizontally from each eye center to the center
    int d2 = mInterocularDistance / 2;

    // Compute a left and right eye center X location
    int rightX = mEyesCenter.x - d2;
    int leftX = mEyesCenter.x + d2;

    // Eye center Y value
    int eyeY = mEyesCenter.y;

//    DrawEyebrow(graphics, wxPoint(rightX - 10, eyeY - 16), wxPoint(rightX + 4, eyeY - 18));
//    DrawEyebrow(graphics, wxPoint(leftX - 4, eyeY - 20), wxPoint(leftX + 9, eyeY - 18));
//
//    DrawEye(graphics, wxPoint(leftX, eyeY));
//    DrawEye(graphics, wxPoint(rightX, eyeY));

    if (mLeftEye.IsLoaded() && mRightEye.IsLoaded())
    {
        // Determine the point on the screen were we will draw the left eye
        wxPoint leye = TransformPoint(wxPoint(leftX, eyeY));
        // And draw the bitmap there
        mLeftEye.DrawImage(graphics, leye, mPlacedR);

        // Repeat the process for the right eye.
        wxPoint reye = TransformPoint(wxPoint(rightX, eyeY));
        mRightEye.DrawImage(graphics, reye, mPlacedR);
    }
    else
    {
        DrawEyebrow(graphics, wxPoint(rightX - 10, eyeY - 16), wxPoint(rightX + 4, eyeY - 18));
        DrawEyebrow(graphics, wxPoint(leftX - 4, eyeY - 20), wxPoint(leftX + 9, eyeY - 18));

        DrawEye(graphics, wxPoint(leftX, eyeY));
        DrawEye(graphics, wxPoint(rightX, eyeY));
    }

}


/**
 * Draw an eyebrow, automatically transforming the points
 *
 * Draw a line from (x1, y1) to (x2, y2) after transformation
 * to the local coordinate system.
 * @param graphics Graphics context to draw on
 * @param p1 First point
 * @param p2 Second point
 */
void HeadTop::DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics,
        wxPoint p1, wxPoint p2)
{
    auto eb1 = TransformPoint(p1);
    auto eb2 = TransformPoint(p2);

    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(eb1.x, eb1.y, eb2.x, eb2.y);
}


/**
 * Draw an eye using an Ellipse
 * @param graphics The graphics context to draw on
 * @param p1 Where to draw before transformation */
void HeadTop::DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1)
{
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);

    auto e1 = TransformPoint(p1);

    float wid = 15.0f;
    float hit = 20.0f;

    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}


/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}
