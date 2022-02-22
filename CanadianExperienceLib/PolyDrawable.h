/**
 * @file PolyDrawable.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "pch.h"
#include "Drawable.h"

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable {
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;

    /// The array of point objects
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;

public:

    /// Destructor
    virtual ~PolyDrawable() { }

    /// Default constructor (disabled)
    PolyDrawable() = delete;

    /// Copy constructor (disabled)
    PolyDrawable(const PolyDrawable&) = delete;

    /// Assignment operator
    void operator=(const PolyDrawable&) = delete;

    PolyDrawable(const std::wstring& name);

    /**
    * Draw this drawable
    * @param graphics Graphics object to draw on
    */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) override;

    void AddPoint(wxPoint point);

    /**
     * Get colour
     * @return colour
     */
    wxColour GetColor() const { return mColor; }

    /**
     * Set colour
     * @param colour
     */
    void SetColor(wxColour colour) { mColor = colour; }

};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
