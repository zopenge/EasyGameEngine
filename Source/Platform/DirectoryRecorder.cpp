#include "EGEPlatform.h"

DirectoryRecorder::DirectoryRecorder(WStringPtr directory)
    : mOldDirectory(FileSystem::GetCurrentDir()) {
	FileSystem::SetCurrentDir(directory);
}

DirectoryRecorder::~DirectoryRecorder() {
	FileSystem::SetCurrentDir(mOldDirectory);
}
