//! @file     winLibrary.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

// VersionInfoBase
template< typename Type >
struct VersionInfoBase
{
 _word mLength; 
 _word mValueLength; 
 _word mType; 
 _charw mKeyName[1];

 inline _ubool IsValidPtr( const _void* ptr ) const
  { return EGE_PTR_WITHIN( ptr, &mLength, mLength ); }

 inline const Type* GetNext( ) const
  { return (const Type*) EGE_ALIGN_UP32( (_dword) &mLength + mLength ); }

 inline const _charw* GetValue( ) const
  { return (const _charw*) EGE_ALIGN_UP32( mKeyName + wcslen( mKeyName ) + 1 ); }
};

// StringData
struct StringData : public VersionInfoBase< StringData >
{

};

// StringTableData
struct StringTableData : public VersionInfoBase< StringTableData >
{
 inline const StringData* GetChildren( ) const
  { return (const StringData*) EGE_ALIGN_UP32( mKeyName + 9 ); }
};

// StringFileInfo
struct StringFileInfo : public VersionInfoBase< StringFileInfo >
{
    inline _ubool IsValid( ) const
  { return Platform::CompareString( mKeyName, L"StringFileInfo" ) == 0; }

 inline const StringTableData* GetChildren( ) const
  { return (const StringTableData*) EGE_ALIGN_UP32( mKeyName + 15 ); }
};

// VarInfo
struct VarInfo : public VersionInfoBase< VarInfo >
{
 _word   mPadding;
 _dword mValue;
};

// VarFileInfo
struct VarFileInfo : public VersionInfoBase< VarFileInfo >
{
 _word mPadding;
 VarInfo mChildren;

 inline const VarInfo* GetChildren( ) const
  { return (const VarInfo*) EGE_ALIGN_UP32( mKeyName + 12 ); }
};

// VersionInfo
struct VersionInfo : public VersionInfoBase< VersionInfo >
{
 _charw    mPaddingKeyName[15];
 _word    mPadding;
 VS_FIXEDFILEINFO mFixedFileInfo[1];

    inline _ubool IsValid( ) const
  { return Platform::CompareString( mKeyName, L"VS_VERSION_INFO" ) == 0; }
 
 inline const StringFileInfo* GetChildren( ) const
  { return (const StringFileInfo*) EGE_ALIGN_UP32( (_dword) mFixedFileInfo + mValueLength ); }
};

//! Get the aligned size in bytes.
static _dword GetAlignedSize( _dword origin, _dword alignment )
{ 
 return ( origin + alignment - 1 ) / alignment * alignment; 
} 

//! The DllMain function declaration
typedef _int (*DllMainFunc)( _handle, _dword, _void* );

//----------------------------------------------------------------------------
// Library Implementation
//----------------------------------------------------------------------------

_ubool Library::LoadVersionInfo( const _void* address )
{
 // Get the DLL version info
 const VersionInfo* versioninfo = (const VersionInfo*) address;
 if ( versioninfo->IsValid( ) == _false )
  return _false;

 // Get the DLL string file info
 const StringFileInfo* stringfileinfo = versioninfo->GetChildren( );
 if ( stringfileinfo->IsValid( ) == _false )
  return _false;

 // Get the string table data
 const StringTableData* stringtabledata = stringfileinfo->GetChildren( );

 // Get the string data
 const StringData* stringdata = stringtabledata->GetChildren( );

 // Analyze the string data
 while ( stringtabledata->IsValidPtr( stringdata ) )
 {
  // Get the key name
  WStringPtr keyname = stringdata->mKeyName;

  // It's internal name
  if ( keyname == L"InternalName" )
  {
   mInternalName = stringdata->GetValue( );
  }
  // It's copyright
  else if ( keyname == L"LegalCopyright" )
  {
   mCopyright = stringdata->GetValue( );
  }
  // It's product version 
  else if ( keyname == L"ProductVersion" )
  {
   mVersion = stringdata->GetValue( );
  }

  // Jump to the next string data
  stringdata = stringdata->GetNext( );
 }

 // Get the var file info data
 const VarFileInfo* varfileinfo = (const VarFileInfo*) stringdata;

 // Get the var info data
 const VarInfo* varinfo = varfileinfo->GetChildren( );

 // Analyze the var info
 while ( varfileinfo->IsValidPtr( varinfo ) )
 {
  // Jump to the next var info data
  varinfo = varinfo->GetNext( );
 }

 return _true;
}

_ubool Library::LoadEmbeddedManifestInfo( const _void* address, _dword size )
{
 // Copy the embedded manifest info
 mEmbeddedManifest.CopyString( (const _chara*) address, size );

 return _true;
}

