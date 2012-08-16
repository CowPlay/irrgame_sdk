/*
 * irrgameThread.cpp
 *
 *  Created on: Aug 13, 2012
 *      Author: gregorytkach
 */

#include "threads/irrgameThread.h"

namespace irrgame
{
	namespace threads
	{

		//! Gets callback input args
		void* irrgameThread::getCallbackArg()
		{
			return CallbackArg;
		}

		//! Gets thread callback
		delegateThreadCallback* irrgameThread::getCallback()
		{
			return Callback;
		}

		//! Gets thread name
		core::stringc irrgameThread::getName()
		{
			return Name;
		}
	}
}

