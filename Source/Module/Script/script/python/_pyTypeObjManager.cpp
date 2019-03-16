//! @file     _pyTypeObjManager.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_PYTHON_ == 1)

//----------------------------------------------------------------------------
// _pyTypeObjManager Implementation
//----------------------------------------------------------------------------

_pyTypeObjManager::_pyTypeObjManager( )
{
}

_pyTypeObjManager::~_pyTypeObjManager( )
{
}

_void _pyTypeObjManager::Finalize( )
{
	mObjects.Clear( _true );
}

PyTypeObject* _pyTypeObjManager::SearchObjType( const AStringObj& name )
{
	PyTypeObjectPairArray::Iterator it = mObjects.SearchAscending( name );
	if ( it.IsValid( ) == _false )
		return _null;

	PyTypeObjectPair& pair = it;

	return pair.mObject2;
}

_void _pyTypeObjManager::AddObjType( const AStringObj& name, PyTypeObject* py_obj )
{
	mObjects.InsertAscending( PyTypeObjectPair( name, py_obj ) );
}

_void _pyTypeObjManager::RemoveObjType( const AStringObj& name )
{
	mObjects.RemoveAscending( name );
}

#endif