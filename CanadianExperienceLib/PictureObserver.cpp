/**
 * @file PictureObserver.cpp
 * @author Md Samad
 */
#include "pch.h"
#include "Picture.h"
#include "PictureObserver.h"

/**
 * Set the picture for this observer
 * @param picture The picture to set
 */
void PictureObserver::SetPicture(std::shared_ptr<Picture> picture)
{
    mPicture = picture;
    mPicture->AddObserver(this);
}

/**
  * Destructor
  *
  * Must be declared as virtual:
  * virtual ~PictureObserver();
  */
PictureObserver::~PictureObserver()
{
    if (mPicture!=nullptr) {
        mPicture->RemoveObserver(this);
    }
}


