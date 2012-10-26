/*
 * EColorMaterial.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef ECOLORMATERIAL_H_
#define ECOLORMATERIAL_H_

namespace irrgame
{

	namespace video
	{

		//! These flags allow to define the interpretation of vertex color when lighting is enabled
		/** Without lighting being enabled the vertex color is the only value defining the fragment color.
		 Once lighting is enabled, the four values for diffuse, ambient, emissive, and specular take over.
		 With these flags it is possible to define which lighting factor shall be defined by the vertex color
		 instead of the lighting factor which is the same for all faces of that material.
		 The default is to use vertex color for the diffuse value, another pretty common value is to use
		 vertex color for both diffuse and ambient factor. */
		enum E_COLOR_MATERIAL
		{
			//! Don't use vertex color for lighting
			ECM_NONE = 0,
			//! Use vertex color for diffuse light, this is default
			ECM_DIFFUSE,
			//! Use vertex color for ambient light
			ECM_AMBIENT,
			//! Use vertex color for emissive light
			ECM_EMISSIVE,
			//! Use vertex color for specular light
			ECM_SPECULAR,
			//! Use vertex color for both diffuse and ambient light
			ECM_DIFFUSE_AND_AMBIENT
		};

	}  // namespace video

}  // namespace irrgame

#endif /* ECOLORMATERIAL_H_ */
