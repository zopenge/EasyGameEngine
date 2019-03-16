//! @file     AlignerObjectLine.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// AlignerObjectLine Implementation
//----------------------------------------------------------------------------

AlignerObjectLine::AlignerObjectLine( )
{

}

AlignerObjectLine::~AlignerObjectLine( )
{

}

Vector2 AlignerObjectLine::GetStartPos( const FlagsObject& alignment, const Vector2& textsize, _float lineheight, _float& justified_wordspace ) const
{
	Vector2 start_pos = Vector2::cOrigin;
	start_pos.y = lineheight;

	if ( alignment.HasFlags( _ALIGNMENT_LEFT ) )
	{
		// none.
	}
	else if ( alignment.HasFlags( _ALIGNMENT_RIGHT ) )
	{
		start_pos.x = textsize.x - mWidth;
	}
	else if ( alignment.HasFlags( _ALIGNMENT_HORZ_CENTER ) )
	{
		start_pos.x = ( textsize.x - mWidth ) * 0.5f;
	}
	else if ( alignment.HasFlags( _ALIGNMENT_HORZ_JUSTIFIED ) )
	{
		// Get the total number of objects
		_dword number = mObjects.Number( );

		// If we just have one character then skip to justify it
		if ( number == 1 )
		{
			justified_wordspace = 0;
		}
		else
		{
			// Get the total width of objects
			_float width = GetObjectsTotalWidth( );

			// Get the space number
			_dword spacenumber = number - 1;

			// Calculate the justified word space ( the average space of block's elements )
			justified_wordspace = EGE_RATIO( textsize.x - width, spacenumber );
		}
	}

	return start_pos;
}

_void AlignerObjectLine::AddBlock( AlignerObjectBlock& block )
{
	if ( block.GetObjects( ).Number( ) == 0 )
		return;

	// Update size info
	mWidth			+= block.GetWidth( );
	mHeight			 = Math::Max( mHeight, block.GetHeight( ) );
	mBaseLineHeight  = Math::Max( mBaseLineHeight, block.GetBaseLineHeight( ) );
	mBottom			 = Math::Max( mBottom, block.GetBottom( ) );

	// Update objects
	mObjects += block.GetObjects( );
}

_void AlignerObjectLine::PlaceLine( const FlagsObject& flags, const FlagsObject& alignment, const Vector2& space, const Vector2& size, _float lineheight, Line2DArray* underlinearray )
{
	// Get the start position and justified word space
	_float	justified_wordspace	= 0.0f;
	Vector2 start_pos			= GetStartPos( alignment, size, lineheight, justified_wordspace );

	if ( underlinearray != _null )
	{
		Line2D underline;
		underline.mPoints[0]	= start_pos;
		underline.mPoints[0].y += mBaseLineHeight + mBottom + 1;
		underline.mPoints[1]	= underline.mPoints[0];
		underline.mPoints[1].x += GetObjectsTotalWidth( );
		underlinearray->Append( underline );
	}

	// Set the measurable objects position
	for ( _dword i = 0; i < mObjects.Number( ); ++ i )
	{
		IMeasurableObject* obj = mObjects[i];
		EGE_ASSERT( obj != _null );

		// Get the region of object
		RectF region = obj->GetRegion( );

		// Update the position
		Vector2 pos = Vector2::cOrigin;
		if ( flags.HasFlags( _ALIGNER_USE_LEFT_TOP_AS_ORIGIN ) )
		{
			pos.x = start_pos.x + obj->GetLeft( );
			pos.y = start_pos.y + mBaseLineHeight - obj->GetBaseLineHeight( );
		}
		else
		{
			pos.x = start_pos.x + obj->GetLeft( ) - region.l - size.x * 0.5f;
			pos.y = start_pos.y + mBaseLineHeight - obj->GetBaseLineHeight( ) - region.t - size.y * 0.5f;
		}

		// Update position
		obj->SetPosition( pos );

		// Update start x-position
		start_pos.x += region.GetWidth( ) + space.x;

		// Plus space
		if ( alignment.HasFlags( _ALIGNMENT_HORZ_JUSTIFIED ) )
			start_pos.x += justified_wordspace;
		else
			start_pos.x += obj->GetSpace( );
	}
}