//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_FIND_IN_RANGES_H__QM
#define RICH_BOOL_FIND_IN_RANGES_H__QM

namespace RichBool
{
	namespace detail
	{
		template <typename It, typename Idx>
		struct EnhIt
		{
			EnhIt(It i, Idx idx_): it(i), idx(idx_) {}
			It it;
			Idx idx;
			EnhIt& operator++()
			{
				++it;
				++idx;
				return *this;
			}
		};


		template <typename It_, class EC, class RB>
		class FindInRangeBase
		{
		protected:
			It_ b;
			EC ec;
			RB rb;
		public:
			typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

			FindInRangeBase(It it, EC ec_, RB rb_=RB()): b(it), ec(ec_), rb(rb_) {}

			It begin() const { return b; }
			EIt ebegin() const { return EIt(b,0); }
			bool is_end(const EIt &it) const { return !ec(it.it, it.idx); }
			bool empty() const { return !ec(b,0); }
			void Reset() {}
		};

		template <typename It_, class EC, class RB>
		class FindInRange: public FindInRangeBase<It_, EC, RB>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, RB>::b;
			using FindInRangeBase<It_, EC, RB>::ec;
			using FindInRangeBase<It_, EC, RB>::rb;
#endif
			FindInRange(It it, EC ec_, RB rb_=RB()): FindInRangeBase<It_, EC, RB>(it, ec_, rb_) {}

			IndexType size() const { return ec.length(b); }

			template <typename T>
			EIt Find(const T &t) const
			{
				typename EC::IndexType idx=0;
				It it=b;
				for (; ec(it,idx); ++it, ++idx)
					if (rb(t,*it)) break;
				return EIt(it,idx);
			}
			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				typename EC::IndexType idx=0;
				It it=b;
				st = Analysis::NotOk;
				for (; ec(it,idx); ++it, ++idx)
				{
					const Analysis::State s = rb.SafeCheck(t,*it);
					if ((s==Analysis::Ok)||(s==Analysis::BadValue))
					{
						st = s;
						break;
					}
				}
				return EIt(it,idx);
			}
		};

		template <typename It_, class EC, class RB>
		class FindInMarkedRangeBase: public FindInRangeBase<It_, EC, RB>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

			BoolVector found;

			FindInMarkedRangeBase(It it, EC ec_, RB rb_=RB()):
				FindInRangeBase<It_, EC, RB>(it, ec_, rb_), found(ec_.length(it),false)
			{}
			bool HasUnfound() const
			{
				for (size_t i=0; i<array_size(found); ++i)
					if (!found[i])
						return true;
				return false;
			}
			void Reset()
			{
				for (size_t i=0; i<array_size(found); ++i)
					found[i]=false;
			}
		};

		template <typename It_, class EC, class RB>
		class FindInMarkedRange: public FindInMarkedRangeBase<It_, EC, RB>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, RB>::b;
			using FindInRangeBase<It_, EC, RB>::ec;
			using FindInRangeBase<It_, EC, RB>::rb;
            using FindInMarkedRangeBase<It_, EC, RB>::found;
#endif
			FindInMarkedRange(It it, EC ec_, RB rb_=RB()):
				FindInMarkedRangeBase<It_, EC, RB>(it, ec_, rb_)
			{}

			IndexType size() const { return ec.length(b); }

			template <typename T>
			EIt Find(const T &t)
			{
				typename EC::IndexType idx=0;
				It it=b;
				for (; ec(it,idx); ++it, ++idx)
					if (rb(t,*it)&&!found[idx]) { found[idx]=true; break; }
				return EIt(it,idx);
			}
			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				typename EC::IndexType idx=0;
				It it=b;
				st=Analysis::NotOk;
				for (; ec(it,idx); ++it, ++idx)
				{
					if (!found[idx])
					{
						const Analysis::State s = rb.SafeCheck(t,*it);
						if (s==Analysis::Ok)
						{ st=s; found[idx]=true; break; }
						else if (s==Analysis::BadValue)
						{ st=s; break; }
					}
				}
				return EIt(it,idx);
			}
		};

		template <typename T, typename Pred>
		bool equal_pred(const T &t1, const T &t2, Pred pred)
		{
			return !pred(t1,t2) && !pred(t2,t1);
		}
		template <typename T, typename Pred>
		Analysis::State equal_pred_safe(const T &t1, const T &t2, Pred pred)
		{
			Analysis::State st=pred.SafeCheck(t1,t2);
			if (st==Analysis::Ok)
				return Analysis::NotOk;
			if (st==Analysis::BadValue)
				return Analysis::BadValue;
			return !pred(t2,t1) ? Analysis::Ok : Analysis::NotOk;
		}

		template <typename It_, class EC, class Sort>
		class FindInSortedRange: public FindInRangeBase<It_, EC, Sort>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, Sort>::b;
			using FindInRangeBase<It_, EC, Sort>::ec;
			using FindInRangeBase<It_, EC, Sort>::rb;
