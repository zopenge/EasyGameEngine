#include "EGEPlatform.h"

TempDir::TempDir(WStringPtr root_dir) {
	FileSystem::GetTempDirName(root_dir, mDirPath);
	FileSystem::CleanDir(mDirPath);
}

TempDir::TempDir(const TempDir& root_dir) {
	FileSystem::GetTempDirName(root_dir.GetDirPath(), mDirPath);
	FileSystem::CleanDir(mDirPath);
}

TempDir::~TempDir() {
	FileSystem::DeleteDir(mDirPath);
}
