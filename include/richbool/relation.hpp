//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_RELATION_H__QM
#define RICH_BOOL_RELATION_H__QM

namespace RichBool
{
	namespace detail
	{
		template<typename T>
		T max_(T t1, T t2)
		{
			return t1>t2 ? t1 : t2;
		}

	}

	///////////////////////////////////////////////////////////
	// Rich Boolean functors for comparisons without roundoff

	struct EqualRelation
	{
		enum { equality=true };
		bool operator()(int result) const
		{
			return result==0;
		}
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return t1==t2;
		}
		static const char* name()
		{
			return " == ";
		}
	};

	struct LessRelation
	{
		enum { equality=false };
		bool operator()(int result) const
		{
			return result<0;
		}
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return t1<t2;
		}
		static const char* name()
		{
			return " < ";
		}
	};

	struct LessOrEqualRelation
	{
		enum { equality=false };
		bool operator()(int result) const
		{
			return result<=0;
		}
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return t1<=t2;
		}
		static const char* name()
		{
			return " <= ";
		}
	};

	struct MoreRelation
	{
		enum { equality=false };
		bool operator()(int result) const
		{
			return result>0;
		}
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return t1>t2;
		}
		static const char* name()
		{
			return " > ";
		}
	};

	struct MoreOrEqualRelation
	{
		enum { equality=false };
		bool operator()(int result) const
		{
			return result>=0;
		}
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return t1>=t2;
		}
		static const char* name()
		{
			return " >= ";
		}
	};

	struct DifferentRelation
	{
		enum { equality=false };
		bool operator()(int result) const
		{
			return result!=0;
		}
		template <typename T1, typename T2>
		bool operator()(const T1 &t1, const T2 &t2) const
		{
			return t1!=t2;
		}
		static const char* name()
		{
			return " != ";
		}
	};

	///////////////////////////////////////////////////////////
	// Rich Boolean functors for comparisons with roundoff

	struct EqualNearRelation
	{
		enum { equality=true };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return fabs(t1-t2)<=t3;
		}
		static const char* name()
		{
			return " ==~ ";
		}
	};

	struct LessNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return t1<(t2+t3);
		}
		static const char* name()
		{
			return " <~ ";
		}
	};

	struct LessOrEqualNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return t1<=(t2+t3);
		}
		static const char* name()
		{
			return " <=~ ";
		}
	};

	struct MoreNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return (t1+t3)>t2;
		}
		static const char* name()
		{
			return " >~ ";
		}
	};

	struct MoreOrEqualNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return (t1+t3)>=t2;
		}
		static const char* name()
		{
			return " >=~ ";
		}
	};

	struct DifferentNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			return fabs(t1-t2)>=t3;
		}
		static const char* name()
		{
			return " !=~ ";
		}
	};

	struct EqualRelativeNearRelation
	{
		enum { equality=true };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = max_(fabs(t1), fabs(t2))*t3;
			return fabs(t1-t2)<=max_diff;
		}
		static const char* name()
		{
			return " ==~ ";
		}
	};

	struct LessRelativeNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = detail::max_(fabs(t1), fabs(t2))*t3;
			return t1<(t2+max_diff);
		}
		static const char* name()
		{
			return " <~ ";
		}
	};

	struct LessOrEqualRelativeNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = detail::max_(fabs(t1), fabs(t2))*t3;
			return t1<=(t2+max_diff);
		}
		static const char* name()
		{
			return " <=~ ";
		}
	};

	struct MoreRelativeNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = detail::max_(fabs(t1), fabs(t2))*t3;
			return (t1+max_diff)>t2;
		}
		static const char* name()
		{
			return " >~ ";
		}
	};

	struct MoreOrEqualRelativeNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = detail::max_(fabs(t1), fabs(t2))*t3;
			return (t1+max_diff)>=t2;
		}
		static const char* name()
		{
			return " >=~ ";
		}
	};

	struct DifferentRelativeNearRelation
	{
		enum { equality=false };
		template <typename T1, typename T2, typename T3>
		bool operator()(const T1 &t1, const T2 &t2, const T3 &t3) const
		{
			T3 max_diff = detail::max_(fabs(t1), fabs(t2))*t3;
			return fabs(t1-t2)>=max_diff;
		}
		static const char* name()
		{
			return " !=~ ";
		}
	};

	struct Dummy {};

	inline EqualRelation operator==(const Dummy&, const Dummy&)
	{
		return EqualRelation();
	}

	inline LessRelation operator<(const Dummy&, const Dummy&)
	{
		return LessRelation();
	}

	inline LessOrEqualRelation operator<=(const Dummy&, const Dummy&)
	{
		return LessOrEqualRelation();
	}

	inline MoreRelation operator>(const Dummy&, const Dummy&)
	{
		return MoreRelation();
	}

	inline MoreOrEqualRelation operator>=(const Dummy&, const Dummy&)
	{
		return MoreOrEqualRelation();
	}

	inline DifferentRelation operator!=(const Dummy&, const Dummy&)
	{
		return DifferentRelation();
	}


	struct DummyNear {};

	inline EqualNearRelation operator==(const DummyNear&, const DummyNear&)
	{
		return EqualNearRelation();
	}

	inline LessNearRelation operator<(const DummyNear&, const DummyNear&)
	{
		return LessNearRelation();
	}

	inline LessOrEqualNearRelation operator<=(const DummyNear&, const DummyNear&)
	{
		return LessOrEqualNearRelation();
	}

	inline MoreNearRelation operator>(const DummyNear&, const DummyNear&)
	{
		return MoreNearRelation();
	}

	inline MoreOrEqualNearRelation operator>=(const DummyNear&, const DummyNear&)
	{
		return MoreOrEqualNearRelation();
	}

	inline DifferentNearRelation operator!=(const DummyNear&, const DummyNear&)
	{
		return DifferentNearRelation();
	}

	struct DummyRelNear {};

	inline EqualRelativeNearRelation operator==(const DummyRelNear&, const DummyRelNear&)
	{
		return EqualRelativeNearRelation();
	}

	inline LessRelativeNearRelation operator<(const DummyRelNear&, const DummyRelNear&)
	{
		return LessRelativeNearRelation();
	}

	inline LessOrEqualRelativeNearRelation operator<=(const DummyRelNear&, const DummyRelNear&)
	{
		return LessOrEqualRelativeNearRelation();
	}

	inline MoreRelativeNearRelation operator>(const DummyRelNear&, const DummyRelNear&)
	{
		return MoreRelativeNearRelation();
	}

	inline MoreOrEqualRelativeNearRelation operator>=(const DummyRelNear&, const DummyRelNear&)
	{
		return MoreOrEqualRelativeNearRelation();
	}

	inline DifferentRelativeNearRelation operator!=(const DummyRelNear&, const DummyRelNear&)
	{
		return DifferentRelativeNearRelation();
	}
}

#endif // #ifndef RICH_BOOL_RELATION_H__QM
