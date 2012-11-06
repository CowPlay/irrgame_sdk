// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_FILE_SYSTEM_H_INCLUDED__
#define __I_FILE_SYSTEM_H_INCLUDED__

#include "io/xml/IXMLReader.h"
#include "io/xml/IXMLWriter.h"
#include "io/SPath.h"
//#include "io/IArchiveLoader.h"
#include "io/IFileArchive.h"
#include "io/IReadFile.h"
#include "io/IWriteFile.h"
#include "io/EFileSystemTypes.h"
namespace irrgame
{
	namespace io
	{

		class IFileList;
		class IAttributes;

		//! The FileSystem manages files and archives and provides access to them.
		//! Represents a Facade which contatins access to read, write file functions, create attributes, file lists, archives etc.
		/** It manages where files are, so that modules which use the the IO do not
		 need to know where every file is located. A file could be in a .zip-Archive or
		 as file on disk, using the IFileSystem makes no difference to this. */
		class SharedFileSystem: public virtual IReferenceCounted
		{
			public:
				//! Singleton realization
				static SharedFileSystem& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedFileSystem();

				//! Destructor. Should use only one time.
				virtual ~SharedFileSystem();

				//! Copy constructor. Do not implement.
				SharedFileSystem(const SharedFileSystem& root);

				//! Override equal operator. Do not implement.
				const SharedFileSystem& operator=(SharedFileSystem&);

			public:
				//! Creates a XML Reader from a file which returns all parsed strings as ASCII/UTF-8 characters (char*).
				/** See IXMLReader for more information on how to use the parser.
				 \return 0, if file could not be opened, otherwise a pointer to the created
				 IXMLReader is returned. After use, the reader
				 has to be deleted using its IXMLReader::drop() method.
				 See IReferenceCounted::drop() for more information. */
				IXMLReader* createXMLReader(const core::stringc& filename);

				//! Creates a XML Reader from a file which returns all parsed strings as ASCII/UTF-8 characters (char*).
				/** See IXMLReader for more information on how to use the parser.
				 \return 0, if file could not be opened, otherwise a pointer to the created
				 IXMLReader is returned. After use, the reader
				 has to be deleted using its IXMLReader::drop() method.
				 See IReferenceCounted::drop() for more information. */
				IXMLReader* createXMLReader(IReadFile* file);

				//! Creates a XML Writer from a file.
				/** \return 0, if file could not be opened, otherwise a pointer to the created
				 IXMLWriter is returned. After use, the reader
				 has to be deleted using its IXMLWriter::drop() method.
				 See IReferenceCounted::drop() for more information. */
				IXMLWriter* createXMLWriter(const core::stringc& filename);

				//! Creates a XML Writer from a file.
				/** \return 0, if file could not be opened, otherwise a pointer to the created
				 IXMLWriter is returned. After use, the reader
				 has to be deleted using its IXMLWriter::drop() method.
				 See IReferenceCounted::drop() for more information. */
				IXMLWriter* createXMLWriter(IWriteFile* file);

				//! Converts a relative path to an absolute (unique) path, resolving symbolic links if required
				//! Platform dependies
				/** \param filename Possibly relative file or directory name to query.
				 \result Absolute filename which points to the same file. */
				core::stringc getAbsolutePath(const core::stringc& filename);

				//! flatten a path and file name for example: "/you/me/../." becomes "/you"
				core::stringc& flattenFilename(core::stringc& directory,
						const core::stringc& root = "/");

				//! Opens a file for read access. File should be exists.
				/** \param filename: Name of file to open.
				 \return Returns a pointer to the created file interface.
				 The returned pointer should be dropped when no longer needed.
				 See IReferenceCounted::drop() for more information. */
				IReadFile* createReadFile(const core::stringc& filename);

				//! Creates an IReadFile interface for accessing memory like a file.
				/** This allows you to use a pointer to memory where an IReadFile is requested.
				 \param memory: A pointer to the start of the file in memory
				 \param len: The length of the memory in bytes
				 \param fileName: The name given to this file
				 \param deleteMemoryWhenDropped: True if the memory should be deleted
				 along with the IReadFile when it is dropped.
				 \return Returns a pointer to the created file interface.
				 The returned pointer should be dropped when no longer needed.
				 See IReferenceCounted::drop() for more information.
				 */
				IReadFile* createMemoryReadFile(void* memory, s32 len,
						const core::stringc& fileName,
						bool deleteMemoryWhenDropped = false);

				//! Creates an IReadFile interface for accessing files inside files.
				/** This is useful e.g. for archives.
				 \param fileName: The name given to this file
				 \param alreadyOpenedFile: Pointer to the enclosing file
				 \param pos: Start of the file inside alreadyOpenedFile
				 \param areaSize: The length of the file
				 \return A pointer to the created file interface.
				 The returned pointer should be dropped when no longer needed.
				 See IReferenceCounted::drop() for more information.
				 */
				IReadFile* createLimitReadFile(const core::stringc& fileName,
						IReadFile* alreadyOpenedFile, long pos, long areaSize);

