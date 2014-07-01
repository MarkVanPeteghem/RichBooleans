//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (See accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef WX_H__QM
#define WX_H__QM

#include "richbool/wxstring.hpp"
#include "richbool/wx_iter.hpp"

namespace RichBool
{
	struct MakeClassInfoString
	{
		enum { showString = true };

		detail::String operator()(const char *ci) const
		{
			return ci;
		}

		detail::String operator()(const wxClassInfo *ci) const
		{
			return ci->GetClassName();
		}
	};

	struct WxIsKindOfCore: public FunctorCore
	{
		template<typename T>
		bool operator()(const T &t, wxClassInfo *ci) const
		{
			return t.IsKindOf(ci);
		}

		template<typename T>
		bool operator()(const T &t, const wxChar *szTypeName) const
		{
			return t.IsKindOf(wxClassInfo::FindClass(szTypeName));
		}

		const char* GetTextBefore1() const
		{
			return "wxClassInfo(";
		}
		const char* GetTextAfter1() const
		{
			return ")";
		}

		template<typename T, typename CI>
		detail::String GetResult1(const T &t, const CI *) const
		{
			return t.GetClassInfo()->GetClassName();
		}
		const char* GetTextBeforeResult1() const
		{
			return ":";
		}

		const char* GetTextBefore2() const
		{
			return " is kind of ";
		}
	};

	template <class GetValue1=Value, class GetValue2=Value,
		class Stringize1=MakeString, class Stringize2=MakeClassInfoString>
	struct WxIsKindOf: public Wrapper2Arg<WxIsKindOfCore, GetValue1, GetValue2,
		Stringize1, Stringize2>
	{
		WxIsKindOf(GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
			Wrapper2Arg<WxIsKindOfCore,
				GetValue1, GetValue2, Stringize1, Stringize2>(gv1, gv2)
		{}
	};

	struct WxHasTypeCore: public WxIsKindOfCore
	{
		template<typename T>
		bool operator()(const T &t, wxClassInfo *ci) const
		{
			return t.GetClassInfo() == ci;
		}

		template<typename T>
		bool operator()(const T &t, const wxChar *szTypeName) const
		{
			return t.GetClassInfo() == wxClassInfo::FindClass(szTypeName);
		}

		const char* GetTextBefore2() const
		{
			return " == ";
		}
	};

	template <class GetValue1=Value, class GetValue2=Value,
		class Stringize1=MakeString, class Stringize2=MakeClassInfoString>
	struct WxHasType: public Wrapper2Arg<WxHasTypeCore, GetValue1, GetValue2,
		Stringize1, Stringize2>
	{
		WxHasType(GetValue1 gv1=GetValue1(), GetValue2 gv2=GetValue2()):
			Wrapper2Arg<WxHasTypeCore,
				GetValue1, GetValue2, Stringize1, Stringize2>(gv1, gv2)
		{}
	};

	struct WxEqualTypesCore: public FunctorCore
	{
		template<typename T1, typename T2>
		bool operator()(const T1 &a, const T2 &b) const
		{
			return a.GetClassInfo()==b.GetClassInfo();
		}

		const char* GetTextBefore1() const
		{
			return "wxClassInfo(";
		}
		const char* GetTextAfter1() const
		{
			return ")";
		}

		template<typename T1, typename T2>
		detail::String GetResult1(const T1 &t, const T2 &) const
		{
			return t.GetClassInfo()->GetClassName();
		}
		const char* GetTextBeforeResult1() const
		{
			return ":";
		}

		const char* GetTextBefore2() const
		{
			return " == wxClassInfo(";
		}
		const char* GetTextAfter2() const
		{
			return ")";
		}

		template<typename T1, typename T2>
		detail::String GetResult2(const T1 &, const T2 &t) const
		{
			return t.GetClassInfo()->GetClassName();
		}
		const char* GetTextBeforeResult2() const
		{
			return ":";
		}
	};

	RICHBOOL_WRAPPER2ARG(WxEqualTypes, WxEqualTypesCore)
	typedef WxEqualTypes<Pointer<>, Pointer<> > WxEqualTypesPtr;
}

#define rbWX_IS_KIND_OF(t, classInfo) \
	rb2_RB(t,classInfo, RichBool::WxIsKindOf<Pointer<> >())
#define rbvWX_IS_KIND_OF(t, classInfo) \
	rbv2_1_RB(t,classInfo, RichBool::WxIsKindOf<Pointer<> >())

#define rbWX_HAS_TYPE(t, classInfo) \
	rb2_RB(t,classInfo, RichBool::WxHasType<Pointer<> >())
#define rbvWX_HAS_TYPE(t, classInfo) \
	rbv2_1_RB(t,classInfo, RichBool::WxHasType<Pointer<> >())

#define rbWX_EQUAL_TYPES(a, b) rb2_RB(a,b,RichBool::WxEqualTypesPtr())
#define rbvWX_EQUAL_TYPES(a, b) rbv2_1_RB(a,b,RichBool::WxEqualTypesPtr())

#endif // #ifndef WX_H__QM
