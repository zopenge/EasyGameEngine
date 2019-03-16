//! @file     TLogger.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TLogger
//----------------------------------------------------------------------------

template< typename Type >
class TLogger : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	//!	The thread lock
	Lock		mLock;

	//!	The filter flags
	FlagsObject	mFilterFlags;
	//!	The options
	FlagsObject	mOptions;

	//!	The history	log string
	WString		mHistoryLogString;

protected:
	//!	When pre-write log string.
	virtual _void OnPreWriteLogString( _LOG type, WString& string ) PURE;
	//!	When write log string.
	virtual _void OnWriteLogString( WStringPtr string ) PURE;

protected:
	//!	Build the current thread ID string.
	static WString BuildCurrentThreadIDString( );
	//!	Build the current time string.
	static WString BuildCurrentTimeString( );
	//!	Build the log type string.
	static WStringPtr BuildLogTypeString( _LOG type );

	//!	Append the log section name.
	static _void AppendLogSectionName( WString& log_string, WStringPtr name );

protected:
	TLogger( );
	virtual ~TLogger( );

// ILogger Interface
public:
	virtual const FlagsObject&	GetFilterFlags( ) const override;
	virtual _void				SetFilterFlags( _dword flags ) override;

	virtual _void				EnableOption( _dword option, _ubool enable ) override;
	virtual _ubool				IsEnableOption( _dword option ) const override;

	virtual WStringPtr			GetHistoryLog( ) const override;
	virtual _void				ClearHistoryLog( ) override;

	virtual _void				Write( _LOG type, WStringPtr string ) override;
	virtual _void				Write( _LOG type, WStringPtr category, WStringPtr string ) override;

	virtual _void				WriteOriginalLog( WStringPtr string ) override;
};

//----------------------------------------------------------------------------
// TLogger Implementation
//----------------------------------------------------------------------------

template< typename Type >
TLogger< Type >::TLogger( )
{
}

template< typename Type >
TLogger< Type >::~TLogger( )
{
}

template< typename Type >
WString TLogger< Type >::BuildCurrentThreadIDString( )
{
	_thread_id id = Platform::GetCurrentThreadID( );

	return FORMAT_WSTRING_1( L"0x%.16llx", id );
}

template< typename Type >
WString TLogger< Type >::BuildCurrentTimeString( )
{
	// Get the current local time
	CalendarTime currenttime;
	Platform::GetLocalTime( currenttime );

	// Build the time string
	return Time( currenttime ).ToWString( );
}

template< typename Type >
WStringPtr TLogger< Type >::BuildLogTypeString( _LOG type )
{
	switch ( type )
	{
		case _LOG_DEBUG:	return L"D";
		case _LOG_TRACE:	return L"T";
		case _LOG_ERROR:	return L"E";
		case _LOG_WARNING:	return L"W"; 
		case _LOG_FATAL:	return L"F"; 
		default:
			return L"?";
	}
}

template< typename Type >
_void TLogger< Type >::AppendLogSectionName( WString& log_string, WStringPtr name )
{
	if ( name.IsEmpty( ) )
		return;

	log_string += L"[";
	log_string += name;
	log_string += L"]";
}

template< typename Type >
const FlagsObject& TLogger< Type >::GetFilterFlags( ) const
{
	return mFilterFlags;
}

template< typename Type >
_void TLogger< Type >::SetFilterFlags( _dword flags )
{
	mFilterFlags = flags;
}

template< typename Type >
_void TLogger< Type >::EnableOption( _dword option, _ubool enable )
{
	mOptions.EnableFlags( option, enable );
}

template< typename Type >
_ubool TLogger< Type >::IsEnableOption( _dword option ) const
{
	return mOptions.HasFlags( option );
}

template< typename Type >
WStringPtr TLogger< Type >::GetHistoryLog( ) const
{
	return mHistoryLogString;
}

template< typename Type >
_void TLogger< Type >::ClearHistoryLog( )
{
	LockOwner lock_owner( mLock );

	mHistoryLogString.Clear( );
}

template< typename Type >
_void TLogger< Type >::Write( _LOG type, WStringPtr string )
{
	Write( type, L"", string );
}

template< typename Type >
_void TLogger< Type >::Write( _LOG type, WStringPtr category, WStringPtr string )
{
	if ( string.IsEmpty( ) )
		return;

	// Append the section info of log string
	WString log_string;
	AppendLogSectionName( log_string, BuildLogTypeString( type ) );
	AppendLogSectionName( log_string, BuildCurrentThreadIDString( ) );
	if ( mFilterFlags.HasFlags( ILogger::_FILTER_WITH_TIME ) )
		AppendLogSectionName( log_string, BuildCurrentTimeString( ) );
	if ( mFilterFlags.HasFlags( ILogger::_FILTER_WITH_CATEGORY ) )
		AppendLogSectionName( log_string, category );

	// Pre-Write log string
	OnPreWriteLogString( type, log_string );

	// Append the log string
	log_string += string;
	log_string += L"\n";

	// Write log string
	WriteOriginalLog( log_string );
}

template< typename Type >
_void TLogger< Type >::WriteOriginalLog( WStringPtr string )
{
	// Update history log string
	if ( mOptions.HasFlags( ILogger::_OPTION_KEEP_HISTORY ) )
	{
		mLock.Enter( );
		mHistoryLogString += string;
		mLock.Leave( );
	}
	
	// Write log string
	OnWriteLogString( string );
}

}