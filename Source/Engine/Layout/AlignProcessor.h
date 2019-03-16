//! @file     AlignProcessor.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
// 
// //----------------------------------------------------------------------------
// // IAlignProcessor
// //----------------------------------------------------------------------------
// 
// class IAlignProcessor
// {
// public:
// 	//!	Check whether it's new line tag or not.
// 	virtual _ubool IsNewLineTag( _dword index ) const PURE;
// 
// 	//!	Check whether can skip.
// 	virtual _ubool CanSkip( _dword index ) const PURE;
// 	//!	Check whether can split.
// 	virtual _ubool CanSplit( _dword index ) const PURE;
// 
// 	//!	Get the object size.
// 	virtual Vector2 GetObjectSize( _dword index ) const PURE;
// 	//!	Get the object number.
// 	virtual _dword GetObjectNumber( ) const PURE;
// 
// 	//!	Place the objects.
// 	virtual _void PlaceObjects( _dword start_index, _dword number, const Vector2& start_pos ) PURE;
// };
// 
// //----------------------------------------------------------------------------
// // StringAlignProcessor
// //----------------------------------------------------------------------------
// 
// class StringAlignProcessor : public IAlignProcessor
// {
// private:
// 	typedef CallbackFunc< IAligner::OnPlaceString, _void, VoidParameters2 > OnPlaceStringFunc;
// 
// private:
// 	//!	The string
// 	WStringPtr			mString;
// 	//!	The string length
// 	_dword				mStringLength;
// 	//!	The font face
// 	IFontFace*			mFontFace;
// 
// 	//!	The callback function
// 	OnPlaceStringFunc	mPlaceStringFunc;
// 
// public:
// 	StringAlignProcessor( WStringPtr string, IFontFace* font_face, IAligner::OnPlaceString funcpointer, const VoidParameters2& parameters );
// 	virtual ~StringAlignProcessor( );
// 
// // IAlignProcessor Interface
// public:
// 	virtual _ubool	IsNewLineTag( _dword index ) const override;
// 
// 	virtual _ubool	CanSkip( _dword index ) const override;
// 	virtual _ubool	CanSplit( _dword index ) const override;
// 
// 	virtual Vector2	GetObjectSize( _dword index ) const override;
// 	virtual _dword	GetObjectNumber( ) const override;
// 
// 	virtual _void	PlaceObjects( _dword start_index, _dword number, const Vector2& start_pos ) override;
// };
// 
// //----------------------------------------------------------------------------
// // MeasurableObjectAlignProcessor
// //----------------------------------------------------------------------------
// 
// class MeasurableObjectAlignProcessor : public IAlignProcessor
// {
// private:
// 	typedef CallbackFunc< IAligner::OnPlaceObject, _void, VoidParameters2 > OnPlaceObjectFunc;
// 
// private:
// 	//!	The measurable objects
// 	const IMeasurableObject**	mObjects;
// 	//!	The number of objects
// 	_dword						mNumber;
// 
// 	//!	The callback function
// 	OnPlaceObjectFunc			mPlaceObjectFunc;
// 
// public:
// 	MeasurableObjectAlignProcessor( const IMeasurableObject* objects[], _dword number, IAligner::OnPlaceObject funcpointer, const VoidParameters2& parameters );
// 	virtual ~MeasurableObjectAlignProcessor( );
// 
// // IAlignProcessor Interface
// public:
// 	virtual _ubool	IsNewLineTag( _dword index ) const override;
// 
// 	virtual _ubool	CanSkip( _dword index ) const override;
// 	virtual _ubool	CanSplit( _dword index ) const override;
// 
// 	virtual Vector2	GetObjectSize( _dword index ) const override;
// 	virtual _dword	GetObjectNumber( ) const override;
// 
// 	virtual _void	PlaceObjects( _dword start_index, _dword number, const Vector2& start_pos ) override;
// };

}