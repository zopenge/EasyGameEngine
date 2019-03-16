//! @file     FNTFile.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FNTFile
//----------------------------------------------------------------------------

class FNTFile : public INTERFACE_BASEFILE_IMPL( IFNTFile )
{
private:
	typedef INTERFACE_BASEFILE_IMPL( IFNTFile ) BaseClass;

private:
	//!	The basic info
	struct BasicInfo : public FlagsObject
	{
		enum _FLAG
		{
			_FLAG_BOLD		= 1 << 0,
			_FLAG_ITALIC	= 1 << 1,
			_FLAG_UNICODE	= 1 << 2,
			_FLAG_SMOOTH	= 1 << 3,
			_FLAG_AA		= 1 << 4,
		};

		_int	mSize;
		_int	mStretchH;
		RectI	mPadding;
		PointI	mSpacing;
		WString	mFaceName;
		WString	mCharSet;

		BasicInfo( )
		{
			mSize		= 0;
			mStretchH	= 100;
			mPadding	= RectI::cNull;
			mSpacing	= PointI::cZeroPoint;
		}
	};

	//!	The common info
	struct CommonInfo
	{
		_int	mMaxWidth;
		_int	mLineHeight;
		_int	mBase;
		_int	mScaleW;
		_int	mScaleH;
		_int	mPages;
		_ubool	mIsPacked;

		CommonInfo( )
		{
			mMaxWidth	= 0;
			mLineHeight = 0;
			mBase		= 0;
			mScaleW		= 0;
			mScaleH		= 0;
			mPages		= 0;
			mIsPacked	= _false;
		}
	};

	//!	The char info
	struct CharInfo
	{
		_int	mCode;
		PointI	mPos;
		PointU	mSize;
		PointI	mOffset;
		_int	mAdvanceX;
		_int	mChannels;
		WString	mLetter;

		CharInfo( )
		{
			mCode		= 0;
			mPos		= PointI::cZeroPoint;
			mSize		= PointU::cZeroPoint;
			mOffset		= PointI::cZeroPoint;
			mAdvanceX	= 0;
			mChannels	= 0;
		}
	};
	//!	Use the code's id as key.
	typedef Map< CharInfo, _dword > CharInfoMap;
	typedef Map< CharInfo*, _dword > CharInfoPtrMap;
	typedef Array< CharInfo* > CharInfoPtrArray;

	//!	The page info
	struct PageInfo
	{
		WString		mFileName;
		CharInfoMap	mCharCodes;
	};
	//!	Use the page's id as key.
	typedef Map< PageInfo, _dword > PageInfoMap;
	typedef Array< PageInfo* > PageInfoPtrArray;

	//!	The kerning info
	struct KerningInfo
	{
		_int	mAmount;

		KerningInfo( )
		{
			mAmount = 0;
		}
	};
	//!	Use the first and second code as key.
	typedef Map< KerningInfo, _dword > KerningInfoMap;

private:
	BasicInfo			mBasicInfo;
	CommonInfo			mCommonInfo;
	CharInfoPtrMap		mChars;
	CharInfoPtrArray	mCharsList;
	PageInfoMap			mPages;
	PageInfoPtrArray	mPagesList;
	KerningInfoMap		mKernings;

private:
	// Build the key of first and second code.
	static _dword BuildKey( _dword first_code, _dword second_code );

private:
	//!	Get the character info.
	const CharInfo* GetCharInfo( _dword code ) const;

	//!	Syn character info.
	_void SynCharInfoBase( const CharInfo* char_info, FontFaceCodeInfoBase& info ) const;
	_void SynCharInfo( const CharInfo* char_info, FontFaceCodeInfo& info ) const;

public:
	FNTFile( );
	virtual ~FNTFile( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT	GetFileID( ) const override;

	virtual _ubool 			LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 			Unload( ) override;

// IFNTFile Interface
public:
	virtual _dword			GetPageNumber( ) const override;
	virtual WStringPtr		GetPageImageFileName( _dword page_index ) const override;

	virtual _ubool			HasCharacter( _dword code ) const override;

	virtual PointU			GetCharSize( _dword code ) override;
	virtual _dword			GetCharMaxHeight( ) const override;

	virtual _int			GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const override;

	virtual _ubool			GetFontCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& info ) override; 

	virtual _ubool			RenderCharacter( _dword code, FontFaceCodeInfo& info ) override;

	virtual _dword			GetImageCodesNumber( ) const override;
	virtual _ubool			GetImageCodeInfoByIndex( _dword index, FontFaceCodeInfo& info ) const override;
};

//----------------------------------------------------------------------------
// FNTFile Implementation
//----------------------------------------------------------------------------

}