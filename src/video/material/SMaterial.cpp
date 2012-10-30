/*
 * SMaterial.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#include "video/material/SMaterial.h"

namespace irrgame
{

	namespace video
	{

		//! Returns global const identity material
		SMaterial& SMaterial::getIdentityMaterial()
		{
			static SMaterial instance;
			return instance;
		}

		//! Default constructor. Creates a solid, lit material with white colors
		SMaterial::SMaterial() :
				MaterialType(EMT_SOLID), AmbientColor(255, 255, 255, 255), DiffuseColor(
						255, 255, 255, 255), EmissiveColor(0, 0, 0, 0), SpecularColor(
						255, 255, 255, 255), Shininess(0.0f), MaterialTypeParam(
						0.0f), MaterialTypeParam2(0.0f), Thickness(1.0f), ZBuffer(
						ECFN_LESSEQUAL), AntiAliasing(EAAM_SIMPLE), ColorMask(
						ECP_ALL), ColorMaterial(ECM_DIFFUSE), Wireframe(false), PointCloud(
						false), GouraudShading(true), Lighting(true), ZWriteEnable(
						true), BackfaceCulling(true), FrontfaceCulling(false), FogEnable(
						false), NormalizeNormals(false)
		{
		}

		//! Copy constructor
		SMaterial::SMaterial(const SMaterial& other)
		{
			// These pointers are checked during assignment
			for (u32 i = 0; i < MaterialMaxTextures; ++i)
				TextureLayer[i].TextureMatrix = 0;
			*this = other;
		}

		//! Assignment operator
		SMaterial& SMaterial::operator=(const SMaterial& other)
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

		//! Gets the texture transformation matrix for level i
		matrix4f& SMaterial::getTextureMatrix(u32 i)
		{
			return TextureLayer[i].getTextureMatrix();
		}

		//! Gets the immutable texture transformation matrix for level i
		const matrix4f& SMaterial::getTextureMatrix(u32 i) const
		{
			if (i < MaterialMaxTextures)
				return TextureLayer[i].getTextureMatrix();
			else
				return matrix4f::getIdentityMatrix();
		}

		//! Sets the i-th texture transformation matrix
		void SMaterial::setTextureMatrix(u32 i, const matrix4f& mat)
		{
			IRR_ASSERT(i < MaterialMaxTextures);

			TextureLayer[i].setTextureMatrix(mat);
		}

		//! Gets the i-th texture
		ITexture* SMaterial::getTexture(u32 i) const
		{
			return i < MaterialMaxTextures ? TextureLayer[i].Texture : 0;
		}

		//! Sets the i-th texture
		void SMaterial::setTexture(u32 i, ITexture* tex)
		{
			IRR_ASSERT(i < MaterialMaxTextures);

			TextureLayer[i].Texture = tex;
		}

		//! Sets the Material flag to the given value
		void SMaterial::setFlag(E_MATERIAL_FLAG flag, bool value)
		{
			switch (flag)
			{
				case EMF_WIREFRAME:
				{
					Wireframe = value;
					break;
				}
				case EMF_POINTCLOUD:
				{
					PointCloud = value;
					break;
				}
				case EMF_GOURAUD_SHADING:
				{
					GouraudShading = value;
					break;
				}
				case EMF_LIGHTING:
				{
					Lighting = value;
					break;
				}
				case EMF_ZBUFFER:
				{
					ZBuffer = value;
					break;
				}
				case EMF_ZWRITE_ENABLE:
				{
					ZWriteEnable = value;
					break;
				}
				case EMF_BACK_FACE_CULLING:
				{
					BackfaceCulling = value;
					break;
				}
				case EMF_FRONT_FACE_CULLING:
				{
					FrontfaceCulling = value;
					break;
				}
				case EMF_BILINEAR_FILTER:
				{
					for (u32 i = 0; i < MaterialMaxTextures; ++i)
					{
						TextureLayer[i].BilinearFilter = value;
					}

					break;
				}
				case EMF_TRILINEAR_FILTER:
				{
					for (u32 i = 0; i < MaterialMaxTextures; ++i)
					{
						TextureLayer[i].TrilinearFilter = value;
					}

					break;
				}
				case EMF_ANISOTROPIC_FILTER:
				{
					if (value)
					{
						for (u32 i = 0; i < MaterialMaxTextures; ++i)
						{
							TextureLayer[i].AnisotropicFilter = 0xFF;
						}
					}
					else
					{
						for (u32 i = 0; i < MaterialMaxTextures; ++i)
						{
							TextureLayer[i].AnisotropicFilter = 0;
						}
					}
					break;
				}
				case EMF_FOG_ENABLE:
				{
					FogEnable = value;
					break;
				}
				case EMF_NORMALIZE_NORMALS:
				{
					NormalizeNormals = value;
					break;
				}
				case EMF_TEXTURE_WRAP:
				{
					for (u32 i = 0; i < MaterialMaxTextures; ++i)
					{
						TextureLayer[i].TextureWrapU = (E_TEXTURE_CLAMP) value;
						TextureLayer[i].TextureWrapV = (E_TEXTURE_CLAMP) value;
					}

					break;
				}
				case EMF_ANTI_ALIASING:
				{
					AntiAliasing = value ? EAAM_SIMPLE : EAAM_OFF;
					break;
				}
				case EMF_COLOR_MASK:
				{
					ColorMask = value ? ECP_ALL : ECP_NONE;
					break;
				}
				case EMF_COLOR_MATERIAL:
				{
					ColorMaterial = value ? ECM_DIFFUSE : ECM_NONE;
					break;
				}
				default:
				{
					//Not implemented
					IRR_ASSERT(false);
					break;
				}
			}
		}

		//! Gets the Material flag
		bool SMaterial::getFlag(E_MATERIAL_FLAG flag) const
		{
			bool result = false;

			switch (flag)
			{
				case EMF_WIREFRAME:
				{
					result = Wireframe;
					break;
				}
				case EMF_POINTCLOUD:
				{
					result = PointCloud;
					break;
				}
				case EMF_GOURAUD_SHADING:
				{
					result = GouraudShading;
					break;
				}
				case EMF_LIGHTING:
				{
					result = Lighting;
					break;
				}
				case EMF_ZBUFFER:
				{
					result = ZBuffer != ECFN_NEVER;
					break;
				}
				case EMF_ZWRITE_ENABLE:
				{
					result = ZWriteEnable;
					break;
				}
				case EMF_BACK_FACE_CULLING:
				{
					result = BackfaceCulling;
					break;
				}
				case EMF_FRONT_FACE_CULLING:
				{
					result = FrontfaceCulling;
					break;
				}
				case EMF_BILINEAR_FILTER:
				{
					result = TextureLayer[0].BilinearFilter;
					break;
				}
				case EMF_TRILINEAR_FILTER:
				{
					result = TextureLayer[0].TrilinearFilter;
					break;
				}
				case EMF_ANISOTROPIC_FILTER:
				{
					result = TextureLayer[0].AnisotropicFilter != 0;
					break;
				}
				case EMF_FOG_ENABLE:
				{
					result = FogEnable;
					break;
				}
				case EMF_NORMALIZE_NORMALS:
				{
					result = NormalizeNormals;
					break;
				}
				case EMF_TEXTURE_WRAP:
				{
					result = !(TextureLayer[0].TextureWrapU
							|| TextureLayer[0].TextureWrapV
							|| TextureLayer[1].TextureWrapU
							|| TextureLayer[1].TextureWrapV
							|| TextureLayer[2].TextureWrapU
							|| TextureLayer[2].TextureWrapV
							|| TextureLayer[3].TextureWrapU
							|| TextureLayer[3].TextureWrapV);
					break;
				}
				case EMF_ANTI_ALIASING:
				{
					result = (AntiAliasing == 1);
					break;
				}
				case EMF_COLOR_MASK:
				{
					result = (ColorMask != ECP_NONE);
					break;
				}
				case EMF_COLOR_MATERIAL:
				{
					result = (ColorMaterial != ECM_NONE);
					break;
				}
				default:
				{
					//Not implemented
					IRR_ASSERT(false);
					break;
				}
			}

			return result;
		}

		//! Inequality operator
		inline bool SMaterial::operator!=(const SMaterial& b) const
		{
			bool different = MaterialType != b.MaterialType
					|| AmbientColor != b.AmbientColor
					|| DiffuseColor != b.DiffuseColor
					|| EmissiveColor != b.EmissiveColor
					|| SpecularColor != b.SpecularColor
					|| Shininess != b.Shininess
					|| MaterialTypeParam != b.MaterialTypeParam
					|| MaterialTypeParam2 != b.MaterialTypeParam2
					|| Thickness != b.Thickness || Wireframe != b.Wireframe
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

			for (u32 i = 0; (i < MaterialMaxTextures) && !different; ++i)
			{
				different |= (TextureLayer[i] != b.TextureLayer[i]);
			}

			return different;
		}

		//! Equality operator
		inline bool SMaterial::operator==(const SMaterial& b) const
		{
			return !(b != *this);
		}

		bool SMaterial::isTransparent() const
		{
			return MaterialType == EMT_TRANSPARENT_ADD_COLOR
					|| MaterialType == EMT_TRANSPARENT_ALPHA_CHANNEL
					|| MaterialType == EMT_TRANSPARENT_VERTEX_ALPHA
					|| MaterialType == EMT_TRANSPARENT_REFLECTION_2_LAYER;
		}

	}  // namespace video

}  // namespace irrgame
