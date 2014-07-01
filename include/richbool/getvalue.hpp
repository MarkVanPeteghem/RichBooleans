//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_GET_VALUE_H__QM
#define RICH_BOOL_GET_VALUE_H__QM

#include "richbool/config.hpp"
#include "richbool/badblock.hpp"

namespace RichBool
{
	struct Value
	{
		template<typename T>
		struct Return
		{
            typedef T Type;
        };

		template<typename T>
		struct Argument
		{
            typedef T Type;
        };

		template<typename T>
		const T& operator()(const T &t) const
		{
			return t;
		}

		template<typename T>
		bool BadPtrChain(const T &t) const
		{
			return BadPtr(&t);
		}

		template<typename T, class Stringize_>
		detail::String ToString(const T &t, Stringize_ str) const
		{
			if (BadPtr(&t))
				return PtrToString(&t);
			else
				return str(t);
		}

		template<typename T>
		detail::String AddressToString(const T *t) const
		{
			return PtrToString(t);
		}

		SharedExpression Convert(SharedExpression expr) const
		{
			return expr;
		}

		template <class Expression_>
		struct ExpressionType
		{
			typedef Expression_ Result;
		};
	};

	template<class GetValue=Value>
	struct BasePointer
	{
		BasePointer() {}
		BasePointer(GetValue getValue_): getValue(getValue_) {}

		GetValue getValue;

		template<typename T>
		struct Argument
		{
            typedef T* Type;
		};

		template<typename T>
		const T& operator()(const T *t) const
		{
			return getValue(*t);
		}

		template<typename T>
		bool BadPtrChain(const T &t) const
		{
			return BadPtr(&t) || getValue.BadPtrChain(*t);
		}

		template<typename T, class Stringize_>
		detail::String ToString(const T &t, Stringize_ str) const
		{
			if (BadPtr(&t))
				return PtrToString(&t);
			else if (getValue.BadPtrChain(*t))
				return PtrToString(&t)+" -> "+getValue.ToString(*t, str);
			else
				return getValue.ToString(*t, str);
		}

		template<typename T>
		detail::String AddressToString(const T *t) const
		{
			if (BadPtr(&t))
				return PtrToString(t);
			else
				return PtrToString(t)+" -> "+getValue.AddressToString(*t);
		}

		SharedExpression Convert(SharedExpression expr) const
		{
			return getValue.Convert(new PrefixedExpression("*", expr));
		}
	};

	template<typename Return_, class GetValue=Value>
	struct PointerLike: public BasePointer<GetValue>
	{
		PointerLike() {}
		PointerLike(GetValue getValue_): BasePointer<GetValue>(getValue_) {}

		template<typename T>
		struct Return
		{
            typedef Return_ Type;
        };

		template<typename T>
		struct Argument
		{
		};

		template<typename T>
		const Return_& operator()(const T &t) const
		{
			return getValue(*t);
		}
	};

	template<typename Return_, class GetValue=Value>
	struct PointerLikeToValue: public BasePointer<GetValue>
	{
		PointerLikeToValue()
		{}
		PointerLikeToValue(GetValue getValue_): BasePointer<GetValue>(getValue_)
		{}

		template<typename T>
		struct Return
		{
            typedef Return_ Type;
        };

		template<typename T>
		struct Argument
		{
		};

		template<typename T>
		Return_ operator()(const T &t) const
		{
			return getValue(*t);
		}
	};

#ifndef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION
	template<typename T>
	struct RemovePointer {
	};
	template<typename T> struct RemovePointer<T*> {
		typedef T type;
	};
	template<typename T> struct RemovePointer<T* const> {
		typedef T type;
	};
	template<typename T> struct RemovePointer<T* volatile> {
		typedef T type;
	};
	template<typename T> struct RemovePointer<T* const volatile> {
		typedef T type;
	};

	template<class GetValue=Value>
	struct BasePointerWithReturnType: public BasePointer<GetValue>
	{
		BasePointerWithReturnType() {}
		BasePointerWithReturnType(GetValue getValue_): BasePointer<GetValue>(getValue_) {}

		template<typename T>
		struct Return
		{
		    typedef typename RemovePointer<T>::type OtherArg;
		    typedef typename GetValue::template Return<OtherArg>::Type Type;
		};
	};

	template<class GetValue=Value>
	struct Pointer: public BasePointerWithReturnType<GetValue>
	{
	    typedef BasePointerWithReturnType<GetValue> Base;

		Pointer() {}
		Pointer(GetValue getValue_): BasePointerWithReturnType<GetValue>(getValue_) {}

		template<typename T>
		const typename Base::template Return<T>::Type& operator()(const T &t) const
		{
			return getValue(*t);
		}
	};

	template<class GetValue=Value>
	struct PointerToValue: public BasePointerWithReturnType<GetValue>
	{
	    typedef BasePointerWithReturnType<GetValue> Base;

		PointerToValue() {}
		PointerToValue(GetValue getValue_): BasePointerWithReturnType<GetValue>(getValue_) {}

		template<typename T>
		typename Base::template Return<T>::Type operator()(const T &t) const
		{
			return getValue(*t);
		}
	};
#else

    // Generic Pointer can't be used, only the specialization with Value.
    // We do this so one can use Pointer<>, so the code can be compiled
    // with other compilers that select the fully functional Pointer<...>
	template<class GetValue=Value>
	struct Pointer: public BasePointer<GetValue>
	{};

	template<>
	struct Pointer<Value>: public BasePointer<Value>
	{
		Pointer() {}

		template<typename T>
		const T& operator()(const T *t) const
		{
			return *t;
		}
	};

