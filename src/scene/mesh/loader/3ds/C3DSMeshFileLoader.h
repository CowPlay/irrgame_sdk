//// Copyright (C) 2002-2009 Nikolaus Gebhardt
//// This file is part of the "Irrlicht Engine".
//// For conditions of distribution and use, see copyright notice in irrlicht.h
//
//#ifndef __C_3DS_MESH_FILE_LOADER_H_INCLUDED__
//#define __C_3DS_MESH_FILE_LOADER_H_INCLUDED__
//
//#include "IMeshLoader.h"
//#include "IFileSystem.h"
//#include "ISceneManager.h"
//#include "irrString.h"
//#include "SMesh.h"
//#include "matrix4.h"
//
//namespace irr
//{
//	namespace scene
//	{
//
////! Meshloader capable of loading 3ds meshes.
//		class C3DSMeshFileLoader: public IMeshLoader
//		{
//			public:
//
//				//! Constructor
//				C3DSMeshFileLoader(ISceneManager* smgr, io::IFileSystem* fs);
//
//				//! destructor
//				virtual ~C3DSMeshFileLoader();
//
//				//! returns true if the file maybe is able to be loaded by this class
//				//! based on the file extension (e.g. ".cob")
//				virtual bool isALoadableFileExtension(
//						const io::path& filename) const;
//
//				//! creates/loads an animated mesh from the file.
//				//! \return Pointer to the created mesh. Returns 0 if loading failed.
//				//! If you no longer need the mesh, you should call IAnimatedMesh::drop().
//				//! See IReferenceCounted::drop() for more information.
//				virtual IAnimatedMesh* createMesh(io::IReadFile* file);
//
//			private:
//				bool readChunk(io::IReadFile* file, ChunkData* parent);
//				bool readMaterialChunk(io::IReadFile* file, ChunkData* parent);
//				bool readFrameChunk(io::IReadFile* file, ChunkData* parent);
//				bool readTrackChunk(io::IReadFile* file, ChunkData& data,
//						IMeshBuffer* mb, const core::vector3df& pivot);
//				bool readObjectChunk(io::IReadFile* file, ChunkData* parent);
//				bool readPercentageChunk(io::IReadFile* file, ChunkData* chunk,
//						f32& percentage);
//				bool readColorChunk(io::IReadFile* file, ChunkData* chunk,
//						video::SColor& out);
//
//				void readChunkData(io::IReadFile* file, ChunkData& data);
//				void readString(io::IReadFile* file, ChunkData& data,
//						core::stringc& out);
//				void readVertices(io::IReadFile* file, ChunkData& data);
//				void readIndices(io::IReadFile* file, ChunkData& data);
//				void readMaterialGroup(io::IReadFile* file, ChunkData& data);
//				void readTextureCoords(io::IReadFile* file, ChunkData& data);
//
//				void composeObject(io::IReadFile* file,
//						const core::stringc& name);
//				void loadMaterials(io::IReadFile* file);
//				void cleanUp();
//
//private:
//				scene::ISceneManager* SceneManager;
//				io::IFileSystem* FileSystem;
//
//				f32* Vertices;
//				u16* Indices;
//				u32* SmoothingGroups;
//				core::array<u16> TempIndices;
//				f32* TCoords;
//				u16 CountVertices;
//				u16 CountFaces; // = CountIndices/4
//				u16 CountTCoords;
//				core::array<SMaterialGroup> MaterialGroups;
//
//				SCurrentMaterial CurrentMaterial;
//				core::array<SCurrentMaterial> Materials;
//				core::array<core::stringc> MeshBufferNames;
//				core::matrix4 TransformationMatrix;
//
//				SMesh* Mesh;
//		};
//
//	} // end namespace scene
//} // end namespace irr
//
//#endif
//
