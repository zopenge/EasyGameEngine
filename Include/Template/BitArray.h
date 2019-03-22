//! @file     BitArray.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// BitArray
//----------------------------------------------------------------------------

//! This class represents a bit buffer.
template <_dword _EACH_BITS_NUMBER>
class BitArray {
private:
	enum {
		//!	The chunk bits number
		_CHUNK_BITS_NUMBER = sizeof(_dword) * 8,
	};

private:
	//!	The total bits number
	_dword mTotalBitsNumber;
	//!	The total size in bytes
	_dword mTotalSizeInBytes;
	//!	The buffer data
	_dword* mBuffer;

private:
	//!	Get the buffer size in 32 bits (_dword).
	_dword GetBufferSizeInDword() const;
	//!	Get the mask by each bits number.
	_dword GetBitsMask() const;

public:
	BitArray();
	~BitArray();

public:
	//! Get a element by index.
	//! @param		index		The index of the element in array.
	//! @return		The element value.
	_dword operator[](_dword index) const;

	//!	Clear number of elements.
	//!	@param		none.
	//!	@return		none.
	_void Clear();
	//!	Create elements.
	//!	@param		number	The number of elements.
	//!	@return		none.
	_void Create(_dword number);

	//!	Get the number of elements.
	//!	@param		none.
	//!	@return		The number of elements.
	_dword Number() const;
	//!	Get the total size in bytes.
	//!	@param		none.
	//!	@return		The total size in bytes
	_dword Size() const;

	//!	Get the element value.
	//!	@param		index	The index of elements.
	//!	@return		The element value.
	_dword Get(_dword index) const;
	//!	Set the element value.
	//!	@param		index	The index of elements.
	//!	@param		value	The element value.
	//!	@return		none.
	_void Set(_dword index, _dword value);
	//!	Set all the element value.
	//!	@param		value	The element value.
	//!	@return		none.
	_void SetAll(_dword value);
};

//----------------------------------------------------------------------------
// BitArray Implementation
//----------------------------------------------------------------------------

template <_dword _EACH_BITS_NUMBER>
BitArray<_EACH_BITS_NUMBER>::BitArray() {
	mTotalBitsNumber = 0;
	mTotalSizeInBytes = 0;
	mBuffer = _null;

	// The bits must be power of 2
	EGE_STATIC_ASSERT(_EACH_BITS_NUMBER != 0, "The bits number can not be zero");
	EGE_STATIC_ASSERT((_EACH_BITS_NUMBER & (_EACH_BITS_NUMBER - 1)) == 0, "The bits number must be power of 2");
}

template <_dword _EACH_BITS_NUMBER>
BitArray<_EACH_BITS_NUMBER>::~BitArray() {
	EGE_DELETE_ARRAY(mBuffer);
}

template <_dword _EACH_BITS_NUMBER>
_dword BitArray<_EACH_BITS_NUMBER>::GetBufferSizeInDword() const {
	return mTotalSizeInBytes / sizeof(_dword);
}

template <_dword _EACH_BITS_NUMBER>
_dword BitArray<_EACH_BITS_NUMBER>::GetBitsMask() const {
	switch (_EACH_BITS_NUMBER) {
	case 1:
		return 0x00000001;
	case 2:
		return 0x00000003;
	case 4:
		return 0x0000000F;
	case 8:
		return 0x000000FF;
	case 16:
		return 0x0000FFFF;
	case 32:
		return 0xFFFFFFFF;
	default:
		return 0;
	}
}

template <_dword _EACH_BITS_NUMBER>
_dword BitArray<_EACH_BITS_NUMBER>::operator[](_dword index) const {
	return Get(index);
}

template <_dword _EACH_BITS_NUMBER>
_void BitArray<_EACH_BITS_NUMBER>::Clear() {
	EGE_INIT_ARRAY(mBuffer);
}

template <_dword _EACH_BITS_NUMBER>
_void BitArray<_EACH_BITS_NUMBER>::Create(_dword number) {
	EGE_ASSERT(number != 0);

	// Delete the previous data
	EGE_DELETE_ARRAY(mBuffer);

	// Initialize the bits array info
	mTotalBitsNumber = Math::UpperArrange(number * _EACH_BITS_NUMBER, _CHUNK_BITS_NUMBER);
	mTotalSizeInBytes = mTotalBitsNumber / 8;
	mBuffer = new _dword[GetBufferSizeInDword()];
	memset(mBuffer, 0, mTotalSizeInBytes);
}

template <_dword _EACH_BITS_NUMBER>
_dword BitArray<_EACH_BITS_NUMBER>::Number() const {
	return mTotalBitsNumber / _EACH_BITS_NUMBER;
}

template <_dword _EACH_BITS_NUMBER>
_dword BitArray<_EACH_BITS_NUMBER>::Size() const {
	return mTotalSizeInBytes;
}

template <_dword _EACH_BITS_NUMBER>
_dword BitArray<_EACH_BITS_NUMBER>::Get(_dword index) const {
	_dword n1 = index / _CHUNK_BITS_NUMBER;
	_dword n2 = index % _CHUNK_BITS_NUMBER;

	EGE_ASSERT(n1 < GetBufferSizeInDword());

	return (mBuffer[n1] >> n2) & GetBitsMask();
}

template <_dword _EACH_BITS_NUMBER>
_void BitArray<_EACH_BITS_NUMBER>::Set(_dword index, _dword value) {
	_dword n1 = index / _CHUNK_BITS_NUMBER;
	_dword n2 = index % _CHUNK_BITS_NUMBER;

	EGE_ASSERT(n1 < GetBufferSizeInDword());

	// Get the mask ID
	_dword mask = GetBitsMask() << n2;

	// Update the bits info
	mBuffer[n1] = (mBuffer[n1] & (mask ^ 0xFFFFFFFF)) | (value << n2);
}

template <_dword _EACH_BITS_NUMBER>
_void BitArray<_EACH_BITS_NUMBER>::SetAll(_dword value) {
	for (_dword i = 0; i < Number(); i++)
		Set(i, value);
}

} // namespace EGE