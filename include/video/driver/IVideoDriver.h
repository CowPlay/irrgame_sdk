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
#include "video/fog/FogEntry.h"
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
				 \param fog - instance which contains fog params */
				virtual void setFog(FogEntry* value) = 0;

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

				//! Sets a new render target.
				/** This will only work if the driver supports the
				 EVDF_RENDER_TO_TARGET feature, which can be queried with
				 queryFeature(). Usually, rendering to textures is done in this
				 way:
				 \code
				 // create render target
				 ITexture* target = driver->addRenderTargetTexture(core::dimension2d<u32>(128,128), "rtt1");

				 // ...

				 driver->setRenderTarget(target); // set render target
				 // .. draw stuff here
				 driver->setRenderTarget(0); // set previous render target
				 \endcode
				 Please note that you cannot render 3D or 2D geometry with a
				 render target as texture on it when you are rendering the scene
				 into this render target at the same time. It is usually only
				 possible to render into a texture between the
				 IVideoDriver::beginScene() and endScene() method calls.
				 \param texture New render target. Must be a texture created with
				 IVideoDriver::addRenderTargetTexture(). If set to 0, it sets
				 the previous render target which was set before the last
				 setRenderTarget() call.
				 \param clearBackBuffer Clears the backbuffer of the render
				 target with the color parameter
				 \param clearZBuffer Clears the zBuffer of the rendertarget.
				 Note that because the frame buffer may share the zbuffer with
				 the rendertarget, its zbuffer might be partially cleared too
				 by this.
				 \param color The background color for the render target.
				 \return True if sucessful and false if not. */
				virtual bool setRenderTarget(video::ITexture* texture,
						bool clearBackBuffer = true, bool clearZBuffer = true,
						SColor color = video::SColor(0, 0, 0, 0)) =0;

				//! Draws a pixel.
				/** \param x The x-position of the pixel.
				 \param y The y-position of the pixel.
				 \param color Color of the pixel to draw. */
				virtual void drawPixel(u32 x, u32 y, const SColor& color) = 0;

				//! Draws a 2d image using a color
				/** (if color is other than
				 Color(255,255,255,255)) and the alpha channel of the texture.
				 \param texture Texture to be drawn.
				 \param destPos Upper left 2d destination position where the
				 image will be drawn.
				 \param sourceRect Source rectangle in the image.
				 \param clipRect Pointer to rectangle on the screen where the
				 image is clipped to.
				 If this pointer is NULL the image is not clipped.
				 \param color Color with which the image is drawn. If the color
				 equals Color(255,255,255,255) it is ignored. Note that the
				 alpha component is used: If alpha is other than 255, the image
				 will be transparent.
				 \param useAlphaChannelOfTexture: If true, the alpha channel of
				 the texture is used to draw the image.*/
				virtual void draw2DImage(const video::ITexture* texture,
						const vector2di& destPos, const recti& sourceRect,
						const recti* clipRect = 0,
						SColor color = SColor(255, 255, 255, 255),
						bool useAlphaChannelOfTexture = false) = 0;

				//! Get the size of the screen or render window.
				/** \return Size of screen or render window. */
				virtual const dimension2du& getScreenSize() const = 0;

				//! Get the size of the current render target
				/** This method will return the screen size if the driver
				 doesn't support render to texture, or if the current render
				 target is the screen.
				 \return Size of render target or screen/window */
				virtual const dimension2du& getCurrentRenderTargetSize() const = 0;

				//! Returns true if video driver have errors.
				virtual bool haveError() const = 0;
		};

		//! VideoDriver creator
		IVideoDriver* createVideoDriver(irrgamePlayer* player);

	}
}

#endif /* IVIDEODRIVER_H_ */