_ubool Library::LoadResourceFromMemory( _dword virtualaddress, const _byte* base, const _byte* resource )
{
 // Get the image resource directory entry array address
 const IMAGE_RESOURCE_DIRECTORY_ENTRY* entries = (const IMAGE_RESOURCE_DIRECTORY_ENTRY*) ( resource + sizeof( IMAGE_RESOURCE_DIRECTORY ) );

 // Get the resource entry number
 _dword number = ( (const IMAGE_RESOURCE_DIRECTORY*) resource )->NumberOfNamedEntries + ( (const IMAGE_RESOURCE_DIRECTORY*) resource )->NumberOfIdEntries;

 // Analyze the resource entry
 for ( _dword i = 0; i < number; i ++ )
 {
  // Use string to identify the resource 
  if ( entries[i].NameIsString )
  {
   // Get the resource string
   const IMAGE_RESOURCE_DIR_STRING_U* resourcestring = (const IMAGE_RESOURCE_DIR_STRING_U*) ( base + entries[i].NameOffset );
  }
  // Use ID to identify the resource
  else
  {

  }

  // Has the sub-directory resource
  if ( entries[i].DataIsDirectory )
  {
   // Load the sub-directory resource
   if ( LoadResourceFromMemory( virtualaddress, base, base + entries[i].OffsetToDirectory ) == _false )
    return _false;
  }
  // We reach the resource data entry now
  else
  {
   const IMAGE_RESOURCE_DATA_ENTRY* resourcedata = (const IMAGE_RESOURCE_DATA_ENTRY*) ( base + entries[i].OffsetToDirectory );

   // Get the offset of resource
   _dword offset = resourcedata->OffsetToData - virtualaddress;

   // It's DLL version section
   if ( entries[i].Id == 2052 )
   {
    // Load the DLL version info
    if ( LoadVersionInfo( base + offset ) == _false )
     return _false;
   }
   // It's embedded manifest
   else if ( entries[i].Id == 1033 )
   {
    // Load the DLL embedded manifest info
    if ( LoadEmbeddedManifestInfo( base + offset, resourcedata->Size ) == _false )
     return _false;
   }
   // Other resources
   else
   {
   }
  }
 }

 return _true;
}

