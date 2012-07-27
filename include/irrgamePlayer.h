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
	namespace io
	{
		class IFileSystem;
	}

	class irrgameApp;

	class irrgamePlayer
	{
		public:

			//! Destructor
			virtual ~irrgamePlayer()
			{
			}

//			virtual void run(irrgameApp* application) = 0;

			virtual class io::IFileSystem* getFileSystem() = 0;
	};

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer();
}

#endif /* IRRGAMEPLAYER_H_ */
