//! @file     FileFinder.cpp
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// FileFinder Implementation
//----------------------------------------------------------------------------

FileFinder::FileFinder() {
	mItemNumber = 0;
}

FileFinder::~FileFinder() {
	Close();
}

_ubool FileFinder::PushDir(WStringPtr relative_path, WStringPtr absolute_path) {
	// Initialize folder data
	FolderData folder_data;
	folder_data.mRelativePath = relative_path;
	folder_data.mAbsolutePath = absolute_path;

	// Open the directory
	folder_data.mFinderHandle = Platform::OpenDir(absolute_path.CStr());
	if (folder_data.mFinderHandle == _null)
		return _false;

	// Push into file finder stack
	mFolderDataStack.Push(folder_data);

	return _true;
}

_void FileFinder::PopDir() {
	// Close the directory handle
	Platform::CloseDir(mFolderDataStack.Top().mFinderHandle);

	// Pop it from the stack
	mFolderDataStack.Pop();
}

_ubool FileFinder::ReadDir(FolderData& filefinder, FileData& fileinfo, WStringPtr filter, _dword flags) {
	FileFinderData finddata;
	while (Platform::ReadDir(filefinder.mFinderHandle, finddata)) {
		// Walk subdirectory
		if (finddata.mFileAttributes & _FILE_ATTRIBUTE_DIRECTORY) {
			// Skip for the hidden directory
			if ((finddata.mFileAttributes & _FILE_ATTRIBUTE_HIDDEN) && (flags & _FILE_FINDER_ENUMERATION_SKIP_HIDDEN_DIRECTORY))
				continue;
		}
		// It's file item
		else {
			// Skip for directory only mode
			if (flags & _FILE_FINDER_ENUMERATION_DIRECTORY_ONLY)
				continue;

			// Skip for the hidden file
			if ((finddata.mFileAttributes & _FILE_ATTRIBUTE_HIDDEN) && (flags & _FILE_FINDER_ENUMERATION_SKIP_HIDDEN_FILE))
				continue;

			// Check the extension name
			if ((filter.IsEmpty() == _false) && (Path::DoesMatchExtension(finddata.mFileName, filter) == _false))
				continue;
		}

		// Increase the item number
		mItemNumber++;

		// Feedback the file or directory info
		fileinfo.mFileName = finddata.mFileName;
		fileinfo.mSize = finddata.mFileSize;
		fileinfo.mAttributes = finddata.mFileAttributes;
		fileinfo.mLastWriteTime = *(_qword*)&finddata.mLastWriteTime;

		return _true;
	}

	// No any more files or directories what we can find
	return _false;
}

_ubool FileFinder::Open(WStringPtr path) {
	Close();

	// We assume the empty path that means the current directory path
	if (path.IsEmpty())
		path = L"./";

	// Make sure the path is existing
	if (FileSystem::IsDirectoryExist(path) == _false)
		return _false;

	// Set the root directory
	mRootDirectory = path;

	// Push and open the root directory
	return PushDir(L"", mRootDirectory);
}

_void FileFinder::Close() {
	mItemNumber = 0;

	// Delete all file finder
	for (_dword i = 0; i < mFolderDataStack.Number(); i++) {
		if (mFolderDataStack[i].mFinderHandle != _null)
			Platform::CloseDir(mFolderDataStack[i].mFinderHandle);
	}

	mFolderDataStack.Clear();
}

WStringPtr FileFinder::GetDirectoryPath() const {
	return mRootDirectory;
}

WString FileFinder::GetFileByName(WStringPtr name) {
	// Open the root directory
	if (Open(mRootDirectory) == _false)
		return WString(L"");

	// Get the extension name
	WString extension_name = Path::GetExtension(name);

	// Start to find
	FileData file_info;
	while (Walk(file_info, extension_name, _FILE_FINDER_FILE_MASK, -1)) {
		if (file_info.mFileName == name)
			return file_info.mRelativePath;
	}

	return WString(L"");
}

_ubool FileFinder::HasFile(WStringPtr extension_name, _dword depth) {
	// Open the root directory
	if (Open(mRootDirectory) == _false)
		return _false;

	// Start to find
	FileData file_info;
	while (Walk(file_info, L"", _FILE_FINDER_FILE_MASK, depth)) {
		if (Path::GetExtension(file_info.mFileName) == extension_name)
			return _true;
	}

	return _false;
}

_ubool FileFinder::Walk(FileData& fileinfo, WStringPtr filter, _dword flags, _dword depth) {
	// Walk this directory
	while (mFolderDataStack.Number() > 0) {
		// Get the current file finder
		FolderData& filefinder = mFolderDataStack.Top();

		// Read the directory
		if (ReadDir(filefinder, fileinfo, filter, flags) == _false) {
			// Completed the walk operation, pop and close it
			PopDir();

			// Continue to find from the parent directory again
			continue;
		}

		// Get the file depth
		_dword file_depth = mFolderDataStack.Number();
		if (depth != -1 && file_depth > depth)
			continue; // Out of depth, continue to enumerate

		// Build the file info
		fileinfo.mDepth = file_depth;
		fileinfo.mItemNumber = mItemNumber;
		fileinfo.mRelativePath = Path::BuildFilePath(filefinder.mRelativePath, fileinfo.mFileName);
		fileinfo.mAbsolutePath = Path::BuildFilePath(filefinder.mAbsolutePath, fileinfo.mFileName);

		// Walk for the sub-directory
		if (fileinfo.mAttributes & _FILE_ATTRIBUTE_DIRECTORY) {
			// Open and push the directory
			if (PushDir(fileinfo.mRelativePath, fileinfo.mAbsolutePath) == _false)
				return _false;

			// Enumerate file only
			if (flags & _FILE_FINDER_ENUMERATION_FILE_ONLY)
				continue; // Continue to enumerate
		}

		// We found file or directory
		return _true;
	}

	// No any more files or directories what we can find
	return _false;
}