/**
 * @file TimelineTest.cpp
 * @author Md Samad
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <memory>
#include <Timeline.h>
#include <AnimChannelAngle.h>

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}