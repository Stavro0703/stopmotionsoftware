/**
 * @file AnimChannelPoint.h
 * @author Charles Owen
 *
 * An animation channel specific to points (translational movement)
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
#define CANADIANEXPERIENCE_ANIMCHANNELPOINT_H

#include "AnimChannel.h"

/**
 * An animation channel specific to points (translational movement)
 */
class AnimChannelPoint : public AnimChannel {
private:
    /// The point we compute
    wxPoint mPoint = wxPoint(0, 0);

public:
    AnimChannelPoint() = default;

    /**
     * The point we compute
     * @return  The computed point
     */
    wxPoint GetPoint() { return mPoint; }

    /// A keyframe for a point channel
    class KeyframePoint : public Keyframe
    {
    private:
        /// The keyframe point
        wxPoint mPoint = wxPoint(0, 0);

        /// The channel this keyframe is associated with
        AnimChannelPoint *mChannel;

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param point The animation position for the keyframe
         */
        KeyframePoint(AnimChannelPoint *channel, wxPoint point) :
                Keyframe(channel), mChannel(channel), mPoint(point) {}

        /** Default constructor disabled */
        KeyframePoint() = delete;
        /** Copy constructor disabled */
        KeyframePoint(const KeyframePoint &) = delete;
        /** Assignment operator disabled */
        void operator=(const KeyframePoint &) = delete;

        /// The keyframe point
        /// @return The keyframe point
        wxPoint GetPoint() { return mPoint; }

        /** Use this keyframe as keyframe 1 */
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /** Use this keyframe as keyfraem 2 */
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /** Use this keyframe as the angle */
        void UseOnly() override { mChannel->mPoint = mPoint; }

        wxXmlNode* XmlSave(wxXmlNode* node) override;
    };

    void SetKeyframe(wxPoint point);
    void Tween(double t) override;

private:
    /// The first angle keyframe
    KeyframePoint *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframePoint *mKeyframe2 = nullptr;

protected:
    void XmlLoadKeyframe(wxXmlNode* node) override;
};

#endif //CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
