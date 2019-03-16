//! @file     AlignerObjectBlock.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// AlignerObjectBlock Implementation
//----------------------------------------------------------------------------

AlignerObjectBlock::AlignerObjectBlock( )
{

}

AlignerObjectBlock::~AlignerObjectBlock( )
{

}

_float AlignerObjectBlock::GetObjectsTotalWidth( ) const
{
	_float width = 0.0f;
	for ( _dword i = 0; i < mObjects.Number( ); ++ i )
		width += mObjects[i]->GetRegion( ).GetWidth( );

	return width;
}

_dword AlignerObjectBlock::GetWordSeparatorR2L( ) const
{
	for ( _int i = mObjects.Number( ) - 1; i >= 0; i -- )
	{
		if ( mObjects[i]->IsWordSeparatorTag( ) )
			return i;
	}

	return -1;
}

_void AlignerObjectBlock::ClearObjects( )
{
	BaseClass::Clear( );

	mObjects.Clear( );
}

_void AlignerObjectBlock::AddObject( IMeasurableObject* object, const Vector2& space )
{
	EGE_ASSERT( object != _null );

	// Get the measurable object info
	RectF region = object->GetRegion( );

	// Update blocks info
	mWidth			+= region.GetWidth( ) + object->GetSpace( ) + space.x;
	mHeight			 = Math::Max( mHeight, region.GetHeight( ) );
	mBaseLineHeight	 = Math::Max( mBaseLineHeight, object->GetBaseLineHeight( ) );
	mBottom			 = Math::Max( mBottom, object->GetBottom( ) );

	// Append it into array
	mObjects.Append( object );
}

_void AlignerObjectBlock::RemoveBlocks( _dword index, const Vector2& space )
{
	_dword number = mObjects.Number( ) - index;
	RemoveBlocks( index, number, space );
}

_void AlignerObjectBlock::RemoveBlocks( _dword index, _dword number, const Vector2& space )
{
	mObjects.RemoveByRange( index, number );

	// Refresh the blocks info
	Clear( );
	for ( _dword i = 0; i < mObjects.Number( ); i ++ )
	{
		IMeasurableObject* object = mObjects[i];

		// Get the measurable object info
		RectF region = object->GetRegion( );

		mWidth			+= region.GetWidth( ) + object->GetSpace( ) + space.x;
		mHeight			 = Math::Max( mHeight, region.GetHeight( ) );
		mBaseLineHeight	 = Math::Max( mBaseLineHeight, object->GetBaseLineHeight( ) );
		mBottom			 = Math::Max( mBottom, object->GetBottom( ) );
	}
}