_ubool Library::Load( const _byte* buffer, _dword size, OnLoadDependentDLL funcpointer, const QwordParameters2& parameters )
{
 if ( buffer == _null )
  return _false;

 // Free the previous DLL module
 Free( );

 // It's loaded from the memory
 mLibInMemory = _true;

 // Check the library file size
 if ( size < sizeof( IMAGE_DOS_HEADER ) )
  return _false;

 // Check the DOS header
 IMAGE_DOS_HEADER* dosheader = (IMAGE_DOS_HEADER*) buffer;
 if ( dosheader->e_magic != IMAGE_DOS_SIGNATURE || size < dosheader->e_lfanew + sizeof( IMAGE_NT_HEADERS ) )
  return _false;

 // Get the PE header
 IMAGE_NT_HEADERS* ntheader = (IMAGE_NT_HEADERS*) ( buffer + dosheader->e_lfanew );
 if ( ntheader->Signature != IMAGE_NT_SIGNATURE || ( ( ntheader->FileHeader.Characteristics & IMAGE_FILE_DLL ) == 0 ) )
  return _false;

 // The PE file must can be run
 if ( ( ntheader->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE ) == 0 )
  return _false;

 // Check the optional header size
 if ( ntheader->FileHeader.SizeOfOptionalHeader != sizeof( IMAGE_OPTIONAL_HEADER ) )
  return _false;

 // Get the DOS, COFF, PE header and sections size ( total image size )
 _dword totalimagesize = GetAlignedSize( ntheader->OptionalHeader.SizeOfHeaders, ntheader->OptionalHeader.SectionAlignment );

 // Check the section header
 IMAGE_SECTION_HEADER* sectionheader = (IMAGE_SECTION_HEADER*) ( (const _byte*) ntheader + sizeof( IMAGE_NT_HEADERS ) ); 
 for ( _dword i = 0; i < ntheader->FileHeader.NumberOfSections; i ++ )
 {
  if ( ( sectionheader[i].PointerToRawData + sectionheader[i].SizeOfRawData ) > size )
   return _false;

  // Get the max section size
  _dword codesize = sectionheader[i].Misc.VirtualSize;
  _dword loadsize = sectionheader[i].SizeOfRawData;
  _dword maxsize = Math::Max( loadsize, codesize );

  // Get the section size
  _dword sectionsize = GetAlignedSize( sectionheader[i].VirtualAddress + maxsize, ntheader->OptionalHeader.SectionAlignment ); 
  if ( totalimagesize < sectionsize ) 
   totalimagesize = sectionsize;
 }

 // Check the total image size
 if ( totalimagesize == 0 )
  return _false;

 // Allocate memory to store DLL data
 _byte* memoryaddress = (_byte*) Platform::VirtualAlloc( totalimagesize );
 if ( memoryaddress == _null )
  return _false;

 // Set the module handle as virtual memory address
 mModule = memoryaddress;

 // Copy headers and section data
 EGE_MEM_CPY( memoryaddress, buffer, ntheader->OptionalHeader.SizeOfHeaders + ntheader->FileHeader.NumberOfSections * sizeof( IMAGE_SECTION_HEADER ) );

 // Copy sections
 for ( _dword i = 0; i < ntheader->FileHeader.NumberOfSections; i ++ )
 {
  if ( sectionheader[i].VirtualAddress == 0 || sectionheader[i].SizeOfRawData == 0 )
   continue;

  // Get the section address
  _void* sectionaddress = memoryaddress + sectionheader[i].VirtualAddress;

  // Copy the section into virtual memory
  EGE_MEM_CPY( sectionaddress, buffer + sectionheader[i].PointerToRawData, sectionheader[i].SizeOfRawData );
 }

 // Fixed the DOS, PE and Section headers
 dosheader  = (IMAGE_DOS_HEADER*) memoryaddress;
 ntheader  = (IMAGE_NT_HEADERS*) ( memoryaddress + dosheader->e_lfanew );
 sectionheader = (IMAGE_SECTION_HEADER*) ( (_byte*) ntheader + sizeof( IMAGE_NT_HEADERS ) );

 // Set the NT header
 mNTHeader = ntheader;

 // Get the DLL resource data
 if ( ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_RESOURCE ].VirtualAddress > 0 && ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_RESOURCE ].Size > 0 )
 {
  const _byte* resource = (const _byte*) ( memoryaddress + ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_RESOURCE ].VirtualAddress );

  // Load DLL resource from memory
  if ( LoadResourceFromMemory( ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_RESOURCE ].VirtualAddress, resource, resource ) == _false )
   return _false;
 }

 // Relocate DLL data
 if ( ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress > 0 && ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].Size > 0 )
 {
  _dword delta = (_dword) memoryaddress - ntheader->OptionalHeader.ImageBase;

  // Get the base relocation
  IMAGE_BASE_RELOCATION* relocation = (IMAGE_BASE_RELOCATION*) ( memoryaddress + ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ].VirtualAddress );

  // Start to scan it
  while ( ( relocation->VirtualAddress + relocation->SizeOfBlock ) != 0 )
  {
   _word* locationdata = (_word*) ( (_byte*) relocation + sizeof( IMAGE_BASE_RELOCATION ) ); 

   // Get the number of relocations
   _dword number = ( relocation->SizeOfBlock - sizeof( IMAGE_BASE_RELOCATION ) ) / sizeof( _word );

   for ( _dword i = 0; i < number; i ++ )
   {
    if ( ( locationdata[i] & 0xF000 ) != 0x00003000 )
     continue;

    // Relocate it
    _dword* address = (_dword*)( memoryaddress + relocation->VirtualAddress + ( locationdata[i] & 0x0FFF ) ); 
    *address += delta; 
   }

   // Jump to the next relocation
   relocation = (IMAGE_BASE_RELOCATION*) ( (const _byte*) relocation + relocation->SizeOfBlock );
  }
 }

 // Get the import table offset
 _dword importtableoffset = ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ].VirtualAddress;
 if ( importtableoffset == 0 )
  return _false;

 // Get the import descriptor
 IMAGE_IMPORT_DESCRIPTOR* importdescriptor = (IMAGE_IMPORT_DESCRIPTOR*) ( memoryaddress + importtableoffset ); 

 while ( importdescriptor->Characteristics != 0 ) 
 { 
  IMAGE_THUNK_DATA* real_iat  = (IMAGE_THUNK_DATA*) ( memoryaddress + importdescriptor->FirstThunk ); 
  IMAGE_THUNK_DATA* original_iat = (IMAGE_THUNK_DATA*) ( memoryaddress + importdescriptor->OriginalFirstThunk ); 
  
  // Get the DLL name
  const _chara* name = (const _chara*) ( memoryaddress + importdescriptor->Name );

  // The dll module handle
  _handle dll = Platform::GetModuleHandleA( name );
  if ( dll == _null )
  {
   // Invoke the load dependence DLL callback function
   if ( funcpointer != _null )
    dll = (HMODULE) (*funcpointer)( name, parameters );

   // If the user didn't handle the DLL then we load it in the normal way
   dll = Platform::LoadLibrary( name );
   if ( dll == _null )
    return _false;
  }

  // Get all functions from dll library
  for ( _dword i = 0; ; i ++ )
  {
   if ( original_iat[i].u1.Function == 0 )
    break;

   // Import function
   FARPROC function = _null;
   if ( original_iat[i].u1.Ordinal & IMAGE_ORDINAL_FLAG )
   {
    function = (FARPROC) Platform::GetProcAddress( dll, (LPCSTR) ( original_iat[i].u1.Ordinal & 0x0000FFFF ) );
   }
   else
   {
    IMAGE_IMPORT_BY_NAME* importbyname = (IMAGE_IMPORT_BY_NAME*) ( memoryaddress + original_iat[i].u1.AddressOfData );
    function = (FARPROC) Platform::GetProcAddress( dll, (_chara*) importbyname->Name ); 
   }

   // Check the imported function
   if ( function == _null )
    return _false;

   // We found it
   real_iat[i].u1.Function = (_dword) function;
  }

  // Jump to the next import descriptor
  importdescriptor = (IMAGE_IMPORT_DESCRIPTOR*) ( (const _byte*) importdescriptor + sizeof( IMAGE_IMPORT_DESCRIPTOR ) );
 }

 // Fixed the base address
 ntheader->OptionalHeader.ImageBase = (_dword) memoryaddress;

 // Invoke the DLL entrance function
 mDllMainFunc = (_handle)( memoryaddress + ntheader->OptionalHeader.AddressOfEntryPoint ); 
 if ( (*(DllMainFunc*)(mDllMainFunc))( memoryaddress, DLL_PROCESS_ATTACH, 0 ) == 0 )
 {
  // Attach DLL failed, now we detach it
  (*(DllMainFunc*)(mDllMainFunc))( memoryaddress, DLL_PROCESS_DETACH, 0 ); 
  return _false; 
 }

 return _true;
}

