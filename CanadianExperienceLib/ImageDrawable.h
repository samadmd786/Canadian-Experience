/**
 * @file ImageDrawable.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "pch.h"
#include "Drawable.h"

/**
 * Draw the image on teh screen
 */
class ImageDrawable : public Drawable {
private:
    /// Center of the image
    wxPoint mCenter = wxPoint(0, 0);

protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

public:
    virtual ~ImageDrawable() { }

    /// Default constructor (disabled)
    ImageDrawable() = delete;

    /// Copy constructor (disabled)
    ImageDrawable(const ImageDrawable&) = delete;

    /// Assignment operator
    void operator=(const ImageDrawable&) = delete;

    ImageDrawable(const std::wstring& name, const std::wstring& filename);

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    virtual bool HitTest(wxPoint pos) override;

    /**
     * Get the center
     * @return center
     */
    wxPoint GetCenter() { return mCenter; }

    /**
     * Set center
     * @param center
     */
    void SetCenter(wxPoint center) { mCenter = center; }


};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
