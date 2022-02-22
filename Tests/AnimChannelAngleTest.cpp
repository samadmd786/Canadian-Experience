/**
 * @file AnimChannelAngleTest.cpp
 * @author Md Samad
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>

using namespace std;

class AnimChannelAngleTest : public AnimChannelAngle {
public:

};

TEST(AnimChannelAngleTest, Name)
{
    AnimChannelAngle aimChannelAngle;
    aimChannelAngle.SetName(L"Harold");
    ASSERT_EQ(wstring(L"Harold"),aimChannelAngle.GetName());
}