// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_FPSCOUNTER_H_INCLUDED__
#define __C_FPSCOUNTER_H_INCLUDED__

#include "video/IFPSCounter.h"

namespace irrgame
{
	namespace video
	{

		class CFPSCounter: public IFPSCounter
		{
			public:
				//! Default constructor
				CFPSCounter();

				//! Destructor
				virtual ~CFPSCounter();

				//! returns current fps
				/** This value is updated approximately every 1.5 seconds and
				 is only intended to provide a rough guide to the average frame
				 rate. It is not suitable for use in performing timing
				 calculations or framerate independent movement.
				 \return Approximate amount of frames per second drawn. */
				s32 getFPS() const;

				//! returns primitive count
				u32 getPrimitive() const;

				//! returns average primitive count of last period
				u32 getPrimitiveAverage() const;

				//! returns accumulated primitive count since start
				u32 getPrimitiveTotal() const;

				//! to be called every frame
				void registerFrame(u32 now, u32 primitive);

			private:

				s32 FPS;
				u32 Primitive;
				u32 StartTime;

				u32 FramesCounted;
				u32 PrimitivesCounted;
				u32 PrimitiveAverage;
				u32 PrimitiveTotal;
		};

	} // end namespace video
} // end namespace irr

#endif 

