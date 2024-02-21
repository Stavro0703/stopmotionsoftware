/**
 * @file Timeline.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
 * Constructor
 */
Timeline::Timeline()
{

}

/**
 * Add an animation channel to the timeline
 * @param channel Channel to add
 */
void Timeline::AddChannel(AnimChannel *channel)
{
    mChannels.push_back(channel);
    channel->SetTimeline(this);
}


/** Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
* @param t The new time to set
*/
void Timeline::SetCurrentTime(double t)
{
    // Set the time
    mCurrentTime = t;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}


/**
 * Clear any keyframe at the current time.
 */
void Timeline::ClearKeyframe()
{
    for (auto channel : mChannels)
    {
        channel->ClearKeyframe();
    }
}


/**
 * Save the timeline animation to XML
 * @param root Xml node to save to
 */
void Timeline::Save(wxXmlNode* root)
{
    root->AddAttribute(L"numframes", wxString::Format(wxT("%i"), mNumFrames));
    root->AddAttribute(L"framerate", wxString::Format(wxT("%i"), mFrameRate));

    for (auto channel : mChannels)
    {
       channel->XmlSave(root);
    }
}



/**
* Load a timeline animation from XML
* @param root XML node to load from
*/
void Timeline::Load(wxXmlNode* root)
{
    // Once we know it is open, clear the existing data
    Clear();

    // Get the attributes
    mNumFrames = wxAtoi(root->GetAttribute(L"numframes", L"300"));
    mFrameRate = wxAtoi(root->GetAttribute(L"framerate", L"30"));

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"channel")
        {
            XmlChannel(child);
        }
    }

}


/**
 * Handle the "channel" XML tag.
 * @param node Node that is the channel tag.
 */
void Timeline::XmlChannel(wxXmlNode* node)
{
    // Get the channel name
    auto name = node->GetAttribute(L"name", L"");

    // Find the channel
    for (auto channel : mChannels)
    {
        if (channel->GetName() == name)
        {
            // We found it, let it handle it
            channel->XmlLoad(node);
            break;
        }
    }
}



/** 
 * Clear all keyframes 
 */
void Timeline::Clear()
{
    // Reset the current time and restore to defaults.
    mCurrentTime = 0;
    mNumFrames = 300;
    mFrameRate = 30;

    for (auto channel : mChannels)
    {
        channel->Clear();
    }
}