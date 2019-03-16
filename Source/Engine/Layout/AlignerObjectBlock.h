//! @file     AlignerObjectBlock.h
//! @author   
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// AlignerObjectBlock
//----------------------------------------------------------------------------

class AlignerObjectBlock : public AlignerObjectBase
{
protected:
	typedef AlignerObjectBase BaseClass;

public:
	typedef Array< IMeasurableObject* > ObjectArray;

protected:
	ObjectArray	mObjects;

protected:
	//!	Get objects total number and width.
	_float GetObjectsTotalWidth( ) const;

public:
	AlignerObjectBlock( );
	~AlignerObjectBlock( );

public:
	//! Access measurable objects.
	EGE_GETR_ACCESSOR( ObjectArray, Objects )
	EGE_GETR_ACCESSOR_CONST( ObjectArray, Objects )

public:
	//!	Get the word separator index.
	_dword GetWordSeparatorR2L( ) const;

	//!	Clear objects.
	_void ClearObjects( );
	//!	Add object.
	_void AddObject( IMeasurableObject* object, const Vector2& space );
	//!	Remove blocks.
	_void RemoveBlocks( _dword index, const Vector2& space );
	_void RemoveBlocks( _dword index, _dword number, const Vector2& space );
};

}