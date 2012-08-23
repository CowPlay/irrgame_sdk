#ifndef __I_DELEGATE_H_INCLUDED__
#define __I_DELEGATE_H_INCLUDED__

template<class TRet TEMPLATE_PARAMS>
class I_DELEGATE
{
	public:

		//! Destructor
		virtual ~I_DELEGATE()
		{
		}

		virtual TRet Invoke(PARAMS) = 0;

		virtual bool Compare(I_DELEGATE<TRet TEMPLATE_ARGS>* pDelegate) = 0;
};

#endif

