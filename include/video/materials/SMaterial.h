// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __S_MATERIAL_H_INCLUDED__
#define __S_MATERIAL_H_INCLUDED__

#include "video/videoutils.h"

#include "video/SColor.h"
#include "core/irrgamemath.h"

#include "SMaterialLayer.h"

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
			public:
				//! Default constructor. Creates a solid, lit material with white colors
				SMaterial() :
						MaterialType(EMT_SOLID), AmbientColor(255, 255, 255,
								255), DiffuseColor(255, 255, 255, 255), EmissiveColor(
								0, 0, 0, 0), SpecularColor(255, 255, 255, 255), Shininess(
								0.0f), MaterialTypeParam(0.0f), MaterialTypeParam2(
								0.0f), Thickness(1.0f), ZBuffer(ECFN_LESSEQUAL), AntiAliasing(
								EAAM_SIMPLE), ColorMask(ECP_ALL), ColorMaterial(
								ECM_DIFFUSE), Wireframe(false), PointCloud(
								false), GouraudShading(true), Lighting(true), ZWriteEnable(
								true), BackfaceCulling(true), FrontfaceCulling(
								false), FogEnable(false), NormalizeNormals(
								false)
				{
				}

				//! Copy constructor
				/** \param other Material to copy from. */
				SMaterial(const SMaterial& other)
				{
					// These pointers are checked during assignment
					for (u32 i = 0; i < MaterialMaxTextures; ++i)
						TextureLayer[i].TextureMatrix = 0;
					*this = other;
				}

				//! Assignment operator
				/** \param other Material to copy from. */
				SMaterial& operator=(const SMaterial& other)
				{
					// Check for self-assignment!
					if (this == &other)
						return *this;

					MaterialType = other.MaterialType;

					AmbientColor = other.AmbientColor;
					DiffuseColor = other.DiffuseColor;
					EmissiveColor = other.EmissiveColor;
					SpecularColor = other.SpecularColor;
					Shininess = other.Shininess;
					MaterialTypeParam = other.MaterialTypeParam;
					MaterialTypeParam2 = other.MaterialTypeParam2;
					Thickness = other.Thickness;
					for (u32 i = 0; i < MaterialMaxTextures; ++i)
					{
						TextureLayer[i] = other.TextureLayer[i];
					}

					Wireframe = other.Wireframe;
					PointCloud = other.PointCloud;
					GouraudShading = other.GouraudShading;
					Lighting = other.Lighting;
					ZWriteEnable = other.ZWriteEnable;
					BackfaceCulling = other.BackfaceCulling;
					FrontfaceCulling = other.FrontfaceCulling;
					FogEnable = other.FogEnable;
					NormalizeNormals = other.NormalizeNormals;
					ZBuffer = other.ZBuffer;
					AntiAliasing = other.AntiAliasing;
					ColorMask = other.ColorMask;
					ColorMaterial = other.ColorMaterial;

					return *this;
				}

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

				//! Gets the texture transformation matrix for level i
				/** \param i The desired level. Must not be larger than MATERIAL_MAX_TEXTURES.
				 \return Texture matrix for texture level i. */
				matrix4& getTextureMatrix(u32 i)
				{
					return TextureLayer[i].getTextureMatrix();
				}

				//! Gets the immutable texture transformation matrix for level i
				/** \param i The desired level.
				 \return Texture matrix for texture level i, or identity matrix for levels larger than MATERIAL_MAX_TEXTURES. */
				const matrix4& getTextureMatrix(u32 i) const
				{
					if (i < MaterialMaxTextures)
						return TextureLayer[i].getTextureMatrix();
					else
						return IdentityMatrix;
				}

				//! Sets the i-th texture transformation matrix
				/** \param i The desired level.
				 \param mat Texture matrix for texture level i. */
				void setTextureMatrix(u32 i, const matrix4& mat)
				{
					IRR_ASSERT(i < MaterialMaxTextures);

					TextureLayer[i].setTextureMatrix(mat);
				}

				//! Gets the i-th texture
				/** \param i The desired level.
				 \return Texture for texture level i, if defined, else 0. */
				ITexture* getTexture(u32 i) const
				{
					return i < MaterialMaxTextures ? TextureLayer[i].Texture : 0;
				}

				//! Sets the i-th texture
				/** If i>=MATERIAL_MAX_TEXTURES this setting will be ignored.
				 \param i The desired level.
				 \param tex Texture for texture level i. */
				void setTexture(u32 i, ITexture* tex)
				{
					IRR_ASSERT(i < MaterialMaxTextures);

					TextureLayer[i].Texture = tex;
				}

				//! Sets the Material flag to the given value
				/** \param flag The flag to be set.
				 \param value The new value for the flag. */
				void setFlag(E_MATERIAL_FLAG flag, bool value)
				{
					switch (flag)
					{
						case EMF_WIREFRAME:
							Wireframe = value;
							break;
						case EMF_POINTCLOUD:
							PointCloud = value;
							break;
						case EMF_GOURAUD_SHADING:
							GouraudShading = value;
							break;
						case EMF_LIGHTING:
							Lighting = value;
							break;
						case EMF_ZBUFFER:
							ZBuffer = value;
							break;
						case EMF_ZWRITE_ENABLE:
							ZWriteEnable = value;
							break;
						case EMF_BACK_FACE_CULLING:
							BackfaceCulling = value;
							break;
						case EMF_FRONT_FACE_CULLING:
							FrontfaceCulling = value;
							break;
						case EMF_BILINEAR_FILTER:
						{
							for (u32 i = 0; i < MaterialMaxTextures; ++i)
								TextureLayer[i].BilinearFilter = value;
						}
							break;
						case EMF_TRILINEAR_FILTER:
						{
							for (u32 i = 0; i < MaterialMaxTextures; ++i)
								TextureLayer[i].TrilinearFilter = value;
						}
							break;
						case EMF_ANISOTROPIC_FILTER:
						{
							if (value)
								for (u32 i = 0; i < MaterialMaxTextures; ++i)
									TextureLayer[i].AnisotropicFilter = 0xFF;
							else
								for (u32 i = 0; i < MaterialMaxTextures; ++i)
									TextureLayer[i].AnisotropicFilter = 0;
						}
							break;
						case EMF_FOG_ENABLE:
							FogEnable = value;
							break;
						case EMF_NORMALIZE_NORMALS:
							NormalizeNormals = value;
							break;
						case EMF_TEXTURE_WRAP:
						{
							for (u32 i = 0; i < MaterialMaxTextures; ++i)
							{
								TextureLayer[i].TextureWrapU =
										(E_TEXTURE_CLAMP) value;
								TextureLayer[i].TextureWrapV =
										(E_TEXTURE_CLAMP) value;
							}
						}
							break;
						case EMF_ANTI_ALIASING:
							AntiAliasing = value ? EAAM_SIMPLE : EAAM_OFF;
							break;
						case EMF_COLOR_MASK:
							ColorMask = value ? ECP_ALL : ECP_NONE;
							break;
						case EMF_COLOR_MATERIAL:
							ColorMaterial = value ? ECM_DIFFUSE : ECM_NONE;
							break;
						default:
							break;
					}
				}

				//! Gets the Material flag
				/** \param flag The flag to query.
				 \return The current value of the flag. */
				bool getFlag(E_MATERIAL_FLAG flag) const
				{
					switch (flag)
					{
						case EMF_WIREFRAME:
							return Wireframe;
						case EMF_POINTCLOUD:
							return PointCloud;
						case EMF_GOURAUD_SHADING:
							return GouraudShading;
						case EMF_LIGHTING:
							return Lighting;
						case EMF_ZBUFFER:
							return ZBuffer != ECFN_NEVER;
						case EMF_ZWRITE_ENABLE:
							return ZWriteEnable;
						case EMF_BACK_FACE_CULLING:
							return BackfaceCulling;
						case EMF_FRONT_FACE_CULLING:
							return FrontfaceCulling;
						case EMF_BILINEAR_FILTER:
							return TextureLayer[0].BilinearFilter;
						case EMF_TRILINEAR_FILTER:
							return TextureLayer[0].TrilinearFilter;
						case EMF_ANISOTROPIC_FILTER:
							return TextureLayer[0].AnisotropicFilter != 0;
						case EMF_FOG_ENABLE:
							return FogEnable;
						case EMF_NORMALIZE_NORMALS:
							return NormalizeNormals;
						case EMF_TEXTURE_WRAP:
							return !(TextureLayer[0].TextureWrapU
									|| TextureLayer[0].TextureWrapV
									|| TextureLayer[1].TextureWrapU
									|| TextureLayer[1].TextureWrapV
									|| TextureLayer[2].TextureWrapU
									|| TextureLayer[2].TextureWrapV
									|| TextureLayer[3].TextureWrapU
									|| TextureLayer[3].TextureWrapV);
						case EMF_ANTI_ALIASING:
							return (AntiAliasing == 1);
						case EMF_COLOR_MASK:
							return (ColorMask != ECP_NONE);
						case EMF_COLOR_MATERIAL:
							return (ColorMaterial != ECM_NONE);
					}

					return false;
				}

				//! Inequality operator
				/** \param b Material to compare to.
				 \return True if the materials differ, else false. */
				inline bool operator!=(const SMaterial& b) const
				{
					bool different = MaterialType != b.MaterialType
							|| AmbientColor != b.AmbientColor
							|| DiffuseColor != b.DiffuseColor
							|| EmissiveColor != b.EmissiveColor
							|| SpecularColor != b.SpecularColor
							|| Shininess != b.Shininess
							|| MaterialTypeParam != b.MaterialTypeParam
							|| MaterialTypeParam2 != b.MaterialTypeParam2
							|| Thickness != b.Thickness
							|| Wireframe != b.Wireframe
							|| PointCloud != b.PointCloud
							|| GouraudShading != b.GouraudShading
							|| Lighting != b.Lighting || ZBuffer != b.ZBuffer
							|| ZWriteEnable != b.ZWriteEnable
							|| BackfaceCulling != b.BackfaceCulling
							|| FrontfaceCulling != b.FrontfaceCulling
							|| FogEnable != b.FogEnable
							|| NormalizeNormals != b.NormalizeNormals
							|| AntiAliasing != b.AntiAliasing
							|| ColorMask != b.ColorMask
							|| ColorMaterial != b.ColorMaterial;
					for (u32 i = 0; (i < MaterialMaxTextures) && !different;
							++i)
					{
						different |= (TextureLayer[i] != b.TextureLayer[i]);
					}
					return different;
				}

				//! Equality operator
				/** \param b Material to compare to.
				 \return True if the materials are equal, else false. */
				inline bool operator==(const SMaterial& b) const
				{
					return !(b != *this);
				}

				bool isTransparent() const
				{
					return MaterialType == EMT_TRANSPARENT_ADD_COLOR
							|| MaterialType == EMT_TRANSPARENT_ALPHA_CHANNEL
							|| MaterialType == EMT_TRANSPARENT_VERTEX_ALPHA
							|| MaterialType
									== EMT_TRANSPARENT_REFLECTION_2_LAYER;
				}
		};

		//TODO: make it static
		extern SMaterial IdentityMaterial;

	} // end namespace video
} // end namespace irrgame

#endif
