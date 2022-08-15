TYPE := app
TARGET_DIR = $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

TARGET = Sandbox.$(TYPE)

FLAGS += -g
LIBS += -lpthread

include ../../tools/makefiles/$(TYPE).mk
