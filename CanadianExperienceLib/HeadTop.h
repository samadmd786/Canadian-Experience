/**
 * @file HeadTop.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "pch.h"
#include "ImageDrawable.h"
#include "AnimChannelPoint.h"

class Drawable;

/**
 * Class to create harold head
 */
class HeadTop : public ImageDrawable {
private:

    /// Point channel
    AnimChannelPoint mChannel;
public:

    HeadTop(const std::wstring& name, const std::wstring& filename);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool IsMovable() override;

    wxPoint TransformPoint(wxPoint p);

    /**
     * Set the timeline
     * @param timeline timeline reference to be used
     */
    void SetTimeline(Timeline* timeline) override;

    void SetKeyframe() override;

    void GetKeyframe() override;

};

#endif //CANADIANEXPERIENCE_HEADTOP_H
