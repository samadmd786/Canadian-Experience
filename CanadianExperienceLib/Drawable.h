/**
 * @file Drawable.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_DRAWABLE_H
#define CANADIANEXPERIENCE_DRAWABLE_H

#include "pch.h"
#include "Actor.h"
#include "AnimChannelAngle.h"

class Timeline;

/**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class Drawable {
private:

/// The drawable name
    std::wstring mName;

    /// The position of this drawable relative to its parent
    wxPoint mPosition = wxPoint(0, 0);

    /// The rotation of this drawable relative to its parent
    double mRotation = 0;

    /// The actor using this drawable
    Actor* mActor = nullptr;

    /// The parent using this drawable
    Drawable* mParent = nullptr;

    /// The vector of children
    std::vector<std::shared_ptr<Drawable>> mChildren;

protected:
    /// The actual position in the drawing
    wxPoint mPlacedPosition = wxPoint(0, 0);

    /// The actual rotation in the drawing
    double mPlacedR = 0;

    Drawable(const std::wstring& name);

    wxPoint RotatePoint(wxPoint point, double angle);

/// The animation channel for animating the angle of this drawable
AnimChannelAngle mChannel;
public:
    /// Destructor
    virtual ~Drawable() { }

    /// Default constructor (disabled)
    Drawable() = delete;

    /// Copy constructor (disabled)
    Drawable(const Drawable&) = delete;

    /// Assignment operator
    void operator=(const Drawable&) = delete;

    void SetActor(Actor* actor);

    void Place(wxPoint offset, double rotate);

    void AddChild(std::shared_ptr<Drawable> child);

    void Move(wxPoint delta);

    /**
     * Draw this drawable
     * @param graphics Graphics object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) = 0;

    /**
      * Is this a movable drawable?
      * @return true if movable
      */
    virtual bool IsMovable() { return false; }

    /**
     * Get the name
     * @return name
     */
    wxString GetName() const { return mName; }

    /**
     * Get the position
     * @return position
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * The actor position
     * @return parent
     */

    Drawable* GetParent() { return mParent; }

    /**
     * Set the parent
     * @param drawable Drawable to need to be set
     */
    void SetParent(Drawable* drawable) { mParent = drawable; }

    /**
     * Set the position
     * @param position position to need to be set
     */
    void SetPosition(wxPoint position) { mPosition = position; }

    /**
     * Get rotation
     * @return rotation
     */
    double GetRotation() const { return mRotation; }

    /**
     * Set rotation
     * @param rotation
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    virtual void SetTimeline(Timeline* timeline);

    /**
   * The angle animation channel
   * @return Pointer to animation channel
   */
    AnimChannelAngle* GetAngleChannel() { return &mChannel; }

    virtual void SetKeyframe();

    virtual void GetKeyframe();
};

#endif //CANADIANEXPERIENCE_DRAWABLE_H
