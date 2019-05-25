#include "EGEPlatform.h"

// The size of memory allocation node in bytes
static const _dword cSizeOfNode = sizeof(Link<MemoryAllocation>::Node);

//----------------------------------------------------------------------------
// Internal Function Implementation
//----------------------------------------------------------------------------

//! Get the base address of using outside.
static _void* GetBaseAddress(const Link<MemoryAllocation>::Node* node) {
	EGE_ASSERT(node != _null);

	return ((_byte*)node) + cSizeOfNode;
}

//! Get the node address from base address of using outside.
static Link<MemoryAllocation>::Node* GetNodeAddress(_void* address) {
	EGE_ASSERT(address != _null);

	return (Link<MemoryAllocation>::Node*)(((_byte*)address) - cSizeOfNode);
}

#if defined(_PLATFORM_WINDOWS_) && !defined(_USE_STANDARD_MEM_OPERATOR_) && !defined(_USE_STANDARD_MALLOC_OPERATOR_)

//! The CRT allocation hooker
static int OnCRTAllocHookCallback(int nAllocType, void* userData, size_t size,
                                  int nBlockType, long requestNumber,
                                  const unsigned char* filename,
                                  int lineNumber) {
	// Skip for CRT memory block
	if (nBlockType == _CRT_BLOCK) return TRUE;

	AStringPtr filename_ansi = (const _chara*)filename;

	switch (nAllocType) {
		case _HOOK_ALLOC: {
			if (filename != _null) {
				if (filename_ansi == "wincore.cpp" || filename_ansi == "plex.cpp" ||
				    filename_ansi == "strcore.cpp" || filename_ansi == "oleinit.cpp" ||
				    filename_ansi == "winmenu.cpp") {
					return TRUE;
				}
			}

			Memory::GetInstance().AllocBlock(requestNumber, size, (const _chara*)filename, lineNumber);
		} break;

		case _HOOK_REALLOC: {
			_CrtMemBlockHeader* header = pHdr(userData);
			Memory::GetInstance().ReallocBlock(header->lRequest, requestNumber, size, (const _chara*)filename, lineNumber);
		} break;

		case _HOOK_FREE: {
			_CrtMemBlockHeader* header = pHdr(userData);
			Memory::GetInstance().FreeBlock(header->lRequest);
		} break;

		default:
			break;
	}

	return TRUE;
}

#endif

//----------------------------------------------------------------------------
// Memory Implementation
//----------------------------------------------------------------------------

Memory::Memory() {
	mReferencedID = 0x12340000 | Random::Gen(0x0000FFFF);

	mIsUseFullCallstackCheck = _false;
	mMaxFrameNumber = _DEFAULT_MAX_FRAME_NUMBER;
	mFileNameFilter[0] = 0;
	mLineNumberFilter = 0;

	mCurAllocNumber = 0;
	mCurAllocSize = 0;
}

Memory::~Memory() {
}

