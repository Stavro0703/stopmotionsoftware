/**
 * @file Timeline.h
 * @author Charles Owen
 *
 * This class implements a timeline that manages the animation
 */

#ifndef CANADIANEXPERIENCE_TIMELINE_H
#define CANADIANEXPERIENCE_TIMELINE_H

class AnimChannel;

/**
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
class Timeline {
private:
    void XmlChannel(wxXmlNode* node);

    int mNumFrames = 300;       ///< Number of frames in the animation
    int mFrameRate = 30;        ///< Animation frame rate in frames per second
    double mCurrentTime = 0;    ///< The current animation time

    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;

public:
    Timeline();

    /// Copy constructor (disabled)
    Timeline(const Timeline &) = delete;

    /// Assignment operator
    void operator=(const Timeline &) = delete;

    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}

    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}

    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}

    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}

    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    void SetCurrentTime(double currentTime);

    /** Get the current frame.
     *
     * This is the frame associated with the current time
     * @return Current frame
     */
    int GetCurrentFrame() const { return int(mCurrentTime * mFrameRate); }

    /**
     * Get the animation duration
     * @return Animation duration in seconds
     */
    double GetDuration() const { return (double)mNumFrames / mFrameRate; }

    void Clear();

    void ClearKeyframe();

    void AddChannel(AnimChannel* channel);

    void Save(wxXmlNode* root);

    void Load(wxXmlNode* root);


};

#endif //CANADIANEXPERIENCE_TIMELINE_H
