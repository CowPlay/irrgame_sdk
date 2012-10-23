#ifndef __C_STATIC_DELEGATE_H_INCLUDED__
#define __C_STATIC_DELEGATE_H_INCLUDED__

#include "string.h"
namespace irrgame
{
	template<class TRet, class TP1>
	class CStaticDelegate: public IDelegate<TRet, TP1>
	{
		public:
			typedef TRet (*PFunc)(TP1 p1);

		public:
			//! Default construcotr
			CStaticDelegate(PFunc pFunc);

			//! Destructor
			virtual ~CStaticDelegate();

			virtual TRet Invoke(TP1 p1);

			virtual bool Compare(IDelegate<TRet, TP1>* pDelegate);

		private:
			//! Pointer to static function
			PFunc Func;
	};

	//! Default construcotr
	template<class TRet, class TP1>
	CStaticDelegate<TRet, TP1>::CStaticDelegate(PFunc func) :
			Func(func)
	{
	}

	//! Destructor
	template<class TRet, class TP1>
	CStaticDelegate<TRet, TP1>::~CStaticDelegate()
	{
	}

	template<class TRet, class TP1>
	TRet CStaticDelegate<TRet, TP1>::Invoke(TP1 p1)
	{
		return Func(p1);
	}

	template<class TRet, class TP1>
	bool CStaticDelegate<TRet, TP1>::Compare(IDelegate<TRet, TP1>* pDelegate)
	{
		bool result = true;

		CStaticDelegate<TRet, TP1>* pStaticDel = dynamic_cast<CStaticDelegate<
				TRet, TP1>*>(pDelegate);

		if (pStaticDel == NULL || pStaticDel->Func != Func)
			result = false;

		return result;
	}

	//!Creator
	template<class TRet, class TP1>
	IDelegate<TRet, TP1>* NewDelegate(TRet (*pFunc)(TP1 p1))
	{
		return new CStaticDelegate<TRet, TP1>(pFunc);
	}
}
// namespace irrgame

#endif
