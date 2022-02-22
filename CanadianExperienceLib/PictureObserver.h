/**
 * @file PictureObserver.h
 * @author Md Samad
 *
 *
 */
#include "pch.h"
#include <memory>
#include "vector"

#ifndef CANADIANEXPERIENCE_PICTUREOBSERVER_H
#define CANADIANEXPERIENCE_PICTUREOBSERVER_H

class Picture;

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class PictureObserver {
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

protected:
    /// Constructor
    PictureObserver() { }

public:

    /// Copy Constructor (Disabled)
    PictureObserver(const PictureObserver&) = delete;

    /// Assignment Operator (Disabled)
    void operator=(const PictureObserver&) = delete;

    /**
    * Destructor
    *
    * Must be declared as virtual:
    * virtual ~PictureObserver();
    */
    ~PictureObserver();

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    /**
     * Getter for the Picture
    * @return the picture
    */
    std::shared_ptr<Picture> GetPicture() { return mPicture; }

    void SetPicture(std::shared_ptr<Picture> picture);
};

#endif //CANADIANEXPERIENCE_PICTUREOBSERVER_H
