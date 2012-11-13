#ifndef __I_DELEGATE_H_INCLUDED__
#define __I_DELEGATE_H_INCLUDED__

#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	//! Interface of object which contains pointer to instance method or static function
	template<class TRet, class TParam>
	class IMethod : public IReferenceCounted
	{
		public:

			//! Destructor
			virtual ~IMethod()
			{
			}

			//! Call function which contains in this delegate
			virtual TRet invoke(TParam p) = 0;

			//! Return True if this delegate was equal other delegate. Otherwise return False;
			virtual bool operator==(IMethod<TRet, TParam>* other) = 0;

			//! Returns True if contatins pointer to static function. Otherwise - return False.
			virtual bool isStatic() = 0;
	};

}  // namespace irrgame

#endif

