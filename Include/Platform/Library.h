#pragma once

namespace EGE {

/// <summary>
/// The library.
/// </summary>
class Library {
public:
	//! When loaded dependence DLL library.
	//! @param filename  The DLL library file name.
	//! @param Params  The user defined Params.
	//! @return The dll module handle when we handled the DLL loading
	//! procession.
	typedef _handle (*OnLoadDependentDLL)(AStringPtr dllfilename, const QwordParams2& Params);

private:
	typedef CallbackFunc<OnLoadDependentDLL, _handle, QwordParams2> LoadDependentDLLFunc;

private:
	//! True indicates loaded from memory, otherwise loaded from file
	_ubool mLibInMemory;
	//! The DLL module
	_handle mModule;
	//! The NT header
	_handle mNTHeader;
	//! The DllMain function
	_handle mDllMainFunc;

	//! The library internal name
	WString mInternalName;
	//! The library copyright
	WString mCopyright;
	//! The library version
	Version mVersion;

	//! The library embedded manifest
	AString mEmbeddedManifest;

private:
	//! Load DLL version info.
	//! @param address   The DLL version info address.
	//! @return True indicates the library had been loaded.
	_ubool LoadVersionInfo(const _void* address);
	//! Load DLL embedded manifest info.
	//! @param address   The DLL embedded manifest info
	//! address.
	//! @param size   The DLL embedded manifest info size
	//! in bytes.
	//! @return True indicates the library had been loaded.
	_ubool LoadEmbeddedManifestInfo(const _void* address, _dword size);
	//! Load DLL resource from memory.
	//! @param virtualaddress The RVA of image resource directory.
	//! @param base   The base image resource
	//! directory.
	//! @param resource  The current image resource
	//! directory.
	//! @return True indicates the library had been loaded.
	_ubool LoadResourceFromMemory(_dword virtualaddress, const _byte* base, const _byte* resource);

public:
	Library();
	~Library();

public:
	//! Load library from file.
	//! @param filename  The DLL file name.
	//! @return True indicates success, false indicates failure.
	_ubool Load(WStringPtr filename);
	//! Load library from memory.
	//! @param buffer   The memory buffer data.
	//! @param size   The memory buffer size.
	//! @param funcpointer  The load dependent libraries
	//! function pointer.
	//! @param Params  The user defined Params.
	//! @return True indicates success, false indicates failure.
	_ubool Load(const _byte* buffer, _dword size, OnLoadDependentDLL funcpointer, const QwordParams2& Params);
	//! Free library.
	//! @param none.
	//! @return none.
	_void Free();

	//! Get the function from library in ANSI mode.
	//! @param functionname The function name.
	//! @return The function pointer.
	_void* GetFunction(AStringPtr functionname) const;
	//! Get the function from library in UNICODE mode.
	//! @param functionname The function name.
	//! @return The function pointer.
	_void* GetFunction(WStringPtr functionname) const;

	//! Check whether the library had been loaded.
	//! @param none.
	//! @return True indicates the library had been loaded.
	_ubool IsLoaded() const;

	//! Get the library internal name.
	//! @param none.
	//! @return The library internal name.
	WStringPtr GetInternalName() const;
	//! Get the library copyright.
	//! @param none.
	//! @return The library copyright.
	WStringPtr GetCopyright() const;
	//! Get the library version.
	//! @param none.
	//! @return The library version.
	const Version& GetVersion() const;

	//! Get the library embedded manifest.
	//! @param none.
	//! @return The library embedded manifest.
	AStringPtr GetEmbeddedManifest() const;
};

} // namespace EGE