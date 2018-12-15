#if !defined(_VISION_CONTROL_HPP_)
#define _VISION_CONTROL_HPP_

namespace visionControl {

    const int VISION_SENSOR_PORT = 8;

    typedef enum {
        notTargeting,
        redFlag,
        blueFlag,
        flag
    } tTargetingState;

    void init();

    void move(void* param);

    tTargetingState getState();

    void setState(tTargetingState state);

    bool isTargeting();
}

#endif
