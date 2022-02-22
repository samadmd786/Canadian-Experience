/**
 * @file AnimChannelAngle.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"
#include <memory>

/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
private:

    /// Angle of the animation
    double mAngle = 0;

protected:

    /// Class to represent KeyframeAngle
    class KeyframeAngle : public Keyframe {
    private:

        /// Angle of the channel
        double mAngle;

        /// The channel this keyframe is associated with
        AnimChannelAngle* mChannel;
    protected:

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle* channel, double angle)
                :Keyframe(channel), mChannel(channel), mAngle(angle) { }

        virtual ~KeyframeAngle() { }

        /// Default constructor (disabled)
        KeyframeAngle() = delete;

        /// Copy constructor (disabled)
        KeyframeAngle(const KeyframeAngle&) = delete;

        /// Assignment operator
        void operator=(const KeyframeAngle&) = delete;

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

        /**
         * Get Angle
         * @return angle angle to be returned
         */
        double GetAngle() { return mAngle; }

        /**
         * Set Angle
         * @param angle
         */
        void SetAngle(double angle) { mAngle = angle; }
    };

    virtual void Tween(double t) override;

private:
    /// The first angle keyframe
    KeyframeAngle* mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle* mKeyframe2 = nullptr;
public:
    /// Destructor
    virtual ~AnimChannelAngle() { }

    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle&) = delete;

    /// Assignment operator
    void operator=(const AnimChannelAngle&) = delete;

    /**
     * Get angle
     * @return angle
     */
    double GetAngle() { return mAngle; }

    void SetKeyframe(double angle);

    AnimChannelAngle() { }
};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
