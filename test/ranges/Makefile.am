## Process this file with automake to produce Makefile.in

check_PROGRAMS = richbooltest

TESTS = richbooltest

testSOURCES = all_test.cpp     is_multi_subset_of_sorted.cpp \
  all_unique_test.cpp             is_ordered_subset_of.cpp \
  compare_test.cpp                is_ordered_subset_of_sorted.cpp \
  compare_unordered_test.cpp      is_subset_of.cpp \
  container_tostring.cpp          is_subset_of_sorted.cpp \
  find_in_marked_range.cpp        sorted_test.cpp \
  find_in_multi_marked_range.cpp  sort_to_equal.cpp \
  find_in_range.cpp               stl_test.cpp \
  find_ordered_in_range.cpp       stub_container_test.cpp \
  has_test.cpp                    unique_test.cpp \
  inarray_test.cpp                is_multi_subset_of.cpp

if WXWIDGETS
#no -pedantic for wxWidgets (errors about long long and more)
#and -Wcast-qual and -Wconversion (too many warnings):
AM_CXXFLAGS = -ansi -I../common -Wshadow -Wwrite-strings
testSOURCES += wx_std_test.cpp wx_test.cpp
else
AM_CXXFLAGS = -ansi -I../common -pedantic -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
endif

frameworkSOURCES = ../common/rbtest.cpp ../common/richbooltest.cpp \
  ../common/rbtest.hpp

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
