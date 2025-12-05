#include "ui/draw/draw.h"
#include "keyboard_input.h"
#include "raylib.h"

extern void free(void *ptr);
extern int puts(const char *str);

void printl(const char *str){
    puts(str);
}

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
    SetTargetFPS(1);
    ctx->width = w;
    ctx->height = h;
    ctx->stride = 4 * w;
}

void free_sized(void* ptr, size_t size)
{
    free(ptr);
}

void halt(int reason){
    // exit(reason);
}

bool read_key(keypress *kp){
    return false;
}

uint64_t get_time(){
    return 0;
}
