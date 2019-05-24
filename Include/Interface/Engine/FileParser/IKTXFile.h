#pragma once

namespace EGE {

/// <summary>
/// KTX (Khronos Texture) is a lightweight file format for OpenGL textures, designed around how textures are loaded in OpenGL.
/// </summary>
class IKTXFile : public ICompressedTexFile {
public:
	//!	The KTX header info
	//!	http://www.khronos.org/opengles/sdk/tools/KTX/file_format_spec/#2.14
	struct HeaderData {
		// Header
		_byte mIdentifier[12];
		_dword mEndianness;
		_dword mGLType;
		_dword mGLTypeSize;
		_dword mGLFormat;
		_dword mGLInternalFormat;
		_dword mGLBaseInternalFormat;
		_dword mPixelWidth;
		_dword mPixelHeight;
		_dword mPixelDepth;
		_dword mNumberOfArrayElements;
		_dword mNumberOfFaces;
		_dword mNumberOfMipmapLevels;
		_dword mBytesOfKeyValueData;
	};

public:
	//!	Get the header info.
	//!	@param		none.
	//!	@return		The header info.
	virtual const HeaderData& GetHeaderData() const PURE;
};

} // namespace EGE