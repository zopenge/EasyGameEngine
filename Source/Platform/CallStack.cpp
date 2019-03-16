//! @file     CallStack.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// CallStack Implementation
//----------------------------------------------------------------------------

_void CallStack::OnCallStackFrameCallback( _dword linenumber, const _chara* funcname, const _chara* filename, _void* parameter1, _void* /*parameter2*/ )
{
 CallStack* callstack = (CallStack*) parameter1;
 EGE_ASSERT( callstack != _null );

 callstack->Create( linenumber, funcname, filename );
}

_void CallStack::Create( _dword linenumber, const _chara* funcname, const _chara* filename )
{
 // Get function name and file name total bytes size
 _dword funcnamesize = funcname ? Platform::StringLength( funcname ) + 1 : 0;
 _dword filenamesize = filename ? Platform::StringLength( filename ) + 1 : 0;

 // Get the total size of callstack frame
 _dword totalsize = funcnamesize + filenamesize + sizeof( CallStackFrameNode );

 // Allocate memory space
 _byte* buffer = (_byte*) Platform::HeapAlloc( totalsize );
 EGE_ASSERT( buffer != _null );

 // Create link node to store stack frame
 CallStackFrameNode* linknode = (CallStackFrameNode*) buffer;
 linknode->mPrev     = _null;
 linknode->mNext     = _null;

 // Update the buffer pointer
 buffer += sizeof( CallStackFrameNode );

 // Build callstack frame
 CallStackFrame& callstackframe = linknode->mElement;
 callstackframe.mLineNumber  = linenumber;
 callstackframe.mFuncName  = _null;
 callstackframe.mFileName  = _null;

 // Copy the function name 
 if ( funcname != _null )
 {
  callstackframe.mFuncName = (_chara*) buffer;
  EGE_MEM_CPY( callstackframe.mFuncName, funcname, funcnamesize );

  // Update the buffer pointer
  buffer += funcnamesize;
 }
 
 // Copy the file name 
 if ( filename != _null )
 {
  callstackframe.mFileName = (_chara*) buffer;
  EGE_MEM_CPY( callstackframe.mFileName, filename, filenamesize );
 }

 // Insert to stack frame list.
 Link< CallStackFrame >::InsertTail( linknode );
}

_void CallStack::Create( _dword linenumber, const _charw* funcname, const _charw* filename )
{
 // Convert function name to ANSI
 _chara funcname_ansi[1024]; funcname_ansi[0] = 0;
 if ( funcname != _null )
  Platform::Utf16ToAnsi( funcname_ansi, 1024, funcname );

 // Convert file name to ANSI
 _chara filename_ansi[1024]; filename_ansi[0] = 0;
 if ( filename != _null )
  Platform::Utf16ToAnsi( filename_ansi, 1024, filename );

 // Create the callstack frame
 Create( linenumber, funcname ? funcname_ansi : _null, filename ? filename_ansi : _null );
}

_void CallStack::Release( )
{
 while ( mHead != _null )
 {
  Node* temp = mHead; mHead = temp->mNext;

  Platform::HeapFree( temp );
 }

 Link< CallStackFrame >::Clear( );
}