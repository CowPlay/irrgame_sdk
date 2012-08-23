/*
 * irrgameApp.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEAPPLICATION_H_
#define IRRGAMEAPPLICATION_H_

#include "core/irrgamebase.h"
namespace irrgame
{
	class irrgamePlayer;

	class irrgameApp: public IReferenceCounted
	{

		public:
			//! Destructor
			virtual ~irrgameApp()
			{
			}

			//! Default constructor
//			irrgameApp(irrgamePlayer* player);

			virtual void run() = 0;

//			virtual void onApplicationSuspend() = 0;

	};
}

#endif /* IRRGAMEAPPLICATION_H_ */
