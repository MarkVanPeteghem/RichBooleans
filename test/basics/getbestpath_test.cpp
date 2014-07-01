//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "rbtest.hpp"
#include "richbool/richbool.hpp"
#include "richbool/finddiff.hpp"
#include <iostream>
#include <iomanip>

using namespace RichBool;
using RichBool::detail::String;

template<typename Sum>
void printGrid(detail::BestMatch<Sum> grid[][11], int n1, int n2)
{
	for (int i=0; i<n1; ++i)
	{
		for (int j=0; j<n2; ++j)
		{
			std::cout << '(' << grid[i][j].dir << ',' << std::setw(2) << grid[i][j].points << ") ";
		}
		std::cout << std::endl;
	}
	std::cout << ' ' << std::endl;
}

RB_TEST(Accumulate_Int_1And5_A)
{
	const int m = 10, l = 1;
	int matches[3][10] = {
		{ l, m, l, l },
		{ l, l, l, l },
		{ l, l, m, l },
	};

	detail::BestMatch<int> grid[4][11];
	detail::AccumulatePoints(grid, matches, 3, 4, m, m);
	//printGrid(grid, 4, 5);

	RB_PASS(rbEQUAL(grid[3][3].dir, 'M'));
	RB_PASS(rbEQUAL(grid[2][2].dir, '1'));
	RB_PASS(rbEQUAL(grid[1][2].dir, 'M'));
}

RB_TEST(Accumulate_Int_1And5_B)
{
	const int m = 10, l = 1;
	int matches[3][10] = {
		{ l, m, l },
		{ l, l, m },
		{ l, l, l },
	};

	detail::BestMatch<int> grid[4][11];
	detail::AccumulatePoints(grid, matches, 3, 3, m, m);
	//printGrid(grid, 4, 4);

	RB_PASS(rbEQUAL(grid[2][3].dir, 'M'));
	RB_PASS(rbEQUAL(grid[1][2].dir, 'M'));
	RB_PASS(rbEQUAL(grid[0][1].dir, '2'));
}

RB_TEST(BestPath_Bool_Straight)
{
	bool matches[2][10] = {
		{ true, false },
		{ false, true }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 2, 2, strDiff, pos1, pos2, true);

	RB_PASS(rbEQUAL(strDiff, "MM"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 2u));
}

RB_TEST(Accumulate_bool_A)
{
	bool matches[3][10] = {
		{ false , false, false },
		{ true , false, false },
		{ false, true , false },
	};

	detail::BestMatch<unsigned short> grid[4][11];
	detail::AccumulatePoints(grid, matches, 3, 3, true, (unsigned short)4);
	//printGrid(grid, 4, 4);

	RB_PASS(rbEQUAL(grid[3][3].dir, '2'));
	RB_PASS(rbEQUAL(grid[3][2].dir, 'M'));
	RB_PASS(rbEQUAL(grid[2][1].dir, 'M'));
	RB_PASS(rbEQUAL(grid[1][0].dir, '1'));
}

RB_TEST(Accumulate_bool_B)
{
	bool matches[3][10] = {
		{ false , true, false },
		{ false , false, true },
		{ false, false , false },
	};

	detail::BestMatch<unsigned short> grid[4][11];
	detail::AccumulatePoints(grid, matches, 3, 3, true, (unsigned short)4);
	//printGrid(grid, 4, 4);

	RB_PASS(rbEQUAL(grid[3][3].dir, '1'));
	RB_PASS(rbEQUAL(grid[2][3].dir, 'M'));
	RB_PASS(rbEQUAL(grid[1][2].dir, 'M'));
	RB_PASS(rbEQUAL(grid[0][1].dir, '2'));
}

RB_TEST(BestPath_Bool_3by3_A)
{
	bool matches[3][10] = {
		{ false, false, false },
		{ true, false, false },
		{ false, true, false }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 3, 3, strDiff, pos1, pos2, true);

	RB_PASS(rbEQUAL(strDiff, "1MM"));
	RB_PASS(rbEQUAL(pos1, 3u));
	RB_PASS(rbEQUAL(pos2, 2u));
}

RB_TEST(BestPath_Bool_3by3_B)
{
	bool matches[3][10] = {
		{ false, true, false },
		{ false, false, true },
		{ false, false, false }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 3, 3, strDiff, pos1, pos2, true);

	RB_PASS(rbEQUAL(strDiff, "2MM"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 3u));
}

RB_TEST(BestPath_Bool_2by3)
{
	bool matches[2][10] = {
		{ true, false, false },
		{ false, true, true },
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 2, 3, strDiff, pos1, pos2, true);

	RB_PASS(rbEQUAL(strDiff, "MM"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 2u));
}

