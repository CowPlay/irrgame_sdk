/*
 * IVideoDriver.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IVIDEODRIVER_H_
#define IVIDEODRIVER_H_

#include "core/engine/IReferenceCounted.h"
#include "video/material/IMaterialRenderer.h"
#include "video/color/SColor.h"
#include "video/fog/EFogType.h"
#include "video/IFPSCounter.h"
#include "EVideoDriverFeatures.h"

namespace irrgame
{

	class irrgamePlayer;

	namespace video
	{
		class ITexture;

		class IVideoDriver: public IReferenceCounted
		{
			public:
				//! Destructor
				virtual ~IVideoDriver()
				{
				}

				//! Applications must call this method before performing any rendering.
				/** This method can clear the back- and the z-buffer.
				 \param color The color used for back buffer clearing
				 \param backBuffer Specifies if the back buffer should be
				 cleared, which means that the screen is filled with the color
				 specified. If this parameter is false, the back buffer will
				 not be cleared and the color parameter is ignored.
				 \param zBuffer Specifies if the depth buffer (z buffer) should
				 be cleared. It is not nesesarry to do so if only 2d drawing is
				 used.
				 \param sourceRect Pointer to a rectangle defining the source
				 rectangle of the area to be presented. Set to null to present
				 everything. Note: not implemented in all devices.
				 */
				virtual void beginScene(
						SColor color = SColor(255, 100, 101, 140),
						bool backBuffer = true, bool zBuffer = true,
						recti* sourceRect = 0) = 0;

				//! Presents the rendered image to the screen.
				/** Applications must call this method after performing any
				 rendering.
				 */
				virtual void endScene() = 0;

				//! Returns FPS counter.
				virtual IFPSCounter* getFPSCounter() const = 0;

				//! Get access to a named texture.
				/** Loads the texture from disk if it is not
				 already loaded and generates mipmap levels if desired.
				 Texture loading can be influenced using the
				 setTextureCreationFlag() method. The texture can be in several
				 imageformats, such as BMP, JPG, TGA, PCX, PNG, and PSD.
				 \param filename Filename of the texture to be loaded.
				 \return Pointer to the texture, or 0 if the texture
				 could not be loaded. This pointer should not be dropped. See
				 IReferenceCounted::drop() for more information. */
//				virtual ITexture* getTexture(const stringc& path) = 0;
//! Sets the fog mode.
				/** These are global values attached to each 3d object rendered,
				 which has the fog flag enabled in its material.
				 \param color Color of the fog
				 \param fogType Type of fog used
				 \param start Only used in linear fog mode (linearFog=true).
				 Specifies where fog starts.
				 \param end Only used in linear fog mode (linearFog=true).
				 Specifies where fog ends.
				 \param density Only used in exponential fog mode
				 (linearFog=false). Must be a value between 0 and 1.
				 \param pixelFog Set this to false for vertex fog, and true if
				 you want per-pixel fog.
				 \param rangeFog Set this to true to enable range-based vertex
				 fog. The distance from the viewer is used to compute the fog,
				 not the z-coordinate. This is better, but slower. This might not
				 be available with all drivers and fog settings. */
				virtual void setFog(SColor color = SColor(0, 255, 255, 255),
						EFogType fogType = EFT_FOG_LINEAR, f32 start = 50.0f,
						f32 end = 100.0f, f32 density = 0.01f, bool pixelFog =
								false, bool rangeFog = false) = 0;

				//! Adds a new material renderer to the video device.
				/** Use this method to extend the VideoDriver with new material
				 types. To extend the engine using this method do the following:
				 Derive a class from IMaterialRenderer and override the methods
				 you need. For setting the right renderstates, you can try to
				 get a pointer to the real rendering device using
				 IVideoDriver::getExposedVideoData(). Add your class with
				 IVideoDriver::addMaterialRenderer(). To use an object being
				 displayed with your new material, set the MaterialType member of
				 the SMaterial struct to the value returned by this method.
				 If you simply want to create a new material using vertex and/or
				 pixel shaders it would be easier to use the
				 video::IGPUProgrammingServices interface which you can get
				 using the getGPUProgrammingServices() method.
				 \param renderer A pointer to the new renderer.
				 \return The number of the material type which can be set in
				 SMaterial::MaterialType to use the renderer. -1 is returned if
				 an error occured. For example if you tried to add an material
				 renderer to the software renderer or the null device, which do
				 not accept material renderers. */
				virtual s32 addMaterialRenderer(
						IMaterialRenderer* renderer) = 0;
		};

		//! VideoDriver creator
		IVideoDriver* createVideoDriver(irrgamePlayer* player);

	}
}

#endif /* IVIDEODRIVER_H_ */
