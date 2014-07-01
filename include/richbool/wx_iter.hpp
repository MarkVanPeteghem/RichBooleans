//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_WX_ITERATOR_H__QM
#define RICH_BOOL_WX_ITERATOR_H__QM

#define WX_DEFINE_ARRAY_ITERATOR(TYPE, ARRAY, ITERATOR) \
class Const##ITERATOR; \
class ITERATOR { \
	friend class Const##ITERATOR; \
public: \
	ITERATOR(ARRAY &arr, size_t pos=0): m_array(&arr), m_pos(pos) {} \
	ITERATOR(const ITERATOR &iter): m_array(iter.m_array), m_pos(iter.m_pos) {} \
	ITERATOR& operator++() { ++m_pos; return *this; } \
	ITERATOR operator++(int) { ITERATOR copy(*this); ++m_pos; return copy; } \
	ITERATOR& operator--() { --m_pos; return *this; } \
	ITERATOR operator--(int) { ITERATOR copy(*this); --m_pos; return copy; } \
	TYPE& operator*() { return m_array->Item(m_pos); } \
	const TYPE& operator*() const { return m_array->Item(m_pos); } \
	TYPE* operator->() { return &m_array->Item(m_pos); } \
	const TYPE* operator->() const { return &m_array->Item(m_pos); } \
	ITERATOR operator=(const ITERATOR &it) \
	{ m_array=it.m_array; m_pos=it.m_pos; return *this; } \
	bool operator==(const ITERATOR &it) const \
	{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
	bool operator!=(const ITERATOR &it) const \
	{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); } \
	bool operator==(const Const##ITERATOR &it) const; \
	bool operator!=(const Const##ITERATOR &it) const; \
private: \
	ARRAY *m_array; \
	size_t m_pos; \
}; \
inline ITERATOR begin(ARRAY &arr) { return ITERATOR(arr); } \
inline ITERATOR end(ARRAY &arr) \
{ return ITERATOR(arr, arr.GetCount()); } \
inline size_t size(ARRAY &arr) \
{ return arr.GetCount(); } \
class Const##ITERATOR { \
	friend class ITERATOR; \
public: \
	Const##ITERATOR(const ARRAY &arr, size_t pos=0): m_array(&arr), m_pos(pos) {} \
	Const##ITERATOR(const Const##ITERATOR &iter): m_array(iter.m_array), m_pos(iter.m_pos) {} \
	Const##ITERATOR& operator++() { ++m_pos; return *this; } \
	Const##ITERATOR operator++(int) { Const##ITERATOR copy(*this); ++m_pos; return copy; } \
	Const##ITERATOR& operator--() { --m_pos; return *this; } \
	Const##ITERATOR operator--(int) { Const##ITERATOR copy(*this); --m_pos; return copy; } \
	const TYPE& operator*() const { return m_array->Item(m_pos); } \
	const TYPE* operator->() const { return &m_array->Item(m_pos); } \
	Const##ITERATOR operator=(const ITERATOR &it) \
	{ m_array=it.m_array; m_pos=it.m_pos; return *this; } \
	Const##ITERATOR operator=(const Const##ITERATOR &it) \
	{ m_array=it.m_array; m_pos=it.m_pos; return *this; } \
	bool operator==(const ITERATOR &it) const \
	{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
	bool operator!=(const ITERATOR &it) const \
	{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); } \
	bool operator==(const Const##ITERATOR &it) const \
	{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
	bool operator!=(const Const##ITERATOR &it) const \
	{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); } \
private: \
	const ARRAY *m_array; \
	size_t m_pos; \
}; \
inline Const##ITERATOR begin(const ARRAY &arr) { return Const##ITERATOR(arr); } \
inline Const##ITERATOR end(const ARRAY &arr) \
{ return Const##ITERATOR(arr, arr.GetCount()); } \
inline size_t size(const ARRAY &arr) \
{ return arr.GetCount(); } \
inline bool ITERATOR::operator==(const Const##ITERATOR &it) const \
{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
inline bool ITERATOR::operator!=(const Const##ITERATOR &it) const \
{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); }

#define WX_DEFINE_ARRAY_ITERATOR_P(TYPE, ARRAY, ITERATOR) \
class Const##ITERATOR; \
class ITERATOR { \
	friend class Const##ITERATOR; \
public: \
	ITERATOR(ARRAY &arr, size_t pos=0): m_array(&arr), m_pos(pos) {} \
	ITERATOR(const ITERATOR &iter): m_array(iter.m_array), m_pos(iter.m_pos) {} \
	ITERATOR& operator++() { ++m_pos; return *this; } \
	ITERATOR operator++(int) { ITERATOR copy(*this); ++m_pos; return copy; } \
	ITERATOR& operator--() { --m_pos; return *this; } \
	ITERATOR operator--(int) { ITERATOR copy(*this); --m_pos; return copy; } \
	TYPE& operator*() { return m_array->Item(m_pos); } \
	const TYPE& operator*() const { return m_array->Item(m_pos); } \
	ITERATOR operator=(const ITERATOR &it) \
	{ m_array=it.m_array; m_pos=it.m_pos; return *this; } \
	bool operator==(const ITERATOR &it) const \
	{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
	bool operator!=(const ITERATOR &it) const \
	{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); } \
	bool operator==(const Const##ITERATOR &it) const; \
	bool operator!=(const Const##ITERATOR &it) const; \
private: \
	ARRAY *m_array; \
	size_t m_pos; \
}; \
inline ITERATOR begin(ARRAY &arr) { return ITERATOR(arr); } \
inline ITERATOR end(ARRAY &arr) \
{ return ITERATOR(arr, arr.GetCount()); } \
inline size_t size(ARRAY &arr) \
{ return arr.GetCount(); } \
class Const##ITERATOR { \
	friend class ITERATOR; \
public: \
	Const##ITERATOR(const ARRAY &arr, size_t pos=0): m_array(&arr), m_pos(pos) {} \
	Const##ITERATOR(const Const##ITERATOR &iter): m_array(iter.m_array), m_pos(iter.m_pos) {} \
	Const##ITERATOR& operator++() { ++m_pos; return *this; } \
	Const##ITERATOR operator++(int) { Const##ITERATOR copy(*this); ++m_pos; return copy; } \
	Const##ITERATOR& operator--() { --m_pos; return *this; } \
	Const##ITERATOR operator--(int) { Const##ITERATOR copy(*this); --m_pos; return copy; } \
	const TYPE& operator*() const { return m_array->Item(m_pos); } \
	Const##ITERATOR operator=(const ITERATOR &it) \
	{ m_array=it.m_array; m_pos=it.m_pos; return *this; } \
	Const##ITERATOR operator=(const Const##ITERATOR &it) \
	{ m_array=it.m_array; m_pos=it.m_pos; return *this; } \
	bool operator==(const ITERATOR &it) const \
	{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
	bool operator!=(const ITERATOR &it) const \
	{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); } \
	bool operator==(const Const##ITERATOR &it) const \
	{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
	bool operator!=(const Const##ITERATOR &it) const \
	{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); } \
private: \
	const ARRAY *m_array; \
	size_t m_pos; \
}; \
inline Const##ITERATOR begin(const ARRAY &arr) { return Const##ITERATOR(arr); } \
inline Const##ITERATOR end(const ARRAY &arr) \
{ return Const##ITERATOR(arr, arr.GetCount()); } \
inline size_t size(const ARRAY &arr) \
{ return arr.GetCount(); } \
inline bool ITERATOR::operator==(const Const##ITERATOR &it) const \
{ return (m_array==it.m_array) && (m_pos==it.m_pos); } \
inline bool ITERATOR::operator!=(const Const##ITERATOR &it) const \
{ return (m_array!=it.m_array) || (m_pos!=it.m_pos); }


#define WX_DEFINE_LIST_ITERATOR(TYPE, LIST, ITERATOR) \
class ITERATOR { \
public: \
	ITERATOR(LIST &list, bool end): m_node(end ? 0 : list.GetFirst()) {} \
	ITERATOR(const ITERATOR &iter): m_node(iter.m_node) {} \
	ITERATOR& operator++() { m_node = m_node->GetNext(); return *this; } \
	ITERATOR operator++(int) { ITERATOR copy(*this); m_node = m_node->GetNext(); return copy; } \
	ITERATOR& operator--() { m_node = m_node->GetPrevious(); return *this; } \
	ITERATOR operator--(int) { ITERATOR copy(*this); m_node = m_node->GetPrevious(); return copy; } \
	TYPE& operator*() { return m_node ? *m_node->GetData() : *(TYPE*)0; } \
	const TYPE& operator*() const { return m_node ? *m_node->GetData() : *(TYPE*)0; } \
	TYPE* operator->() { return m_node ? m_node->GetData() : (TYPE*)0; } \
	const TYPE* operator->() const { return m_node ? m_node->GetData() : (TYPE*)0; } \
	bool operator==(const ITERATOR &it) const \
	{ return m_node==it.m_node; } \
	bool operator!=(const ITERATOR &it) const \
	{ return m_node!=it.m_node; } \
private: \
	LIST::Node *m_node; \
}; \
inline ITERATOR begin(LIST &list) { return ITERATOR(list, false); } \
inline ITERATOR end(LIST &list) { return ITERATOR(list, true); } \
inline size_t size(LIST &list) \
{ return list.GetCount(); } \
class Const##ITERATOR { \
public: \
	Const##ITERATOR(const LIST &list, bool end): m_node(end ? 0 : list.GetFirst()) {} \
	Const##ITERATOR(const Const##ITERATOR &iter): m_node(iter.m_node) {} \
	Const##ITERATOR& operator++() { m_node = m_node->GetNext(); return *this; } \
	Const##ITERATOR operator++(int) { Const##ITERATOR copy(*this); m_node = m_node->GetNext(); return copy; } \
	Const##ITERATOR& operator--() { m_node = m_node->GetPrevious(); return *this; } \
	Const##ITERATOR operator--(int) { Const##ITERATOR copy(*this); m_node = m_node->GetPrevious(); return copy; } \
	const TYPE& operator*() const { return m_node ? *m_node->GetData() : *(TYPE*)0; } \
	const TYPE* operator->() const { return m_node ? m_node->GetData() : (TYPE*)0; } \
	bool operator==(const Const##ITERATOR &it) const \
	{ return m_node==it.m_node; } \
	bool operator!=(const Const##ITERATOR &it) const \
	{ return m_node!=it.m_node; } \
private: \
	LIST::Node *m_node; \
}; \
inline Const##ITERATOR begin(const LIST &list) { return Const##ITERATOR(list, false); } \
inline Const##ITERATOR end(const LIST &list) { return Const##ITERATOR(list, true); } \
inline size_t size(const LIST &list) \
{ return list.GetCount(); }

#define WX_DEFINE_LIST_ITERATOR_P(TYPE, LIST, ITERATOR) \
class ITERATOR { \
public: \
	ITERATOR(LIST &list, bool end): m_node(end ? 0 : list.GetFirst()) {} \
	ITERATOR(const ITERATOR &iter): m_node(iter.m_node) {} \
	ITERATOR& operator++() { m_node = m_node->GetNext(); return *this; } \
	ITERATOR operator++(int) { ITERATOR copy(*this); m_node = m_node->GetNext(); return copy; } \
	ITERATOR& operator--() { m_node = m_node->GetPrevious(); return *this; } \
	ITERATOR operator--(int) { ITERATOR copy(*this); m_node = m_node->GetPrevious(); return copy; } \
	TYPE& operator*() { return m_node ? *m_node->GetData() : *(TYPE*)0; } \
	const TYPE& operator*() const { return m_node ? *m_node->GetData() : *(TYPE*)0; } \
	bool operator==(const ITERATOR &it) const \
	{ return m_node==it.m_node; } \
	bool operator!=(const ITERATOR &it) const \
	{ return m_node!=it.m_node; } \
private: \
	LIST::Node *m_node; \
}; \
inline ITERATOR begin(LIST &list) { return ITERATOR(list, false); } \
inline ITERATOR end(LIST &list) { return ITERATOR(list, true); } \
inline size_t size(LIST &list) \
{ return list.GetCount(); } \
class Const##ITERATOR { \
public: \
	Const##ITERATOR(const LIST &list, bool end): m_node(end ? 0 : list.GetFirst()) {} \
	Const##ITERATOR(const Const##ITERATOR &iter): m_node(iter.m_node) {} \
	Const##ITERATOR& operator++() { m_node = m_node->GetNext(); return *this; } \
	Const##ITERATOR operator++(int) { Const##ITERATOR copy(*this); m_node = m_node->GetNext(); return copy; } \
	Const##ITERATOR& operator--() { m_node = m_node->GetPrevious(); return *this; } \
	Const##ITERATOR operator--(int) { Const##ITERATOR copy(*this); m_node = m_node->GetPrevious(); return copy; } \
	const TYPE& operator*() const { return m_node ? *m_node->GetData() : *(TYPE*)0; } \
	bool operator==(const Const##ITERATOR &it) const \
	{ return m_node==it.m_node; } \
	bool operator!=(const Const##ITERATOR &it) const \
	{ return m_node!=it.m_node; } \
private: \
	LIST::Node *m_node; \
}; \
inline Const##ITERATOR begin(const LIST &list) { return Const##ITERATOR(list, false); } \
inline Const##ITERATOR end(const LIST &list) { return Const##ITERATOR(list, true); } \
inline size_t size(const LIST &list) \
{ return list.GetCount(); }

#endif // #ifndef RICH_BOOL_WX_ITERATOR_H__QM
