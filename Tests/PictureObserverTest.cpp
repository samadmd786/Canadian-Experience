/**
 * @file PictureObserverTest.cpp
 * @author Md Samad
 */

#include <pch.h>
#include <PictureObserver.h>
#include <Picture.h>
#include "gtest/gtest.h"

class PictureObserverMock : public PictureObserver {
public:
    PictureObserverMock()
            :PictureObserver() { }

    virtual void UpdateObserver() override { mUpdated = true; }

    bool mUpdated = false;

};

TEST(PictureObserverTest, Construct)
{
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, GetPicture)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    observer.GetPicture();
    ASSERT_FALSE(observer.GetPicture());

    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.GetPicture());
}

TEST(PictureObserverTest, TwoObserver)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;
    // Create a mock observer object
    PictureObserverMock observer2;

    // And set it for the observer:
    observer.SetPicture(picture);

    // And set it for the observer:
    observer2.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);
}

TEST(PictureObserverTest, ObserverDestroyed)
{
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();
    PictureObserverMock observer;
    {
        PictureObserverMock observer2;

        // And set it for the observer:
        observer2.SetPicture(picture);
        picture->UpdateObservers();

        ASSERT_TRUE(observer2.mUpdated);
    }
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);


}

