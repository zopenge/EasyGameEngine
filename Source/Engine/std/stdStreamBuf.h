//! @file     stdStreamBuf.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// stdStreamBuf
//----------------------------------------------------------------------------

class stdStreamBuf : public std::streambuf
{
// std::streambuf overlapped functions
private:
	virtual int_type	overflow( int_type c ) override;
	virtual int			sync( ) override;

protected:
	//!	When write string from std.
	virtual _void WriteString( const std::string& message ) PURE;

public:
	stdStreamBuf( int buffer_size );
	virtual ~stdStreamBuf( );
};

//----------------------------------------------------------------------------
// stdTraceStreamBuf
//----------------------------------------------------------------------------

class stdTraceStreamBuf : public stdStreamBuf
{
private:
	typedef stdStreamBuf BaseClass;

// stdStreamBuf Interface
protected:
	virtual _void WriteString( const std::string& message ) override;

public:
	stdTraceStreamBuf( int buffer_size );
	virtual ~stdTraceStreamBuf( );
};

//----------------------------------------------------------------------------
// stdErrorStreamBuf
//----------------------------------------------------------------------------

class stdErrorStreamBuf : public stdStreamBuf
{
private:
	typedef stdStreamBuf BaseClass;

// stdStreamBuf Interface
protected:
	virtual _void WriteString( const std::string& message ) override;

public:
	stdErrorStreamBuf( int buffer_size );
	virtual ~stdErrorStreamBuf( );
};

}