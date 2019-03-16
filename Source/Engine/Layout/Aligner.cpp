//! @file     Aligner.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Aligner Implementation
//----------------------------------------------------------------------------

Aligner::Aligner( )
{
}

Aligner::~Aligner( )
{
}

_dword Aligner::SearchWordSeparatorIndex( ) const
{
	_dword word_spearator_index = mCurrentLine.GetWordSeparatorR2L( );
	if ( word_spearator_index == -1 )
		return -1;
	
	if ( word_spearator_index == 0 )
		return -1;

	if ( word_spearator_index == mCurrentLine.GetObjects( ).Number( ) - 1 )
		return -1;

	return word_spearator_index;
}

_void Aligner::PlaceCurLine( _dword& line_number, _float& currentheight, const FlagsObject& alignment, const Vector2& space, const Vector2& size, const FlagsObject& flags, Line2DArray* underlinearray )
{
	if ( mCurrentLine.GetObjects( ).Number( ) == 0 )
		return;

	// Place line
	mCurrentLine.PlaceLine( flags, alignment, space, size, currentheight, underlinearray );

	// Update current height
	currentheight += mCurrentLine.GetHeight( ) + space.y;

	// Update line number
	line_number ++;

	// Clear line
	mCurrentLine.ClearObjects( );
}

_void Aligner::PlaceLinesWithAlignmentType( Array< IMeasurableObjectRef >& objects, _float currentheight, const Vector2& margin_size, const Vector2& size, const FlagsObject& alignment, Line2DArray* underlinearray ) const
{
	Vector2 halfsize = size * 0.5f;

	if ( alignment.HasFlags( _ALIGNMENT_TOP ) )
	{
		// none.
		for ( _dword i = 0; i < objects.Number( ); ++ i )
		{
			Vector2 position = objects[i]->GetPosition( ) + margin_size;
			objects[i]->SetPosition( position );
		}

		if ( underlinearray != _null )
		{
			for ( _dword i = 0; i < underlinearray->Number( ); ++ i )			
				(*underlinearray)[i] += margin_size - halfsize;
		}
	}
	else if ( alignment.HasFlags( _ALIGNMENT_BOTTOM ) )
	{
		_float height = currentheight - size.y;
		for ( _dword i = 0; i < objects.Number( ); ++ i )
		{
			Vector2 position = objects[i]->GetPosition( ) + margin_size;
			position.y -= height;
			objects[i]->SetPosition( position );
		}

		if ( underlinearray != _null )
		{
			for ( _dword i = 0; i < underlinearray->Number( ); ++ i )	
				(*underlinearray)[i] += Vector2( margin_size.x, margin_size.y - height ) - halfsize;
		}
	}
	else if ( alignment.HasFlags( _ALIGNMENT_VERT_CENTER ) || alignment.HasFlags( _ALIGNMENT_VERT_JUSTIFIED ) )
	{
		_float height = ( currentheight - size.y ) * 0.5f;
		for ( _dword i = 0; i < objects.Number( ); ++ i )
		{
			Vector2 position = objects[i]->GetPosition( ) + margin_size;
			position.y -= height;
			objects[i]->SetPosition( position );
		}

		if ( underlinearray != _null )
		{
			for ( _dword i = 0; i < underlinearray->Number( ); ++ i )	
				(*underlinearray)[i] += Vector2( margin_size.x, margin_size.y - height ) - halfsize;
		}
	}
}

_void Aligner::FeedbackRealSize( const Array< IMeasurableObjectRef >& objects, RectF* real_size ) const
{
	EGE_ASSERT( real_size != _null );

	real_size->l = Math::cMaxFloat;
	real_size->t = Math::cMaxFloat;
	real_size->r = Math::cMinFloat;
	real_size->b = Math::cMinFloat;

	for ( _dword i = 0; i < objects.Number( ); ++ i )
	{
		const RectF&	region		= objects[i]->GetRegion( );
		const Vector2&	position	= objects[i]->GetPosition( );

		Vector2 lt = position + Vector2( region.l, region.t );
		Vector2 rb = position + Vector2( region.r, region.b );

		if ( lt.x < real_size->l )
			real_size->l = lt.x;

		if ( lt.y < real_size->t )
			real_size->t = lt.y;

		if ( rb.x > real_size->r )
			real_size->r = rb.x;

		if ( rb.y > real_size->b )
			real_size->b = rb.y;
	}
}

_void Aligner::HorzAlignObject( Array< IMeasurableObjectRef >& objects, const FlagsObject& alignment, const Vector2& margin_size, const Vector2& space, const Vector2& size, const FlagsObject& flags, RectF* real_size, Line2DArray* underlinearray )
{
	// Clear current line info
	mCurrentLine.ClearObjects( );
	mCurrentWords.ClearObjects( );

	// The height of current line
	_float	currentheight	= 0.0f;
	// The line number
	_dword	line_number		= 0;

	// Start to align objects
	for ( _dword i = 0; i < objects.Number( ); ++ i )
	{
		IMeasurableObject* obj = objects[i];

		// Set the line number
		obj->SetLineNumber( line_number );

		// It's new line tag
		if ( obj->IsNewLineTag( ) )
		{
			// Add the new line tag
			mCurrentWords.AddObject( obj, space );

			// Update line
			mCurrentLine.AddBlock( mCurrentWords );
			mCurrentWords.ClearObjects( );

			// Place a line
			PlaceCurLine( line_number, currentheight, alignment, space, size, flags, underlinearray );
		}
		else
		{
			// Append words
			mCurrentWords.AddObject( obj, space );

			// Test whether need to auto-new-line
			if ( flags.HasFlags( _ALIGNER_AUTO_LINE_WRAP ) && ( ( mCurrentLine.GetWidth( ) + mCurrentWords.GetWidth( ) ) > size.x ) )
			{
				// First start to search the word separator index
				_dword word_spearator_index = SearchWordSeparatorIndex( );
				if ( word_spearator_index != -1 )
				{
					// Save the removed words
					AlignerObjectBlock removed_words;
					for ( _dword j = word_spearator_index + 1; j < mCurrentLine.GetObjects( ).Number( ); j ++ )
						removed_words.AddObject( mCurrentLine.GetObjects( )[j], space );

					// Remove words and they will add to the next line
					mCurrentLine.RemoveBlocks( word_spearator_index + 1, space );

					// Place a line
					PlaceCurLine( line_number, currentheight, alignment, space, size, flags, underlinearray );

					// Get the removed words prepare for the next line
					mCurrentLine.ClearObjects( );
					mCurrentLine.AddBlock( removed_words );
				}
				else
				{
					// Place a line
					PlaceCurLine( line_number, currentheight, alignment, space, size, flags, underlinearray );
				}
			}

			// Update line
			mCurrentLine.AddBlock( mCurrentWords );
			mCurrentWords.ClearObjects( );
		}
	}

	// Process the last line
	mCurrentLine.AddBlock( mCurrentWords );
	mCurrentLine.PlaceLine( flags, alignment, space, size, currentheight, underlinearray );

	// Update current height
	currentheight += mCurrentLine.GetHeight( ) + space.y;

	// Clear current line info
	mCurrentLine.ClearObjects( );
	mCurrentWords.ClearObjects( );

	// Place lines with alignment type
	PlaceLinesWithAlignmentType( objects, currentheight, margin_size, size, alignment, underlinearray );

	// Feedback the real size if needed
	if ( real_size != _null )
		FeedbackRealSize( objects, real_size );
}