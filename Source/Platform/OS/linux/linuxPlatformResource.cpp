#include "EGEPlatform.h"

_handle Platform::FindResource(_handle /*module*/, const _charw* resname, const _charw* path) {
	// Build resource file name
	WString res_filename = Path::BuildFilePath(path, resname);

	OUTPUT_DEBUG_STRING(FORMAT_WSTRING_1(L"Platform::FindResource : '%s' ...\n", res_filename.Str()));

	// use asset manager to open asset by filename
	// AASSET_MODE_BUFFER: This performs fast small reads
	// AASSET_MODE_RANDOM: This reads chunks of data forward and backward
	// AASSET_MODE_STREAMING: This reads data sequentially with occasional forward seeks
	AAsset* asset = AAssetManager_open(GetAndroidAssetManager(), UString().FromString(res_filename).Str(), AASSET_MODE_BUFFER);
	if (asset == _null)
		return _null;

	OUTPUT_DEBUG_STRING(FORMAT_WSTRING_1(L"Platform::FindResource : '%s' [OK]\n", res_filename.Str()));

	return asset;
}

_handle Platform::LoadResource(_handle /*module*/, _handle resinfo) {
	// The resource info is resource data handle on android
	return resinfo;
}

_void Platform::FreeResource(_handle module, _handle resinfo) {
	AAsset* asset = (AAsset*)resinfo;
	if (asset == _null)
		return;

	AAsset_close(asset);
}

const _byte* Platform::LockResource(_handle resdata) {
	AAsset* asset = (AAsset*)resdata;
	if (asset == _null)
		return _null;

	return (const _byte*)AAsset_getBuffer(asset);
}

_dword Platform::SizeOfResource(_handle /*module*/, _handle resinfo) {
	AAsset* asset = (AAsset*)resinfo;
	if (asset == _null)
		return 0;

	return (_dword)AAsset_getLength(asset);
}

_ubool Platform::EnumResourceNames(_handle module, const _charw* sub_dir_name, OnEnumResNameProc funcpointer, _void* parameter) {
	if (funcpointer == _null)
		return _false;

	return EnumAndroidResFiles(sub_dir_name, (_void*)funcpointer, parameter);
}