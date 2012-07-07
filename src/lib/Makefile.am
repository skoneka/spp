# this is example-file: src/mylib/Makefile.am

# additional include pathes necessary to compile the C++ library
#AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@

###############################################################################
# THE LIBRARIES TO BUILD
###############################################################################

# the library names to build (note we are building static libs only)
lib_LIBRARIES = libspp.a

# where to install the headers on the system
libspp_adir = $(includedir)/spp

# the list of header files that belong to the library (to be installed later)
libspp_a_HEADERS =	\
						db_io.h \
						db_types.h \
						define.h \
						spp.h \
						util.h

# the sources to add to the library and to add to the source distribution
libspp_a_SOURCES =	\
						$(spp_a_HEADERS) \
						db_io.c \
						spp.c \
						util.c
						
###############################################################################
