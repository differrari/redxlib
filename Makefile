CC         := gcc
CXX        := g++
LD         := ld
AR         := ar
DUMP 	   := objdump

OS_PATH ?= ../os

EXEC_NAME ?= redxlib.a

STDINC ?= $(OS_PATH)/shared/
CFLAGS ?= -std=c99 -I$(STDINC) -I. -O0
C_SOURCE ?= $(shell find . -name '*.c')
OBJ ?= $(C_SOURCE:%.c=%.o)

.PHONY: dump

%.o : %.c
	$(CC) $(CFLAGS) -c -c $< -o $@ -I=$(STDINC)

$(EXEC_NAME): $(OBJ)
	$(AR) rcs $@ $(OBJ)

all: $(EXEC_NAME)

clean: 	
	rm $(OBJ)
	rm $(EXEC_NAME)

dump: all
	$(DUMP) -S $(EXEC_NAME) > dump
