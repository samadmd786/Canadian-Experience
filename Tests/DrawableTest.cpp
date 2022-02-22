/**
 * @file DrawableTest.cpp
 * @author Md Samad
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>

using namespace std;

class DrawableMock : public Drawable {
public:
    DrawableMock(const std::wstring& name)
            :Drawable(name) { }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override { }

    virtual bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableMock, TestDrawableConstructor)
{
    DrawableMock drawable(L"Harold");
    ASSERT_EQ(std::wstring(L"Harold"), drawable.GetName());
}

TEST(DrawableMock, position)
{
    DrawableMock drawable(L"Harold");
    ASSERT_EQ(wxPoint(0, 0), drawable.GetPosition());

    drawable.SetPosition(wxPoint(50, 50));
    ASSERT_EQ(wxPoint(50, 50), drawable.GetPosition());

}


TEST(DrawableMock, rotation)
{
    DrawableMock drawable(L"Harold");
    ASSERT_NEAR(0, drawable.GetRotation(), 0.00001);

    drawable.SetRotation(1.23);
    ASSERT_NEAR(1.23, drawable.GetRotation(), 0.00001);

}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}