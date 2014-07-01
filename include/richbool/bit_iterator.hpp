//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICHBOOL_BIT_ITERATOR_H__QM
#define RICHBOOL_BIT_ITERATOR_H__QM

#include "richbool/export.hpp"

namespace RichBool
{
    // iterator that iterates over bits in a buffer
    // most significant bits are returned first
    class RICHBOOL_DLL_API BitIterator
    {
        const char *m_bits;
        int m_bit;
        int m_dir;
        int m_mask;
    public:
        BitIterator(const void *bits, int nrBytes);
        bool operator*() const;
        void operator++();
    };
}

#endif // #ifndef RICHBOOL_BIT_ITERATOR_H__QM