RB_TEST(BestPath_Bool_5by5_A)
{
	bool matches[5][10] = {
		{ false, false, false, false, true },
		{ true, false, false, false, false },
		{ false, false, false, false, true },
		{ false, true, false, false, false },
		{ false, false, true, false, false }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 5, 5, strDiff, pos1, pos2, true);

	RB_PASS(rbEQUAL(strDiff, "1M1MM"));
	RB_PASS(rbEQUAL(pos1, 5u));
	RB_PASS(rbEQUAL(pos2, 3u));
}

RB_TEST(BestPath_Bool_5by5_B)
{
	bool matches[5][10] = {
		{ false, true, false, false, false },
		{ false, false, false, true, false },
		{ false, false, false, false, true },
		{ false, false, false, false, false },
		{ true, false, true, false, false }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 5, 5, strDiff, pos1, pos2, true);

	RB_PASS(rbEQUAL(strDiff, "2M2MM"));
	RB_PASS(rbEQUAL(pos1, 3u));
	RB_PASS(rbEQUAL(pos2, 5u));
}

RB_TEST(BestPath_Int_Straight)
{
	int matches[2][10] = {
		{ 2, 0 },
		{ 0, 2 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 2, 2, strDiff, pos1, pos2, 2);

	RB_PASS(rbEQUAL(strDiff, "MM"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 2u));
}

RB_TEST(BestPath_Int_1And2_A)
{
	int l = 2;
	int matches[4][10] = {
		{ l, l, l, l },
		{ 5, l, l, 5 },
		{ l, l, l, l },
		{ l, 5, l, l }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	size_t points = detail::GetBestPath(matches, 4, 4, strDiff, pos1, pos2, 5);
	RB_ASSERT(rbEQUAL(points, 4u));

	detail::BestMatch<int> grid[5][11];
	detail::AccumulatePoints(grid, matches, 4, 4, 5, 5);
	//printGrid(grid, 5, 5);

	RB_PASS(rbEQUAL(strDiff, "1M1M"));
	RB_PASS(rbEQUAL(pos1, 4u));
	RB_PASS(rbEQUAL(pos2, 2u));
}

RB_TEST(BestPath_Int_1And2_C)
{
	int matches[1][10] = {
		{ 0, 1, 0 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	size_t points = detail::GetBestPath(matches, 1, 3, strDiff, pos1, pos2, 2);
	RB_ASSERT(rbEQUAL(points, 2u));

	detail::BestMatch<int> grid[2][11];
	detail::AccumulatePoints(grid, matches, 1, 3, 2, 4);
	//printGrid(grid, 5, 5);

	RB_PASS(rbEQUAL(strDiff, "2X"));
	RB_PASS(rbEQUAL(pos1, 1u));
	RB_PASS(rbEQUAL(pos2, 2u));
}

RB_TEST(BestPath_Int_1And2_D)
{
	int matches[3][10] = {
		{ 0 },
		{ 1 },
		{ 0 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	size_t points = detail::GetBestPath(matches, 3, 1, strDiff, pos1, pos2, 2);
	RB_ASSERT(rbEQUAL(points, 2u));

	detail::BestMatch<int> grid[4][11];
	detail::AccumulatePoints(grid, matches, 3, 1, 4, 2);
	//printGrid(grid, 4, 2);

	RB_PASS(rbEQUAL(strDiff, "1X"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 1u));
}

RB_TEST(Accumulate_Int_1And5_2by4)
{
	int matches[2][10] = {
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 5 }
	};

	detail::BestMatch<int> grid[3][11];
	detail::AccumulatePoints(grid, matches, 2, 4, 5, 5);
	//printGrid(grid, 3, 5);
}

RB_TEST(BestPath_Int_1And2_2by4)
{
	int matches[2][10] = {
		{ 0, 2, 0, 0 },
		{ 0, 0, 0, 4 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	size_t points = detail::GetBestPath(matches, 2, 4, strDiff, pos1, pos2, 4);
	RB_ASSERT(rbEQUAL(points, 6u));

	RB_PASS(rbEQUAL(strDiff, "2X2M"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 4u));
}

RB_TEST(BestPath_Int_1And2_3by5)
{
	int l = 1;
	int matches[3][10] = {
		{ 5, l, l, l, l },
		{ l, l, 5, l, l },
		{ l, l, l, l, 5 },
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	size_t points = detail::GetBestPath(matches, 3, 5, strDiff, pos1, pos2, 5);
	RB_ASSERT(rbEQUAL(points, 4u));

	RB_PASS(rbEQUAL(strDiff, "M2M2M"));
	RB_PASS(rbEQUAL(pos1, 3u));
	RB_PASS(rbEQUAL(pos2, 5u));
}

RB_TEST(BestPath_Int_1And2_B)
{
	int l = 1;
	int matches[4][10] = {
		{ l, 5, l, l },
		{ l, l, l, 5 },
		{ l, l, l, l },
		{ l, 5, l, l }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	size_t points = detail::GetBestPath(matches, 4, 4, strDiff, pos1, pos2, 5);
	RB_ASSERT(rbEQUAL(points, 4u));

	RB_PASS(rbEQUAL(strDiff, "2M2M"));
	RB_PASS(rbEQUAL(pos1, 2u));
	RB_PASS(rbEQUAL(pos2, 4u));
}

RB_TEST(BestPath_Int_0And2)
{
	int matches[5][10] = {
		{ 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 2 },
		{ 0, 2, 0, 0, 0 },
		{ 0, 0, 2, 0, 0 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 5, 5, strDiff, pos1, pos2, 2);

	RB_PASS(rbEQUAL(strDiff, "1M1MM"));
	RB_PASS(rbEQUAL(pos1, 5u));
	RB_PASS(rbEQUAL(pos2, 3u));
}

RB_TEST(BestPath_Int_0And2_OneMatch)
{
	int matches[4][10] = {
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 2 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 4, 4, strDiff, pos1, pos2, 2);

	RB_PASS(rbEQUAL(strDiff, "XXXM"));
	RB_PASS(rbEQUAL(pos1, 4u));
	RB_PASS(rbEQUAL(pos2, 4u));

	detail::BestMatch<int> grid[5][11];
	detail::AccumulatePoints(grid, matches, 4, 4, 2, 2);
	//printGrid(grid, 5, 5);
}

RB_TEST(BestPath_Int_0And2_OneMatch_FourPartialMatches)
{
	int matches[4][10] = {
		{ 3, 3, 0, 0 },
		{ 3, 3, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 6 }
	};

	String strDiff;
	unsigned short pos1=0, pos2=0;
	detail::GetBestPath(matches, 4, 4, strDiff, pos1, pos2, 6);

	RB_PASS(rbEQUAL(strDiff, "XXXM"));
	RB_PASS(rbEQUAL(pos1, 4u));
	RB_PASS(rbEQUAL(pos2, 4u));
}

RB_TEST(LongSequence1)
{
	String str1 = "123456789001234", str2 = "23456789001234";
	String strDiff;

	RichBool::Analysis::State st =
		detail::FindDifferences<bool>::FindDifference(str1.begin(), detail::MakeEndCondition(str1.end()),
		str2.begin(), detail::MakeEndCondition(str2.end()),
		strDiff, Equal<>());

	RB_ASSERT(rbEQUAL(st, RichBool::Analysis::NotOk));
	RB_PASS(rbEQUAL(strDiff, "1MMMMMMMMMMMMMM"));
}

RB_TEST(LongSequence2)
{
	String str1 = "23456789001234", str2 = "123456789001234";
	String strDiff;

	RichBool::Analysis::State st =
		detail::FindDifferences<bool>::FindDifference(str1.begin(), detail::MakeEndCondition(str1.end()),
		str2.begin(), detail::MakeEndCondition(str2.end()),
		strDiff, Equal<>());

	RB_ASSERT(rbEQUAL(st, RichBool::Analysis::NotOk));
	RB_PASS(rbEQUAL(strDiff, "2MMMMMMMMMMMMMM"));
}

RB_TEST(LongSequence3)
{
	String str1 = "12345", str2 = "23445";
	String strDiff;

	RichBool::Analysis::State st =
		detail::FindDifferences<bool>::FindDifference(str1.begin(), detail::MakeEndCondition(str1.end()),
		str2.begin(), detail::MakeEndCondition(str2.end()),
		strDiff, Equal<>());

	RB_ASSERT(rbEQUAL(st, RichBool::Analysis::NotOk));
	RB_PASS(rbOR_BE(rbEQUAL(strDiff, "1MM2MM"), rbEQUAL(strDiff, "1MMM2M")));
}

RB_TEST(LongSequence_LittleMatch)
{
	String str1 = "12345", str2 = "66778912";
	String strDiff;

	RichBool::Analysis::State st =
		detail::FindDifferences<bool>::FindDifference(
			str1.begin(), detail::MakeEndCondition(str1.end()),
			str2.begin(), detail::MakeEndCondition(str2.end()),
			strDiff, Equal<>());

	RB_ASSERT(rbEQUAL(st, RichBool::Analysis::NotOk));
	RB_PASS(rbEQUAL(strDiff, "222222MM111"));
}
