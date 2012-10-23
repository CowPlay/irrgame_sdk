#ifndef __C_METHOD_DELEGATE_H_INCLUDED__
#define __C_METHOD_DELEGATE_H_INCLUDED__
#include "IDelegate.h"

namespace irrgame
{
	template<class TObj, class TRet, class TP1>
	class CMethodDelegate: public IDelegate<TRet, TP1>
	{
		public:

			typedef TRet (TObj::*PMethod)(TP1 p1);

			//! Default constructor
			CMethodDelegate(TObj* pObj, PMethod pMethod);

			//! Destructor
			virtual ~CMethodDelegate();

			virtual TRet Invoke(TP1 p1);

			virtual bool Compare(IDelegate<TRet, TP1>* pDelegate);

		private:
			//! Pointer to instance
			TObj *Obj;
			//! pointer to instance method
			PMethod Method;
	};

	//! Default constructor
	template<class TObj, class TRet, class TP1>
	CMethodDelegate<TObj, TRet, TP1>::CMethodDelegate(TObj* obj, PMethod method) :
			Obj(obj), Method(method)
	{
	}

	//! Destructor
	template<class TObj, class TRet, class TP1>
	CMethodDelegate<TObj, TRet, TP1>::~CMethodDelegate()
	{
	}

	template<class TObj, class TRet, class TP1>
	TRet CMethodDelegate<TObj, TRet, TP1>::Invoke(TP1 p1)
	{
		return (Obj->*Method)(p1);
	}

	template<class TObj, class TRet, class TP1>
	bool CMethodDelegate<TObj, TRet, TP1>::Compare(
			IDelegate<TRet, TP1>* pDelegate)
	{
		bool result = true;

		CMethodDelegate<TObj, TRet, TP1> *pMethodDel =
				dynamic_cast<CMethodDelegate<TObj, TRet, TP1>*>(pDelegate);

		if (pMethodDel == NULL || pMethodDel->Obj != Obj
				|| pMethodDel->Method != Method)
		{
			result = false;
		}

		return result;
	}

	//!Creator
	template<class TObj, class TRet, class TP1>
	IDelegate<TRet, TP1>* NewDelegate(TObj* pObj, TRet (TObj::*pMethod)(TP1 p1))
	{
		return new CMethodDelegate<TObj, TRet, TP1>(pObj, pMethod);
	}
}
// namespace irrgame

#endif