				//! Creates an IWriteFile interface for accessing memory like a file.
				/** This allows you to use a pointer to memory where an IWriteFile is requested.
				 You are responsible for allocating enough memory.
				 \param memory: A pointer to the start of the file in memory (allocated by you)
				 \param len: The length of the memory in bytes
				 \param fileName: The name given to this file
				 \param deleteMemoryWhenDropped: True if the memory should be deleted
				 along with the IWriteFile when it is dropped.
				 \return Returns a pointer to the created file interface.
				 The returned pointer should be dropped when no longer needed.
				 See IReferenceCounted::drop() for more information.
				 */
				IWriteFile* createMemoryWriteFile(void* memory, s32 len,
						const core::stringc& fileName,
						bool deleteMemoryWhenDropped = false);

				//! Opens a file for write access.
				/** \param filename: Name of file to open.
				 \param append: If the file already exist, all write operations are
				 appended to the file. Otherwise - file will create.
				 \return Returns a pointer to the created file interface
				 The returned pointer should be dropped when no longer needed.
				 See IReferenceCounted::drop() for more information. */
				IWriteFile* createWriteFile(const core::stringc& filename,
						bool append = false);

				//! Get the current working directory.
				/** \return Current working directory as a string. */
				//! Platform dependies
				const core::stringc& getWorkingDirectory();

				//! Changes the current working directory.
				/** \param newDirectory: A string specifying the new working directory.
				 The string is operating system dependent. Under Windows it has
				 the form "<drive>:\<directory>\<sudirectory>\<..>". An example would be: "C:\Windows\"
				 \return True if successful, otherwise false. */
				bool changeWorkingDirectoryTo(const core::stringc& value);

				//! Determines if a file exists and could be opened.
				/** \param filename is the string identifying the file which should be tested for existence.
				 \return Returns true if file exists, and false if it does not exist or an error occured. */
				bool existFile(const core::stringc& filename);

				//! Creates a list of files and directories in the current working directory and returns it.
				/** \return a Pointer to the created IFileList is returned. After the list has been used
				 it has to be deleted using its IFileList::drop() method.
				 See IReferenceCounted::drop() for more information. */
				IFileList* createFileList();

				//! Creates a new empty collection of attributes, usable for serialization and more.
				/** Can be null to prevent automatic texture loading by attributes.
				 \return Pointer to the created object.
				 If you no longer need the object, you should call IAttributes::drop().
				 See IReferenceCounted::drop() for more information. */
				IAttributes* createEmptyAttributes();

			protected:

				//! Currently used FileSystemType
				EFileSystemType FileSystemType;

				//! WorkingDirectory for Native and Virtual filesystems
				core::stringc WorkingDirectory[2];

				//				//! currently attached ArchiveLoaders
				//				array<IArchiveLoader*> ArchiveLoader;

