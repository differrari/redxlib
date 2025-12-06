#include "ui/draw/draw.h"
#include "raylib.h"
#include "syscalls/syscalls.h"

#define CONVERT_COLOR(color) GetColor(((color & 0xFFFFFF) << 8) | ((color >> 24) & 0xFF))

void begin_drawing(draw_ctx *ctx){
    BeginDrawing();
}

void destroy_draw_ctx(draw_ctx *ctx){
    CloseWindow();
}

void commit_draw_ctx (draw_ctx *ctx){
    EndDrawing();
}

void request_draw_ctx(draw_ctx *ctx){
    uint32_t w = ctx->width ? ctx->width : 600;
    uint32_t h = ctx->height ? ctx->height : 300;
    InitWindow(w, h, "raylib [core] example - basic window");
    SetTargetFPS(10);
    ctx->width = w;
    ctx->height = h;
    ctx->stride = 4 * w;
}

bool should_close_ctx(){
    return WindowShouldClose();
}

void fb_clear(draw_ctx *ctx, uint32_t color) {
    ClearBackground(CONVERT_COLOR(color));
    ctx->full_redraw = 1;
}

void fb_draw_raw_pixel(draw_ctx *ctx, uint32_t x, uint32_t y, color color){

}

void fb_draw_pixel(draw_ctx *ctx, uint32_t x, uint32_t y, color color){

    mark_dirty(ctx, x,y,1,1);
}

void fb_fill_rect(draw_ctx *ctx, int32_t x, int32_t y, uint32_t width, uint32_t height, color color){
    DrawRectangle(x, y, width, height, CONVERT_COLOR(color));
    mark_dirty(ctx, x,y,width,height);
}

void fb_draw_img(draw_ctx *ctx, uint32_t x, uint32_t y, uint32_t *img, uint32_t img_width, uint32_t img_height){
    fb_draw_partial_img(ctx, img, x, y, img_width, img_height, (image_transform){});
}

void fb_draw_partial_img(draw_ctx *ctx, uint32_t *img, uint32_t x, uint32_t y, uint32_t full_width, uint32_t full_height, image_transform transform){


    mark_dirty(ctx, x,y, full_width, full_height);
}

gpu_rect fb_draw_line(draw_ctx *ctx, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, color color){
    const uint32_t ox0 = x0, oy0 = y0, ox1 = x1, oy1 = y1;

    int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = (y1 > y0) ? (y0 - y1) : (y1 - y0);
    dy = dy < 0 ? -dy : dy;
    int sy = (y0 < y1) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;) {

        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }

    uint32_t min_x = (ox0 < ox1) ? ox0 : ox1;
    uint32_t min_y = (oy0 < oy1) ? oy0 : oy1;
    uint32_t max_x = (ox0 > ox1) ? ox0 : ox1;
    uint32_t max_y = (oy0 > oy1) ? oy0 : oy1;

    if (max_x >= ctx->width) max_x = ctx->width - 1;
    if (max_y >= ctx->height) max_y = ctx->height - 1;

    const uint32_t bw = (max_x >= min_x) ? (max_x - min_x + 1) : 0;
    const uint32_t bh = (max_y >= min_y) ? (max_y - min_y + 1) : 0;

    if (bw && bh) mark_dirty(ctx, min_x, min_y, bw, bh);

    return (gpu_rect) { {min_x, min_y}, {bw, bh} };
}

void fb_draw_raw_char(draw_ctx *ctx, uint32_t x, uint32_t y, char c, uint32_t scale, uint32_t color){

}

void fb_draw_char(draw_ctx *ctx, uint32_t x, uint32_t y, char c, uint32_t scale, uint32_t color){
    fb_draw_raw_char(ctx, x, y, c, scale, color);
    mark_dirty(ctx, x,y,CHAR_SIZE*scale,CHAR_SIZE*scale);
}

gpu_size fb_draw_string(draw_ctx *ctx, const char* s, uint32_t x0, uint32_t y0, uint32_t scale, uint32_t color){
    DrawText(s, x0, y0, 24 * scale, CONVERT_COLOR(color));
}

uint32_t fb_get_char_size(uint32_t scale){
    return CHAR_SIZE * scale;
}
