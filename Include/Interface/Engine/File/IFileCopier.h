//! @file     IFileCopier.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IFileCopier
//----------------------------------------------------------------------------

class IFileCopier : public IObject
{
public:
	virtual _ubool Start( _dword read_chunk_size, const MD5Code& md5_code, IStreamReader* stream_reader, WStringPtr filepath ) PURE;
	virtual _void Stop( ) PURE;
};

}