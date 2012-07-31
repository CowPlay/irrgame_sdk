#ifndef __C_METHOD_DELEGATE_H_INCLUDED__
#define __C_METHOD_DELEGATE_H_INCLUDED__
#include "IDelegate.h"


template<class TObj, class TRet TEMPLATE_PARAMS>
class C_METHOD_DELEGATE : public I_DELEGATE<TRet TEMPLATE_ARGS>
{
	public:

	typedef TRet (TObj::*PMethod)(PARAMS);

	C_METHOD_DELEGATE(TObj* pObj, PMethod pMethod)
	{
		m_pObj = pObj;
		m_pMethod = pMethod;
	}

	virtual ~C_METHOD_DELEGATE()
	{
	}

	virtual TRet Invoke(PARAMS)
	{
		return (m_pObj->*m_pMethod)(ARGS);
	}

	virtual bool Compare(I_DELEGATE<TRet TEMPLATE_ARGS>* pDelegate)
	{
		C_METHOD_DELEGATE<TObj, TRet TEMPLATE_ARGS>* pMethodDel =
		dynamic_cast<C_METHOD_DELEGATE<TObj, TRet TEMPLATE_ARGS>*>(pDelegate);
		if
		(
				pMethodDel == NULL ||
				pMethodDel->m_pObj != m_pObj ||
				pMethodDel->m_pMethod != m_pMethod
		)
		{
			return false;
		}

		return true;
	}

	private:
	TObj *m_pObj;
	PMethod m_pMethod;
};

//!Creator
template <class TObj, class TRet TEMPLATE_PARAMS>
I_DELEGATE<TRet TEMPLATE_ARGS>* NewDelegate(TObj* pObj, TRet (TObj::*pMethod)(PARAMS))
{
	return new C_METHOD_DELEGATE<TObj, TRet TEMPLATE_ARGS> (pObj, pMethod);
}
#endif
