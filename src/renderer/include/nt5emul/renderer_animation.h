#pragma once

// #include <nt5emul/renderer_keyframe.h>

struct renderer_keyframe;

#include <stdbool.h>

struct renderer_animation {
    // keyframe array
    struct renderer_keyframe *keyframes;
    // amount of objects inside keyframes array
    unsigned int count;

    // currently processed keyframe
    unsigned int current_keyframe;

    // starting value to work with
    // modified when keyframe is finished
    double starting_value;

    // current value
    // it also would be incremented by current_value from linked animation but you can disable this behaviour
    double current_value;

    // time spent on whole animation
    double time;

    // time spent on a currently processed keyframe
    double itime;

    // delta time for this animation
    double delta;

    // linked animation
    struct render_animation *linked_animation;

    // if this flag is set to true then current_value also would include current_value from the linked_animation
    bool influenced;    
};

void _ntRendererUpdateAnimation(struct renderer_animation *animation);