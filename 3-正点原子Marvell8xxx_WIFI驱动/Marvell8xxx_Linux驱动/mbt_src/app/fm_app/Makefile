#
# File : fm_app/Makefile
#
# Copyright (C) 2014-2018, Marvell International Ltd. All Rights Reserved

# Override CFLAGS for application sources, remove __ kernel namespace defines
CFLAGS := $(filter-out -D__%, $(EXTRA_CFLAGS))

#
# List of application executables to create
#
libobjs:= fm_main.o
exectarget=fmapp
TARGETS := $(exectarget)

#
# Make target rules
#

# All rule compiles list of TARGETS using builtin program target from src rule
all :
$(exectarget): $(libobjs)
	$(CC) $(CFLAGS) $(libobjs) -o $(exectarget)

# Update any needed TARGETS and then copy to the install path
build all: $(TARGETS)

clean:
	@rm -f $(exectarget)
	@rm -f *.o

distclean: clean
	@rm -f *~ core
	@rm -f tags
