/**
 * @file AnimChannel.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

class Timeline;

/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
private:

    /// name of channel
    std::wstring mName;

    /// first keyframe
    int mKeyframe1 = -1;

    /// second keyframe
    int mKeyframe2 = -1;

    /// The timeline object
    Timeline* mTimeline = nullptr;

protected:

    /// Class that represents a keyframe
    class Keyframe {
    private:

        /// frame to use
        int mFrame;

        /// The channel this keyframe is associated with
        AnimChannel* mChannel;
    protected:
        /**
        * Constructor
        * @param channel Channel we are associated with
        */
        Keyframe(AnimChannel* channel)
                :mChannel(channel) { }

    public:
        virtual ~Keyframe() { }

        /// Default constructor (disabled)
        Keyframe() = delete;

        /// Copy constructor (disabled)
        Keyframe(const Keyframe&) = delete;

        /// Assignment operator
        void operator=(const Keyframe&) = delete;

        /**
         * use points as first keyframe
         */
        virtual void UseAs1() = 0;

        /**
         * use points as second keyframe
         */
        virtual void UseAs2() = 0;

        /**
         * use only keyframe
         */
        virtual void UseOnly() = 0;

        /**
         * Get frame
         * @return frame
         */
        int GetFrame() { return mFrame; }

        /**
         * Set Frame
         * @param frame
         */
        void SetFrame(int frame) { mFrame = frame; }
    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Tween function
     * @param t time
     */
    virtual void Tween(double t) = 0;

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;
public:
    /// Default constructor
    AnimChannel() { }

    /// Destructor
    virtual ~AnimChannel() { }

    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel&) = delete;

    /// Assignment operator
    void operator=(const AnimChannel&) = delete;

    bool IsValid();

    void SetFrame(int currFrame);

    /**
     * Get name
     * @return name
     */
    std::wstring GetName() { return mName; }

    /**
     * Set name
     * @param name
     */
    void SetName(std::wstring name) { mName = name; }

    /**
     * Get Timeline
     * @return timeline
     */
    Timeline* GetTimeline() { return mTimeline; }

    /**
     * Set timeline
     * @param timeline
     */
    void SetTimeline(Timeline* timeline) { mTimeline = timeline; }

    bool DeleteKeyframe(int currentTime);
};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
