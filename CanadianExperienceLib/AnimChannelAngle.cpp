/**
 * @file AnimChannelAngle.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "AnimChannelAngle.h"


/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param angle Angle for the keyframe.
 */
void AnimChannelAngle::SetKeyframe(double angle)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    auto keyframe = std::make_shared<KeyframeAngle>(this, angle);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}


/**
 * Compute an angle that is an interpolation
 * between two keyframes
 *
 * This function is called after Use1 and Use2,
 * so we have pointers to valid keyframes of the
 * type KeyframeAngle. This function computes the
 * tweening.
 *
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
 * Other values interpolate between.
 */
void AnimChannelAngle::Tween(double t)
{
    mAngle = mKeyframe1->GetAngle() * (1 - t) +
            mKeyframe2->GetAngle() * t;
}

/** Save this keyframe to an XML node
* @param node The node we are going to be a child of
* @return Allocated XML node.
*/
wxXmlNode* AnimChannelAngle::KeyframeAngle::XmlSave(wxXmlNode* node)
{
    auto itemNode = AnimChannel::Keyframe::XmlSave(node);
    itemNode->AddAttribute(L"angle", wxString::Format(wxT("%f"), mAngle));

    return itemNode;
}



/**
* Handle loading this channel's keyframe type
* @param node keyframe tag node
*/
void AnimChannelAngle::XmlLoadKeyframe(wxXmlNode* node)
{
    auto angleStr = node->GetAttribute(L"angle", L"0");

    double angle;
    angleStr.ToDouble(&angle);

    // Set a keyframe there
    SetKeyframe(angle);
}

