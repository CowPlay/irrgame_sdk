/*
 * irrgamePlayer.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEPLAYER_H_
#define IRRGAMEPLAYER_H_

#include "core/irrgamebase.h"
#include "io/SPath.h"
#include "io/config/IPlayerConfigReader.h"
#include "irrgameApp.h"

namespace irrgame
{
	namespace events
	{
		class IUserEventHandler;
	}  // namespace events

	namespace io
	{
		class IFileSystem;
	}  // namespace io

	namespace scene
	{
		class ISceneManager;
	}  // namespace scene

	namespace video
	{
		class IVideoDriver;
	}  // namespace video

	class irrgameApp;

	class irrgamePlayer: public IReferenceCounted
	{
		public:

			//! Destructor
			virtual ~irrgamePlayer()
			{
			}

			//! Gets pointer to config reader
			//! @return - pointer to config reader
			virtual io::IPlayerConfigReader* getConfigReader() = 0;

			virtual scene::ISceneManager* getSceneManager() = 0;

			virtual video::IVideoDriver* getVideoDriver() = 0;

			//! Returns user event receiver
			/* If you want handle any user event - you must work with this object.
			 * */
			virtual events::IUserEventHandler* getUserEventsHandler() = 0;

			virtual void run(irrgameApp* application) = 0;

			//! This func need for flush OpenGL context
			virtual void flush() = 0;

			//get application

		protected:

			//! Run player internal. Must be overriden in every realization of player.
			//! Handle user events in this func
			virtual bool runInternal() = 0;
	};

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer();
}

#endif /* IRRGAMEPLAYER_H_ */
