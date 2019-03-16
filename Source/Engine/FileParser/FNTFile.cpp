//! @file     FNTFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FNTFile Implementation
//----------------------------------------------------------------------------

FNTFile::FNTFile( )
{
}

FNTFile::~FNTFile( )
{
}

_dword FNTFile::BuildKey( _dword first_code, _dword second_code )
{
	return ( first_code << 16 ) | second_code;
}

const FNTFile::CharInfo* FNTFile::GetCharInfo( _dword code ) const
{
	const CharInfo* const * char_info = mChars.Search( code );
	if ( char_info == _null )
		return _null;

	return *char_info;
}

_void FNTFile::SynCharInfoBase( const CharInfo* char_info, FontFaceCodeInfoBase& info ) const
{
	EGE_ASSERT( char_info != _null );

	info.mCode			= (_charw) char_info->mCode;
	info.mCharWidth		= (_short)char_info->mSize.x;
	info.mCharHeight	= (_short)char_info->mSize.y;
	info.mMaxCharWidth	= mCommonInfo.mMaxWidth;
	info.mMaxCharHeight	= mCommonInfo.mLineHeight;
	info.mAdvanceX		= char_info->mAdvanceX;
	info.mBearingY		= 0;
	info.mOffsetX		= char_info->mOffset.x;
	info.mOffsetY		= char_info->mOffset.y;
	info.mAscender		= info.mOffsetY * 2;
	info.mDescender		= 0;
	info.mBaseLine		= mCommonInfo.mBase;
}

_void FNTFile::SynCharInfo( const CharInfo* char_info, FontFaceCodeInfo& info ) const
{
	SynCharInfoBase( char_info, info );

	// Get bitmap width, height, stride and buffer
	info.mBitmapLeft	= (_short) char_info->mPos.x;
	info.mBitmapTop		= (_short) char_info->mPos.y;
	info.mBitmapWidth	= (_short) char_info->mSize.x;
	info.mBitmapHeight	= (_short) char_info->mSize.y;
	// Get the offset
	info.mOffsetX		= char_info->mOffset.x;
	info.mOffsetY		= char_info->mOffset.y;
}

_FILE_FORMAT FNTFile::GetFileID( ) const
{
	return _FF_FNT;
}

