// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __S_MATERIAL_H_INCLUDED__
#define __S_MATERIAL_H_INCLUDED__

#include "video/utils/SharedVideoUtils.h"

#include "SMaterialLayer.h"
#include "video/color/SColor.h"

#include "EMaterialTypes.h"
#include "EMaterialFlags.h"
#include "EBlendFactor.h"
#include "EColorPlane.h"
#include "EColorMaterial.h"
#include "EAlphaSource.h"
#include "EComparisonFunc.h"
#include "EAntiAliasingMode.h"

namespace irrgame
{
	namespace video
	{
		class ITexture;

		//! Struct for holding parameters for a material renderer
		class SMaterial
		{
				/*
				 * Static methods
				 */
			public:

				//! Returns global const identity material
				static SMaterial& getIdentityMaterial();

			public:
				//! Default constructor. Creates a solid, lit material with white colors
				SMaterial();

				//! Copy constructor
				/** \param other Material to copy from. */
				SMaterial(const SMaterial& other);

				//! Assignment operator
				/** \param other Material to copy from. */
				SMaterial& operator=(const SMaterial& other);

				//! Gets the texture transformation matrix for level i
				/** \param i The desired level. Must not be larger than MATERIAL_MAX_TEXTURES.
				 \return Texture matrix for texture level i. */
				matrix4f& getTextureMatrix(u32 i);

				//! Gets the immutable texture transformation matrix for level i
				/** \param i The desired level.
				 \return Texture matrix for texture level i, or identity matrix for levels larger than MATERIAL_MAX_TEXTURES. */
				const matrix4f& getTextureMatrix(u32 i) const;

				//! Sets the i-th texture transformation matrix
				/** \param i The desired level.
				 \param mat Texture matrix for texture level i. */
				void setTextureMatrix(u32 i, const matrix4f& mat);

				//! Gets the i-th texture
				/** \param i The desired level.
				 \return Texture for texture level i, if defined, else 0. */
				ITexture* getTexture(u32 i) const;

				//! Sets the i-th texture
				/** If i>=MATERIAL_MAX_TEXTURES this setting will be ignored.
				 \param i The desired level.
				 \param tex Texture for texture level i. */
				void setTexture(u32 i, ITexture* tex);

				//! Sets the Material flag to the given value
				/** \param flag The flag to be set.
				 \param value The new value for the flag. */
				void setFlag(E_MATERIAL_FLAG flag, bool value);

				//! Gets the Material flag
				/** \param flag The flag to query.
				 \return The current value of the flag. */
				bool getFlag(E_MATERIAL_FLAG flag) const;

				//! Inequality operator
				/** \param b Material to compare to.
				 \return True if the materials differ, else false. */
				inline bool operator!=(const SMaterial& b) const;

				//! Equality operator
				/** \param b Material to compare to.
				 \return True if the materials are equal, else false. */
				inline bool operator==(const SMaterial& b) const;

				bool isTransparent() const;

			public:

				//! Texture layer array.
				SMaterialLayer TextureLayer[MaterialMaxTextures];

				//! Type of the material. Specifies how everything is blended together
				E_MATERIAL_TYPE MaterialType;

				//! How much ambient light (a global light) is reflected by this material.
				/** The default is full white, meaning objects are completely
				 globally illuminated. Reduce this if you want to see diffuse
				 or specular light effects. */
				SColor AmbientColor;

				//! How much diffuse light coming from a light source is reflected by this material.
				/** The default is full white. */
				SColor DiffuseColor;

				//! Light emitted by this material. Default is to emit no light.
				SColor EmissiveColor;

				//! How much specular light (highlights from a light) is reflected.
				/** The default is to reflect white specular light. See
				 SMaterial::Shininess on how to enable specular lights. */
				SColor SpecularColor;

