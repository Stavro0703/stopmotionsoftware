/**
 * @file AnimChannelAngle.h
 * @author Charles Owen
 *
 * Animation channel for angles
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"

/**
 * Animation channel for angles
 */
class AnimChannelAngle : public AnimChannel {
private:
    double mAngle = 0;  ///< The computed animation angle

protected:
    /// A keyframe for an angle channel
    class KeyframeAngle : public Keyframe
    {
    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
            Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /** Default constructor disabled */
        KeyframeAngle() = delete;
        /** Copy constructor disabled */
        KeyframeAngle(const KeyframeAngle &) = delete;
        /** Assignment operator disabled */
        void operator=(const KeyframeAngle &) = delete;

        /**
         * Get the angle at this keyframe
         * @return Angle in radians
         */
        double GetAngle() { return mAngle; }

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

    private:
        double mAngle;  ///< The angle for this keyframe

        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

        wxXmlNode* XmlSave(wxXmlNode* node) override;
    };

protected:
    void XmlLoadKeyframe(wxXmlNode* node) override;

    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;

public:
    AnimChannelAngle() {}

    /**
     * Get the current time angle
     * @return Angle in radians
     */
    double GetAngle() { return mAngle; }

    void SetKeyframe(double angle);
    void Tween(double t) override;
};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
