//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef RICH_BOOL_SHARED_POINTER_H__QM
#define RICH_BOOL_SHARED_POINTER_H__QM

namespace RichBool
{
	namespace detail
	{
		template<typename T>
		class MemoryRefCount
		{
		public:
			typedef T Type;

			MemoryRefCount(T *t_): count(1), t(t_)
			{}

			virtual ~MemoryRefCount() {}

			const T* Get() { return t; }
			void AddRef() { ++count; }
			virtual void Release()
			{
				--count;
				if (count==0)
					delete this;
			}

		protected:
			int count;
			T *t;
		};

		template<typename T>
		class PointerRefCount: public MemoryRefCount<T>
		{
		public:
			PointerRefCount(T *t_): MemoryRefCount<T>(t_)
			{}
			~PointerRefCount()
			{
				delete this->t;
			}
		};

		template<typename T>
		class ArrayRefCount: public MemoryRefCount<T>
		{
		public:
			ArrayRefCount(T *t_): MemoryRefCount<T>(t_)
			{}
			~ArrayRefCount()
			{
				delete[] this->t;
			}
		};

		// Shared pointer class.
		// Once a pointer is assigned to a RichBool::ConstSharedMemory
		// object, it can't be changed through it anymore.
		// This class is not threadsafe, because Rich Booleans are typically
		// used in only one thread, so the most performant option was chosen.
		template <class RefCount>
		class ConstSharedMemory
		{
		public:
			typedef typename RefCount::Type Type;

			ConstSharedMemory(): m_RefCount(0) {}
			ConstSharedMemory(Type *t)
			{
				if (t)
					m_RefCount = new RefCount(t);
				else
					m_RefCount = 0;
			}

			ConstSharedMemory(const ConstSharedMemory &sp)
			{
				m_RefCount = sp.m_RefCount;
				if (m_RefCount)
					m_RefCount->AddRef();
			}

			~ConstSharedMemory()
			{
				if (m_RefCount)
					m_RefCount->Release();
			}

			ConstSharedMemory& operator=(Type *t)
			{
				if (m_RefCount)
					m_RefCount->Release();
				if (t)
					m_RefCount = new RefCount(t);
				else
					m_RefCount = 0;
				return *this;
			}

			ConstSharedMemory& operator=(const ConstSharedMemory &sp)
			{
				if (m_RefCount)
					m_RefCount->Release();

				m_RefCount = sp.m_RefCount;

				if (m_RefCount)
					m_RefCount->AddRef();

				return *this;
			}

			operator bool() const
			{
				return m_RefCount && m_RefCount->Get()!=0;
			}

			const Type& operator*() const
			{
				return *m_RefCount->Get();
			}

			const Type* operator->() const
			{
				return m_RefCount->Get();
			}

			const Type* Get() const
			{
				return m_RefCount ? m_RefCount->Get() : 0;
			}
		private:
			RefCount *m_RefCount;
		};
	}

	template <typename T>
	struct ConstSharedPointer: public detail::ConstSharedMemory<detail::PointerRefCount<T> >
	{
		ConstSharedPointer(T*t=0)
			: detail::ConstSharedMemory<detail::PointerRefCount<T> >(t)
		{}
	};

	template <typename T>
	struct ConstSharedArray: public detail::ConstSharedMemory<detail::ArrayRefCount<T> >
	{
		ConstSharedArray(T*t=0)
			: detail::ConstSharedMemory<detail::ArrayRefCount<T> >(t)
		{}
		const T& operator[](size_t idx) const
		{
			return this->Get()[idx];
		}
	};
}

#endif // #ifndef RICH_BOOL_SHARED_POINTER_H__QM
