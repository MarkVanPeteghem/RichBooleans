//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/containers.hpp"

RB_TEST(OneValue)
{
	int arr[] = { 2 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2), arr, RichBool::AllEqual<>()));
}

RB_TEST(TwoValues)
{
	int arr[] = { 2, 4 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4), arr, RichBool::AllEqual<>()));
}

RB_TEST(ThreeValues)
{
	int arr[] = { 2, 4, 5 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5), arr, RichBool::AllEqual<>()));
}

RB_TEST(FourValues)
{
	int arr[] = { 2, 4, 5, 7 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7), arr, RichBool::AllEqual<>()));
}

RB_TEST(FiveValues)
{
	int arr[] = { 2, 4, 5, 7, 11 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7, 11), arr, RichBool::AllEqual<>()));
}

RB_TEST(SixValues)
{
	int arr[] = { 2, 4, 5, 7, 11, 12 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7, 11, 12), arr, RichBool::AllEqual<>()));
}

RB_TEST(SevenValues)
{
	int arr[] = { 2, 4, 5, 7, 11, 12, 15 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7, 11, 12, 15), arr, RichBool::AllEqual<>()));
}

RB_TEST(EightValues)
{
	int arr[] = { 2, 4, 5, 7, 11, 12, 15, 16 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7, 11, 12, 15, 16), arr, RichBool::AllEqual<>()));
}

RB_TEST(NineValues)
{
	int arr[] = { 2, 4, 5, 7, 11, 12, 15, 16, 20 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7, 11, 12, 15, 16, 20), arr, RichBool::AllEqual<>()));
}

RB_TEST(TenValues)
{
	int arr[] = { 2, 4, 5, 7, 11, 12, 15, 16, 20, 22 };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(2, 4, 5, 7, 11, 12, 15, 16, 20, 22), arr, RichBool::AllEqual<>()));
}


#define STRING_ARRAY_COMPARE RichBool::Compare<>().That(RichBool::StringsEqualCS())
#define WSTRING_ARRAY_COMPARE RichBool::Compare<>().That(RichBool::WStringsEqualCS())

RB_TEST(OneStringValue)
{
	std::string arr[] = { "a" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(TwoStringValues)
{
	std::string arr[] = { "a", "ab" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(ThreeStringValues)
{
	std::string arr[] = { "a", "ab", "abc" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(FourStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(FiveStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7", "11" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7", "11"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(SixStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7", "11", "12" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7", "11", "12"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(SevenStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7", "11", "12", "15" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7", "11", "12", "15"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(EightStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7", "11", "12", "15", "16" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7", "11", "12", "15", "16"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(NineStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7", "11", "12", "15", "16", "20" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7", "11", "12", "15", "16", "20"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(TenStringValues)
{
	std::string arr[] = { "a", "ab", "abc", "7", "11", "12", "15", "16", "20", "22" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values("a", "ab", "abc", "7", "11", "12", "15", "16", "20", "22"), arr, STRING_ARRAY_COMPARE));
}

RB_TEST(OneWStringValue)
{
	std::wstring arr[] = { L"a" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(TwoWStringValues)
{
	std::wstring arr[] = { L"a", L"ab" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(ThreeWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(FourWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(FiveWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7", L"11" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7", L"11"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(SixWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7", L"11", L"12" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7", L"11", L"12"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(SevenWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7", L"11", L"12", L"15" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7", L"11", L"12", L"15"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(EightWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7", L"11", L"12", L"15", L"16" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7", L"11", L"12", L"15", L"16"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(NineWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7", L"11", L"12", L"15", L"16", L"20" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7", L"11", L"12", L"15", L"16", L"20"), arr, WSTRING_ARRAY_COMPARE));
}

RB_TEST(TenWStringValues)
{
	std::wstring arr[] = { L"a", L"ab", L"abc", L"7", L"11", L"12", L"15", L"16", L"20", L"22" };
	RB_ASSERT(rbIN_CONTAINER_ARRAY(RichBool::Values(L"a", L"ab", L"abc", L"7", L"11", L"12", L"15", L"16", L"20", L"22"), arr, WSTRING_ARRAY_COMPARE));
}
