//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_FINDDIFF_H__QM
#define RICH_BOOL_FINDDIFF_H__QM

#include <stdexcept>

#include "richbool/portability.hpp"
#include "richbool/getpoints.hpp"

namespace RichBool
{
	namespace detail
	{
		// template class to specify the end of a range
		// with either an end iterator or the length of the range
		template <typename It>
		class EndCondition
		{
			It end;
		public:
			typedef size_t IndexType;
			EndCondition(It end_): end(end_) {}
			template <typename It2>
			bool operator()(It2 it, size_t ) const
			{
				return it!=end;
			}
			template <typename It2>
			size_t length(It2 begin) const
			{
				size_t l = 0;
				for ( ; begin!=end; ++begin) ++l;
				return l;
			}
			template <typename It2>
			size_t ra_length(It2 begin) const
			{
				return end-begin;
			}
			template <typename It2>
			It ra_end(It2 ) const
			{
				return end;
			}
		};

#ifndef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
		template <typename T>
		class EndCondition<T*>
		{
			T* end;
		public:
			typedef size_t IndexType;
			EndCondition(T* end_): end(end_) {}
			template <typename It2>
			bool operator()(It2 it, size_t ) const
			{
				return it!=end;
			}
			template <typename It2>
			size_t length(It2 begin) const
			{
				return end-begin;
			}
			template <typename It2>
			size_t ra_length(It2 begin) const
			{
				return end-begin;
			}
			template <typename It2>
			T* ra_end(It2 ) const
			{
				return end;
			}
		};
#endif

		#define RICHBOOL_END_CONDITION(TYPE) template<> class EndCondition<TYPE> { \
			TYPE n; \
		public: \
			typedef TYPE IndexType;\
			EndCondition(TYPE n_): n(n_) {} \
			template <typename It> \
			bool operator()(It, TYPE i) const \
			{ return n!=i; } \
			template <typename It> \
			TYPE length(It ) const { return n; } \
			template <typename It> \
			TYPE ra_length(It ) const { return n; } \
			template <typename It> \
			It ra_end(It begin) const { return begin+n; } \
		}

		RICHBOOL_END_CONDITION(short);
		RICHBOOL_END_CONDITION(int);
		RICHBOOL_END_CONDITION(long);
		RICHBOOL_END_CONDITION(unsigned short);
		RICHBOOL_END_CONDITION(unsigned int);
		RICHBOOL_END_CONDITION(unsigned long);

		#undef RICHBOOL_END_CONDITION

		template <typename It>
		EndCondition<It> MakeEndCondition(It it) { return EndCondition<It>(it); }


		const unsigned int maxNrMatches = 10;

		template<typename Sum>
		struct BestMatch
		{
			char dir;
			Sum points;
		};

        template <typename T>
        struct MaxValue
        {};
        template <>
        struct MaxValue<unsigned int>
        {
            enum { Value = 0xffffffff };
        };
        template <>
        struct MaxValue<int>
        {
            enum { Value = 0x7fffffff };
        };
        template <>
        struct MaxValue<unsigned short>
        {
            enum { Value = 0xffff };
        };

		template<typename Points, typename Sum>
		void AccumulatePoints(
				BestMatch<Sum> grid[maxNrMatches+1][maxNrMatches+1],
				const Points matches[maxNrMatches][maxNrMatches],
				unsigned int n1, unsigned int n2,
				Points good,
				Sum maximum)
		{
		    if (maxNrMatches*maximum > MaxValue<Sum>::Value)
		    {
		        throw std::range_error("calculation of best path may overflow");
		    }

			// fill grid
			grid[0][0].dir = 'M';
			grid[0][0].points = 0;

			const Sum gapCost = static_cast<Sum>((maximum>2) ? maximum/2 : 1);

			unsigned int i1=0, i2=0;
			for ( ; i1<n1; ++i1)
			{
				grid[i1+1][0].dir = '1';
				grid[i1+1][0].points = static_cast<Sum>(grid[i1][0].points + gapCost);
			}
			for (i2=0; i2<n2; ++i2)
			{
				grid[0][i2+1].dir = '2';
				grid[0][i2+1].points = static_cast<Sum>(grid[0][i2].points + gapCost);
			}

			for (i1=0; i1<n1; ++i1)
				for (i2=0; i2<n2; ++i2)
				{
					Sum pm = static_cast<Sum>(grid[i1][i2].points + maximum-
						ToNumPoints<Points>::Convert(matches[i1][i2]));
					Sum p1 = static_cast<Sum>(grid[i1][i2+1].points+gapCost);
					Sum p2 = static_cast<Sum>(grid[i1+1][i2].points+gapCost);
					const bool goodMatch = matches[i1][i2]==good;
					bool pm1 = pm<p1;
					if (pm==p1)
					{
						if ( (grid[i1][i2].dir=='M') || (grid[i1][i2].dir=='X') )
							pm1 = true;
					}
					bool pm2 = pm<p2;
					if (pm==p2)
					{
						if ( (grid[i1][i2].dir=='M') || (grid[i1][i2].dir=='X') )
							pm2 = true;
					}
					if (pm1)
					{
						if (pm2)
						{
							grid[i1+1][i2+1].points = pm;
							grid[i1+1][i2+1].dir = goodMatch ? 'M' : 'X';
						}
						else
						{
							grid[i1+1][i2+1].points = p2;
							grid[i1+1][i2+1].dir = '2';
						}
					}
					else
					{
						if (p1<p2)
						{
							grid[i1+1][i2+1].points = p1;
							grid[i1+1][i2+1].dir = '1';
						}
						else
						{
							grid[i1+1][i2+1].points = p2;
							grid[i1+1][i2+1].dir = '2';
						}
					}
				}
		}

