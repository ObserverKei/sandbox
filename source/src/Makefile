TYPE := app
TARGET_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

TARGET = Sandbox.$(TYPE)

FLAGS += -g
LIBS += -lpthread 
ASAN=-lasan -fsanitize=address -fsanitize-recover=address -fno-stack-protector -fno-omit-frame-pointer


include ../../tools/makefiles/$(TYPE).mk
