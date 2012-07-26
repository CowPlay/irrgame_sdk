/*
 * irrgameApp.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEAPPLICATION_H_
#define IRRGAMEAPPLICATION_H_
namespace irrgame
{
	class irrgamePlayer;

	class irrgameApp
	{

		public:
			//! Destructor
			virtual ~irrgameApp()
			{
			}

			irrgameApp(irrgamePlayer* player);

			virtual void run() = 0;

			void onApplicationSuspend();

	};
}

#endif /* IRRGAMEAPPLICATION_H_ */
