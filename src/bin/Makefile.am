# this is example-file: src/bin/Makefile.am

# additional include pathes necessary to compile the C++ programs
#AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@

###############################################################################
# THE PROGRAMS TO BUILD
###############################################################################

# the program to build (the names of the final binaries)
bin_PROGRAMS = spp

# list of sources for the 'helloWorld' binary
spp_SOURCES =	\
						main.c \
						ui_text.h \
						ui_text.c \
						parser.c \
						parser.h \
                        man_tester.xxd

# the additional libraries needed to link helloWorld
spp_LDADD = 	$(top_builddir)/src/lib/libspp.a $(AM_LDFLAGS)

###############################################################################
