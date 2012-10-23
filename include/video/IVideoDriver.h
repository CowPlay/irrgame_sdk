/*
 * IVideoDriver.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IVIDEODRIVER_H_
#define IVIDEODRIVER_H_

#include "core/engine/IReferenceCounted.h"
#include "core/irrgameshapes.h"
#include "SColor.h"
#include "EVideoDriverFeatures.h"
#include "core/irrgameshapes.h"
#include "video/IFPSCounter.h"

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
				virtual void beginScene(SColor color = SColor(255, 0, 0, 0),
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
		};

		//! VideoDriver creator
		IVideoDriver* createVideoDriver(irrgamePlayer* player);

	}
}

#endif /* IVIDEODRIVER_H_ */
