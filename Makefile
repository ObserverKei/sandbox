TYPE = dir

BASEDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

ifeq ($(BASEDIR), $(shell pwd))
SUBDIRS = source tools
endif##($(BASEDIR), $(shell pwd))

all: $(OUTDIR) $(SUBDIRS)

$(OUTDIR): 
	if [ ! -d ${OUTDIR} ]; then install -d ${OUTDIR}; fi

.PHONY: all 

#ifneq ($(MAKECMDGOALS),runenv)
include $(BASEDIR)/tools/makefiles/$(TYPE).mk
#endif
