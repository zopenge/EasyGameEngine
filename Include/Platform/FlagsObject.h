//! @file     FlagsObject.h
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FlagsObject
//----------------------------------------------------------------------------

class FlagsObject
{
public:
 static FlagsObject cNull;

protected:
 _dword mFlags;

public:
 FlagsObject( );
 FlagsObject( _dword flags );
 FlagsObject( const FlagsObject& flags );
 ~FlagsObject( );

public:
 //! Convert to 32 bits value.
 operator _dword( ) const;

 //! Combine flags.
 FlagsObject& operator += ( _dword flags );
 FlagsObject operator + ( _dword flags ) const;
 FlagsObject& operator |= ( _dword flags );
 FlagsObject operator | ( _dword flags ) const;
 //! Remove flags.
 FlagsObject& operator -= ( _dword flags );
 FlagsObject operator - ( _dword flags ) const;

 //! Compare flags.
 _ubool operator == ( _dword flags ) const;
 //! Compare flags.
 _ubool operator != ( _dword flags ) const;

public:
 //! Clear all flags.
 //! @param none.
 //! @return none.
 _void Clear( );

 //! Check whether has the specified flags or not.
 //! @param flags  The flags would be checked.
 //! @param match_all True indicates must match all flags.
 //! @return True indicates has this flag.
 _ubool HasFlags( _dword flags, _ubool match_all = _false ) const;
 //! Enable/Disable flag.
 //! @param flags  The flags would be checked.
 //! @param enable  True indicates enable it.
 //! @return none.
 _void EnableFlags( _dword flags, _ubool enable );
 //! Combine flags.
 //! @param flags  The flags would be combined.
 //! @return none.
 _void CombineFlags( _dword flags );
 //! Clear flags.
 //! @param flags  The flags would be cleared.
 //! @return none.
 _void ClearFlags( _dword flags );

 //! Set the flags.
 //! @param flags  The flags.
 //! @return none.
 _void SetFlags( _dword flags );
 //! Get the flags.
 //! @param none.
 //! @return The flags.
 _dword GetFlags( ) const;
};

//----------------------------------------------------------------------------
// FlagsObject Implementation
//----------------------------------------------------------------------------

inline FlagsObject::FlagsObject( ) : mFlags( 0 )
{
}

inline FlagsObject::FlagsObject( _dword flags ) : mFlags( flags )
{
}

inline FlagsObject::FlagsObject( const FlagsObject& flags ) : mFlags( flags.GetFlags( ) )
{
}

inline FlagsObject::~FlagsObject( )
{

}

inline FlagsObject::operator _dword( ) const
{
 return mFlags;
}

inline FlagsObject& FlagsObject::operator += ( _dword flags )
{
 mFlags |= flags;

 return *this;
}

inline FlagsObject FlagsObject::operator + ( _dword flags ) const
{
 FlagsObject flags_object( mFlags );
 flags_object += flags;

 return flags_object;
}

inline FlagsObject& FlagsObject::operator |= ( _dword flags )
{
 mFlags |= flags;

 return *this;
}

inline FlagsObject FlagsObject::operator | ( _dword flags ) const
{
 FlagsObject flags_object( mFlags );
 flags_object |= flags;

 return flags_object;
}

inline FlagsObject& FlagsObject::operator -= ( _dword flags )
{
 mFlags &= ~flags;

 return *this;
}

inline FlagsObject FlagsObject::operator - ( _dword flags ) const
{
 FlagsObject flags_object( mFlags );
 flags_object -= flags;

 return flags_object;
}

inline _ubool FlagsObject::operator == ( _dword flags ) const
{
 return mFlags == flags;
}

inline _ubool FlagsObject::operator != ( _dword flags ) const
{
 return mFlags != flags;
}

inline _void FlagsObject::Clear( )
{
 mFlags = 0;
}

inline _ubool FlagsObject::HasFlags( _dword flags, _ubool match_all ) const
{
 if ( match_all )
  return ( mFlags & flags ) == flags;
 else
  return ( mFlags & flags ) != 0;
}

inline _void FlagsObject::EnableFlags( _dword flags, _ubool enable )
{
 if ( enable )
  CombineFlags( flags );
 else
  ClearFlags( flags );
}

inline _void FlagsObject::CombineFlags( _dword flags )
{
 mFlags |= flags;
}

inline _void FlagsObject::ClearFlags( _dword flags )
{
 mFlags &= ~flags;
}

inline _void FlagsObject::SetFlags( _dword flags )
{
 mFlags = flags;
}

inline _dword FlagsObject::GetFlags( ) const
{
 return mFlags;
}

}
