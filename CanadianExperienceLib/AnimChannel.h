/**
 * @file AnimChannel.h
 * @author Charles Owen
 *
 * Base class for an animation channel
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H



class Timeline;

/**
 * Base class for an animation channel
 */
class AnimChannel {
private:
    /// The channel name
    std::wstring mName;

    /// The first keyframe
    int mKeyframe1 = -1;

    /// The second keyframe
    int mKeyframe2 = -1;

    /// The timeline object
    Timeline *mTimeline = nullptr;

protected:
    /// Default constructor
    AnimChannel() {}
    
    /// Class that represents a keyframe
    class Keyframe
    {
    public:
        /** Default constructor disabled */
        Keyframe() = delete;
        /** Copy constructor disabled */
        Keyframe(const Keyframe &) = delete;
        /** Assignment operator disabled */
        void operator=(const Keyframe &) = delete;

        /**
         * Get the frame for this keyframe
         * @return The keyframe frame number
         */
        int GetFrame() const { return mFrame; }

        /**
         * Set the frame for this keyframe
         * @param f The new frame number to set
         */
        void SetFrame(int f) { mFrame = f; }

        /// Indicates this keyframe is used as Keyframe1
        virtual void UseAs1() = 0;

        /// Indicates this keyframe is used as Keyframe2
        virtual void UseAs2() = 0;

        /// Indicates this is the only keyframe
        virtual void UseOnly() = 0;

        virtual wxXmlNode* XmlSave(wxXmlNode* node);

    private:
        /// The channel this keyframe is associated with
        AnimChannel *mChannel;

        int mFrame; ///< The frame number for the keyframe

    protected:
        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    };

public:
    /// Destructor
    virtual ~AnimChannel() {}

    /** Copy constructor disabled */
    AnimChannel(const AnimChannel &) = delete;
    /** Assignment operator disabled */
    void operator=(const AnimChannel &) = delete;

    /** Set the channel name
     * @param name The new name to set */
    void SetName(const std::wstring &name) { mName = name; }

    /**
     * Get the channel name
     * @return Channel name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Set the timeline for this channel
     * @param timeline The timeline to use
     */
    void SetTimeline(Timeline *timeline) { mTimeline = timeline; }

    /**
     * Get the timeline for this channel
     * @return The timeline pointer
     */
    Timeline *GetTimeline() { return mTimeline; }

    void SetFrame(int currFrame);

    /**
     * Is the channel valid, meaning has keyframes?
     * @return true if the channel is valid.
     */
    bool IsValid() { return mKeyframe1 >= 0 || mKeyframe2 >= 0; }
    void ClearKeyframe();

    virtual void Clear();
    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    virtual void XmlLoad(wxXmlNode* node);

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

protected:
    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Channel type specific loading and keyframe creation
     * @param node Node to load from
     */
    virtual void XmlLoadKeyframe(wxXmlNode* node) = 0;

    /**
     * Tween between two keyframes
     * @param t The T value (0 to 1)
     * */
    virtual void Tween(double t) = 0;
};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