_void Library::Free( )
{
 if ( mModule == _null )
  return;

 // Free library memory
 if ( mLibInMemory == _true )
 {
  // Detach DLL
  if ( mDllMainFunc != _null )
   (*(DllMainFunc*)(mDllMainFunc))( mModule, DLL_PROCESS_DETACH, 0 ); 

  // Free virtual memory
  Platform::VirtualFree( (_void*) mModule ); 
 }
 // Free library using win32 API
 else
 {
  Platform::FreeLibrary( mModule );
 }

 mLibInMemory = _false;
 mModule   = _null;
 mNTHeader  = _null;
 mDllMainFunc = _null;

 // Clear the library resource
 mInternalName = L"";
 mCopyright  = L"";
 mVersion  = Version::cZero;
}

_void* Library::GetFunction( AStringPtr functionname ) const
{
 if ( mModule == _null )
  return _null;

 // Get function from library memory
 if ( mLibInMemory == _true )
 {
  // get the base memory
  const _byte* basememory = (const _byte*) mModule;
  if ( basememory == _null )
   return _null;

  // Get the NT header
  const IMAGE_NT_HEADERS* ntheader = (const IMAGE_NT_HEADERS*) mNTHeader;
  if ( ntheader == _null )
   return _null;

  // Check the data directory
  if ( ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress == 0 || ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].Size == 0 )
   return _null; 

  // Get the offset start and size of data directory
  _dword offsetstart = ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress;
  _dword size   = ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].Size; 

  // Get the export directory
  IMAGE_EXPORT_DIRECTORY* exportdirectory = (IMAGE_EXPORT_DIRECTORY*) ( basememory + ntheader->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress );

  // Get the export directory info
  _dword  exportbase  = exportdirectory->Base; 
  _dword  functionnumber = exportdirectory->NumberOfFunctions; 
  _dword  namenumber  = exportdirectory->NumberOfNames;
  _dword* functionaddress = (_dword*)( basememory + exportdirectory->AddressOfFunctions ); 
  _word* ordinaladdress = (_word*)( basememory + exportdirectory->AddressOfNameOrdinals ); 
  _dword* nameaddress  = (_dword*)( basememory + exportdirectory->AddressOfNames ); 

  // Try to find the ordinal of function by name
  for ( _dword i = 0; i < namenumber; i ++ ) 
  {
   // Get the export function name
   const _chara* name = (const _chara*)( basememory + nameaddress[i] ); 

   // Compare the function name
   if ( functionname == name )
   {
    // Get the function offset
    _dword functionoffset = functionaddress[ ordinaladdress[i] ];
    if ( functionoffset > offsetstart && functionoffset < ( offsetstart + size ) )
     return _null; 

    // Feedback the function interface
    return (_void*)( basememory + functionoffset ); 
   } 
  }

  // The function is not existing
  return _null;
 }
 // Get function pointer from module handle
 else
 {
  return Platform::GetProcAddress( mModule, functionname.Str( ) );
 }
}