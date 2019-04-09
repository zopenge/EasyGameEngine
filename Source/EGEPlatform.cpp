#include "EGEPlatform.h"

_thread_id EGE::gMainThreadID = 0;
PerformanceData EGE::gPerformanceData;
CPUData EGE::gCPUData;
GPUData EGE::gGPUData;
OSData EGE::gOSData;

//----------------------------------------------------------------------------
// Specified template static variables implementation
//----------------------------------------------------------------------------

template <>
const PointI PointI::cZeroPoint(0, 0);
template <>
const PointI PointI::cMaxPoint(0x7FFFFFFF, 0x7FFFFFFF);
template <>
const PointI PointI::cMinPoint(0x80000001, 0x80000001);

template <>
const PointU PointU::cZeroPoint(0, 0);
template <>
const PointU PointU::cMaxPoint(0xFFFFFFFF, 0xFFFFFFFF);
template <>
const PointU PointU::cMinPoint(0x00000001, 0x00000001);

template <>
const PointF PointF::cZeroPoint(0.0f, 0.0f);
template <>
const PointF PointF::cMaxPoint(3.402823466e+38f, 3.402823466e+38f);
template <>
const PointF PointF::cMinPoint(-3.402823466e+38f, -3.402823466e+38f);

template <>
const RectI RectI::cNull(0, 0, 0, 0);
template <>
const RectU RectU::cNull(0, 0, 0, 0);
template <>
const RectF RectF::cNull(0.0f, 0.0f, 0.0f, 0.0f);

template <>
const RectI RectI::cMax(Math::cMinInt, Math::cMinInt, Math::cMaxInt, Math::cMaxInt);
template <>
const RectU RectU::cMax(Math::cMinDword, Math::cMinDword, Math::cMaxDword, Math::cMaxDword);
template <>
const RectF RectF::cMax(Math::cMinFloat, Math::cMinFloat, Math::cMaxFloat, Math::cMaxFloat);

template <>
const WordRange WordRange::cNull(0, 0);
template <>
const DwordRange DwordRange::cNull(0, 0);
template <>
const QwordRange QwordRange::cNull(0, 0);
template <>
const FloatRange FloatRange::cNull(0.0f, 0.0f);

template <>
const WordProgression WordProgression::cNull(0, 0);
template <>
const DwordProgression DwordProgression::cNull(0, 0);
template <>
const FloatProgression FloatProgression::cNull(0.0f, 0.0f);

template <>
const DwordDataField DwordDataField::cNull(0, 0);

template <>
const QwordParams2 QwordParams2::cNull(0, 0);
template <>
const QwordParams3 QwordParams3::cNull(0, 0, 0);
template <>
const QwordParams4 QwordParams4::cNull(0, 0, 0, 0);

//----------------------------------------------------------------------------
// Memory Overload Implementation
//----------------------------------------------------------------------------

#ifndef _USE_STANDARD_MEM_OPERATOR_

#	ifndef _USE_STANDARD_MALLOC_OPERATOR_

void _ege_free(void* pointer, const char* filename, int linenumber) {
	EGE::Memory::GetInstance().Free(pointer, filename, linenumber);
}

void* _ege_malloc(size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Alloc((_dword)size, filename, linenumber);
}

void* _ege_calloc(size_t number, size_t size, const char* filename, int linenumber) {
	EGE::_void* buffer = EGE::Memory::GetInstance().Alloc((_dword)(number * size), filename, linenumber);
	if (buffer != _null) {
		EGE_MEM_SET(buffer, 0, number * size);
	}

	return buffer;
}

void* _ege_realloc(void* pointer, size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Realloc(pointer, (_dword)size, filename, linenumber);
}

#	endif

#	undef new

// Overload New And Delete Operations
void* operator new(size_t size) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, _null, 0);
}

void* operator new(size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, filename, linenumber);
}

void* operator new[](size_t size) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, _null, 0);
}

void* operator new[](size_t size, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Alloc((EGE::_dword)size, filename, linenumber);
}

void operator delete(void* pointer) {
	return EGE::Memory::GetInstance().Free(pointer, _null, 0);
}

void operator delete(void* pointer, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Free(pointer, filename, linenumber);
}

void operator delete[](void* pointer) {
	return EGE::Memory::GetInstance().Free(pointer, _null, 0);
}

void operator delete[](void* pointer, const char* filename, int linenumber) {
	return EGE::Memory::GetInstance().Free(pointer, filename, linenumber);
}

#endif // _USE_STANDARD_MEM_OPERATOR_
