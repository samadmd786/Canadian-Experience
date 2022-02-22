/**
 * @file TimelineDlg.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

#include "pch.h"
#include "Timeline.h"

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:

    /// Number of frames in the animation
    int mNumberOfFrames;

    /// Frame Rate
    int mFrameRate;

public:

    TimelineDlg(wxWindow* parent, Timeline* timeline);

    /// Timeline object
    Timeline* mTimeline;

    void OnOK(wxCommandEvent& event);
};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
