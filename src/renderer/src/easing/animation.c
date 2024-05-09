#include <nt5emul/renderer_keyframe.h>
#include <nt5emul/renderer_animation.h>
#include <nt5emul/renderer_ease.h>
#include <stddef.h>

void _ntRendererUpdateAnimation(struct renderer_animation *animation) {
    if (animation->count == 0) return;
    if (animation->current_keyframe >= animation->count) return;

    if (animation->linked_animation != NULL) {
        _ntRendererUpdateAnimation(animation->linked_animation);
    }

    struct renderer_keyframe *selected = animation->keyframes + animation->current_keyframe;

    if (animation->itime >= selected->length) {
        animation->itime = 0;
        animation->current_keyframe++;

        if (animation->current_keyframe >= animation->count) return;
    
        animation->starting_value += selected->ending_value;

        selected = animation->keyframes + animation->current_keyframe;
    }

    static double (*easings[TOEnd])(double) = {
        _rendererLinear, _rendererInSine, _rendererOutSine,
        _rendererInOutSine, _rendererInQuad, _rendererOutQuad,
        _rendererInOutQuad, _rendererInCubic, _rendererOutCubic,
        _rendererInOutCubic, _rendererInQuart, _rendererOutQuart,
        _rendererInOutQuart, _rendererInQuint, _rendererOutQuint,
        _rendererInOutQuint, _rendererInExpo, _rendererOutExpo,
        _rendererInOutExpo, _rendererInCirc, _rendererOutCirc,
        _rendererInOutCirc, _rendererInBack, _rendererOutBack,
        _rendererInOutBack, _rendererInElastic, _rendererOutElastic,
        _rendererInOutElastic, _rendererInBounce, _rendererOutBounce,
        _rendererInOutBounce 
    };

    double (*selected_easing)(double) = easings[selected->easing];

    double res = selected_easing(animation->itime / selected->length);

    if (selected->easing == TOLinear) {
        res = (double)1 - res;
    }

    animation->current_value = animation->starting_value + (selected->ending_value * res);    

    animation->time += animation->delta;
    animation->itime += animation->delta;
}