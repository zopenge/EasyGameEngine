//! @file     Aligner.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Aligner
//----------------------------------------------------------------------------

class Aligner : public INTERFACE_OBJECT_IMPL( IAligner )
{
public:
	typedef INTERFACE_OBJECT_IMPL( IAligner ) BaseClass;

private:
	AlignerObjectLine	mCurrentLine;
	AlignerObjectBlock	mCurrentWords;

private:
	//!	Search for the word separator index for current words.
	_dword SearchWordSeparatorIndex( ) const;

	//!	Place current line.
	_void PlaceCurLine( _dword& line_number, _float& currentheight, const FlagsObject& alignment, const Vector2& space, const Vector2& size, const FlagsObject& flags, Line2DArray* underlinearray );

	//!	Place lines with alignment type.
	_void PlaceLinesWithAlignmentType( Array< IMeasurableObjectRef >& objects, _float currentheight, const Vector2& margin_size, const Vector2& size, const FlagsObject& alignment, Line2DArray* underlinearray ) const;

	//!	Feedback the real size.
	_void FeedbackRealSize( const Array< IMeasurableObjectRef >& objects, RectF* real_size ) const;

public:
	Aligner( );
	virtual ~Aligner( );

// IAligner Interface
public:
	virtual _void HorzAlignObject( Array< IMeasurableObjectRef >& objects, const FlagsObject& alignment, const Vector2& margin_size, const Vector2& space, const Vector2& size, const FlagsObject& flags, RectF* real_size, Line2DArray* underlinearray ) override;
};

//----------------------------------------------------------------------------
// Aligner Implementation
//----------------------------------------------------------------------------

}