#endif
			FindInSortedRange(It b_, EC ec_, Sort s=Sort()): FindInRangeBase<It, EC, Sort>(b_, ec_, s) {}

			IndexType size() const { return ec.ra_length(b); }

			// Note: this function supposes that the range is not empty.
			template <typename T>
			EIt Find(const T &t) const
			{
				It bb=b, ee=ec.ra_end(b);
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					if (rb(t,*n))
						ee -= (ee-n);
					else
						bb = n;
				}
				return equal_pred(*bb,t,rb) ? EIt(bb,bb-b) : EIt(ec.ra_end(b), ec.length(b));
			}
			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				It bb=b, ee=ec.ra_end(b);
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					Analysis::State s=rb.SafeCheck(t,*n);
					if (s==Analysis::Ok)
						ee -= (ee-n);
					else if (s==Analysis::NotOk)
						bb = n;
					else
					{
						st = Analysis::BadValue;
						return EIt(n, n-b);
					}
				}
				st=equal_pred_safe(*bb,t,rb);
				if (st!=Analysis::NotOk)
					return EIt(bb,bb-b);
				else
					return EIt(ec.ra_end(b), ec.length(b));
			}
			void Reset()
			{}
		};

		template <typename It_, class EC, class Sort>
		class FindInMarkedSortedRange: public FindInMarkedRangeBase<It_, EC, Sort>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It_,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, Sort>::b;
			using FindInRangeBase<It_, EC, Sort>::ec;
			using FindInRangeBase<It_, EC, Sort>::rb;
            using FindInMarkedRangeBase<It_, EC, Sort>::found;
