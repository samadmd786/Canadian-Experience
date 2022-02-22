/**
 * @file PolyDrawable.cpp
 * @author Md Samad
 */
#include "pch.h"
#include "PolyDrawable.h"

/**
 * Constructor
 * @param name name of the file
 */
PolyDrawable::PolyDrawable(const std::wstring& name)
        :Drawable(name)
{

}

/**
 * Add the point
 * @param point point to be added
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}

void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!mPoints.empty()) {

        mPath = graphics->CreatePath();
        mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR)+mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++) {
            mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR)+mPlacedPosition);
        }
        mPath.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(mPath);
    }
}

bool PolyDrawable::HitTest(wxPoint pos)
{

    return mPath.Contains(pos.x, pos.y);
}