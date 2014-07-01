//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef PREDICATES_H__QM
#define PREDICATES_H__QM


// some simple predicates to use in tests

class IsEven
{
public:
	bool operator()(int n) const
	{
		return n%2==0;
	}
};

class ProductIs
{
public:
	ProductIs(int prod): product(prod) {}
	int product;

	bool operator()(int a, int b) const
	{
		return a*b==product;
	}
	bool operator()(int a, int b, int c) const
	{
		return a*b*c==product;
	}
	bool operator()(int a, int b, int c, int d) const
	{
		return a*b*c*d==product;
	}
	bool operator()(int a, int b, int c, int d, int e) const
	{
		return a*b*c*d*e==product;
	}
	bool operator()(int a, int b, int c, int d, int e, int f) const
	{
		return a*b*c*d*e*f==product;
	}
};

class ProductIs12: public ProductIs
{
public:
	ProductIs12(): ProductIs(12)
	{}
};

struct PredMore
{
	bool operator()(int a, int b) const
	{
		return a>b;
	}	
};

#endif // #ifndef PREDICATES_H__QM
