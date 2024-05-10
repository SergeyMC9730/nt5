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
    // it also can be incremented by current_value from linked animation but this behaviour is disabled by default
    double current_value;

    // local current value
    // it is not affected by the linked animation
    double local_current_value;

    // value on animation end
    double final_value;

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

    // animation id, useful for debugging
    int anim_id;

    // indicates if animation has been completed or not
    bool completed;

    // indicates if animation has been completed locally or not
    bool completed_local;

    // indicates if animation is valid or not
    bool valid;
};

void _ntRendererUpdateAnimation(struct renderer_animation *animation);