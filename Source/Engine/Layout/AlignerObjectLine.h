//! @file     AlignerObjectLine.h
//! @author   
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// AlignerObjectLine
//----------------------------------------------------------------------------

class AlignerObjectLine : public AlignerObjectBlock
{
private:
	//!	Get the start position and feedback justified word space.
	Vector2 GetStartPos( const FlagsObject& alignment, const Vector2& textsize, _float lineheight, _float& justified_wordspace ) const;

public:
	AlignerObjectLine( );
	~AlignerObjectLine( );

public:
	//!	Add block.
	_void AddBlock( AlignerObjectBlock& block );

	//!	Place
	_void PlaceLine( const FlagsObject& flags, const FlagsObject& alignment, const Vector2& space, const Vector2& size, _float lineheight, Line2DArray* underlinearray );
};

}