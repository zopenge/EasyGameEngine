//! @file     chromeAppThread.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// chromeAppThread
//----------------------------------------------------------------------------

class chromeAppThread : public Thread
{
private:
	_void InitFileSystem( );

// Thread Interface
private:
	virtual _dword	OnRunThread( const QwordParameters2& parameters ) override;
	virtual _void	OnCloseThread( _dword exitcode, const QwordParameters2& parameters ) override;

public:
	chromeAppThread( );
	virtual ~chromeAppThread( );

public:
	_ubool Initialize( );
	_void Finalize( );
};

// --------------------------------------------------------------------------------------------------------------
// chromeAppThread Implementation
// --------------------------------------------------------------------------------------------------------------

}