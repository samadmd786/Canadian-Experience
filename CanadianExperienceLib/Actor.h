/**
 * @file Actor.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

#include <memory>
#include "AnimChannelPoint.h"

class Drawable;

class Picture;

/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class Actor {
private:
    /// The actor name
    std::wstring mName;

    /// Is this actor enabled (drawable)?
    bool mEnabled = true;

    /// The actor position
    wxPoint mPosition;

    /// Is the actor clickable?
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// The picture using this drawable
    Picture* mPicture = nullptr;

    /// The animation channel for animating the point of this drawable
    AnimChannelPoint mChannel;

public:
    /// Default constructor (disabled)
    Actor() = delete;

    /// Copy constructor (disabled)
    Actor(const Actor&) = delete;

    /// Assignment operator
    void operator=(const Actor&) = delete;

    /// Destructor
    virtual ~Actor() { }

    Actor(const std::wstring& name);

    void SetRoot(std::shared_ptr<Drawable> root);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<Drawable> HitTest(wxPoint pos);

    void AddDrawable(std::shared_ptr<Drawable> drawable);

    /**
     * Get the actor name
     * @return Actor name
     * */
    std::wstring GetName() const { return mName; }

    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Get the position
     * @return position
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Get the picture
     * @return picture
     */
    Picture* GetPicture() { return mPicture; }

    void SetPicture(Picture* picture);

    /**
     * Actor is clickable
     * @return true if actor is clickable
     */
    bool IsClickable() const { return mClickable; }

    /**
    * Set Actor Enabled
    * @param enabled New enabled status
    */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * The actor position
     * @param position The new actor position
     */
    void SetPosition(wxPoint position) { mPosition = position; }

    /**
     * Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    void SetKeyframe();

    void GetKeyframe();

    /**
     * The point animation channel
     * @return Pointer to animation channel
     */
    AnimChannelPoint* GetPositionChannel() { return &mChannel; }

};

#endif //CANADIANEXPERIENCE_ACTOR_H
