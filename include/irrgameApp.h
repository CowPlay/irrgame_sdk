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
		irrgameApp(irrgamePlayer* player);


		void onApplicationSuspend();

		virtual void run() = 0;



	};
}



#endif /* IRRGAMEAPPLICATION_H_ */
