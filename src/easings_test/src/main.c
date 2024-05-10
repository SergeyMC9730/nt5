#include <stdio.h>
#include <nt5emul/renderer.h>
#include <nt5emul/renderer_animation.h>
#include <nt5emul/renderer_keyframe.h>

#define FRAMES 2

struct box_movement {
    struct movement {
        struct renderer_animation anim;
        struct renderer_keyframe keyframes[FRAMES];
    } x;
    struct movement x2;

    struct movement y;
} box_animation;

void draw(void *user) {
    ClearBackground(BLACK);

    DrawRectangle(box_animation.x.anim.current_value, box_animation.y.anim.current_value, 40, 40, RED);

    DrawFPS(10, 10);
}
void update(void *user) {
    box_animation.x.anim.delta = (double)1 / (double)GetFPS();
    box_animation.y.anim.delta = box_animation.x.anim.delta;
    box_animation.x2.anim.delta = box_animation.y.anim.delta;

    _ntRendererUpdateAnimation(&box_animation.x.anim);
    _ntRendererUpdateAnimation(&box_animation.y.anim);
}

void setupAnimation() {
    box_animation.x.anim.count = FRAMES;
    box_animation.x2.anim.count = 1;
    box_animation.y.anim.count = FRAMES;

    box_animation.x.anim.anim_id = 1;
    box_animation.x2.anim.anim_id = 2;

    box_animation.x.keyframes[0] = (struct renderer_keyframe){
        .easing = TOInOutCubic,
        .ending_value = 200,
        .length = 2.f 
    };
    box_animation.x.keyframes[1] = (struct renderer_keyframe){
        .easing = TOLinear,
        .ending_value = 0,
        .length = 0.5f 
    };

    box_animation.y.keyframes[0] = (struct renderer_keyframe){
        .easing = TOInOutCubic,
        .ending_value = 200,
        .length = 2.f 
    };
    box_animation.y.keyframes[1] = (struct renderer_keyframe){
        .easing = TOOutBack,
        .ending_value = -200,
        .length = 1.f
    };

    box_animation.x2.keyframes[0] = (struct renderer_keyframe){
        .easing = TOLinear,
        .ending_value = 400,
        .length = 4
    };

    box_animation.x.anim.keyframes = box_animation.x.keyframes;
    box_animation.y.anim.keyframes = box_animation.y.keyframes;
    box_animation.x2.anim.keyframes = box_animation.x2.keyframes;

    box_animation.x.anim.linked_animation = &box_animation.x2.anim;
    box_animation.x.anim.influenced = true;
}

int main() {
    _ntRendererCreateEnvironmentEx(true);

    // SetTargetFPS(30);

    renderer_state_t *st = _ntRendererGetState();

    setupAnimation();

    st->layers[0].on_draw.callback = draw;
    st->layers[0].on_update.callback = update;

    _ntRendererJoin();

    return 0;
}