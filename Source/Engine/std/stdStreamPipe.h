//! @file     stdStreamBuf.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// stdStreamPipe
//----------------------------------------------------------------------------

class stdStreamPipe : public Pipe
{
protected:
	_dword	mID;
	_handle	mOldHandle;

protected:
	stdStreamPipe( _dword id );
	~stdStreamPipe( );
};

//----------------------------------------------------------------------------
// stdTraceStreamPipe
//----------------------------------------------------------------------------

class stdTraceStreamPipe : public stdStreamPipe
{
private:
	typedef stdStreamPipe BaseClass;

public:
	stdTraceStreamPipe( );
	~stdTraceStreamPipe( );
};

//----------------------------------------------------------------------------
// stdErrorStreamPipe
//----------------------------------------------------------------------------

class stdErrorStreamPipe : public stdStreamPipe
{
private:
	typedef stdStreamPipe BaseClass;

public:
	stdErrorStreamPipe( );
	~stdErrorStreamPipe( );
};

}