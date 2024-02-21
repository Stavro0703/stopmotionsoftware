/**
 * @file ViewEdit.h
 * @author Charles B. Owen
 *
 *  Basic edit view class for the Canadian Experience
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

#ifndef CANADIANEXPERIENCE_VIEWEDIT_H
#define CANADIANEXPERIENCE_VIEWEDIT_H

#include "PictureObserver.h"

class Actor;
class Drawable;

/**
 * View class for our aquarium
 */
class ViewEdit final : public wxScrolledCanvas, public PictureObserver {
private:
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftDoubleClick(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

    void OnEditMove(wxCommandEvent& event);
    void OnEditRotate(wxCommandEvent& event);
    void OnUpdateEditMove(wxUpdateUIEvent& event);
    void OnUpdateEditRotate(wxUpdateUIEvent& event);
	void OnChangeMachineOne(wxCommandEvent &event);
	void OnChangeMachineTwo(wxCommandEvent &event);
	void OnMachineSetFrame(wxCommandEvent &event);

    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

    /// The currently selected actor
    std::shared_ptr<Actor> mSelectedActor;

    /// The currently selected drawable
    std::shared_ptr<Drawable> mSelectedDrawable;

public:
    /// The current mouse mode
    enum class Mode {Move, Rotate};

    /// The currently set mouse mode
    Mode mMode = Mode::Move;

public:
    ViewEdit(wxFrame* parent);

    void UpdateObserver() override;
};

#endif //CANADIANEXPERIENCE_VIEWEDIT_H
