/**
 * @file ImageDrawable.h
 * @author Charles Owen
 *
 * A drawable that displays an image
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable that displays an image
 */
class ImageDrawable : public Drawable {
private:
    /// The underlying image we are drawing
    std::unique_ptr<wxImage> mImage;

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

    /// The center of the image
    wxPoint mCenter = wxPoint(0, 0);

public:
    ImageDrawable(const std::wstring& name, const std::wstring& filename);

    /**
     * Set the center to rotate around
     * @param center New center
     */
    void SetCenter(wxPoint center) { mCenter = center; }

    /**
     * Get the center to rotate around
     * @return Center
     */
    wxPoint GetCenter() const { return mCenter; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;
};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
