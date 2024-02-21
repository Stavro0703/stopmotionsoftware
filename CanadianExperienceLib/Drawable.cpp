/**
 * @file Drawable.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "Drawable.h"
#include "Actor.h"
#include "Timeline.h"

/**
 * Constructor
 * \param name The drawable name
 */
Drawable::Drawable(const std::wstring &name) : mName(name)
{

}


/**
 * Add the channels for this drawable to a timeline
 * @param timeline The timeline class.
 */
void Drawable::SetTimeline(Timeline *timeline)
{
    timeline->AddChannel(&mChannel);
}

/**
 * Set the actor using this drawable
 * @param actor Actor using this drawable
 */
void Drawable::SetActor(Actor *actor)
{
    mActor = actor;

    // Set the channel name
    mChannel.SetName(actor->GetName() + L":" + mName);
}


/**
 * Set a keyframe based on the current position.
 */
void Drawable::SetKeyframe()
{
    mChannel.SetKeyframe(mRotation);
}

/**
 * Get a keyframe update from the animation system.
 */
void Drawable::GetKeyframe()
{
    if (mChannel.IsValid())
        mRotation = mChannel.GetAngle();
}


/**
 * Place this drawable relative to its parent
 *
 * This works hierarchically from top item down.
 * @param offset Parent offset
 * @param rotate Parent rotation
 */
void Drawable::Place(wxPoint offset, double rotate)
{
    // Combine the transformation we are given with the transformation
    // for this object.
    mPlacedPosition = offset + RotatePoint(mPosition, rotate);
    mPlacedR = mRotation + rotate;

    // Update our children
    for (auto drawable : mChildren)
    {
        drawable->Place(mPlacedPosition, mPlacedR);
    }
}


/**
 * Add a child drawable to this drawable
 * @param child The child to add
 */
void Drawable::AddChild(std::shared_ptr<Drawable> child)
{
    mChildren.push_back(child);
    child->mParent = this;
    child->SetParent(this);
}




/**
 * Move this drawable some amount
 * @param delta The amount to move
 */
void Drawable::Move(wxPoint delta)
{
    if (mParent != nullptr)
    {
        mPosition = mPosition + RotatePoint(delta, -mParent->mPlacedR);
    }
    else
    {
        mPosition = mPosition + delta;
    }
}


/** Rotate a point by a given angle.
 * @param point The point to rotate
 * @param angle An angle in radians
 * @return Rotated point
 */
wxPoint Drawable::RotatePoint(wxPoint point, double angle)
{
    double cosA = cos(angle);
    double sinA = sin(angle);

    return wxPoint(int(cosA * point.x + sinA * point.y),
            int(-sinA * point.x + cosA * point.y));
}