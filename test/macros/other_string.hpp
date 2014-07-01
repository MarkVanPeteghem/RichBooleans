//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef OTHER_STRING_H__QM
#define OTHER_STRING_H__QM

#include <string>

template<class T>
class other_allocator
{
	std::allocator<T> a;
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

	other_allocator() {}

	template<typename T1>
    other_allocator(const other_allocator<T1>&) throw() {}

	bool operator==(const other_allocator<T> &al) const
	{
		return a==al.a;
	}

    pointer address(reference x) const
	{
		return a.address(x);
	}
    const_pointer address(const_reference x) const
	{
		return a.address(x);
	}
    pointer allocate(size_type n, const void *hint)
	{
		return a.allocate(n, hint);
	}
    pointer allocate(size_type n)
	{
		return a.allocate(n, 0);
	}
    void deallocate(pointer p, size_type n)
	{
		a.deallocate(p, n);
	}
    void construct(pointer p, const T& val)
	{
		a.construct(p, val);
	}
    void destroy(pointer p)
	{
		a.destroy(p);
	}
    size_type max_size() const
	{
		return a.max_size();
	}

	template<typename T1>
	struct rebind
	{ typedef other_allocator<T1> other; };
};

template<typename E>
class other_string: public std::basic_string<E, std::char_traits<E>, other_allocator<E> >
{
	typedef std::basic_string<E, std::char_traits<E>, other_allocator<E> > super;
public:
	other_string() {}
	other_string(const other_string &str): super(str) {}
	other_string(const E* s): super(s) {}
};

#endif // #ifndef OTHER_STRING_H__QM
