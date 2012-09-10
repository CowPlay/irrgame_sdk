#ifndef __C_DELEGATE_H_INCLUDED__
#define __C_DELEGATE_H_INCLUDED__
#include "core/irrgamecollections.h"
#include "IDelegate.h"

template<class TRet TEMPLATE_PARAMS>
class C_DELEGATE
{
	public:

		//TODO: replace this data
		void* Data;

	public:
		typedef I_DELEGATE<TRet TEMPLATE_ARGS> IDelegate;

		typedef irrgame::core::array<IDelegate*> DelegateArray;

		C_DELEGATE(IDelegate* pDelegate = NULL) :
				Data(0)
		{
			Add(pDelegate);
		}

		virtual ~C_DELEGATE()
		{
			RemoveAll();
		}

		bool IsNull()
		{
			return Functions.empty();
		}

		C_DELEGATE<TRet TEMPLATE_ARGS>& operator=(IDelegate* pDelegate)
		{
			RemoveAll();
			Add(pDelegate);
			return *this;
		}

		C_DELEGATE<TRet TEMPLATE_ARGS>& operator+=(IDelegate* pDelegate)
		{
			Add(pDelegate);
			return *this;
		}

		C_DELEGATE<TRet TEMPLATE_ARGS>& operator-=(IDelegate* pDelegate)
		{
			Remove(pDelegate);
			return *this;
		}

		TRet operator()(PARAMS)
		{
			return Invoke(ARGS);
		}

	private:
		void Add(IDelegate* pDelegate)
		{
			if (pDelegate != NULL)
				Functions.pushBack(pDelegate);
		}

		void Remove(IDelegate* pDelegate)
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

		void RemoveAll()
		{
			for (u32 i = 0; i < Functions.size(); i++)
				delete Functions[i];

			Functions.clear();
		}

		TRet Invoke(PARAMS)
		{
			TRet result;

			u32 defaultSize = Functions.size();

			for (u32 i = 0; i < this->Functions.size() && this != NULL; i++)
			{
				result = Functions[i]->Invoke(ARGS);

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

	private:
		DelegateArray Functions;
};
#endif
