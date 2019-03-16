//! @file     NSMappedFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// NSMappedFile
//----------------------------------------------------------------------------

//!	Thanks for sharing code: http://memfrag.se/blog/Memory-Mapped-Files
@interface NSMappedFile : NSObject
{
@private
	NSString *path;
	void *baseAddress;
	NSUInteger size;
}

// The path of the file to map into memory.
@property (nonatomic, readonly) NSString *path;

// The memory address where the file is mapped.
// NULL when the file is not mapped into memory.
@property (nonatomic, readonly) void *baseAddress;

// Total size of the file.
@property (nonatomic, readonly) NSUInteger size;

// Returns YES when the file is mapped into memory.
@property (nonatomic, readonly) BOOL isMapped;

// Prepares to map the specified file, but does not
// actually map the file into memory.
- (id)initWithPath:(NSString *)pathToFile;

// Maps the file into memory.
// Returns pointer to start of file or NULL if unsuccessful.
- (void *)map;

// Unmaps the file from memory.
// The pointer returned by map is no longer valid.
- (void)unmap;

@end