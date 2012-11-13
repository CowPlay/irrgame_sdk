#ifndef __C_METHOD_DELEGATE_H_INCLUDED__
#define __C_METHOD_DELEGATE_H_INCLUDED__

#include "IMethod.h"

namespace irrgame
{
	//! Class which represents a wrapper to method of some instance
	template<class TObj, class TRet, class TParam>
	class InstanceMethod: public IMethod<TRet, TParam>
	{
		public:

			typedef TRet (TObj::*PMethod)(TParam p1);

		public:

			//! Default constructor
			InstanceMethod(TObj* pObj, PMethod pMethod);

			//! Destructor
			virtual ~InstanceMethod();

			//! Call function which contains in this delegate
			virtual TRet invoke(TParam p);

			//! Return True if this delegate was equal other delegate. Otherwise return False;
			virtual bool operator==(IMethod<TRet, TParam>* other);

			//! Returns True if contatins pointer to static function. Otherwise - return False.
			virtual bool isStatic();

		private:
			//! Pointer to instance
			TObj* Instance;
			//! Pointer to instance method
			PMethod Method;
	};

	//! Default constructor
	template<class TObj, class TRet, class TParam>
	inline InstanceMethod<TObj, TRet, TParam>::InstanceMethod(TObj* obj,
			PMethod method) :
			Instance(obj), Method(method)
	{
	}

	//! Destructor
	template<class TObj, class TRet, class TParam>
	inline InstanceMethod<TObj, TRet, TParam>::~InstanceMethod()
	{
	}

	//! Call function which contains in this delegate
	template<class TObj, class TRet, class TParam>
	inline TRet InstanceMethod<TObj, TRet, TParam>::invoke(TParam p)
	{
		return (Instance->*Method)(p);
	}

	//! Return True if this delegate was equal other delegate. Otherwise return False;
	template<class TObj, class TRet, class TParam>
	inline bool InstanceMethod<TObj, TRet, TParam>::operator==(
			IMethod<TRet, TParam>* other)
	{
		if (!other)
			return false;

		if (this == other)
			return true;

		if (other->isStatic())
			return false;

		InstanceMethod<TObj, TRet, TParam>* instanceDelegate =
				static_cast<InstanceMethod<TObj, TRet, TParam>*>(other);

		return instanceDelegate->Instance == this->Instance
				&& instanceDelegate->Method == this->Method;
	}

	//! Returns True if contatins pointer to static function. Otherwise - return False.
	template<class TObj, class TRet, class TParam>
	inline bool InstanceMethod<TObj, TRet, TParam>::isStatic()
	{
		return false;
	}

	//! Creator of pointer to instance method. Use it when you want add new method to your delegate.
	template<class TObj, class TRet, class TParam>
	IMethod<TRet, TParam>* NewDelegate(TObj* instance,
			TRet (TObj::*method)(TParam p))
	{
		return new InstanceMethod<TObj, TRet, TParam>(instance, method);
	}

} // namespace irrgame

#endif
