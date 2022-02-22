/**
 * @file AnimChannelPoint.cpp
 * @author Md Samad
 */

#include "pch.h"
#include "AnimChannelPoint.h"

void AnimChannelPoint::Tween(double t)
{
    wxPoint a = mKeyframe1->Getpoint();
    wxPoint b = mKeyframe2->Getpoint();

    mPoint = wxPoint(double(a.x+t*(b.x-a.x)),
            double(a.y+t*(b.y-a.y)));
}

/**
 * Set the keyframe
 * @param point keyframe to be set at the point
 */
void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    auto keyframe = std::make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}
