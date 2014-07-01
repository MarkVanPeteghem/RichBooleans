//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/bit_iterator.hpp"

namespace RichBool
{
    static bool IsBigEndian()
    {
        int n = 1;
        const char *ch = (const char *)&n;
        return ch[0]==0;
    }

    BitIterator::BitIterator(const void *bits, int nrBytes): m_bit(7), m_mask(1<<7)
    {
        if (!IsBigEndian())
        {
            m_bits = ((const char*)bits)+nrBytes-1;
            m_dir = -1;
        }
        else
        {
            m_bits = (const char*)bits;
            m_dir = 1;
        }
    }

    bool BitIterator::operator*() const
    {
        return ((*m_bits)&m_mask)==m_mask;
    }

    void BitIterator::operator++()
    {
        --m_bit;
        if (m_bit<0)
        {
            m_bits += m_dir;
            m_bit = 7;
            m_mask = 1<<m_bit;
        }
        else
        {
            m_mask >>= 1;
        }
    }
}
