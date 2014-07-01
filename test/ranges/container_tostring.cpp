//  Copyright (C) 2004, 2005, 2006 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (See accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/portability.hpp"
#include "richbool/richbool.hpp"


struct Streamable
{
	Streamable(): n(0) {}
	Streamable(int n_): n(n_) {}

	int n;
};

RB_CONVERSION_HEADER(Streamable)
{
	str << 's' << val.n;
	return str;
}

#ifndef RICHBOOL_USE_WX

RB_TEST(VectorIntEmpty)
{
	std::vector<int> vec;
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[]"));
}

RB_TEST(VectorIntOneElement)
{
	std::vector<int> vec;
	vec.push_back(1);
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[1]"));
}

RB_TEST(VectorIntTwoElements)
{
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[1 2]"));
}

RB_TEST(VectorStringTwoElements)
{
	std::vector<std::string> vec;
	vec.push_back("abc");
	vec.push_back("xyz");
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[abc xyz]"));
}

RB_TEST(ListIntTwoElements)
{
	std::list<int> l;
	l.push_back(1);
	l.push_back(2);
	RB_PASS(rbEQUAL(RichBool::ToString(l), "[1 2]"));
}

RB_TEST(SetIntTwoElements)
{
	std::set<int> s;
	s.insert(1);
	s.insert(2);
	RB_PASS(rbEQUAL(RichBool::ToString(s), "[1 2]"));
}

typedef std::set<int, std::greater<int> > ReverseSetInt;
RICHBOOL_CONTAINER_TO_STRING(ReverseSetInt)

RB_TEST(ReverseSetIntTwoElements)
{
	std::set<int, std::greater<int> > s;
	s.insert(1);
	s.insert(2);
	RB_PASS(rbEQUAL(RichBool::ToString(s), "[2 1]"));
}

RB_TEST(MultiSetIntTwoElements)
{
	std::multiset<int> s;
	s.insert(1);
	s.insert(2);
	RB_PASS(rbEQUAL(RichBool::ToString(s), "[1 2]"));
}

RB_TEST(DequeIntTwoElements)
{
	std::deque<int> d;
	d.push_back(1);
	d.push_back(2);
	RB_PASS(rbEQUAL(RichBool::ToString(d), "[1 2]"));
}

RICHBOOL_STD_MAP_TO_STRING(int, std::string)

RB_TEST(MapIntStringTwoElements)
{
	std::map<int, std::string> m;
	m[1] = "abc";
	m[5] = "xyz";
	RB_PASS(rbEQUAL(RichBool::ToString(m), "[(1,abc) (5,xyz)]"));
}

RICHBOOL_STD_MAP_TO_STRING_P(int, std::string, std::greater<int>)

RB_TEST(ReverseMapIntStringTwoElements)
{
	std::map<int, std::string, std::greater<int> > m;
	m[1] = "abc";
	m[5] = "xyz";
	RB_PASS(rbEQUAL(RichBool::ToString(m), "[(5,xyz) (1,abc)]"));
}


RICHBOOL_STD_MULTIMAP_TO_STRING(int, std::string)

RB_TEST(MultiMapIntStringTwoElements)
{
	std::multimap<int, std::string> m;
	m.insert(std::make_pair(1, std::string("abc")));
	m.insert(std::make_pair(5, std::string("xyz")));
	RB_PASS(rbEQUAL(RichBool::ToString(m), "[(1,abc) (5,xyz)]"));
}

typedef std::pair<int, int> PairIntInt;
RICHBOOL_PAIR_TO_STRING(int, int)
RICHBOOL_STD_MAP_TO_STRING(int, PairIntInt)

RB_TEST(MapIntPairInt_TwoElements)
{
	std::map<int, std::pair<int, int> > m;
	m[1] = std::make_pair(1,2);
	m[5] = std::make_pair(3,4);
	RB_PASS(rbEQUAL(RichBool::ToString(m), "[(1,(1,2)) (5,(3,4))]"));
}

RICHBOOL_CONTAINER_TO_STRING(std::vector<Streamable>)

RB_TEST(VectorStreamable)
{
	std::vector<Streamable> vec;
	vec.push_back(Streamable(1));
	vec.push_back(Streamable(2));
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[s1 s2]"));
}

RICHBOOL_CONTAINER_TO_STRING(std::vector< std::vector<int> >)

RB_TEST(VectorVectorIntFourElements)
{
	std::vector<int> vec1, vec2;
	vec1.push_back(1);
	vec1.push_back(2);
	vec2.push_back(3);
	vec2.push_back(4);

	std::vector<std::vector<int> > vec;
	vec.push_back(vec1);
	vec.push_back(vec2);
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[[1 2] [3 4]]"));
}

#else

#include "richbool/wx_iter.hpp"
#include <wx/arrimpl.cpp>
#include <wx/listimpl.cpp>

WX_DEFINE_ARRAY_ITERATOR(wxString, wxArrayString, wxArrayStringIterator)
RICHBOOL_XCONTAINER_TO_STRING(wxArrayString)


WX_DEFINE_ARRAY_INT(int, IntArray);
WX_DEFINE_ARRAY_ITERATOR_P(int, IntArray, IntArrayIterator)

WX_DECLARE_LIST(int, IntList); // WX_DEFINE_LIST(IntList); is in wx_test.cpp
WX_DEFINE_LIST_ITERATOR_P(int, IntList, IntListIterator)


RICHBOOL_XCONTAINER_TO_STRING(IntArray)
RICHBOOL_XCONTAINER_TO_STRING(IntList)

RB_TEST(VectorIntEmpty)
{
	IntArray vec;
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[]"));
}

RB_TEST(VectorIntOneElement)
{
	IntArray vec;
	vec.Add(1);
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[1]"));
}

RB_TEST(VectorIntTwoElements)
{
	IntArray vec;
	vec.Add(1);
	vec.Add(2);
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[1 2]"));
}

RB_TEST(VectorStringTwoElements)
{
	wxArrayString vec;
	vec.Add("abc");
	vec.Add("xyz");
	RB_PASS(rbEQUAL(RichBool::ToString(vec), "[abc xyz]"));
}

RB_TEST(ListIntTwoElements)
{
	int a=1, b=2;
	IntList l;
	l.Append(&a);
	l.Append(&b);
	RB_PASS(rbEQUAL(RichBool::ToString(l), "[1 2]"));
}

WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, Map);
RICHBOOL_WX_MAP_TO_STRING(Map)

RB_TEST(MapTwoElements)
{
	Map map;
	map[1] = "abc";
	map[2] = "xyz";

	RB_PASS(rbEQUAL(RichBool::ToString(map), "[(1,abc) (2,xyz)]"));
}

#endif
