/**
 * @file MainFrame.cpp
 * @author Charles B. Owen
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "Picture.h"
#include "MainFrame.h"
#include "PictureFactory.h"

/// Directory within the resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 */
MainFrame::MainFrame()
{

}

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    //
    // Create the picture
    //

    auto standardPaths = wxStandardPaths::Get();
    auto imagesDir = standardPaths.GetResourcesDir().ToStdWstring()+ImagesDirectory;

    // Create our picture
    PictureFactory factory;
    mPicture = factory.Create(imagesDir);

    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");

#ifdef WIN32
    // This sets the frame icon on Windows systems
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif
    mViewEdit = new ViewEdit(this);
    mViewTimeline = new ViewTimeline(this, imagesDir);

    auto sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(mViewEdit, 1, wxEXPAND | wxALL);
    sizer->Add(mViewTimeline, 0, wxEXPAND | wxALL);

    SetSizer(sizer);
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);


    // Tell the views about the picture
    mViewEdit->SetPicture(mPicture);
    mViewTimeline->SetPicture(mPicture);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Application about box menu handler
 */
void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();
}