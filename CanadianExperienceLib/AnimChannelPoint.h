/**
 * @file AnimChannelPoint.h
 * @author Md Samad
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
#define CANADIANEXPERIENCE_ANIMCHANNELPOINT_H

#include "AnimChannel.h"
#include <memory>

class Timeline;

/**
 * Class to create points for channel
 */
class AnimChannelPoint : public AnimChannel {
private:

    /// Point of the channel
    wxPoint mPoint;

protected:

    /// Class to represent KeyframePoint
    class KeyframePoint : public Keyframe {
    private:

        /// Point of the channel
        wxPoint mPoint;

        /// The channel this keyframe is associated with
        AnimChannelPoint* mChannel;

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param point The point for the keyframe
         */
        KeyframePoint(AnimChannelPoint
        * channel, wxPoint point)
                :Keyframe(channel), mChannel(channel), mPoint(point) { }

        virtual ~KeyframePoint() { }

        /// Default constructor (disabled)
        KeyframePoint() = delete;

        /// Copy constructor (disabled)
        KeyframePoint(const KeyframePoint&) = delete;

        /// Assignment operator
        void operator=(const KeyframePoint&) = delete;

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the point
        void UseOnly() override { mChannel->mPoint = mPoint; }

        /**
         * Get point
         * @return point
         */
        wxPoint Getpoint() { return mPoint; }

        /**
         * Set point
         * @param point
         */
        void SetPoint(wxPoint point) { mPoint = point; }
    };

    /**
     * Tween function
     * @param t time
     */
    virtual void Tween(double t) override;

private:
    /// The first point keyframe
    KeyframePoint* mKeyframe1 = nullptr;

    /// The second point keyframe
    KeyframePoint* mKeyframe2 = nullptr;
public:
    /// Destructor
    virtual ~AnimChannelPoint() { }

    /// Copy constructor (disabled)
    AnimChannelPoint(const AnimChannelPoint&) = delete;

    /// Assignment operator
    void operator=(const AnimChannelPoint&) = delete;

    /**
     * Get point
     * @return point
     */
    wxPoint GetPoint() { return mPoint; }

    void SetKeyframe(wxPoint point);

    AnimChannelPoint() { }
};

#endif //CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
