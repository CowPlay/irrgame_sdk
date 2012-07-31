#ifndef __C_STATIC_DELEGATE_H_INCLUDED__
#define __C_STATIC_DELEGATE_H_INCLUDED__

#include "string.h"

template<class TRet TEMPLATE_PARAMS>
class C_STATIC_DELEGATE : public I_DELEGATE<TRet TEMPLATE_ARGS>
{
	public:

	typedef TRet (*PFunc)(PARAMS);

	C_STATIC_DELEGATE(PFunc pFunc)
	{
		m_pFunc = pFunc;
	}

	virtual ~C_STATIC_DELEGATE()
	{
	}

	virtual TRet Invoke(PARAMS)
	{
		return m_pFunc(ARGS);
	}

	virtual bool Compare(I_DELEGATE<TRet TEMPLATE_ARGS>* pDelegate)
	{
		C_STATIC_DELEGATE<TRet TEMPLATE_ARGS>* pStaticDel =
		dynamic_cast<C_STATIC_DELEGATE<TRet TEMPLATE_ARGS>*>(pDelegate);

		if(pStaticDel == NULL || pStaticDel->m_pFunc != m_pFunc)
		return false;

		return true;
	}

	private:
	//! Pointer to static function
	PFunc m_pFunc;
};

//!Creator
template<class TRet TEMPLATE_PARAMS>
I_DELEGATE<TRet TEMPLATE_ARGS>* NewDelegate(TRet (*pFunc)(PARAMS))
{
	return new C_STATIC_DELEGATE<TRet TEMPLATE_ARGS>(pFunc);
}

#endif
