//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifndef STUB_CONTAINER_H__QM
#define STUB_CONTAINER_H__QM

#include <vector>

// This is a simple but working container,
// of which the iterators are input iterators.
// It is used to test rich booleans that are meant
// to work on input iterators. If it is used with
// rich booleans that are not meant to work on
// input iterators, errors might occur.

class StubContainer
{
public:
	StubContainer(): m_idx(0)
	{
	}
	StubContainer(int a1): m_idx(0)
	{
		m_array.push_back(a1);
	}
	StubContainer(int a1, int a2): m_idx(0)
	{
		m_array.push_back(a1);
		m_array.push_back(a2);
	}
	StubContainer(int a1, int a2, int a3): m_idx(0)
	{
		m_array.push_back(a1);
		m_array.push_back(a2);
		m_array.push_back(a3);
	}
	StubContainer(int a1, int a2, int a3, int a4): m_idx(0)
	{
		m_array.push_back(a1);
		m_array.push_back(a2);
		m_array.push_back(a3);
		m_array.push_back(a4);
	}

	StubContainer(int a1, int a2, int a3, int a4, int a5): m_idx(0)
	{
		m_array.push_back(a1);
		m_array.push_back(a2);
		m_array.push_back(a3);
		m_array.push_back(a4);
		m_array.push_back(a5);
	}

	int getInt() const { return m_array[m_idx]; }
	void inc() const { ++m_idx; }
	bool atEnd() const { return m_idx>=m_array.size(); }
	void rewind() { m_idx=0; }
	size_t size() const { return m_array.size(); }
	size_t idx() const { return m_idx; }

	template <typename RV>
	class GenIterator
	{
	public:
		GenIterator(): m_cont(0) {}
		GenIterator(const StubContainer &cont): m_cont(&cont) {}

		RV operator*() { return m_cont->getInt(); }
		GenIterator& operator++() { m_cont->inc(); return *this; }
		const GenIterator& operator++() const { m_cont->inc(); return *this; }
		size_t idx() { return m_cont->idx(); }

		bool operator==(const GenIterator &iter) const
		{
			if (!m_cont && !iter.m_cont)
				return true;
			if (!m_cont)
				return iter.m_cont->atEnd();
			if (!iter.m_cont)
				return m_cont->atEnd();

			return m_cont == iter.m_cont;
		}

		bool operator!=(const GenIterator &iter) const
		{
			return !(*this==iter);
		}

	protected:
		const StubContainer *m_cont;
	};

	typedef GenIterator<int> Iterator;
	typedef GenIterator<const int> ConstIterator;

	GenIterator<int> begin() { return GenIterator<int>(*this); }
	GenIterator<int> end() { return GenIterator<int>(); }

	GenIterator<const int> begin() const { return GenIterator<const int>(*this); }
	GenIterator<const int> end() const { return GenIterator<const int>(); }

	std::vector<int> m_array;
	mutable unsigned int m_idx;
};

#endif // #ifndef STUB_CONTAINER_H__QM













