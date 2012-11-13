#ifndef __C_STATIC_DELEGATE_H_INCLUDED__
#define __C_STATIC_DELEGATE_H_INCLUDED__

#include "IMethod.h"

namespace irrgame
{
	//! Class which represents a wrapper to static method
	template<class TRet, class TParam>
	class StaticFunction: public IMethod<TRet, TParam>
	{
		public:
			typedef TRet (*FunctionPointer)(TParam p1);

		public:
			//! Default construcotr
			StaticFunction(FunctionPointer function);

			//! Destructor
			virtual ~StaticFunction();

			//! Call function which contains in this delegate
			virtual TRet invoke(TParam p);

			//! Return True if this delegate was equal other delegate. Otherwise return False;
			virtual bool operator==(IMethod<TRet, TParam>* other);

			//! Returns True if contatins pointer to static function. Otherwise - return False.
			virtual bool isStatic();

		private:
			//! Pointer to static function
			FunctionPointer Function;
	};

	//! Default construcotr
	template<class TRet, class TParam>
	StaticFunction<TRet, TParam>::StaticFunction(FunctionPointer function) :
			Function(function)
	{
	}

	//! Destructor
	template<class TRet, class TParam>
	StaticFunction<TRet, TParam>::~StaticFunction()
	{
	}

	//! Call function which contains in this delegate
	template<class TRet, class TParam>
	TRet StaticFunction<TRet, TParam>::invoke(TParam p)
	{
		return Function(p);
	}

	//! Return True if this delegate was equal other delegate. Otherwise return False;
	template<class TRet, class TParam>
	bool StaticFunction<TRet, TParam>::operator==(IMethod<TRet, TParam>* other)
	{
		if (!other)
			return false;

		if (this == other)
			return true;

		if (!other->isStatic())
			return false;

		StaticFunction<TRet, TParam>* staticDelegate = static_cast<StaticFunction<
				TRet, TParam>*>(other);

		return staticDelegate->Function == this->Function;
	}

	//! Returns True if contatins pointer to static function. Otherwise - return False.
	template<class TRet, class TParam>
	inline bool StaticFunction<TRet, TParam>::isStatic()
	{
		return true;
	}

	//! Creator of pointer to static function. Use it when you want add new method to your delegate.
	template<class TRet, class TParam>
	IMethod<TRet, TParam>* NewDelegate(TRet (*function)(TParam p))
	{
		return new StaticFunction<TRet, TParam>(function);
	}

} // namespace irrgame

#endif
