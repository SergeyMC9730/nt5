#include <nt5emul/dwm/button.h>

// if user clicks to button function returns true
bool _ntDrawDWMButton(struct dwm_context *ctx, struct dwm_button *btn) {
    Vector2 mouse = GetMousePosition();

    btn->activated.state = IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, btn->button);
    
    btn->howered.state = IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, btn->button);

    // if (btn->howered = false)

    Rectangle sz = btn->button;

    float font_sz = ctx->fonts.tahoma8_bld.real_size * 0.5f;
    float spacing = ctx->fonts.tahoma8_bld.spacing;

    Vector2 szText = MeasureTextEx(ctx->fonts.tahoma8_bld.font, btn->text, font_sz, spacing);

    int alignY = (sz.height - szText.y) / 2;

    Color borders[4] = {
        ctx->theme.basic.active_border_color,
        ctx->theme.basic.window_base_color,
        ctx->theme.basic.button_dk_shadow,
        ctx->theme.basic.button_shadow_color
    };

    Color border1, border2, border3, border4;

    Vector2 text_pos = {
        btn->button.x + 2,
        btn->button.y + alignY
    };

    if (btn->howered.state) {
        border1 = borders[0];
        border2 = borders[2];

        border3 = borders[3];
        border4 = borders[1];

        text_pos.x++;
        text_pos.y++;
    } else {
        border1 = borders[0];
        border2 = borders[1];

        border3 = borders[2];
        border4 = borders[3];
    }

    DrawLine(sz.x, sz.y, sz.x + sz.width - 1, sz.y, border1);
    DrawLine(sz.x, sz.y, sz.x, sz.y + sz.height, border1);

    DrawLine(sz.x - 1, sz.y + sz.height, sz.x + sz.width, sz.y + sz.height, border3);
    DrawLine(sz.x + sz.width, sz.y + sz.height, sz.x + sz.width, sz.y, border3);

    DrawLine(sz.x + 1, sz.y + 1, sz.x + sz.width - 2, sz.y + 1, border2);
    DrawLine(sz.x + 1, sz.y + 1, sz.x + 1, sz.y + sz.height - 1, border2);

    DrawLine(sz.x - 1 + 1, sz.y + sz.height - 1, sz.x + sz.width - 1, sz.y + sz.height - 1, border4);
    DrawLine(sz.x + sz.width - 1, sz.y + sz.height - 1, sz.x + sz.width - 1, sz.y + 1, border4);

    DrawRectangle(sz.x + 1, sz.y + 2, sz.width - 3, sz.height - 3, border1);

    DrawTextEx(ctx->fonts.tahoma8_bld.font, btn->text, (Vector2){
        text_pos.x, text_pos.y
    }, font_sz, spacing, ctx->theme.basic.button_text_color);

    return btn->activated.state;
}