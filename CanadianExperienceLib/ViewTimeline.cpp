/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 * @author Md Samad
 */

#include "pch.h"
#include <memory>
#include <wx/dcbuffer.h>
#include <sstream>
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include "Picture.h"
#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Actor.h"

using namespace std;
/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

/**
 Constructor
 * @param parent The main wxFrame object
 * @param imagesDir image to be used
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring& imagesDir)
        :wxScrolledCanvas(parent,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(100, Height),
        wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::SetKeyframe, this,
            XRCID("SetKeyframe"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::DeleteKeyframe, this,
            XRCID("DeleteKeyframe"));

    mPointerImage = make_unique<wxImage>(imagesDir+PointerImageFile, wxBITMAP_TYPE_ANY);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    Timeline* timeline = GetPicture()->GetTimeline();
    SetVirtualSize(timeline->GetNumFrames()*TickSpacing+BorderLeft+BorderRight, Height);
    SetScrollRate(1, 0);
    int left = BorderLeft;
    int shortTick = TickTop+TickShort;
    int longTick = TickTop+TickLong;
    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    wxPen pen(wxColour(0, 0, 0), 1);
    graphics->SetPen(pen);

    wxFont font(wxSize(0, TickFontSize),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    int tickNum = timeline->GetNumFrames();
    for (int i = 0; i<=tickNum; i++) {
        if (i%timeline->GetFrameRate()==0) {
            graphics->StrokeLine(left, TickTop, left, longTick);
            std::wstringstream str;
            str << i/timeline->GetFrameRate();
            std::wstring wstr = str.str();
            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);
            graphics->DrawText(wstr, left-(w/2), longTick);
        }
        else {
            graphics->StrokeLine(left, TickTop, left, shortTick);
        }
        left += TickSpacing;

    }

    if (mPointerBitmap.IsNull()) {
        mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);
    }
    graphics->DrawBitmap(mPointerBitmap,
            (int) (timeline->GetCurrentTime()*timeline->GetFrameRate()*TickSpacing+BorderLeft/2), 10,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());


}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent& event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline* timeline = GetPicture()->GetTimeline();
    int pointerX = (int) (timeline->GetCurrentTime()*
            timeline->GetFrameRate()*TickSpacing+BorderLeft);

    mMovingPointer = x>=pointerX-mPointerImage->GetWidth()/2 &&
            x<=pointerX+mPointerImage->GetWidth()/2;

    if (mMovingPointer) {
        int xx = 0;
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent& event)
{
    OnMouseMove(event);

}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent& event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    wxPoint newMouse(click.x, click.y);
    int x = click.x;
    // Get the timeline
    Timeline* timeline = GetPicture()->GetTimeline();
    if (mMovingPointer && event.LeftIsDown()) {
        double time = (double) (click.x-BorderLeft)/(timeline->GetFrameRate()*TickSpacing);
        if (time<0) {
            time = 0;
        }
        else if (time>timeline->GetDuration()) {
            time = timeline->GetDuration();
        }
        GetPicture()->SetAnimationTime(time);
    }
    else {
        mMovingPointer = false;
    }

}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if (dlg.ShowModal()==wxID_OK) {
        // The dialog box has changed the Tmeline settings
        GetPicture()->UpdateObservers();
    }
}

/**
 * Set the keyframe
 * @param event use for binding
 */
void ViewTimeline::SetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor: *picture) {
        actor->SetKeyframe();
    }
}

/**
 * Delete the keyframe
 * @param event use for binding
 */
void ViewTimeline::DeleteKeyframe(wxCommandEvent& event)
{
    Timeline* timeline = GetPicture()->GetTimeline();
    bool keyframeDeleted = timeline->DeleteKeyframe();
    if (keyframeDeleted) {
        GetPicture()->SetAnimationTime(timeline->GetCurrentTime());
    }
}


