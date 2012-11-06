///*
// * IArchiveLoader.h
// *
// *  Created on: Jul 26, 2012
// *      Author: gregorytkach
// */
//
//#ifndef IARCHIVELOADER_H_
//#define IARCHIVELOADER_H_
//
//namespace irrgame
//{
//	namespace io
//	{
//		//! Class which is able to create an archive from a file.
//		/** If you want the Irrlicht Engine be able to load archives of
//		 currently unsupported file formats (e.g .wad), then implement
//		 this and add your new Archive loader with
//		 IFileSystem::addArchiveLoader() to the engine. */
//		class IArchiveLoader: public virtual IReferenceCounted
//		{
//			public:
//				//! Check if the file might be loaded by this class
//				/** Check based on the file extension (e.g. ".zip")
//				 \param filename Name of file to check.
//				 \return True if file seems to be loadable. */
//				virtual bool isALoadableFileFormat(
//						const path& filename) const =0;
//
//				//! Check if the file might be loaded by this class
//				/** This check may look into the file.
//				 \param file File handle to check.
//				 \return True if file seems to be loadable. */
//				virtual bool isALoadableFileFormat(
//						io::IReadFile* file) const =0;
//
//				//! Check to see if the loader can create archives of this type.
//				/** Check based on the archive type.
//				 \param fileType The archive type to check.
//				 \return True if the archile loader supports this type, false if not */
//				virtual bool isALoadableFileFormat(
//						E_FILE_ARCHIVE_TYPE fileType) const =0;
//
//				//! Creates an archive from the filename
//				/** \param filename File to use.
//				 \param ignoreCase Searching is performed without regarding the case
//				 \param ignorePaths Files are searched for without checking for the directories
//				 \return Pointer to newly created archive, or 0 upon error. */
//				virtual IFileArchive* createArchive(const path& filename,
//						bool ignoreCase, bool ignorePaths) const =0;
//
//				//! Creates an archive from the file
//				/** \param file File handle to use.
//				 \param ignoreCase Searching is performed without regarding the case
//				 \param ignorePaths Files are searched for without checking for the directories
//				 \return Pointer to newly created archive, or 0 upon error. */
//				virtual IFileArchive* createArchive(io::IReadFile* file,
//						bool ignoreCase, bool ignorePaths) const =0;
//		};
//
//	}
//}
//
//#endif /* IARCHIVELOADER_H_ */
