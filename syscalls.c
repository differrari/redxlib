#include "ui/draw/draw.h"
#include "keyboard_input.h"
#include "mouse_input.h"
#include "raylib.h"
#include "math/math.h"
#include "syscalls/syscalls.h"
#include "keycode_convert.h"

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

bool keypresses[512];

bool read_event(kbd_event *event){
    //TODO: modifiers
    int key;
    // do {
        key = GetKeyPressed();
        if (key){
            event->type = KEY_PRESS;
            event->key = raylib_to_redacted[key];
            keypresses[key] = true;
            return true;
        }
    // } while (key);
    for (int i = 0; i < 512; i++)
        if (keypresses[i] && IsKeyUp(i)){
            printf("Key released %i",i);
            event->type = KEY_RELEASE;
            event->key = raylib_to_redacted[i];
            keypresses[i] = false;
            return true;
        }
    return false;
}

void get_mouse_status(mouse_input *in){
    in->x = GetMouseX();
    in->y = GetMouseY();
    in->scroll = ((int)GetMouseWheelMove() & 0xFF);
    in->buttons = 0;
    for (int i = 0; i < 3; i++)
        in->buttons |= (IsMouseButtonPressed(i) & 1) << i;
}

FS_RESULT openf(const char* path, file* descriptor){
    printf("Opening file %s",path);
    return FS_RESULT_DRIVER_ERROR;
}

size_t readf(file *descriptor, char* buf, size_t size){
    return 0;
}

size_t writef(file *descriptor, const char* buf, size_t size){
    return 0;
}

void closef(file *descriptor){

}

