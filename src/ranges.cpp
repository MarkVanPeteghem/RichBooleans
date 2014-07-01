//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "richbool/ranges.hpp"

namespace RichBool
{
	namespace detail
	{
		const char * const AllMessages::s_msg="predicate applies to all elements in range ";

		const char * const HasMessages::s_msg="predicate applies to at least one element in range ";

		const char * const UniqueMessages::s_msg="predicate applies to exactly one element in range ";

		const char *AdjacentMessages::s_msg=
				"predicate applies to adjacent elements in range ";

		const char *AllPairsMessages::s_msg = "predicate applies to all pairs in ";

		const char * const CompareMessages::s_msg="predicate applies to ranges ";

		const char *CompareUnorderedMessages::s_msg="predicate applies to unordered ranges ";

		const char *MatchesSubsetOfMessages::s_msg = " matches with subset of ";
	}
}
