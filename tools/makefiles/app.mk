MYDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
include $(MYDIR)/env.mk

SUBDIRS ?= 
C_SOURCES = $(wildcard *.c)
CPP_SOURCES = $(wildcard *.cpp)

OBJS = $(wildcard *.cpp *.c)
#$(patsubst %.c,%.cpp,$(SOURCES)) 

ifeq ($(findstring .so, $(TARGET)),.so)

    TYPE ?= so
    INSTALL_DIR ?= $(LIBDIR)

else

    TYPE ?= app
    INSTALL_DIR ?= bin

endif##($(findstring .so, $(TARGET)),)

ifeq ($(TYPE),so)

    OUTDIR := $(BASEDIR)/_out/lib
    DESTDIR := /usr/lib

else ifeq ($(TYPE),app)

    OUTDIR := $(BASEDIR)/_out/bin
    DESTDIR := /usr/bin

endif##($(TYPE),so)

ifeq ($(findstring .cpp, $(OBJS)),.cpp)

    CC = g++

else##($(findstring .c, $(OBJS)),)

    CC = gcc

endif##($(findstring .c, $(OBJS)),)


%.o:%.c
	$(CC) -c -o $@ $^ $(FLAGS) $(INCLUDES)

%.o:%.cpp
	$(CC) -c -o $@ $^ $(FLAGS) $(INCLUDES)
	
$(TARGET): $(C_SOURCES:.c=.o) $(CPP_SOURCES:.cpp=.o) 
	$(CC) -o $@ $^ $(FLAGS) $(LIBS)
	if [ ! -d $(OUTDIR) ]; then install -d $(OUTDIR); fi
	cp $@ $(OUTDIR)/

all: $(TARGET)

clean:
	rm -r $(TARGET) $(OUTDIR) *.o 

#ifneq ($(MAKECMDGOALS),runenv)
#include $(BASEDIR)/Makefile
#endif##($(MAKECMDGOALS),runenv)
