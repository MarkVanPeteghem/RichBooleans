## Process this file with automake to produce Makefile.in

SOURCES = src/analysis.cpp src/functors.cpp src/ranges.cpp src/string.cpp src/badblock.cpp src/tmpbool.cpp src/bool.cpp src/der_analysis.cpp src/expression.cpp src/portability.cpp src/bit_iterator.cpp src/values.cpp src/fileutils.cpp

# suppose the header files are not yet installed, so add the include directory:
AM_CPPFLAGS = -I./include


if WXWIDGETS

# don't use -pedantic flag with wxWidgets builds (problems with long long and more):
AM_CXXFLAGS = -O2 -ansi -Wall -Wshadow -Wwrite-strings
lib_LIBRARIES = librichbool-wx.a
librichbool_wx_a_SOURCES = $(SOURCES)
librichbool_wx_a_CPPFLAGS = -DRICHBOOL_USE_WX -I./include `wx-config --cxxflags`

else

AM_CXXFLAGS = -O2 -ansi -pedantic -Wall -Wextra -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
lib_LIBRARIES = librichbool.a
librichbool_a_SOURCES = $(SOURCES)

endif

SUBDIRS = . test/basics test/macros test/ranges include
