/**
 * @file AnimChannel.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "AnimChannel.h"

#include "Timeline.h"


/**
 * Determine how we should insert a keyframe into our keyframe list.
 * @param keyframe The keyframe to insert
 */
void AnimChannel::InsertKeyframe(std::shared_ptr<Keyframe> keyframe)
{
    // Get the current frame and tell it to the keyframe we are setting.
    int currFrame = mTimeline->GetCurrentFrame();
    keyframe->SetFrame(currFrame);

    // The possible options for keyframe insertion
    enum class Action { Append, Replace, Insert } action;

    // Determine the action we will do
    if (mKeyframe1 < 0)
    {
        // There is no first keyframe. This means
        // we are before any keyframes or there are no keyframes.
        // If before a keyframe, we insert, otherwise, we append
        action = mKeyframe2 >= 0 ? Action::Insert : Action::Append;
    }
    else
    {
        // We know mKeyframe1 is valid
        // So, we are after it.
        int frame1 = mKeyframes[mKeyframe1]->GetFrame();

        if (mKeyframe2 < 0)
        {
            // There is no second keyframe.
            // If we are after the current frame, we append.
            // If we are on the current frame, we replace.
            action = frame1 < currFrame ? Action::Append : Action::Replace;
        }
        else
        {
            // There is a second keyframe
            // If we are before the first frame, we insert
            // If not, we replace
            action = frame1 < currFrame ? Action::Insert : Action::Replace;
        }
    }

    //
    // And do the appropriate action
    //
    switch (action)
    {
    case Action::Append:
        // Add to end and the keyframe to the left becomes the new keyframe
        mKeyframes.push_back(keyframe);
        mKeyframe1 = (int)mKeyframes.size() - 1;
        break;

    case Action::Replace:
        // Replace the current keyframe
        mKeyframes[mKeyframe1] = keyframe;
        break;

    case Action::Insert:
        // Insert after mKeyframe1
        // and mKeyframe1 becomes this new insertion (frame we are on)
        mKeyframes.insert(mKeyframes.begin() + (mKeyframe1 + 1), keyframe);
        mKeyframe1++;
        break;
    }

}


/**
 * Ensure the keyframe indices are valid for the current time.
 *
 * The location pointed to by keyframe1 must be a time less than or
 * equal to the current time and the location pointed to by keyframe2
 * must be the next location and a location greater than the current
 * time. Note that the time may be before or after the first or last
 * item in the list.  We indicate that with values of -1 for the
 * indices.
 * @param currFrame The frame we are on.
 */
void AnimChannel::SetFrame(int currFrame)
{
    // Should we move forward in time?
    while (mKeyframe2 >= 0 && mKeyframes[mKeyframe2]->GetFrame() <= currFrame)
    {
        mKeyframe1 = mKeyframe2;
        mKeyframe2++;
        if (mKeyframe2 >= (int)mKeyframes.size())
            mKeyframe2 = -1;
    }

    // Should we move backwards in time?
    while (mKeyframe1 >= 0 && mKeyframes[mKeyframe1]->GetFrame() > currFrame)
    {
        mKeyframe2 = mKeyframe1;
        mKeyframe1--;
    }

    // Four possibilities here:
    // No keyframes  (mKeyframe1 < 0 and mKeyframe2 < 0)
    // Only a keyframe to the left (mKeyframe1 >= 0 and mKeyframe2 < 0)
    // Between two keyframes (mKeyframe1 >= 0 and mKeyframe2 >= 0)
    // Only a keyframe to the right (mKeyframe1 < 0 and mKeyframe2 >= 0)
    if (mKeyframe1 >= 0 && mKeyframe2 >= 0)
    {
        // Between two keyframes
        // So we have to tween
        mKeyframes[mKeyframe1]->UseAs1();
        mKeyframes[mKeyframe2]->UseAs2();

        // Compute the t value
        double frameRate = GetTimeline()->GetFrameRate();
        double time1 = mKeyframes[mKeyframe1]->GetFrame() / frameRate;
        double time2 = mKeyframes[mKeyframe2]->GetFrame() / frameRate;
        double t = (GetTimeline()->GetCurrentTime() - time1) / (time2 - time1);

        // And tween
        Tween(t);
    }
    else if (mKeyframe1 >= 0)
    {
        // We are only using keyframe 1
        mKeyframes[mKeyframe1]->UseOnly();
    }
    else if (mKeyframe2 >= 0)
    {
        // We are only using keyframe 2
        mKeyframes[mKeyframe2]->UseOnly();
    }
}

/**
 * Clear the current keyframe.
 */
void AnimChannel::ClearKeyframe()
{
    // If there is no keyframe1, we are not on a keyframe
    if (mKeyframe1 < 0)
        return;

    // We know mKeyframe1 is valid
    // Determine the frame number for the first keyframe
    int frame1 = mKeyframes[mKeyframe1]->GetFrame();

    // What is the current frame?
    int currFrame = GetTimeline()->GetCurrentFrame();

    // This is only valid if we are on a keyframe, as
    // indicated by mKeyframe1 equal to the current frame.
    if (frame1 != currFrame)
        return;

    mKeyframes.erase(mKeyframes.begin() + mKeyframe1);

    // The current frame becomes the previous frame
    // or -1 if we are on frame 0
    mKeyframe1--;

    // If the next frame is valid, it will be decreased by 1
    if (mKeyframe2 >= 0)
        mKeyframe2--;
}


/** Save this item to an XML node
 * @param node The node we are going to be a child of
 * @return Allocated XML node.
 */
wxXmlNode* AnimChannel::XmlSave(wxXmlNode* node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"channel");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"name", mName);

    for (auto keyframe : mKeyframes)
    {
        keyframe->XmlSave(itemNode);
    }

    return itemNode;
}


/**
 * Save this keyframe to an XML node
 * @param node The node we are going to be a child of
 * @return Allocated XML node
 */
wxXmlNode* AnimChannel::Keyframe::XmlSave(wxXmlNode* node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"keyframe");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"frame", wxString::Format(wxT("%i"), mFrame));

    return itemNode;
}



/**
* Handle loading this channel from a channel tag.
* @param node channel tag node
*/
void AnimChannel::XmlLoad(wxXmlNode* node)
{
    //
    // Traverse the children of the node
    //
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"keyframe")
        {
            int frame = wxAtoi(child->GetAttribute(L"frame", L"0"));

            // Pretend we are at that time
            GetTimeline()->SetCurrentTime(double(frame) / double(GetTimeline()->GetFrameRate()));

            // Have the derived class set the keyframe
            XmlLoadKeyframe(child);
        }
    }
}


/**
 * Clear all keyframes for this channel.
 */
void AnimChannel::Clear()
{
    mKeyframes.clear();
    mKeyframe1 = -1;
    mKeyframe2 = -1;
}