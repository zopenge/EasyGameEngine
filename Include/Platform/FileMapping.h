#pragma once

namespace EGE {

/// <summary>
/// The file mapping.
/// </summary>
class FileMapping : public KernelObject {
private:
	//! The mapping file handle
	_handle mFileHandle;

	//! The mapping buffer size
	_dword mSize;
	//! The mapping buffer data
	_byte* mBuffer;

private:
	//! Initialize.
	//! @param none.
	//! @return True indicates success false indicates failure.
	_ubool Initialize();

public:
	FileMapping();
	~FileMapping();

public:
	//! Get the mapping buffer size, in bytes.
	//! @param none.
	//! @return The mapping buffer size, in bytes.
	_dword GetSize() const;
	//! Get the mapping buffer data.
	//! @param none.
	//! @return The mapping buffer data pointer.
	_byte* GetBuffer() const;

	//! Create the file mapping.
	//! @param filename The file name.
	//! @return True indicates success false indicates failure.
	_ubool Create(WStringPtr filename);
	//! Close the file mapping.
	//! @param none.
	//! @return none.
	_void Close();
};

} // namespace EGE