//! @file     ImageFillerScanLines.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ImageFillerScanLines Implementation
//----------------------------------------------------------------------------

ImageFillerScanLines::ImageFillerScanLines( const PointU& size, const PointU& space ) : BaseClass( size, space )
{
	// All the region can be filled
	mRegionMaskBuffer = new _byte[ mFreeArea ];
	EGE_MEM_SET( mRegionMaskBuffer, 0, mFreeArea );

	// We have one base line
	mBaseLines.Append( 0 );
}

ImageFillerScanLines::~ImageFillerScanLines( )
{
	ClearAllImages( );
}

_void ImageFillerScanLines::UpdateRegionMaskBuffer( const RectU& rect )
{
	for ( _dword y = rect.t; y < rect.t + rect.GetHeight( ); y ++ )
		EGE_MEM_SET( mRegionMaskBuffer + y * mSize.x + rect.l, 1, rect.GetWidth( ) );
}

_ubool ImageFillerScanLines::TestRegionMaskBuffer( const RectU& rect ) const
{
	for ( _dword y = rect.t; y < rect.t + rect.GetHeight( ); y ++ )
	{
		for ( _dword x = rect.l; x < rect.l + rect.GetWidth( ); x ++ )
		{
			if ( mRegionMaskBuffer[ y * mSize.x + x ] != 0 )
				return _false;
		}
	}

	return _true;
}

_dword ImageFillerScanLines::GetFreeXStartPosition( _dword y )
{
	for ( _dword x = 0; x < mSize.x; x ++ )
	{
		if ( mRegionMaskBuffer[ y * mSize.x + x ] == 0 )
			return x;
	}

	return -1;
}

_void ImageFillerScanLines::CleanupBaseLines( )
{
	// Check each scan lines and remove it if lower than minimal height size 
	for ( _dword j = 1; j < mBaseLines.Number( ); j ++ )
	{
		if ( Math::Abs( mBaseLines[j - 1] - mBaseLines[j] ) < _MIN_HEIGHT_BETWEEN_EACH_LINES )
			mBaseLines.RemoveByIndex( -- j );
	}
}

_ubool ImageFillerScanLines::OnAddImage( _dword width, _dword height, RectU& rect )
{
	// Start to fill image
	for ( _dword i = 0; i < mBaseLines.Number( ); i ++ )
	{
		// Get the start y-position
		_short y = mBaseLines[i];

		// Test the height
		if ( mSize.y - y < height )
			continue;

		// Find the start x-position
		_dword x = GetFreeXStartPosition( y );
		if ( x == -1 )
		{
			// This base line is full
			mBaseLines.RemoveByIndex( i -- );
			continue;
		}

		// Test the width
		if ( mSize.x - x < width )
			continue;

		// We can fill in this image, now feedback the left-top position to operation
		rect.InitWithSize( x, y, width, height );

		// Test the region mask buffer
		if ( TestRegionMaskBuffer( rect ) == _false )
			continue;

		// Update the region mask buffer
		UpdateRegionMaskBuffer( rect );

		// Get the split base line position
		_dword baseline = y + height;

		// If the new X-position reach the max size of this image then remove it
		if ( x + width == mSize.x )
		{
			mBaseLines.RemoveByIndex( i );
		}
		else if ( baseline < mSize.y )
		{
			// Insert a new Y-position base line ( if it's existing then skip it )
			if ( mBaseLines.SearchAscending( (_word) baseline ).IsValid( ) == _false )
				mBaseLines.InsertAscending( (_word) baseline );
		}

		// Cleanup the base lines
		CleanupBaseLines( );

		return _true;
	}

	return _false;
}

_ubool ImageFillerScanLines::OnFreeImage( const RectU& rect )
{
	return _false;
}

_void ImageFillerScanLines::ClearAllImages( )
{
	BaseClass::ClearAllImages( );

	// Clear the used area
	EGE_DELETE_ARRAY( mRegionMaskBuffer );

	// We have one base line
	mBaseLines.Clear( );
	mBaseLines.Append( 0 );
}