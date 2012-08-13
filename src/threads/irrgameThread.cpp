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

		//! Gets thread name
		core::stringc irrgameThread::getName()
		{
			return Name;
		}
	}
}

