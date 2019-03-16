//! @file     EGE_Memory.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    The EGE::Memory config of EasyGameEngine
//! Copyright ...

#pragma once

#ifndef _USE_STANDARD_MEM_OPERATOR_

#ifdef _PLATFORM_WINDOWS_

	#ifndef _USE_STANDARD_MALLOC_OPERATOR_
		#define EGE_HEAP_FREE_API	_CRTNOALIAS
		#define EGE_HEAP_ALLOC_API	_CRTNOALIAS _CRTRESTRICT

		#undef realloc
		#undef malloc
		#undef calloc
		#undef free

		#define free	ege_free
		#define calloc	ege_calloc
		#define malloc	ege_malloc
		#define realloc	ege_realloc

		#define ege_malloc( s )     _ege_malloc( s, __FILE__, __LINE__ )
		#define ege_calloc( n, s )  _ege_calloc( n, s, __FILE__, __LINE__ )
		#define ege_realloc( p, s ) _ege_realloc( p, s, __FILE__, __LINE__ )
		#define ege_free( p )       _ege_free( p, __FILE__, __LINE__ )

		// Overload Malloc And Free Operations
		#ifdef _cplusplus
		extern "C" {
		#endif
		void  _ege_free( void* pointer, const char* filename, int linenumber );
		void* _ege_malloc( size_t size, const char* filename, int linenumber );
		void* _ege_calloc( size_t number, size_t size, const char* filename, int linenumber );
		void* _ege_realloc( void* pointer, size_t size, const char* filename, int linenumber );
		#ifdef _cplusplus
		}
		#endif
	#endif

#endif // _PLATFORM_WINDOWS_

#ifndef _DISABLE_OVERLOAD_NEW_DELETE
	// Overload New And Delete Operations
	void* operator new ( size_t size );
	void* operator new ( size_t size, const char* filename, int linenumber );
	void* operator new[] ( size_t size );
	void* operator new[] ( size_t size, const char* filename, int linenumber );
	void operator delete ( void* pointer );
	void operator delete ( void* pointer, const char* filename, int linenumber );
	void operator delete[] ( void* pointer );
	void operator delete[] ( void* pointer, const char* filename, int linenumber );

	#define new new( __FILE__, __LINE__ )
#endif // _DISABLE_OVERLOAD_NEW_DELETE

#endif // _USE_STANDARD_MEM_OPERATOR_