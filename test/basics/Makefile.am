## Process this file with automake to produce Makefile.in

check_PROGRAMS = richbooltest

TESTS = richbooltest

testSOURCES = analysis_equal.cpp \
  bit_iterator.cpp \
  bitsare_match_test.cpp \
  bool_test.cpp \
  end_condition_test.cpp \
  expression_test.cpp \
  getarg_test.cpp \
  getbestpath_test.cpp \
  logic_test.cpp \
  relation_test.cpp \
  safecheck.cpp \
  shared_memory_test.cpp \
  streamtest.cpp \
  swap_test.cpp \
  tmpbool_test.cpp \
  values_test.cpp \
  version_test.cpp \
  wrappertest.cpp

# no -W and -Wall, because these give many warnings about comma operator
if WXWIDGETS
#also no -pedantic for wxWidgets (errors about long long and more)
#and no -Wcast-qual and -Wconversion (too many warnings):
AM_CXXFLAGS = -ansi -I../common -Wshadow -Wwrite-strings
else
AM_CXXFLAGS = -ansi -I../common -pedantic -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
endif

frameworkSOURCES = ../common/rbtest.cpp ../common/richbooltest.cpp ../common/rbtest.hpp

helperSOURCES = ../common/other_string.hpp ../common/predicates.hpp \
  ../common/stub_container.hpp ../common/testable_analysis_for_ranges.hpp \
  ../common/testable_analysis_with_strings.hpp

# we suppose the header files are installed now, so we actually also
# check whether the installation of the header files was ok
# so we don't specify an include path, and suppose that
# CPLUS_INCLUDE_PATH is set correctly (to contain e.g. /usr/local/)

richbooltest_SOURCES = $(testSOURCES) $(frameworkSOURCES) $(helperSOURCES) 

# link with the richbooleans library (presume it is not yet installed)
if WXWIDGETS
richbooltest_LDADD = -lrichbool-wx
AM_CPPFLAGS = -DRICHBOOL_USE_WX `wx-config --cxxflags`
AM_LDFLAGS = `wx-config --libs`
else
richbooltest_LDADD = -lrichbool
endif