_ubool FNTFile::LoadFromStream( IStreamReader* stream_reader )
{
	Unload( );

	if ( BaseClass::LoadFromStream( stream_reader ) == _false )
		return _false;

	// Create command line parser
	ICommandLineParserRef cmd_line = GetInterfaceFactory( )->CreateCommandLineParser( );
	if ( cmd_line.IsNull( ) )
		return _false;

	// Read the encode type
	_ENCODING encode_type = _ENCODING_ANSI;
	stream_reader->ReadEncodeType( encode_type );

	// Start to analyze FNT file line by line
	AString line_string;
	while ( stream_reader->ReadLine( encode_type, line_string ) )
	{
		// Initialize command line parser
		cmd_line->Initialize( line_string );

		// Check the arguments
		if ( cmd_line->GetArgumentsNumber( ) == 0 )
			continue;

		// Get the key
		WStringPtr key = cmd_line->GetArgumentByIndex( 0 )->mValue;

		// It's info section
		if ( key == L"info" )
		{
			mBasicInfo.mFaceName	= cmd_line->GetArgumentByKeyName( L"face" )->mValue;
			mBasicInfo.mSize		= cmd_line->GetArgumentByKeyName( L"size" )->GetValue( 10 );
			mBasicInfo.mCharSet		= cmd_line->GetArgumentByKeyName( L"charset" )->GetValue( 10 );
			mBasicInfo.mStretchH	= cmd_line->GetArgumentByKeyName( L"stretchH" )->GetValue( 10 );
			mBasicInfo.mPadding		= cmd_line->GetArgumentByKeyName( L"padding" )->GetRegionI( );
			mBasicInfo.mSpacing		= cmd_line->GetArgumentByKeyName( L"spacing" )->GetPointI( );
			mBasicInfo.EnableFlags( BasicInfo::_FLAG_BOLD, cmd_line->HasArgument( L"bold" ));
			mBasicInfo.EnableFlags( BasicInfo::_FLAG_ITALIC, cmd_line->HasArgument( L"italic" ) );
			mBasicInfo.EnableFlags( BasicInfo::_FLAG_UNICODE, cmd_line->HasArgument( L"unicode" ) );
			mBasicInfo.EnableFlags( BasicInfo::_FLAG_SMOOTH, cmd_line->HasArgument( L"smooth" ) );
			mBasicInfo.EnableFlags( BasicInfo::_FLAG_AA, cmd_line->HasArgument( L"aa" ) );
		}
		// It's common section
		else if ( key == L"common" )
		{
			mCommonInfo.mLineHeight	= cmd_line->GetArgumentByKeyName( L"lineHeight" )->GetValue( 10 );
			mCommonInfo.mBase		= cmd_line->GetArgumentByKeyName( L"base" )->GetValue( 10 );
			mCommonInfo.mScaleW		= cmd_line->GetArgumentByKeyName( L"scaleW" )->GetValue( 10 );
			mCommonInfo.mScaleH		= cmd_line->GetArgumentByKeyName( L"scaleH" )->GetValue( 10 );
			mCommonInfo.mPages		= cmd_line->GetArgumentByKeyName( L"pages" )->GetValue( 10 );
			mCommonInfo.mIsPacked	= EGE_BOOLEAN( cmd_line->GetArgumentByKeyName( L"packed" )->GetValue( 10 ) );
		}
		// It's page section
		else if ( key == L"page" )
		{
			_dword page_id = cmd_line->GetArgumentByKeyName( L"id" )->GetValue( 10 );

			PageInfo& page_info = mPages[page_id];
			page_info.mFileName	= cmd_line->GetArgumentByKeyName( L"file" )->mValue;

			mPagesList.Append( &page_info );
		}
		// It's char section
		else if ( key == L"char" )
		{
			CharInfo char_info;
			char_info.mCode		= cmd_line->GetArgumentByKeyName( L"id" )->GetValue( 10 );
			char_info.mPos.x	= cmd_line->GetArgumentByKeyName( L"x" )->GetValue( 10 );
			char_info.mPos.y	= cmd_line->GetArgumentByKeyName( L"y" )->GetValue( 10 );
			char_info.mSize.x	= cmd_line->GetArgumentByKeyName( L"width" )->GetValue( 10 );
			char_info.mSize.y	= cmd_line->GetArgumentByKeyName( L"height" )->GetValue( 10 );
			char_info.mOffset.x	= cmd_line->GetArgumentByKeyName( L"xoffset" )->GetValue( 10 );
			char_info.mOffset.y	= cmd_line->GetArgumentByKeyName( L"yoffset" )->GetValue( 10 );
			char_info.mAdvanceX	= cmd_line->GetArgumentByKeyName( L"xadvance" )->GetValue( 10 );
			char_info.mChannels	= cmd_line->GetArgumentByKeyName( L"chnl" )->GetValue( 10 );
			char_info.mLetter	= cmd_line->GetArgumentByKeyName( L"letter" )->mValue;

			mCommonInfo.mMaxWidth = Math::Max( (_int)char_info.mSize.x, mCommonInfo.mMaxWidth );

			_dword page_id	= cmd_line->GetArgumentByKeyName( L"page" )->GetValue( 10 );
			CharInfo& new_char_info = mPages[ page_id ].mCharCodes[ char_info.mCode ];
			new_char_info = char_info;

			mChars[ char_info.mCode ] = &new_char_info;

			mCharsList.Append( &new_char_info );
		}
		// It's kerning section
		else if ( key == L"kerning" )
		{
			KerningInfo kerning_info;
			kerning_info.mAmount = cmd_line->GetArgumentByKeyName( L"amount" )->GetValue( 10 );

			_dword first_char_id	= cmd_line->GetArgumentByKeyName( L"first" )->GetValue( 10 );
			_dword second_char_id	= cmd_line->GetArgumentByKeyName( L"second" )->GetValue( 10 );
			_dword key				= BuildKey( first_char_id, second_char_id );

			mKernings[ key ] = kerning_info;
		}
	}

	return _true;
}

_void FNTFile::Unload( )
{
	mBasicInfo	= BasicInfo( );
	mCommonInfo	= CommonInfo( );
	mChars.Clear( );
	mCharsList.Clear( );
	mPages.Clear( );
	mPagesList.Clear( );
	mKernings.Clear( );
}

_dword FNTFile::GetPageNumber( ) const
{
	return mPagesList.Number( );
}

WStringPtr FNTFile::GetPageImageFileName( _dword page_index ) const
{
	if ( page_index >= mPagesList.Number( ) )
		return L"";

	return mPagesList[ page_index ]->mFileName;
}

_ubool FNTFile::HasCharacter( _dword code ) const
{
	return GetCharInfo( code ) != _null;
}

PointU FNTFile::GetCharSize( _dword code )
{
	const CharInfo* char_info = GetCharInfo( code );
	if ( char_info == _null )
		return PointU::cZeroPoint;

	return char_info->mSize;
}

_dword FNTFile::GetCharMaxHeight( ) const
{
	return mCommonInfo.mLineHeight;
}

_int FNTFile::GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const
{
	_dword key = BuildKey( first_code, second_code );

	const KerningInfo* kerning_info = mKernings.Search( key );
	if ( kerning_info == _null )
		return 0;

	return kerning_info->mAmount;
}

_ubool FNTFile::GetFontCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& info )
{
	const CharInfo* char_info = GetCharInfo( code );
	if ( char_info == _null )
		return _false;

	SynCharInfoBase( char_info, info );

	return _true;
}

_ubool FNTFile::RenderCharacter( _dword code, FontFaceCodeInfo& info )
{
	const CharInfo* char_info = GetCharInfo( code );
	if ( char_info == _null )
		return _false;

	SynCharInfo( char_info, info );

	return _true;
}

_dword FNTFile::GetImageCodesNumber( ) const
{
	return mCharsList.Number( );
}

_ubool FNTFile::GetImageCodeInfoByIndex( _dword index, FontFaceCodeInfo& info ) const
{
	if ( index >= mCharsList.Number( ) )
		return _false;

	SynCharInfo( mCharsList[index], info );

	return _true;

}
