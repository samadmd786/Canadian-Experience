/**
 * @file HeadTop.cpp
 * @author Md Samad
 */

#include "pch.h"
#include "HeadTop.h"
#include "PolyDrawable.h"
#include <memory>
#include "Timeline.h"

using namespace std;

/**
* Get the head
* @param name of the head
* @param filename file where the head is getting from
*/
HeadTop::HeadTop(const std::wstring& name, const std::wstring& filename)
        :ImageDrawable(name, filename)
{

}

/**
* Draw the image drawable
* @param graphics Graphics context to draw on
*/
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);
    wxPoint e1 = TransformPoint(wxPoint(40, 80));
    wxPoint e2 = TransformPoint(wxPoint(70, 80));
    wxPoint eb1 = TransformPoint(wxPoint(30, 60));
    wxPoint eb2 = TransformPoint(wxPoint(45, 60));
    wxPoint eb3 = TransformPoint(wxPoint(65, 60));
    wxPoint eb4 = TransformPoint(wxPoint(80, 60));

    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(eb1.x, eb1.y, eb2.x, eb2.y);
    graphics->StrokeLine(eb3.x, eb3.y, eb4.x, eb4.y);

    float wid = 15.0f;
    float hit = 20.0f;

    // First eye
    graphics->SetBrush(*wxBLACK);
    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

    // Second eye
    graphics->PushState();
    graphics->Translate(e2.x, e2.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();

}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p-GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR)+mPlacedPosition;
}

/**
 * Check if face is movable
 * @return bool
 */
bool HeadTop::IsMovable()
{
    return true;
}

void HeadTop::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
    timeline->AddChannel(&mChannel);
}

/**
 * Set a keyframe on an actor.
 */
void HeadTop::SetKeyframe()
{
    Drawable::SetKeyframe();
    mChannel.SetKeyframe(GetPosition());
}

/**
 * Get a keyframe for an actor.
 */
void HeadTop::GetKeyframe()
{
    Drawable::GetKeyframe();

    if (mChannel.IsValid()) {
        SetPosition(mChannel.GetPoint());
    }
}