    // Generic PointerToValue can't be used, only the specialization with Value.
    // We do this so one can use PointerToValue<>, so the code can be compiled
    // with other compilers that select the fully functional PointerToValue<...>
	template<class GetValue=Value>
	struct PointerToValue: public BasePointer<GetValue>
	{};

	template<>
	struct PointerToValue<Value>: public BasePointer<Value>
	{
		PointerToValue() {}
		PointerToValue(Value getValue_): BasePointer<Value>(getValue_) {}

		template<typename T>
		T operator()(const T *t) const
		{
			return *t;
		}
	};
#endif // #ifndef RICHBOOL_NO_PARTIAL_TEMPLATE_SPECIALIZATION

#ifndef RICHBOOL_NO_TEMPLATE_TYPE_LOOKUP
    template <class T, typename Returned, class GetValue_=Value>
    struct GetMember
    {
        typedef GetValue_ GetValue;
        typedef typename GetValue::template Argument<Returned>::Type Argument;

        GetMember(const Argument T::* m, const char *n, GetValue getValue_=GetValue()):
            member(m), name(n), getValue(getValue_)
        {}

        const Argument T::* member;
        const char *name;
        GetValue getValue;

        template<typename U>
        struct Return
        {
            typedef Returned Type;
        };

        const Returned& operator()(const T &t) const
        {
            return getValue(t.*member);
        }

        bool BadPtrChain(const T &t) const
        {
            return BadPtr(&t) || getValue.BadPtrChain(t.*member);
        }

        template<class Stringize_>
        detail::String ToString(const T &t, const Stringize_ &str) const
        {
            if (BadPtr(&t))
                return PtrToString(&t);
            else if (getValue.BadPtrChain(t.*member))
                return PtrToString(&t)+" -> "+getValue.ToString(t.*member, str);
            else
                return str(getValue(t.*member));
        }

        SharedExpression Convert(SharedExpression expr) const
        {
            return getValue.Convert(new SuffixedExpression(name, expr));
        }
    };

    template <class T, typename Returned, class GetValue_=Value>
    struct CallMethod
    {
        typedef GetValue_ GetValue;
        typedef typename GetValue::template Argument<Returned>::Type Argument;

        CallMethod(Argument (T::*m)() const, const char *n, GetValue getValue_=GetValue()):
            method(m), name(n), getValue(getValue_)
        {}

        Argument (T::*method)() const;
        const char *name;
        GetValue getValue;

        template<typename U>
        struct Return
        {
            typedef Returned Type;
        };

        Returned operator()(const T &t) const
        {
            return getValue((t.*method)());
        }

        bool BadPtrChain(const T &t) const
        {
            return BadPtr(&t) || getValue.BadPtrChain((t.*method)());
        }

        template<class Stringize_>
        detail::String ToString(const T &t, const Stringize_ &str) const
        {
            if (BadPtr(&t))
                return PtrToString(&t);
            else if (getValue.BadPtrChain((t.*method)()))
                return PtrToString(&t)+" -> "+getValue.ToString((t.*method)(), str);
            else
                return str(getValue((t.*method)()));
        }

        SharedExpression Convert(SharedExpression expr) const
        {
            return getValue.Convert(new SuffixedExpression(name, expr));
        }
    };
#endif // #ifndef RICHBOOL_NO_TEMPLATE_TYPE_LOOKUP

    template <class T, typename Returned, typename Argument, class GetValue_=Value>
    struct GetMemberArg
    {
        typedef GetValue_ GetValue;

        GetMemberArg(const Argument T::* const m, const char *n, GetValue getValue_=GetValue()):
            member(m), name(n), getValue(getValue_)
        {}

        const Argument T::* member;
        const char *name;
        GetValue getValue;

        template<typename U>
        struct Return
        {
            typedef Returned Type;
        };

        const Returned& operator()(const T &t) const
        {
            return getValue(t.*member);
        }

        bool BadPtrChain(const T &t) const
        {
            return BadPtr(&t) || getValue.BadPtrChain(t.*member);
        }

        template<class Stringize_>
        detail::String ToString(const T &t, const Stringize_ &str) const
        {
            if (BadPtr(&t))
                return PtrToString(&t);
            else if (getValue.BadPtrChain(t.*member))
                return PtrToString(&t)+" -> "+getValue.ToString(t.*member, str);
            else
                return str(getValue(t.*member));
        }

        SharedExpression Convert(SharedExpression expr) const
        {
            return getValue.Convert(new SuffixedExpression(name, expr));
        }
    };

    template <class T, typename Returned, typename Argument, class GetValue_=Value>
    struct CallMethodArg
    {
        typedef GetValue_ GetValue;

        CallMethodArg(Argument (T::*m)() const, const char *n, GetValue getValue_=GetValue()):
            method(m), name(n), getValue(getValue_)
        {}

        Argument (T::*method)() const;
        const char *name;
        GetValue getValue;

        template<typename U>
        struct Return
        {
            typedef Returned Type;
        };

        Returned operator()(const T &t) const
        {
            return getValue((t.*method)());
        }

        bool BadPtrChain(const T &t) const
        {
            return BadPtr(&t) || getValue.BadPtrChain((t.*method)());
        }

        template<class Stringize_>
        detail::String ToString(const T &t, const Stringize_ &str) const
        {
            if (BadPtr(&t))
                return PtrToString(&t);
            else if (getValue.BadPtrChain((t.*method)()))
                return PtrToString(&t)+" -> "+getValue.ToString((t.*method)(), str);
            else
                return str(getValue((t.*method)()));
        }

        SharedExpression Convert(SharedExpression expr) const
        {
            return getValue.Convert(new SuffixedExpression(name, expr));
        }
    };
}

#endif // #ifndef RICH_BOOL_GET_VALUE_H__QM
