#
# Created by gmakemake (Ubuntu Jun 18 2022) on Mon Aug 12 13:01:56 2024
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags


CPP_FILES =	
C_FILES =	core.c image-manager.c input-buffering.c instruction-index.c main.c util.c
PS_FILES =	
S_FILES =	
H_FILES =	core.h image-manager.h input-buffering.h instruction-index.h util.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	core.o image-manager.o input-buffering.o instruction-index.o util.o 

#
# Main targets
#

all:	main 

main:	main.o $(OBJFILES)
	$(CC) $(CFLAGS) -o main main.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

core.o:	
image-manager.o:	core.h image-manager.h
input-buffering.o:	input-buffering.h
instruction-index.o:	core.h instruction-index.h util.h
main.o:	core.h input-buffering.h instruction-index.h util.h
util.o:	core.h util.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) main.o core

realclean:        clean
	-/bin/rm -f main 
