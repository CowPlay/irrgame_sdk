/*
 * irrgamePlayer.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEPLAYER_H_
#define IRRGAMEPLAYER_H_

#include "core/IReferenceCounted.h"
#include "io/SPath.h"
#include "irrgameApp.h"

namespace irrgame
{
	namespace io
	{
		class IFileSystem;
	}

	class irrgameApp;

	class irrgamePlayer: public IReferenceCounted
	{
		public:

			//! Destructor
			virtual ~irrgamePlayer()
			{
			}

			//!
			virtual void readConfig(const io::path& file) = 0;

			virtual io::IFileSystem* getFileSystem() = 0;

			//			virtual void run(irrgameApp* application) = 0;

			//get application
	};

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer();
}

#endif /* IRRGAMEPLAYER_H_ */
