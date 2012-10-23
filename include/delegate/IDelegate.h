#ifndef __I_DELEGATE_H_INCLUDED__
#define __I_DELEGATE_H_INCLUDED__

namespace irrgame
{
	template<class TRet, class TP1>
	class IDelegate
	{
		public:

			//! Destructor
			virtual ~IDelegate()
			{
			}

			virtual TRet Invoke(TP1 p1) = 0;

			virtual bool Compare(IDelegate<TRet, TP1>* pDelegate) = 0;
	};
}  // namespace irrgame

#endif

