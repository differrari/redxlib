#include "ui/draw/draw.h"
#include "keyboard_input.h"
#include "mouse_input.h"
#include "raylib.h"
#include "math/math.h"
#include "syscalls/syscalls.h"

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

bool read_event(kbd_event *event){
    return false;
}

void get_mouse_status(mouse_input *in){

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

