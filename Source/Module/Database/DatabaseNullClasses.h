//! @file     DatabaseNullClasses.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// NullDatabaseModule
//----------------------------------------------------------------------------

class NullDatabaseModule : public INTERFACE_MODULE_IMPL( IDatabaseModule )
{
public:
	NullDatabaseModule( ) : TModule( L"Database", Version( DATABASE_FILEVER ) ) { }
	virtual ~NullDatabaseModule( ) { }

// IDatabaseModule Interface
public:
	virtual _ubool						Initialize( ) { return _false; }

	virtual WStringR					GetLastError( ) { return WString( L"" ); }

	virtual IDatabaseConnectionPassRef	CreateConnection( WStringPtr dsn, WStringPtr username, WStringPtr password ) { return _null; }
};

}