				//! Value affecting the size of specular highlights.
				/** A value of 20 is common. If set to 0, no specular
				 highlights are being used. To activate, simply set the
				 shininess of a material to a value in the range [0.5;128]:
				 \code
				 sceneNode->getMaterial(0).Shininess = 20.0f;
				 \endcode

				 You can change the color of the highlights using
				 \code
				 sceneNode->getMaterial(0).SpecularColor.set(255,255,255,255);
				 \endcode

				 The specular color of the dynamic lights
				 (SLight::SpecularColor) will influence the the highlight color
				 too, but they are set to a useful value by default when
				 creating the light scene node. Here is a simple example on how
				 to use specular highlights:
				 \code
				 // load and display mesh
				 scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(
				 smgr->getMesh("data/faerie.md2"));
				 node->setMaterialTexture(0, driver->getTexture("data/Faerie2.pcx")); // set diffuse texture
				 node->setMaterialFlag(video::EMF_LIGHTING, true); // enable dynamic lighting
				 node->getMaterial(0).Shininess = 20.0f; // set size of specular highlights

				 // add white light
				 scene::ILightSceneNode* light = smgr->addLightSceneNode(0,
				 core::vector3df(5,5,5), video::SColorf(1.0f, 1.0f, 1.0f));
				 \endcode */
				f32 Shininess;

				//! Free parameter, dependent on the material type.
				/** Mostly ignored, used for example in EMT_PARALLAX_MAP_SOLID
				 and EMT_TRANSPARENT_ALPHA_CHANNEL. */
				f32 MaterialTypeParam;

				//! Second free parameter, dependent on the material type.
				/** Mostly ignored. */
				f32 MaterialTypeParam2;

				//! Thickness of non-3dimensional elements such as lines and points.
				f32 Thickness;

				//! Is the ZBuffer enabled? Default: ECFN_LESSEQUAL
				/** Values are from E_COMPARISON_FUNC. */
				u8 ZBuffer;

				//! Sets the antialiasing mode
				/** Values are chosen from E_ANTI_ALIASING_MODE. Default is
				 EAAM_SIMPLE|EAAM_LINE_SMOOTH, i.e. simple multi-sample
				 anti-aliasing and lime smoothing is enabled. */
				u8 AntiAliasing;

				//! Defines the enabled color planes
				/** Values are defined as or'ed values of the E_COLOR_PLANE enum.
				 Only enabled color planes will be rendered to the current render
				 target. Typical use is to disable all colors when rendering only to
				 depth or stencil buffer, or using Red and Green for Stereo rendering. */
				u8 ColorMask :4;

				//! Defines the interpretation of vertex color in the lighting equation
				/** Values should be chosen from E_COLOR_MATERIAL.
				 When lighting is enabled, vertex color can be used instead of the
				 material values for light modulation. This allows to easily change e.g. the
				 diffuse light behavior of each face. The default, ECM_DIFFUSE, will result in
				 a very similar rendering as with lighting turned off, just with light shading. */
				u8 ColorMaterial :3;

				//! Draw as wireframe or filled triangles? Default: false
				/** The user can access a material flag using
				 \code material.Wireframe=true \endcode
				 or \code material.setFlag(EMF_WIREFRAME, true); \endcode */
				bool Wireframe :1;

				//! Draw as point cloud or filled triangles? Default: false
				bool PointCloud :1;

				//! Flat or Gouraud shading? Default: true
				bool GouraudShading :1;

				//! Will this material be lighted? Default: true
				bool Lighting :1;

				//! Is the zbuffer writeable or is it read-only. Default: true.
				/** This flag is forced to false if the MaterialType is a
				 transparent type and the scene parameter
				 ALLOW_ZWRITE_ON_TRANSPARENT is not set. */
				bool ZWriteEnable :1;

				//! Is backface culling enabled? Default: true
				bool BackfaceCulling :1;

				//! Is frontface culling enabled? Default: false
				bool FrontfaceCulling :1;

				//! Is fog enabled? Default: false
				bool FogEnable :1;

				//! Should normals be normalized?
				/** Always use this if the mesh lit and scaled. Default: false */
				bool NormalizeNormals :1;
		};
	} // end namespace video
} // end namespace irrgame

#endif
