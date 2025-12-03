#include "ui/draw/draw.h"
#include "keyboard_input.h"

extern void free(void *ptr);
extern int puts(const char *str);

void printl(const char *str){
    puts(str);
}

void commit_draw_ctx (draw_ctx *ctx){

}

void request_draw_ctx(draw_ctx *ctx){

}

void free_sized(void* ptr, size_t size)
{
    free(ptr);
}

void halt(int reason){

}

bool read_key(keypress *kp){
    return false;
}

uint64_t get_time(){
    return 0;
}