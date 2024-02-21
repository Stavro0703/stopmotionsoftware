/**
 * @file AnimChannelPoint.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "AnimChannelPoint.h"

using namespace std;


/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param point The point for the keyframe
 */
void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    shared_ptr<KeyframePoint> keyframe = make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/** Compute a tweened point between to points
 * @param t The tweening t value 
 */
void AnimChannelPoint::Tween(double t)
{
    auto a = mKeyframe1->GetPoint();
    auto b = mKeyframe2->GetPoint();

    mPoint = wxPoint(int(a.x + t * (b.x - a.x)),
            int(a.y + t * (b.y - a.y)));
}


/** Save this keyframe to an XML node
* @param node The node we are going to be a child of
* @return Allocated XML node.
*/
wxXmlNode* AnimChannelPoint::KeyframePoint::XmlSave(wxXmlNode* node)
{
    auto itemNode = AnimChannel::Keyframe::XmlSave(node);
    itemNode->AddAttribute(L"x", wxString::Format(wxT("%i"), mPoint.x));
    itemNode->AddAttribute(L"y", wxString::Format(wxT("%i"), mPoint.y));

    return itemNode;
}



/**
* Handle loading this channel's keyframe type
* @param node keyframe tag node
*/
void AnimChannelPoint::XmlLoadKeyframe(wxXmlNode* node)
{
    int x = wxAtoi(node->GetAttribute(L"x", L"0"));
    int y = wxAtoi(node->GetAttribute(L"y", L"0"));

    // Set a keyframe there
    SetKeyframe(wxPoint(x, y));
}