_void Memory::OnOutputStringCallback(_dword id, const _byte* address, const MemoryAllocation& allocation, const QwordParams2& params) {
	File* file = (File*)params[0];

	// The temporary string buffer
	_chara tempstringbuffer[4096];
	tempstringbuffer[0] = 0;

	// The dump string buffer
	_chara dumpstringbuffer[8192];
	dumpstringbuffer[0] = 0;

	// Update string
	if (address != _null)
		Platform::AppendString(dumpstringbuffer, Platform::FormatStringBuffer(tempstringbuffer, 4096, "[%d] Memory Block : 0x%p\t%u\r\n", id, (_void*)address, allocation.mSize));
	else
		Platform::AppendString(dumpstringbuffer, Platform::FormatStringBuffer(tempstringbuffer, 4096, "[%d] Memory Block : %u\r\n", id, allocation.mSize));

	for (_dword i = 0; i < allocation.mFrameNumber; i++) {
		const SymbolFileData& line_info = allocation.mSrcFileLines[i];

		Platform::AppendString(dumpstringbuffer, Platform::FormatStringBuffer(tempstringbuffer, 4096, "\t%s(%u)\r\n", line_info.mFileName, line_info.mLineNumber));
	}

	// Dump string with file name and line number
	if (allocation.mFileNameANSI != _null) {
		// Replace '/' to '\\' character
		_dword index = 0;
		_chara fixed_filename[1024];

		while (_true) {
			_chara code = allocation.mFileNameANSI[index];

			if (code == '/') code = '\\';

			fixed_filename[index++] = code;

			if (code == 0) break;
		}

		Platform::AppendString(dumpstringbuffer, Platform::FormatStringBuffer(tempstringbuffer, 4096, "\t%s(%u)\r\n", fixed_filename, allocation.mLineNumber));
	}
	// Dump string with line number only
	else {
		Platform::AppendString(dumpstringbuffer, Platform::FormatStringBuffer(tempstringbuffer, 4096, "\t?(%u)\r\n", allocation.mLineNumber));
	}

	// Dump 32 bytes memory data
	_dword size = Math::Min((_dword)32, allocation.mSize);

	// Dump memory buffer data
	if (address != _null) {
		_chara bufferdata[1024];
		bufferdata[0] = 0;
		for (_dword i = 0; i < size; i++) {
			_chara data = address[i];

			// Get data by character mode
			if (data == '\r' || data == '\n' || data == '\t' || data == '\b')
				data = '?';
			else if (data == 0)
				data = '.';

			// Convert character to string
			Platform::AppendString(bufferdata, Platform::FormatStringBuffer(tempstringbuffer, 4096, "%c", data));
		}

		// Update the dump string buffer
		Platform::AppendString(dumpstringbuffer, Platform::FormatStringBuffer(tempstringbuffer, 4096, "\t%s\r\n\r\n", bufferdata));
	}

	if (file != _null) {
		file->WriteString(dumpstringbuffer);
	}

#if (_ENABLE_DEBUG_STRING == 1)
	OUTPUT_DEBUG_STRING(dumpstringbuffer);
#endif
}

_void Memory::LockTailOfMemoryBlock(_byte* object, _dword allocedsize) {
	_dword* tail_address = (_dword*)(object + (allocedsize - sizeof(_dword)));
	*tail_address = 0xAABBCCDD;

	// Lock it
	//	::VirtualLock( tail_address, sizeof( _dword ) );
}

_void Memory::UnlockTailOfMemoryBlock(_byte* object, _dword allocedsize) {
	_dword* tail_address = (_dword*)(object + (allocedsize - sizeof(_dword)));
	EGE_ASSERT(*tail_address == 0xAABBCCDD);

	// Unlock it
	//	::VirtualUnlock( tail_address, sizeof( _dword ) );
}

_ubool Memory::IsEnableFullCallstackCheck(_dword line_number,
                                          const _chara* file_name) const {
	if (mIsUseFullCallstackCheck == _false) return _false;

	if (mFileNameFilter[0] != 0) {
		if (file_name == _null) return _false;

		if (Platform::SearchL2R(file_name, mFileNameFilter) == -1) return _false;
	}

	if (mLineNumberFilter != 0 && mLineNumberFilter != line_number) return _false;

	return _true;
}

_void Memory::DumpAllocations(_dword min_size, OnOutputString funcpointer,
                              const AllocationLink& allocations,
                              const QwordParams2& params) {
	// No any memory blocks
	if (allocations.Number() == 0) return;

	// Dump each memory block
	_dword id = 1;
	for (Link<MemoryAllocation>::Iterator it = allocations.GetHeadIterator(); it.IsValid(); it++, id++) {
		const MemoryAllocation& allocation = it;

		if (allocation.mSize < min_size) continue;

		// Get the base address
		_byte* address = (_byte*)GetBaseAddress(it.mNode);
		EGE_ASSERT(address != _null);

		// Dump allocation info
		(*funcpointer)(id, address, allocation, params);
	}
}

_void Memory::DumpAllocations(_dword min_size, OnOutputString funcpointer,
                              const BlockAllocationArray& allocations,
                              const QwordParams2& params) {
	// No any memory blocks
	if (allocations.Number() == 0) return;

	// Dump each memory block
	for (_dword i = 0; i < allocations.Number(); i++) {
		const MemoryBlockAllocation& allocation = allocations[i];

		if (allocation.mSize < min_size) continue;

		// Build allocation
		MemoryAllocation mem_allocation;
		mem_allocation.mReferencedID = 0;
		mem_allocation.mSize = allocation.mSize;
		mem_allocation.mLineNumber = allocation.mLineNumber;
		mem_allocation.mFileNameANSI = allocation.mFileName;
		mem_allocation.mFrameNumber = 0;
		mem_allocation.mSrcFileLines = _null;

		// Dump allocation info
		(*funcpointer)(i + 1, _null, mem_allocation, params);
	}
}

