/**
 * @file HeadTop.h
 * @author Charles Owen
 *
 * Special class for the head top.
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "ImageDrawable.h"
#include "RotatedBitmap.h"
#include "AnimChannelPoint.h"

/**
 * Special class for the head top.
 */
class HeadTop : public ImageDrawable {
private:
    /// Location of the center of the eyes
    wxPoint mEyesCenter = wxPoint(55, 79);

    /// Distance between the eyes in pixels
    int mInterocularDistance = 27;

    RotatedBitmap mLeftEye;        ///< Bitmap for the left eye
    RotatedBitmap mRightEye;       ///< Bitmap for the right eye

    /// Channel for the head position
    AnimChannelPoint mPositionChannel;

public:
    HeadTop(const std::wstring& name, const std::wstring& filename);

    /**
     * Is this drawable movable?
     * @return True because head tops are movable.
     */
    bool IsMovable() override { return true; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    wxPoint TransformPoint(wxPoint p);

    void DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1, wxPoint p2);

    void DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1);

    /**
     * Set the location for the center of the eyes
     * @param center New eyes center location
     */
    void SetEyesCenter(wxPoint center) { mEyesCenter = center; }

    /**
     * Set the distance between the eyes
     * @param d Distance between the eyes in pixels
     */
    void SetInterocularDistance(int d) { mInterocularDistance = d; }

    /**
     * Get a pointer to the left eye bitmap
     * @return Pointers to the left eye bitmap
     */
    RotatedBitmap *GetLeftEye() {return &mLeftEye;}

    /**
     * Get a pointer to the left eye bitmap
     * @return Pointers to the left eye bitmap
     */
    RotatedBitmap *GetRightEye() {return &mRightEye;}

    void SetActor(Actor* actor) override;
    void SetTimeline(Timeline* timeline) override;
    void SetKeyframe() override;
    void GetKeyframe() override;
};

#endif //CANADIANEXPERIENCE_HEADTOP_H
