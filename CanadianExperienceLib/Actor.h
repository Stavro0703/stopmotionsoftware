/**
 * @file Actor.h
 * @author Charles Owen
 *
 * Class for actors in our drawings.
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

#include "AnimChannelPoint.h"

class Drawable;
class Picture;

/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class Actor {
private:
    /// The actor name
    std::wstring mName;

    /// Is this actor enabled (drawable)?
    bool mEnabled = true;

    /// The actor position
    wxPoint mPosition;

    /// Is this actor mouse clickable?
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// The picture this actor is associated with
    Picture *mPicture = nullptr;

    /// The actor position channel
    AnimChannelPoint mChannel;

public:
    virtual ~Actor() {}

    Actor(const std::wstring &name);

    /** Default constructor disabled */
    Actor() = delete;
    /** Copy constructor disabled */
    Actor(const Actor &) = delete;
    /** Assignment operator disabled */
    void operator=(const Actor &) = delete;


    void SetRoot(std::shared_ptr<Drawable> root);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    std::shared_ptr<Drawable> HitTest(wxPoint pos);
    void AddDrawable(std::shared_ptr<Drawable> drawable);

    /**
     * Get the actor name
     * @return Actor name
     * */
    std::wstring GetName() const { return mName; }

    /**
     * The actor position
     * @return The actor position as a point
     * */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * The actor position
     * @param pos The new actor position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }


    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set Actor Enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Actor is clickable
     * @return true if actor is clickable
     */
    bool IsClickable() const { return mClickable; }

    /**
     * Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    void SetPicture(Picture *picture);

    /**
     * Get the picture this actor is for
     * @return The picture object
     */
    Picture *GetPicture() { return mPicture; }

    void SetKeyframe();
    void GetKeyframe();

    /**
     * The position animation channel
     * @return Pointer to animation channel
     */
    AnimChannelPoint *GetPositionChannel() { return &mChannel; }
};

#endif //CANADIANEXPERIENCE_ACTOR_H