_ubool Memory::Initialize() {
#if defined(_PLATFORM_WINDOWS_) && !defined(_USE_STANDARD_MEM_OPERATOR_) && \
    !defined(_USE_STANDARD_MALLOC_OPERATOR_)
	// Initialize CRT hooker
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetAllocHook(OnCRTAllocHookCallback);
#endif

	return _true;
}

_void Memory::Finalize() {
}

_void Memory::EnableFullCallstackCheck(_ubool enable) {
	mIsUseFullCallstackCheck = enable;
}

_void Memory::SetMaxFrameNumberOfFullCallstackCheck(_dword max_frame_number) {
	mMaxFrameNumber = Math::Clamp<_dword>(max_frame_number, _DEFAULT_MIN_FRAME_NUMBER, _DEFAULT_MAX_FRAME_NUMBER);
}

_void Memory::SetFileNameFilterOfFullCallstackCheck(const _chara* filter) {
	if (filter == _null)
		filter = "";

	Platform::CopyString(mFileNameFilter, filter);
}

_void Memory::SetLineNumberFilterOfFullCallstackCheck(_dword line_number) {
	mLineNumberFilter = line_number;
}

_void Memory::AllocBlock(_dword block_number, _dword size,
                         const _chara* filename, _dword linenumber) {
#ifdef _DEBUG
	EGE_ASSERT(mBlockAllocations.SearchAscending(block_number).IsValid() == _false);
#endif

	// Increase the current allocated size
	mCurAllocSize += size;

	// Initialize block allocation
	MemoryBlockAllocation block_allocation;
	block_allocation.mBlockNumber = block_number;
	block_allocation.mSize = size;
	block_allocation.mLineNumber = linenumber;
	if (filename != _null)
		block_allocation.mFileName = Platform::HeapAllocStr(filename);

	// Insert it
	mBlockAllocations.InsertAscending(block_allocation);
}

_void Memory::ReallocBlock(_dword prev_block_number, _dword block_number, _dword size, const _chara* filename, _dword linenumber) {
	// Get old block
	BlockAllocationArray::Iterator it = mBlockAllocations.SearchAscending(prev_block_number);
	if (it.IsValid()) {
		// Get the old block info
		const MemoryBlockAllocation& old_block = it;

		// Increase the current and max allocated size
		if (size > old_block.mSize) {
			mCurAllocSize += (size - old_block.mSize);
		}
		// Decrease the current and max allocated size
		else {
			mCurAllocSize -= (old_block.mSize - size);
		}

		// Remove old block
		mBlockAllocations.Remove(it);
	} else {
		mCurAllocSize += size;
	}

	// Insert new block
	MemoryBlockAllocation block_allocation;
	block_allocation.mBlockNumber = block_number;
	block_allocation.mSize = size;
	block_allocation.mLineNumber = linenumber;
	if (filename != _null)
		block_allocation.mFileName = Platform::HeapAllocStr(filename);

	mBlockAllocations.InsertAscending(block_allocation);
}

_void Memory::FreeBlock(_dword block_number) {
	BlockAllocationArray::Iterator it = mBlockAllocations.SearchAscending(block_number);
	if (it.IsValid()) {
		MemoryBlockAllocation& block_allocation = it;

		if (block_allocation.mFileName != _null)
			Platform::HeapFree(block_allocation.mFileName);

		// Update allocate size
		EGE_ASSERT(mCurAllocSize >= block_allocation.mSize);
		mCurAllocSize -= block_allocation.mSize;

		mBlockAllocations.Remove(it);
	}
}

