export PROJECT := sandbox

export BASEDIR = $(shell __tmpstring=`pwd`; echo $${__tmpstring%%$(PROJECT)*}$(PROJECT))
# echo $${__tmpstring%%$(PROJECT)*}$(PROJECT))
export OUTDIR := $(BASEDIR)/_out

export DESTDIR ?= /usr/
export CFILE ?= *.C
export CFILES ?= $(wildcard *.c)
export OBJS ?= $(CFILES:.c=.o)

export GCOV_FILE ?= $(OBHS:.c=.gcno) $(CFILE:.C=.gcno)
export FLAG := -fPIC -Wall -g -fprofile-arcs -ftest-coverage -lstdc++ 
#export GCOV_PREFIX := $(OUTDIR)

export LIBS += -L$(BASEDIR)/_out/lib -L/usr/lib/
export INCLUDES += -I$(BASEDIR)/source/include -I$(BASEDIR)/tools