#endif
			FindInMarkedSortedRange(It b_, EC ec_, Sort s=Sort()):
				FindInMarkedRangeBase<It, EC, Sort>(b_, ec_, s)
			{}

			IndexType size() const { return ec.ra_length(b); }

			// Note: this function supposes that the range is not empty.
			template <typename T>
			EIt Find(const T &t)
			{
				if (equal_pred(*b,t,rb)&&!found[0])
				{
					found[0]=true;
					return EIt(b,0);
				}
				It bb=b, e=ec.ra_end(b), ee=e-1;
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					if (rb(*n,t))
						bb = n;
					else
						ee -= (ee-n);
				}
				size_t idx=ee-b;
				while (ee!=e)
				{
					if (!equal_pred(*ee,t,rb)) return EIt(e,e-b);
					else if (!found[idx])
					{
						found[idx] = true;
						return EIt(ee, ee-b);
					}
					++idx;
					++ee;
				}
				return EIt(e,e-b);
			}

			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				if (this->empty())
				{
					st = Analysis::NotOk;
					return EIt(b,0);
				}
				Analysis::State s=equal_pred_safe(*b,t,rb);
				if ((s==Analysis::Ok)&&!found[0])
				{
					st = Analysis::Ok;
					found[0]=true;
					return EIt(b,0);
				}
				if (s==Analysis::BadValue)
				{
					st = Analysis::BadValue;
					return EIt(b,0);
				}
				It bb=b, e=ec.ra_end(b), ee=e-1;
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					if (rb(*n,t))
						bb = n;
					else
						ee -= (ee-n);
				}
				size_t idx=ee-b;
				while (ee!=e)
				{
					if (!equal_pred(*ee,t,rb))
					{
						st = Analysis::NotOk;
						return EIt(e,e-b);
					}
					else if (!found[idx])
					{
						found[idx] = true;
						st = Analysis::Ok;
						return EIt(ee,ee-b);
					}
					++idx;
					++ee;
				}
				st = Analysis::NotOk;
				return EIt(e,e-b);
			}
		};

		template <typename It_, class EC, class RB>
		class OrderedFindInRange: public FindInRangeBase<It_, EC, RB>
		{
			typedef typename EC::IndexType IndexType;

			It_ m_it;
			IndexType m_idx;
		public:
            typedef It_ It;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, RB>::b;
			using FindInRangeBase<It_, EC, RB>::ec;
			using FindInRangeBase<It_, EC, RB>::rb;
#endif
			OrderedFindInRange(It it, EC ec_, RB rb_=RB()):
				FindInRangeBase<It_, EC, RB>(it, ec_, rb_), m_it(it), m_idx(0)
			{}

			IndexType size() const { return ec.length(b); }

			template <typename T>
			EIt Find(const T &t)
			{
				It oldIt=m_it;
				IndexType oldIdx=m_idx;
				for (; ec(m_it,m_idx); ++m_it, ++m_idx)
					if (rb(t,*m_it)) return EIt(m_it++,m_idx++);
				EIt rv(m_it,m_idx);
				m_it=oldIt;
				m_idx=oldIdx;
				return rv;
			}
			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				It oldIt=m_it;
				IndexType oldIdx=m_idx;
				st = Analysis::NotOk;
				for (; ec(m_it,m_idx); ++m_it, ++m_idx)
				{
					const Analysis::State s = rb.SafeCheck(t,*m_it);
					if ((s==Analysis::Ok)||(s==Analysis::BadValue))
					{
						st = s;
						return EIt(m_it++,m_idx++);
					}
				}
				EIt rv(m_it,m_idx);
				m_it=oldIt;
				m_idx=oldIdx;
				return rv;
			}
			void Reset()
			{
				m_it=b;
				m_idx=0;
			}
		};

		template <typename It_, class EC, class RB>
		class OrderedFindInRangeSP: public FindInRangeBase<It_, EC, RB>
		{
			typedef typename EC::IndexType IndexType;

			It_ m_it;
			IndexType m_idx;
			bool m_used;
		public:
            typedef It_ It;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, RB>::b;
			using FindInRangeBase<It_, EC, RB>::ec;
			using FindInRangeBase<It_, EC, RB>::rb;
#endif
			OrderedFindInRangeSP(It it, EC ec_, RB rb_=RB()):
				FindInRangeBase<It_, EC, RB>(it, ec_, rb_), m_it(it), m_idx(0), m_used(false)
			{}

			IndexType size() const { return ec.length(b); }

			template <typename T>
			EIt Find(const T &t)
			{
				if (m_used) { ++m_it; ++m_idx; } else m_used=true;
				for (; ec(m_it,m_idx); ++m_it, ++m_idx)
					if (rb(t,*m_it)) return EIt(m_it,m_idx);
				m_used=false;
				return EIt(m_it,m_idx);
			}
			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				if (m_used) { ++m_it; ++m_idx; } else m_used=true;
				st = Analysis::NotOk;
				for (; ec(m_it,m_idx); ++m_it, ++m_idx)
				{
					const Analysis::State s = rb.SafeCheck(t,*m_it);
					if ((s==Analysis::Ok)||(s==Analysis::BadValue))
					{
						st = s;
						return EIt(m_it,m_idx);
					}
				}
				m_used=false;
				return EIt(m_it,m_idx);
			}
			void Reset()
			{
				// should not be called!!
			}
		};

		template <typename It_, class EC, class Sort>
		class OrderedFindInSortedRange: public FindInRangeBase<It_, EC, Sort>
		{
			It_ it;
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, Sort>::b;
			using FindInRangeBase<It_, EC, Sort>::ec;
			using FindInRangeBase<It_, EC, Sort>::rb;
#endif
			OrderedFindInSortedRange(It b_, EC ec_, Sort s=Sort()):
				FindInRangeBase<It, EC, Sort>(b_,ec_,s), it(b_)
			{}

			IndexType size() const { return ec.ra_length(b); }

			template <typename T>
			EIt Find(const T &t)
			{
				if (!ec(it,it-b))
					return EIt(it,it-b);
				if (equal_pred(*it,t,rb))
				{
					IndexType idx=it-b;
					return EIt(it++,idx);
				}
				It bb=it, e=ec.ra_end(b), ee=e-1;
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					if (rb(*n,t))
						bb = n;
					else
						ee -= (ee-n);
				}
				if (!equal_pred(*ee,t,rb))
					return EIt(e,e-b);
				it=ee+1;
				return EIt(ee, ee-b);
			}

			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				if (!ec(it,it-b))
				{
					st=Analysis::NotOk;
					return EIt(it,it-b);
				}
				Analysis::State s=equal_pred_safe(*it,t,rb);
				if ((s==Analysis::Ok))
				{
					st = Analysis::Ok;
					IndexType idx=it-b;
					return EIt(it++,idx);
				}
				if (s==Analysis::BadValue)
				{
					st = Analysis::BadValue;
					return EIt(it,it-b);
				}
				It bb=it, e=ec.ra_end(b), ee=e-1;
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					if (rb(*n,t))
						bb = n;
					else
						ee -= (ee-n);
				}
				if (!equal_pred(*ee,t,rb))
				{
					st = Analysis::NotOk;
					return EIt(e,e-b);
				}
				st = Analysis::Ok;
				it=ee+1;
				return EIt(ee,ee-b);
			}
			void Reset()
			{
				it=b;
			}
		};

		template <typename It_, class EC, class RB>
		class FindInMultiMarkedRange: public FindInMarkedRangeBase<It_, EC, RB>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, RB>::b;
			using FindInRangeBase<It_, EC, RB>::ec;
			using FindInRangeBase<It_, EC, RB>::rb;
			using FindInMarkedRangeBase<It_, EC, RB>::found;