_void* Memory::Alloc(_dword size, const _chara* filename, _dword linenumber) {
	if (size == 0) return _null;

#if defined(_PLATFORM_WINDOWS_)
	LockOwner lock_owner(mLocker);

	// Get the allocated size
	_dword allocedsize = size + cSizeOfNode;

	// We will check the memory bounds in debug mode
#	ifdef _DEBUG
	allocedsize += sizeof(_dword);
#	endif

	// Allocate buffer from heap
	_byte* object = (_byte*)Platform::HeapAlloc(allocedsize);
	if (object == _null) return _null;

		// Set the tail to detect memory out-of-range operation
#	ifdef _DEBUG
	LockTailOfMemoryBlock(object, allocedsize);
#	endif

	// Increase the current allocated size
	mCurAllocSize += size;

	// Create memory allocation record
	Link<MemoryAllocation>::Node* node = (Link<MemoryAllocation>::Node*)object;
	node->mElement.mReferencedID = mReferencedID;
	node->mElement.mSize = size;
	node->mElement.mLineNumber = linenumber;
	node->mElement.mFileNameANSI = filename;
	node->mPrev = _null;
	node->mNext = _null;

	// Get the full callstack info
	if (IsEnableFullCallstackCheck(linenumber, filename)) {
		node->mElement.mSrcFileLines = (SymbolFileData*)Platform::GlobalAlloc(sizeof(SymbolFileData) * mMaxFrameNumber);
		node->mElement.mFrameNumber = DebugSymbol::StackWalk(_null, node->mElement.mSrcFileLines, mMaxFrameNumber);
	} else {
		node->mElement.mSrcFileLines = _null;
		node->mElement.mFrameNumber = 0;
	}

	// Insert this node into memory block link
	mMemoryAllocation.InsertTail(node);

	// Update allocated number
	mCurAllocNumber++;

	// Feedback the memory address
	return GetBaseAddress(node);
#else
	return Platform::HeapAlloc((_dword)size);
#endif
}

_void* Memory::Realloc(_void* buffer, _dword size, const _chara* filename, _dword linenumber) {
	if (buffer == _null) return Alloc(size, filename, linenumber);

#if defined(_PLATFORM_WINDOWS_)
	LockOwner lock_owner(mLocker);

	// Get the node object
	Link<MemoryAllocation>::Node* node = GetNodeAddress(buffer);
	EGE_ASSERT(node->mElement.mReferencedID == mReferencedID);

	// Backup the old buffer size
	_dword oldsize = node->mElement.mSize;

	// Skip for the same buffer size reallocation action
	if (oldsize == size) return buffer;

	// Remove it from the memory block link
	mMemoryAllocation.Remove(node);

	// Get the allocated size
	_dword allocedsize = size + cSizeOfNode;

	// We will check the memory bounds in debug mode
#	ifdef _DEBUG
	allocedsize += sizeof(_dword);
#	endif

	// Realloc it from heap
	node = (Link<MemoryAllocation>::Node*)Platform::HeapReAlloc(node, allocedsize);
	if (node == _null) return _null;

	// Copy the old buffer data
	EGE_MEM_CPY(GetBaseAddress(node), buffer, oldsize);

	// Set the tail to detect memory out-of-range operation
#	ifdef _DEBUG
	LockTailOfMemoryBlock((_byte*)node, allocedsize);
#	endif

	// Create memory allocation record
	node->mElement.mReferencedID = mReferencedID;
	node->mElement.mSize = size;
	node->mElement.mLineNumber = linenumber;
	node->mElement.mFileNameANSI = filename;
	node->mPrev = _null;
	node->mNext = _null;

	// Get the full callstack info
	if (IsEnableFullCallstackCheck(linenumber, filename)) {
		node->mElement.mSrcFileLines = (SymbolFileData*)Platform::GlobalAlloc(sizeof(SymbolFileData) * mMaxFrameNumber);
		node->mElement.mFrameNumber = DebugSymbol::StackWalk(_null, node->mElement.mSrcFileLines, mMaxFrameNumber);
	} else {
		node->mElement.mSrcFileLines = _null;
		node->mElement.mFrameNumber = 0;
	}

	// Insert this node into memory block link
	mMemoryAllocation.InsertTail(node);

	// Increase the current and max allocated size
	if (size > oldsize) {
		mCurAllocSize += (size - oldsize);
	}
	// Decrease the current and max allocated size
	else {
		mCurAllocSize -= (oldsize - size);
	}

	// Update allocated number
	mCurAllocNumber++;

	// Feedback the memory address
	return GetBaseAddress(node);
#else
	return Platform::HeapReAlloc(buffer, size);
#endif
}

