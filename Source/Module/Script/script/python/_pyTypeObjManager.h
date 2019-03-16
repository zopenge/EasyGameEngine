//! @file     _pyTypeObjManager.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _pyTypeObjManager
//----------------------------------------------------------------------------

class _pyTypeObjManager
{
private:
	typedef Pair< AStringObj, PyTypeObject* > PyTypeObjectPair;
	typedef Array< PyTypeObjectPair, AStringObj > PyTypeObjectPairArray;

private:
	//!	The python type object array
	PyTypeObjectPairArray	mObjects;

public:
	_pyTypeObjManager( );
	~_pyTypeObjManager( );

public:
	//!	Finalize.
	_void Finalize( );

	//!	Search the python object resource.
	PyTypeObject* SearchObjType( const AStringObj& name );
	//! Add the python type object resource.
	_void AddObjType( const AStringObj& name, PyTypeObject* py_obj );
	//!	Remove the python object resource.
	_void RemoveObjType( const AStringObj& name );
};

}