				//! currently attached Archives
				core::array<IFileArchive*> FileArchives;

//				//! Adds an archive to the file system.
//				/** After calling this, the Irrlicht Engine will also search and open
//				 files directly from this archive. This is useful for hiding data from
//				 the end user, speeding up file access and making it possible to access
//				 for example Quake3 .pk3 files, which are just renamed .zip files. By
//				 default Irrlicht supports ZIP, PAK, TAR, PNK, and directories as
//				 archives. You can provide your own archive types by implementing
//				 IArchiveLoader and passing an instance to addArchiveLoader.
//				 \param filename: Filename of the archive to add to the file system.
//				 \param ignoreCase: If set to true, files in the archive can be accessed without
//				 writing all letters in the right case.
//				 \param ignorePaths: If set to true, files in the added archive can be accessed
//				 without its complete path.
//				 \param archiveType: If no specific E_FILE_ARCHIVE_TYPE is selected then
//				 the type of archive will depend on the extension of the file name. If
//				 you use a different extension then you can use this parameter to force
//				 a specific type of archive.
//				 \param password An optional password, which is used in case of encrypted archives.
//				 \return Returns true if the archive was added successfully, false if not. */
//				virtual bool addFileArchive(const path& filename,
//						bool ignoreCase = true, bool ignorePaths = true,
//						E_FILE_ARCHIVE_TYPE archiveType = EFAT_UNKNOWN,
//						const core::core::string& password = "") =0;
//
//				//! Adds an external archive loader to the engine.
//				/** Use this function to add support for new archive types to the
//				 engine, for example proprietary or encrypted file storage. */
//				virtual void addArchiveLoader(IArchiveLoader* loader) =0;
//
//				//! Returns the number of archives currently attached to the file system
//				virtual u32 getFileArchiveCount() const =0;
//
//				//! Removes an archive from the file system.
//				/** This will close the archive and free any file handles, but will not close resources which have already
//				 been loaded and are now cached, for example textures and meshes.
//				 \param index: The index of the archive to remove
//				 \return Returns true on success, false on failure */
//				virtual bool removeFileArchive(u32 index) =0;
//
//				//! Removes an archive from the file system.
//				/** This will close the archive and free any file handles, but will not
//				 close resources which have already been loaded and are now cached, for
//				 example textures and meshes.
//				 \param filename The archive of the given name will be removed
//				 \return Returns true on success, false on failure */
//				virtual bool removeFileArchive(const path& filename) =0;
//
//				//! Changes the search order of attached archives.
//				/**
//				 \param sourceIndex: The index of the archive to change
//				 \param relative: The relative change in position, archives with a lower index are searched first */
//				virtual bool moveFileArchive(u32 sourceIndex, s32 relative) =0;
//
//				//! Returns the archive at a given index.
//				virtual IFileArchive* getFileArchive(u32 index) =0;
//
//				//! Adds a zip archive to the file system.
//				/** \deprecated This function is provided for compatibility
//				 with older versions of Irrlicht and may be removed in future versions,
//				 you should use addFileArchive instead.
//				 After calling this, the Irrlicht Engine will search and open files directly from this archive too.
//				 This is useful for hiding data from the end user, speeding up file access and making it possible to
//				 access for example Quake3 .pk3 files, which are no different than .zip files.
//				 \param filename: Filename of the zip archive to add to the file system.
//				 \param ignoreCase: If set to true, files in the archive can be accessed without
//				 writing all letters in the right case.
//				 \param ignorePaths: If set to true, files in the added archive can be accessed
//				 without its complete path.
//				 \return Returns true if the archive was added successfully, false if not. */
//				virtual bool addZipFileArchive(const c8* filename,
//						bool ignoreCase = true, bool ignorePaths = true)
//				{
//					return addFileArchive(filename, ignoreCase, ignorePaths,
//							EFAT_ZIP);
//				}
//
//				//! Adds an unzipped archive (or basedirectory with subdirectories..) to the file system.
//				/** \deprecated This function is provided for compatibility
//				 with older versions of Irrlicht and may be removed in future versions,
//				 you should use addFileArchive instead.
//				 Useful for handling data which will be in a zip file
//				 \param filename: Filename of the unzipped zip archive base directory to add to the file system.
//				 \param ignoreCase: If set to true, files in the archive can be accessed without
//				 writing all letters in the right case.
//				 \param ignorePaths: If set to true, files in the added archive can be accessed
//				 without its complete path.
//				 \return Returns true if the archive was added successful, false if not. */
//				virtual bool addFolderFileArchive(const c8* filename,
//						bool ignoreCase = true, bool ignorePaths = true)
//				{
//					return addFileArchive(filename, ignoreCase, ignorePaths,
//							EFAT_FOLDER);
//				}
//
//				//! Adds a pak archive to the file system.
//				/** \deprecated This function is provided for compatibility
//				 with older versions of Irrlicht and may be removed in future versions,
//				 you should use addFileArchive instead.
//				 After calling this, the Irrlicht Engine will search and open files directly from this archive too.
//				 This is useful for hiding data from the end user, speeding up file access and making it possible to
//				 access for example Quake2/KingPin/Hexen2 .pak files
//				 \param filename: Filename of the pak archive to add to the file system.
//				 \param ignoreCase: If set to true, files in the archive can be accessed without
//				 writing all letters in the right case.
//				 \param ignorePaths: If set to true, files in the added archive can be accessed
//				 without its complete path.(should not use with Quake2 paks
//				 \return Returns true if the archive was added successful, false if not. */
//				virtual bool addPakFileArchive(const c8* filename,
//						bool ignoreCase = true, bool ignorePaths = true)
//				{
//					return addFileArchive(filename, ignoreCase, ignorePaths,
//							EFAT_PAK);
//				}
//

//

//
//
//

//
//				//! Returns the base part of a filename, i.e. the name without the directory part.
//				/** If no directory is prefixed, the full name is returned.
//				 \param filename: The file to get the basename from
//				 \param keepExtension True if filename with extension is returned otherwise everything
//				 after the final '.' is removed as well. */
//				virtual path getFileBasename(const path& filename,
//						bool keepExtension = true) const =0;
//

//

//
//				//! Creates an empty filelist
//				/** \return a Pointer to the created IFileList is returned. After the list has been used
//				 it has to be deleted using its IFileList::drop() method.
//				 See IReferenceCounted::drop() for more information. */
				//! TODO: remove if not need
//				virtual IFileList* createEmptyFileList(const core::core::string& path,
//						bool ignoreCase, bool ignorePaths) =0;
//
//				//! Set the active type of file system.
//				virtual EFileSystemType setFileListSystem(
//						EFileSystemType listType) =0;
//
//
//

//
//
//
		};
	} // end namespace io
} // end namespace irr

#endif

