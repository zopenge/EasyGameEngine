#pragma once

namespace EGE {

/// <summary>
/// The DirectDraw Surface file format (.dds) was introduced with DirectX 7 to store uncompressed and compressed (DXTn) textures.
/// </summary>
class IDDSFile : public ICompressedTexFile {
public:
	//!	DXT version
	enum class DXTVersion {
		DXT_UNKNOWN,
		DXT_1,
		DXT_3,
		DXT_5,
	};

public:
	//!	Get the DXT version.
	//!	@param		none.
	//!	@return		The DXT version.
	virtual DXTVersion GetDXTVersion() const PURE;
	//!	Get the mip-maps level.
	//!	@param		none.
	//!	@return		The mip-maps level.
	virtual _dword GetMipmapLevel() const PURE;

	//!	Get the compressed image buffer.
	//!	@param		none.
	//!	@return		The compressed image buffer.
	virtual const _byte* GetCompressedImageBuffer() const PURE;
};

} // namespace EGE