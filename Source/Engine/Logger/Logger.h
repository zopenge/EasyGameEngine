//! @file     Logger.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Logger
//----------------------------------------------------------------------------

class Logger : public TLogger< ILogger >
{
private:
	typedef TLogger< ILogger > BaseClass;

// TLogger Interface
private:
	virtual _void	OnPreWriteLogString( _LOG type, WString& string ) override;
	virtual _void	OnWriteLogString( WStringPtr string ) override;

public:
	Logger( );
	virtual ~Logger( );
};

//----------------------------------------------------------------------------
// FileLogger
//----------------------------------------------------------------------------

class FileLogger : public TLogger< ILogger >
{
private:
	typedef TLogger< ILogger > BaseClass;

private:
	//!	The log file
	File	mLogFile;

// TLogger Interface
private:
	virtual _void	OnPreWriteLogString( _LOG type, WString& string ) override;
	virtual _void	OnWriteLogString( WStringPtr string ) override;

public:
	FileLogger( );
	virtual ~FileLogger( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr appname );
};

}