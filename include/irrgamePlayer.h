/*
 * irrgamePlayer.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEPLAYER_H_
#define IRRGAMEPLAYER_H_

#include "irrgameApp.h"

namespace irrgame
{
	class irrgameApp;

	class irrgamePlayer
	{
		public:

			//! Destructor
			virtual ~irrgamePlayer() = 0;

			virtual void run(irrgameApp* application) = 0;

			void getFileSystem();

	};

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer();
}

#endif /* IRRGAMEPLAYER_H_ */
