#include "ui/draw/draw.h"
#include "keyboard_input.h"
#include "raylib.h"
#include "math/math.h"

extern void free(void *ptr);
extern int puts(const char *str);
extern void exit(int status);

void printl(const char *str){
    puts(str);
}

void free_sized(void* ptr, size_t size)
{
    free(ptr);
}

void halt(int reason){
    exit(reason);
}

bool read_key(keypress *kp){
    return false;
}

uint64_t get_time(){
    return floor(GetTime() * 1000);
}
