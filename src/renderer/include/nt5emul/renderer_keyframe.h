#pragma once

// value tweak object

#define GEN_TWEAK(tweak) TOIn##tweak, TOOut##tweak, TOInOut##tweak 

typedef enum renderer_tweak_type {
    TOLinear = 0,

    GEN_TWEAK(Sine),
    GEN_TWEAK(Quad),
    GEN_TWEAK(Cubic),
    GEN_TWEAK(Quart),
    GEN_TWEAK(Quint),
    GEN_TWEAK(Expo),
    GEN_TWEAK(Circ),
    GEN_TWEAK(Back),
    GEN_TWEAK(Elastic),
    GEN_TWEAK(Bounce),

    TOEnd
} renderer_tweak_type;

#undef GEN_TWEAK

struct renderer_keyframe {
    // length in seconds
    double length;

    // ending_value is the relative value. starting_value is incremented by ending_value
    // starting value does not directly exists inside a keyframe. starting_value is the resulting movement value from the previous keyframe
    double ending_value;

    renderer_tweak_type easing;
};