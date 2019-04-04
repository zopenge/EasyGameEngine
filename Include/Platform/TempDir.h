#pragma once

namespace EGE {

/// <summary>
/// The temporary directory(create in constructor and delete it in destructor).
/// </summary>
class TempDir {
private:
	WString mDirPath;

public:
	TempDir(WStringPtr root_dir);
	TempDir(const TempDir& root_dir);
	~TempDir();

public:
	WStringPtr GetDirPath() const;
};

inline WStringPtr TempDir::GetDirPath() const {
	return mDirPath;
}

} // namespace EGE
