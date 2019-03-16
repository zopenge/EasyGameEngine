//! @file     AlignProcessor.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// StringAlignProcessor Implementation
//----------------------------------------------------------------------------

// StringAlignProcessor::StringAlignProcessor( WStringPtr string, IFontFace* font_face, IAligner::OnPlaceString funcpointer, const VoidParameters2& parameters )
// {
// 	mString			= string;
// 	mStringLength	= string.GetLength( );
// 	mFontFace		= font_face;
// 
// 	mPlaceStringFunc.Init( funcpointer, parameters );
// }
// 
// StringAlignProcessor::~StringAlignProcessor( )
// {
// 
// }
// 
// _ubool StringAlignProcessor::IsNewLineTag( _dword index ) const
// {
// 	if ( mString[ index ] == '\n' )
// 		return _true;
// 
// 	return _false;
// }
// 
// _ubool StringAlignProcessor::CanSkip( _dword index ) const
// {
// 	if ( mString[ index ] == '\r' )
// 		return _true;
// 
// 	return _false;
// }
// 
// _ubool StringAlignProcessor::CanSplit( _dword index ) const
// {
// 	if ( mString[ index ] == ' ' || mString[ index ] == '\t' )
// 		return _true;
// 
// 	return _false;
// }
// 
// Vector2 StringAlignProcessor::GetObjectSize( _dword index ) const
// {
// 	PointU size = mFontFace->GetCharSize( mString[ index ] );
// 
// 	return Vector2( (_float) size.x, (_float) size.y );
// }
// 
// _dword StringAlignProcessor::GetObjectNumber( ) const
// {
// 	return mStringLength;
// }
// 
// _void StringAlignProcessor::PlaceObjects( _dword start_index, _dword number, const Vector2& start_pos )
// {
// 	Vector2 position = start_pos;
// 
// 	for ( _dword i = 0; i < number; i ++, position.x += GetObjectSize( start_index + i ).x )
// 	{
// 		AlignedStringInfo info;
// 		info.mFontCodeID	= mString[ start_index + i ];
// 		info.mPosition		= position;
// 
// 		mPlaceStringFunc.Invoke( info );
// 	}
// }
// 
// //----------------------------------------------------------------------------
// // MeasurableObjectAlignProcessor Implementation
// //----------------------------------------------------------------------------
// 
// MeasurableObjectAlignProcessor::MeasurableObjectAlignProcessor( const IMeasurableObject* objects[], _dword number, IAligner::OnPlaceObject funcpointer, const VoidParameters2& parameters )
// {
// 	mObjects	= objects;
// 	mNumber		= number;
// 
// 	mPlaceObjectFunc.Init( funcpointer, parameters );
// }
// 
// MeasurableObjectAlignProcessor::~MeasurableObjectAlignProcessor( )
// {
// 
// }
// 
// _ubool MeasurableObjectAlignProcessor::IsNewLineTag( _dword index ) const
// {
// 	// Always can not to be a new line tag
// 	return _false;
// }
// 
// _ubool MeasurableObjectAlignProcessor::CanSkip( _dword index ) const
// {
// 	// Always can not skip
// 	return _false;
// }
// 
// _ubool MeasurableObjectAlignProcessor::CanSplit( _dword index ) const
// {
// 	// Always can split
// 	return _true;
// }
// 
// Vector2 MeasurableObjectAlignProcessor::GetObjectSize( _dword index ) const
// {
// 	return mObjects[ index ]->GetSize( );
// }
// 
// _dword MeasurableObjectAlignProcessor::GetObjectNumber( ) const
// {
// 	return mNumber;
// }
// 
// _void MeasurableObjectAlignProcessor::PlaceObjects( _dword start_index, _dword number, const Vector2& start_pos )
// {
// 	Vector2 position = start_pos;
// 
// 	for ( _dword i = 0; i < number; i ++, position.x += GetObjectSize( start_index + i ).x )
// 	{
// 		AlignedObjectInfo info;
// 		info.mMeasurableObject	= mObjects[ start_index + i ];
// 		info.mPosition			= position;
// 
// 		mPlaceObjectFunc.Invoke( info );
// 	}
// }