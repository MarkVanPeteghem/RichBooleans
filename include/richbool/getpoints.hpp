//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef GET_POINTS_H__QM
#define GET_POINTS_H__QM

namespace RichBool
{
	namespace detail
	{
		template <typename Points>
		struct ToNumPoints
		{
			typedef Points Type;
			static Points Convert(Points p)
			{
				return p;
			}
		};

		template <>
		struct ToNumPoints<bool>
		{
			typedef unsigned short Type;
			static Type Convert(bool p)
			{
				return p ? (unsigned short)2u : (unsigned short)0u;
			}
		};

		template <typename Points>
		struct GetPoints
		{
			typedef typename ToNumPoints<Points>::Type NumPoints;

			template <class RB>
			static Points GetGood(RB rb)
			{
				return rb.GetGood();
			}

			template <class RB, typename T1, typename T2>
			static Points Get(RB rb, const T1 &t1, const T2 &t2)
			{
				return static_cast<Points>(
                    (rb.IsValid1(t1) && rb.IsValid2(t2)) ? rb.GetPoints(t1, t2) : 0
                );
			}

			static Points ToPoints(Points p)
			{
				return p;
			}
		};

		template <>
		struct GetPoints<bool>
		{
			typedef ToNumPoints<bool>::Type NumPoints;

			template <class RB>
			static bool GetGood(RB)
			{
				return true;
			}

			template <class RB, typename T1, typename T2>
			static bool Get(RB rb, const T1 &t1, const T2 &t2)
			{
				return rb.IsValid1(t1) && rb.IsValid2(t2) && rb(t1, t2);
			}

			static bool ToPoints(NumPoints p)
			{
				return p!=0;
			}
		};

		template <typename Points>
		struct GetNumPoints
		{
			typedef typename ToNumPoints<Points>::Type NumPoints;

			template <class RB>
			static NumPoints GetGood(RB rb)
			{
				return rb.GetGood();
			}

			template <class RB, typename T1, typename T2>
			static NumPoints Get(RB rb, const T1 &t1, const T2 &t2)
			{
				return rb.GetPoints(t1, t2);
			}

			template <class RB, typename T1, typename T2, typename T3, typename T4>
			static NumPoints Get(RB rb, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
			{
				return rb.GetPoints(t1, t2, t3, t4);
			}
		};

		template <>
		struct GetNumPoints<bool>
		{
			typedef ToNumPoints<bool>::Type NumPoints;

			template <class RB>
			static NumPoints GetGood(RB )
			{
				return 2;
			}

			template <class RB, typename T1, typename T2>
			static NumPoints Get(RB rb, const T1 &t1, const T2 &t2)
			{
				return rb(t1, t2) ? 2 : 0;
			}
			template <class RB, typename T1, typename T2, typename T3, typename T4>
			static NumPoints Get(RB rb, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
			{
				return rb(t1, t2, t3, t4) ? 2 : 0;
			}
		};
	}
}

#endif // #ifndef GET_POINTS_H__QM
