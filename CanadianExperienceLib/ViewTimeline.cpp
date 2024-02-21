/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>

#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Picture.h"
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
 * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir The directory containing the program images
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring imagesDir) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mPointerImage = make_unique<wxImage>(imagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);
    Bind(wxEVT_TIMER, &ViewTimeline::OnTimer, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnFileSaveAs, this, wxID_SAVEAS);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnFileOpen, this, wxID_OPEN);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditTimelineProperties, this, XRCID("EditTimelineProperties"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnPlayPlay, this, XRCID("PlayPlay"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnPlayStop, this, XRCID("PlayStop"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnPlayPlayFromBeginning, this, XRCID("PlayPlayFromBeginning"));

    mTimer.SetOwner(this);
    mStopWatch.Start(0);
    mStopWatch.Pause();
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int sizeTotal = timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight;
    SetVirtualSize(sizeTotal, 0);
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    if(mPointerBitmap.IsNull())
    {
        mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);
    }

    auto rect = GetClientRect();
    int hit = rect.GetHeight();
    int wid = rect.GetWidth();

    wxFont font(wxSize(0, TickFontSize),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);
    graphics->SetPen(*wxBLACK_PEN);

    int top = TickTop;


    for (int tickNum = 0; tickNum <= timeline->GetNumFrames(); tickNum++)
    {
        int x = BorderLeft + tickNum * TickSpacing;
        int bottom = top + TickShort;

        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;
        if (onSecond)
        {
            bottom = top + TickLong;

            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << tickNum / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);

            graphics->DrawText(wstr, x - w / 2, bottom + 5);
        }

        graphics->StrokeLine(x, bottom, x, top);
    }

    //
    // Draw the pointer
    //
    int pw = mPointerImage->GetWidth();
    int ph = mPointerImage->GetHeight();
    int x = BorderLeft + (int)(timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing);
    graphics->DrawBitmap(mPointerBitmap,
            x - pw / 2, top,
            pw, ph
    );
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - (int)mPointerImage->GetWidth() / 2 && x <= pointerX + (int)mPointerImage->GetWidth() / 2;
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    Timeline *timeline = GetPicture()->GetTimeline();
    if (mMovingPointer && event.LeftIsDown())
    {
        double time = (double)(click.x - BorderLeft) / (timeline->GetFrameRate() * TickSpacing);
        if (time < 0)
        {
            time = 0;
        }
        else if (time > timeline->GetDuration())
        {
            time = timeline->GetDuration();
        }

        GetPicture()->SetAnimationTime(time);
    }
    else
    {
        mMovingPointer = false;
    }

}



/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        GetPicture()->UpdateObservers();
    }
}

/**
 * Handle the Edit>Set Keyframe menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Handle the Edit>Delete Keyframe menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();

    picture->GetTimeline()->ClearKeyframe();
    picture->SetAnimationTime(picture->GetAnimationTime());
}

/**
 * Handle a Play>Play menu option
 * @param event Menu event
 */
void ViewTimeline::OnPlayPlay(wxCommandEvent& event)
{
    if(mPlaying)
    {
        // If already playing
        return;
    }

    auto timeline = GetPicture()->GetTimeline();

    auto frameRate = timeline->GetFrameRate();
    auto time = timeline->GetCurrentTime();

    mStopWatch.Start(lround(time * 1000));
    mTimer.Start(1000 / frameRate);
}

/**
 * Handle a Play>Play from Beginning menu option
 * @param event Menu event
 */
void ViewTimeline::OnPlayPlayFromBeginning(wxCommandEvent& event)
{
    if(mPlaying)
    {
        Stop();
    }

    GetPicture()->SetAnimationTime(0);

    auto timeline = GetPicture()->GetTimeline();

    auto frameRate = timeline->GetFrameRate();

    mStopWatch.Start(0);
    mTimer.Start(1000 / frameRate);
}

/**
 * Handle a Stop button press
 * @param event Button event
 */
void ViewTimeline::OnPlayStop(wxCommandEvent& event)
{
    Stop();
}


/**
 * Handle timer events
 * @param event timer event
 */
void ViewTimeline::OnTimer(wxTimerEvent& event)
{
    auto timeline = GetPicture()->GetTimeline();

    auto newTime = mStopWatch.Time() / 1000.0;
    auto frameRate = timeline->GetFrameRate();

    int frame = (int)lround(newTime * frameRate);
    if(frame >= timeline->GetNumFrames())
    {
        frame = timeline->GetNumFrames();
        Stop();
    }

    GetPicture()->SetAnimationTime(newTime);
}


/**
 * Stop any playback animation
 */
void ViewTimeline::Stop()
{
    mPlaying = false;
    mTimer.Stop();
    mStopWatch.Pause();
}


/**
 * File>Save As menu handler
 * @param event Menu event
 */
void ViewTimeline::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save Animation file"), "", "",
            "Animation Files (*.anim)|*.anim", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    GetPicture()->Save(filename);
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void ViewTimeline::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load Animation file"), "", "",
            "Animation Files (*.anim)|*.anim", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    GetPicture()->Load(filename);
    Refresh();
}