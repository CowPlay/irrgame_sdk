#ifndef __C_DELEGATE_H_INCLUDED__
#define __C_DELEGATE_H_INCLUDED__

#include "core/engine/IReferenceCounted.h"
#include "core/collections/array.h"
#include "IMethod.h"

namespace irrgame
{
	//! Class which contains pointers to few functions(static or instance) with one non-void(!) parameter.
	template<class TRet, class TParam>
	class delegate: public IReferenceCounted
	{
		public:
			typedef IMethod<TRet, TParam> Method;

			typedef irrgame::core::array<Method*> DelegateArray;

		public:

			//! Default constructor
			delegate(Method* method = 0);

			//! Destructor
			virtual ~delegate();

			//! Return True if the array is empty false if not.
			bool empty();

			/*
			 * Operators
			 */

			delegate<TRet, TParam>& operator=(Method* pDelegate);

			//! Adds method to the end of this delegate
			delegate<TRet, TParam>& operator+=(Method* pDelegate);

			//! Remove method from this delegate if it exist
			delegate<TRet, TParam>& operator-=(Method* pDelegate);

			TRet operator()(TParam p);

		private:
			//! Add method to this delegate
			void add(Method* method);

			//! Remove method from this delegate
			void remove(Method* method);

			//! Remove all methods from delegate
			void clear();

			TRet invoke(TParam p);

		private:
			DelegateArray Methods;
	};

	//! Default constructor
	template<class TRet, class TParam>
	delegate<TRet, TParam>::delegate(IMethod<TRet, TParam>* method)
	{
		if (method)
		{
			add(method);
		}
	}

	//! Destructor
	template<class TRet, class TParam>
	delegate<TRet, TParam>::~delegate()
	{
		clear();
	}

	//! Return True if the array is empty false if not.
	template<class TRet, class TParam>
	bool delegate<TRet, TParam>::empty()
	{
		return Methods.empty();
	}

	/*
	 * Operators
	 */
	template<class TRet, class TParam>
	delegate<TRet, TParam>& delegate<TRet, TParam>::operator=(
			IMethod<TRet, TParam>* method)
	{
		IRR_ASSERT(method);

		clear();
		add(method);

		return *this;
	}

	template<class TRet, class TParam>
	delegate<TRet, TParam>& delegate<TRet, TParam>::operator+=(
			IMethod<TRet, TParam>* method)
	{
		IRR_ASSERT(method);

		add(method);

		return *this;
	}

	template<class TRet, class TParam>
	delegate<TRet, TParam>& delegate<TRet, TParam>::operator-=(
			IMethod<TRet, TParam>* method)
	{
		IRR_ASSERT(method);

		remove(method);

		return *this;
	}

	template<class TRet, class TParam>
	TRet delegate<TRet, TParam>::operator()(TParam p1)
	{
		return invoke(p1);
	}

	//! Add function to this delegate
	template<class TRet, class TParam>
	void delegate<TRet, TParam>::add(IMethod<TRet, TParam>* method)
	{
		IRR_ASSERT(method);

		Methods.pushBack(method);
	}

	//! Remove function from this delegate
	template<class TRet, class TParam>
	void delegate<TRet, TParam>::remove(IMethod<TRet, TParam>* method)
	{
		for (u32 i = 0; i < Methods.size(); i++)
		{
			if ((*method) == Methods[i])
			{
				Methods[i]->drop();
				Methods.erase(i);
				break;
			}
		}
	}

	template<class TRet, class TParam>
	//! Remove all functions from delegate
	void delegate<TRet, TParam>::clear()
	{
		for (u32 i = 0; i < Methods.size(); i++)
		{
			Methods[i]->drop();
		}

		Methods.clear();
	}

	template<class TRet, class TParam>
	TRet delegate<TRet, TParam>::invoke(TParam p)
	{
		TRet result;

		u32 defaultSize = Methods.size();

		for (u32 i = 0; i < this->Methods.size(); i++)
		{
			result = Methods[i]->invoke(p);

			u32 currentSize = Methods.size();

			if (currentSize < defaultSize)
			{
				u32 diff = defaultSize - currentSize;
				i -= diff;
				defaultSize = currentSize;
			}
		}

		return result;
	}
} // namespace irrgame

#endif