_void Memory::Free(_void* pointer, const _chara* filename, _dword linenumber) {
	if (pointer == _null) return;

#if defined(_PLATFORM_WINDOWS_)
	LockOwner lock_owner(mLocker);

	// Make sure we have allocated blocks
	EGE_ASSERT(mMemoryAllocation.Number() > 0);

	// Get the node object
	Link<MemoryAllocation>::Node* node = GetNodeAddress(pointer);
	EGE_ASSERT(node->mElement.mReferencedID == mReferencedID);

	// Check the tail to detect memory out-of-range operation
#	ifdef _DEBUG
	_dword allocedsize = node->mElement.mSize + cSizeOfNode + sizeof(_dword);
	UnlockTailOfMemoryBlock((_byte*)node, allocedsize);
#	endif

	// Update allocate size
	EGE_ASSERT(mCurAllocSize >= node->mElement.mSize);
	mCurAllocSize -= node->mElement.mSize;

	// Clear the referenced ID
	node->mElement.mReferencedID = 0;

	// Clear frame info
	Platform::GlobalFree(node->mElement.mSrcFileLines);

	// Remove it from the memory block link
	mMemoryAllocation.Remove(node);

	// Free to heap
	Platform::HeapFree(node);
#else
	Platform::HeapFree(pointer);
#endif
}

_chara* Memory::AllocStr(const _chara* string, const _chara* filename, _dword linenumber) {
	_dword size = AStringPtr(string).SizeOfBytes();
	_chara* buffer = (_chara*)Alloc(size, filename, linenumber);
	EGE_MEM_CPY(buffer, AStringPtr(string).CStr(), size);

	return buffer;
}

_charw* Memory::AllocStr(const _charw* string, const _chara* filename, _dword linenumber) {
	_dword size = WStringPtr(string).SizeOfBytes();
	_charw* buffer = (_charw*)Alloc(size, filename, linenumber);
	EGE_MEM_CPY(buffer, WStringPtr(string).CStr(), size);

	return buffer;
}

_dword Memory::GetCurAllocNumber() const {
	return mCurAllocNumber;
}

_void Memory::ClearCurAllocNumber() {
	mCurAllocNumber = 0;
}

_dword Memory::GetCurAllocSize() const {
	return mCurAllocSize;
}

_dword Memory::GetTotalAllocNumber() const {
	return mMemoryAllocation.Number() + mBlockAllocations.Number();
}

_void* Memory::CreateReferencedBuffer(_dword size) {
	if (size == 0) return _null;

	_byte* realbuffer = (_byte*)Platform::GlobalAlloc(size + 8);
	if (realbuffer == _null) return _null;

	((_dword*)realbuffer)[0] = mReferencedID;
	((_dword*)realbuffer)[1] = 1;

	return realbuffer + 8;
}

_void* Memory::ReserveReferencedBuffer(_void* buffer) {
	if (buffer == _null) return _null;

	_byte* realbuffer = (_byte*)buffer - 8;

	EGE_ASSERT(((_dword*)realbuffer)[0] == mReferencedID);
	EGE_ASSERT(((_dword*)realbuffer)[1] >= 1);

	((_dword*)realbuffer)[1]++;

	return buffer;
}

_ubool Memory::ReleaseReferencedBuffer(_void* buffer) {
	if (buffer == _null) return _true;

	_byte* realbuffer = (_byte*)buffer - 8;

	EGE_ASSERT(((_dword*)realbuffer)[0] == mReferencedID);
	EGE_ASSERT(((_dword*)realbuffer)[1] >= 1);

	((_dword*)realbuffer)[1]--;

	if (((_dword*)realbuffer)[1] != 0) return _false;

	Platform::GlobalFree(realbuffer);

	return _true;
}

_ubool Memory::IsReferencedBuffer(_void* buffer) {
	if (buffer == _null) return _false;

	_byte* realbuffer = (_byte*)buffer - 8;

	return ((_dword*)realbuffer)[0] == mReferencedID;
}

_void Memory::Dump(_dword min_size, OnOutputString funcpointer,
                   const QwordParams2& params) {
	DumpAllocations(min_size, funcpointer, mMemoryAllocation, params);
	DumpAllocations(min_size, funcpointer, mBlockAllocations, params);
}

_void Memory::DumpLeakInfo() {
	File* file = _null;

#ifdef _PLATFORM_WINDOWS_
	File log_file;
	if (log_file.Create(L"memory_leak.log") == _false)
		return;

	file = &log_file;
#endif

	Dump(0, OnOutputStringCallback, QwordParams2((_qword)file, _null));
	mBlockAllocations.Clear(_true);
}
