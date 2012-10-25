// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_VIDEO_MODE_LIST_H_INCLUDED__
#define __IRR_C_VIDEO_MODE_LIST_H_INCLUDED__

#include "video/IVideoModeList.h"
#include "core/irrgameshapes.h"
#include "core/irrgamecollections.h"

namespace irrgame
{
	namespace video
	{

		struct SVideoMode
		{
			public:
				dimension2du Size;
				s32 Depth;

			public:
				bool operator==(const SVideoMode& other) const;
				bool operator <(const SVideoMode& other) const;
		};
		class CVideoModeList: public IVideoModeList
		{
			public:

				//! Default constructor
				CVideoModeList();

				//! Destructor
				virtual ~CVideoModeList();
//
//				//! Gets amount of video modes in the list.
//				virtual s32 getVideoModeCount() const;
//
//				//! Returns the screen size of a video mode in pixels.
//				virtual core::dimension2d<u32> getVideoModeResolution(
//						s32 modeNumber) const;
//
//				//! Returns the screen size of an optimal video mode in pixels.
//				virtual core::dimension2d<u32> getVideoModeResolution(
//						const core::dimension2d<u32>& minSize,
//						const core::dimension2d<u32>& maxSize) const;
//
//				//! Returns the pixel depth of a video mode in bits.
//				virtual s32 getVideoModeDepth(s32 modeNumber) const;
//
//				//! Returns current desktop screen resolution.
//				virtual const core::dimension2d<u32>& getDesktopResolution() const;
//
//				//! Returns the pixel depth of a video mode in bits.
//				virtual s32 getDesktopDepth() const;
//
//				//! adds a new mode to the list
//				void addMode(const core::dimension2d<u32>& size, s32 depth);
//
//				void setDesktop(s32 desktopDepth,
//						const core::dimension2d<u32>& desktopSize);
//
//			private:
//
//
//
//				core::array<SVideoMode> VideoModes;
//				SVideoMode Desktop;
		};

	} // end namespace video
} // end namespace irrgame

#endif