		template<typename Sum>
		size_t GetBestPathFromGrid(BestMatch<Sum> grid[maxNrMatches+1][maxNrMatches+1],
						unsigned int n1, unsigned int n2,
						String &strDiff,
						unsigned short &pos1, unsigned short &pos2)
		{
			unsigned int i1=n1, i2=n2;
			const size_t startDiff = detail::str_size(strDiff);

			const char startDir = grid[i1][i2].dir;
			if (startDir=='1')
				do {
					--i1;
				} while ( (i1>0) && (grid[i1][i2].dir=='1') );
			else if (startDir=='2')
				do {
					--i2;
				} while ( (i2>0) && (grid[i1][i2].dir=='2') );

			size_t points = grid[i1][i2].points;

			while ( (i1!=0) || (i2!=0) )
			{
				const char dir = grid[i1][i2].dir;
				switch (dir)
				{
				case 'M':
				case 'X':
					--i1;
					--i2;
					++pos1;
					++pos2;
					break;
				case '1':
					--i1;
					++pos1;
					break;
				case '2':
					--i2;
					++pos2;
					break;
				default:
					i1 = i2 = 0;
					break;
				}
				strDiff += dir;
			}

			// reverse the part that we now add to string strDiff
			const size_t len = detail::str_size(strDiff)-startDiff;
			for (unsigned int i=0; i<len/2; ++i)
			{
				char ch = strDiff[startDiff+i];
				strDiff[startDiff+i] = strDiff[startDiff+len-1-i];
				strDiff[startDiff+len-1-i] = ch;
			}

			return points;
		}

		template<typename Points>
		size_t GetBestPath(Points matches[maxNrMatches][maxNrMatches],
						unsigned int n1, unsigned int n2,
						String &strDiff,
						unsigned short &pos1, unsigned short &pos2,
						Points good)
		{
			typedef typename ToNumPoints<Points>::Type Sum;
			BestMatch<Sum> grid[maxNrMatches+1][maxNrMatches+1];

			const Sum maximum = ToNumPoints<Points>::Convert(good);

			AccumulatePoints(grid, matches, n1, n2, good, maximum);

			return GetBestPathFromGrid(grid, n1, n2, strDiff, pos1, pos2);
		}

		template<typename Points>
		struct FindDifferences
		{
			template<typename It1, class EC1,
				typename It2, class EC2,
				typename RB>
			static Analysis::State FindDifference(It1 begin1, EC1 ec1,
									   It2 begin2, EC2 ec2,
									   String &strDiff,
									   const RB &rb)
			{
				bool same = true, bv=false;
				typename EC1::IndexType idx1=0;
				typename EC2::IndexType idx2=0;
				while ( ec1(begin1, idx1) && ec2(begin2, idx2) )
				{
					Analysis::State st=rb.SafeCheck(*begin1, *begin2);
					if (st==Analysis::Ok)
					{
						strDiff += 'M';
						++begin1; ++idx1;
						++begin2; ++idx2;
					}
					else
					{
						same = false;
						if (st==Analysis::BadValue)
							bv=true;
						Points matches[maxNrMatches][maxNrMatches];
						unsigned int i1=0, i2=0;
						for (It1 it1 = begin1; (i1<maxNrMatches) && ec1(it1, idx1+i1); ++i1, ++it1)
						{
							i2=0;
							for (It2 it2 = begin2; (i2<maxNrMatches) && ec2(it2, idx2+i2); ++i2, ++it2)
								matches[i1][i2] = GetPoints<Points>::Get(rb, *it1, *it2);
						}
						unsigned short pos1=0, pos2=0;
						GetBestPath(matches, i1, i2, strDiff, pos1, pos2,
							GetPoints<Points>::GetGood(rb));
						for (i1=0; i1<pos1; ++i1) ++begin1;
						idx1 += pos1;
						for (i2=0; i2<pos2; ++i2) ++begin2;
						idx2 += pos2;
					}
				}
				while (ec1(begin1, idx1))
				{
					strDiff += '1';
					++begin1; ++idx1;
					same = false;
				}
				while (ec2(begin2, idx2))
				{
					strDiff += '2';
					++begin2; ++idx2;
					same = false;
				}
				return same ? Analysis::Ok : (bv ? Analysis::BadValue : Analysis::NotOk);
			}
		};

		inline size_t GetPointsFromDiff(const detail::String &strDiff, size_t maximum)
		{
			size_t count=0, good=0;
			for (size_t i=0; i<detail::str_size(strDiff); ++i)
			{
				switch (strDiff[i])
				{
				case 'M':
					good += 2;
					count += 2;
					break;
				case 'X':
					count += 2;
					break;
				case '1':
				case '2':
					++count;
					break;
				}
			}
			return count ? (maximum*good)/count : maximum;
		}
	}
}

#endif // #ifndef RICH_BOOL_FINDDIFF_H__QM
