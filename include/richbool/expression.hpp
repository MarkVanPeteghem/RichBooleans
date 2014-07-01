//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_EXPRESSION_H__QM
#define RICH_BOOL_EXPRESSION_H__QM

#include "richbool/portability.hpp"
#include "richbool/shared_ptr.hpp"


namespace RichBool
{
	class RICHBOOL_DLL_API Expression
	{
		virtual bool Equals(const Expression &expr) const = 0;
	public:
		enum Type { IsEmpty, IsText, IsString, IsIndex, IsPrefix, IsSuffix };

		Expression() {}
		virtual ~Expression() {}

		virtual Type GetType() const = 0;

		bool operator==(const Expression &expr) const;

		virtual operator detail::String() const = 0;

		virtual Expression* Clone() const = 0;
	};

	typedef ConstSharedPointer<Expression> SharedExpression;

	class RICHBOOL_DLL_API IndexExpression: public Expression
	{
		size_t idx;
		virtual bool Equals(const Expression &expr) const;
	public:
		IndexExpression(size_t idx_): idx(idx_) {}

		size_t GetIndex() const { return idx; }

		virtual Type GetType() const;
		virtual operator detail::String() const;
		virtual Expression* Clone() const;
	};

	class RICHBOOL_DLL_API TextExpression: public Expression
	{
		const char *text;
		virtual bool Equals(const Expression &expr) const;
	public:
		TextExpression(const char *text_): text(text_) {}

		const char *GetText() const { return text; }

		virtual Type GetType() const;
		virtual operator detail::String() const;
		virtual Expression* Clone() const;
	};

	class StringExpression: public Expression
	{
		detail::String str;
		virtual RICHBOOL_DLL_API bool Equals(const Expression &expr) const;
	public:
		StringExpression(const detail::String &str_): str(str_) {}

		const detail::String& GetText() const { return str; }

		virtual RICHBOOL_DLL_API Type GetType() const;
		virtual operator detail::String() const
		{
			return '`'+str+'\'';
		}
		virtual Expression* Clone() const
		{
			return new StringExpression(str);
		}
	};

	class PrefixedExpression: public Expression
	{
		const char *prefix;
		SharedExpression expression;

		virtual RICHBOOL_DLL_API bool Equals(const Expression &expr) const;

	public:
		PrefixedExpression(const char *prefix_, SharedExpression expr):
			prefix(prefix_), expression(expr)
		{}
		virtual ~PrefixedExpression()
		{}

		const char* GetPrefix() const { return prefix; }

		RICHBOOL_DLL_API virtual Type GetType() const;
		
		virtual operator detail::String() const
		{
			detail::String str = *expression;
			return prefix+str;
		}

		virtual Expression* Clone() const
		{
			return new PrefixedExpression(prefix, expression->Clone());
		}
	};

	class SuffixedExpression: public Expression
	{
		const char *suffix;
		SharedExpression expression;

		RICHBOOL_DLL_API virtual bool Equals(const Expression &expr) const;

	public:
		SuffixedExpression(const char *suffix_, SharedExpression expr):
			suffix(suffix_), expression(expr)
		{}
		virtual ~SuffixedExpression()
		{}
		const char* GetSuffix() const { return suffix; }

		RICHBOOL_DLL_API virtual Type GetType() const;
		virtual operator detail::String() const
		{
			detail::String str = *expression;
			return str+suffix;
		}

		virtual Expression* Clone() const
		{
			return new SuffixedExpression(suffix, expression->Clone());
		}
	};


	inline SharedExpression MakeExpression(size_t idx)
	{
		return new IndexExpression(idx);
	}

	inline SharedExpression MakeExpression(const char *text)
	{
		return text ? new TextExpression(text) : (TextExpression*)NULL;
	}

	inline SharedExpression MakeExpression(SharedExpression expr)
	{
		return expr;
	}
}

#endif // #ifndef RICH_BOOL_EXPRESSION_H__QM
