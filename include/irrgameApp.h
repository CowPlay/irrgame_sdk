/*
 * irrgameApp.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEAPPLICATION_H_
#define IRRGAMEAPPLICATION_H_

#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	class irrgamePlayer;

	class irrgameApp: public IReferenceCounted
	{

		public:
			//! Default constructor
			//			irrgameApp(irrgamePlayer* player);

			//! Destructor
			virtual ~irrgameApp()
			{
			}

			virtual void run() = 0;

//			virtual void onApplicationSuspend() = 0;

	};
}

#endif /* IRRGAMEAPPLICATION_H_ */