#endif
			FindInMultiMarkedRange(It it, EC ec_, RB rb_=RB()):
				FindInMarkedRangeBase<It_, EC, RB>(it, ec_, rb_)
			{}

			IndexType size() const { return ec.length(b); }

			template <typename T>
			EIt Find(const T &t)
			{
				typename EC::IndexType idx=0;
				It it=b;
				for (; ec(it,idx); ++it, ++idx)
					if (rb(t,*it)&&!found[idx]) found[idx]=true;
				return EIt(it,idx);
			}
			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				typename EC::IndexType idx=0;
				It it=b;
				st=Analysis::NotOk;
				for (; ec(it,idx); ++it, ++idx)
					if (!found[idx])
					{
						const Analysis::State s = rb.SafeCheck(t,*it);
						if (s==Analysis::Ok)
						{ st=s; found[idx]=true; }
						else if (s==Analysis::BadValue)
						{ st=s; break; }
					}
				return EIt(it,idx);
			}
		};

		template <typename It_, class EC, class Sort>
		class FindInMultiMarkedSortedRange: public FindInMarkedRangeBase<It_, EC, Sort>
		{
		public:
            typedef It_ It;
			typedef typename EC::IndexType IndexType;
			typedef EnhIt<It,IndexType> EIt;

#if !defined(_MSC_VER) || (_MSC_VER > 1300)
			using FindInRangeBase<It_, EC, Sort>::b;
			using FindInRangeBase<It_, EC, Sort>::ec;
			using FindInRangeBase<It_, EC, Sort>::rb;
			using FindInMarkedRangeBase<It_, EC, Sort>::found;
#endif
			FindInMultiMarkedSortedRange(It b_, EC ec_, Sort s=Sort()):
				FindInMarkedRangeBase<It_, EC, Sort>(b_, ec_, s)
			{}

			IndexType size() const { return ec.ra_length(b); }

			// Note: this function supposes that the range is not empty.
			template <typename T>
			EIt Find(const T &t)
			{
				if (equal_pred(*b,t,rb)&&!found[0])
				{
					Mark(b,0);
					return EIt(ec.ra_end(b),ec.ra_length(b));
				}
				It bb=b, e=ec.ra_end(b), ee=e-1;
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					if (rb(*n,t))
						bb = n;
					else
						ee -= (ee-n);
				}
				size_t idx=ee-b;
				if (equal_pred(*ee,t,rb)&&!found[idx])
					Mark(ee,idx);
				return EIt(ec.ra_end(b),ec.ra_length(b));
			}

			template <typename T>
			EIt SafeFind(const T &t, Analysis::State &st)
			{
				if (this->empty())
				{
					st = Analysis::NotOk;
					return EIt(b,0);
				}
				Analysis::State s=equal_pred_safe(*b,t,rb);
				if ((s==Analysis::Ok)&&!found[0])
					return SafeMark(b,0,st);
				if (s==Analysis::BadValue)
				{
					st = Analysis::BadValue;
					return EIt(b,0);
				}
				It bb=b, e=ec.ra_end(b), ee=e-1;
				while ((bb+1)<ee)
				{
					It n = bb+(ee-bb)/2;
					s=rb.SafeCheck(*n,t);
					if (s==Analysis::Ok)
						bb = n;
					else if (s==Analysis::NotOk)
						ee -= (ee-n);
					else
						return EIt(n,n-b);
				}
				size_t idx=ee-b;
				if (found[idx]||!equal_pred(*ee,t,rb))
					st = Analysis::NotOk;
				else
					return SafeMark(ee,idx,st);
				return EIt(ec.ra_end(b),ec.ra_length(b));
			}
		protected:
			void Mark(It s, IndexType idx)
			{
				It it=s;
				do
				{
					found[idx] = true;
					++idx;
					++it;
				} while ((it!=ec.ra_end(b))&&equal_pred(*it,*s,rb));
			}
			EIt SafeMark(It s, IndexType idx, Analysis::State &st)
			{
				It it=s;
				found[idx] = true;
				++idx;
				++it;
				while (it!=ec.ra_end(b))
				{
					st=equal_pred_safe(*it,*s,rb);
					if (st==Analysis::NotOk)
						break;
					if (st==Analysis::BadValue)
						return EIt(it,it-b);
					found[idx] = true;
					++idx;
					++it;
				}
				st=Analysis::Ok;
				return EIt(ec.ra_end(b), ec.ra_length(b));
			}
		};
	}
}

#endif // #ifndef RICH_BOOL_FIND_IN_RANGES_H__QM
