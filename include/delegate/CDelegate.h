#ifndef __C_DELEGATE_H_INCLUDED__
#define __C_DELEGATE_H_INCLUDED__
#include "core/irrgamecollections.h"
#include "IDelegate.h"

namespace irrgame
{
	template<class TRet, class TP1>
	class CDelegate
	{
		public:
			typedef IDelegate<TRet, TP1> IDel;

			typedef irrgame::core::array<IDel*> DelegateArray;

			//! Default constructor
			CDelegate(IDel* pDelegate = NULL);

			//! Destructor
			virtual ~CDelegate();

			//! Returns True if delegate does not have functions
			bool IsNull();

			/*
			 * Operators
			 */
			CDelegate<TRet, TP1>& operator=(IDel* pDelegate);

			CDelegate<TRet, TP1>& operator+=(IDel* pDelegate);

			CDelegate<TRet, TP1>& operator-=(IDel* pDelegate);

			TRet operator()(TP1 p1);

		private:
			//! Add function to this delegate
			void Add(IDel* pDelegate);

			//! Remove function from this delegate
			void Remove(IDel* pDelegate);

			//! Remove all functions from delegate
			void RemoveAll();

			TRet Invoke(TP1 p1);
		private:
			DelegateArray Functions;
	};

	//! Default constructor
	template<class TRet, class TP1>
	CDelegate<TRet, TP1>::CDelegate(IDelegate<TRet, TP1>* pDelegate)
	{
		Add(pDelegate);
	}

	//! Destructor
	template<class TRet, class TP1>
	CDelegate<TRet, TP1>::~CDelegate()
	{
		RemoveAll();
	}

	//! Returns True if delegate does not have functions
	template<class TRet, class TP1>
	bool CDelegate<TRet, TP1>::IsNull()
	{
		return Functions.empty();
	}

	/*
	 * Operators
	 */
	template<class TRet, class TP1>
	CDelegate<TRet, TP1>& CDelegate<TRet, TP1>::operator=(
			IDelegate<TRet, TP1>* pDelegate)
	{
		RemoveAll();
		Add(pDelegate);
		return *this;
	}

	template<class TRet, class TP1>
	CDelegate<TRet, TP1>& CDelegate<TRet, TP1>::operator+=(
			IDelegate<TRet, TP1>* pDelegate)
	{
		Add(pDelegate);
		return *this;
	}

	template<class TRet, class TP1>
	CDelegate<TRet, TP1>& CDelegate<TRet, TP1>::operator-=(
			IDelegate<TRet, TP1>* pDelegate)
	{
		Remove(pDelegate);
		return *this;
	}

	template<class TRet, class TP1>
	TRet CDelegate<TRet, TP1>::operator()(TP1 p1)
	{
		return Invoke(p1);
	}

	//! Add function to this delegate
	template<class TRet, class TP1>
	void CDelegate<TRet, TP1>::Add(IDelegate<TRet, TP1>* pDelegate)
	{
		if (pDelegate != NULL)
			Functions.pushBack(pDelegate);
	}

	//! Remove function from this delegate
	template<class TRet, class TP1>
	void CDelegate<TRet, TP1>::Remove(IDelegate<TRet, TP1>* pDelegate)
	{
		for (u32 i = 0; i < Functions.size(); i++)
		{
			if (Functions[i]->Compare(pDelegate))
			{
				delete Functions[i];
				Functions.erase(i);
				break;
			}
		}
	}

	template<class TRet, class TP1>
	//! Remove all functions from delegate
	void CDelegate<TRet, TP1>::RemoveAll()
	{
		for (u32 i = 0; i < Functions.size(); i++)
			delete Functions[i];

		Functions.clear();
	}

	template<class TRet, class TP1>
	TRet CDelegate<TRet, TP1>::Invoke(TP1 p1)
	{
		TRet result;

		u32 defaultSize = Functions.size();

		for (u32 i = 0; i < this->Functions.size() && this != NULL; i++)
		{
			result = Functions[i]->Invoke(p1);

			u32 currentSize = Functions.size();
			if (currentSize < defaultSize)
			{
				u32 diff = defaultSize - currentSize;
				i -= diff;
				defaultSize = currentSize;
			}
		}

		return result;
	}
}
// namespace irrgame

#endif
