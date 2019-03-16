//! @file     TSoundFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TSoundFile
//----------------------------------------------------------------------------

template< typename Type >
class TSoundFile : public Type
{
protected:
	//!	The sound ID3 tags info
	SoundID3TagsInfo	mID3TagsInfo;
	//!	The sound header info.
	SoundHeaderInfo		mHeaderInfo;

protected:
	TSoundFile( );
	virtual ~TSoundFile( );

// IBaseFile Interface
public:
	virtual _void					Unload( ) override;

// ISoundFile Interface
public:
	virtual _ubool					IsStreaming( ) const override;

	virtual const SoundID3TagsInfo& GetID3TagsInfo( ) const override;

	virtual const SoundHeaderInfo&	GetHeaderInfo( ) const override;
};

//----------------------------------------------------------------------------
// TSoundFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TSoundFile< Type >::TSoundFile( )
{
	EGE_INIT( mHeaderInfo );
}

template< typename Type >
TSoundFile< Type >::~TSoundFile( )
{

}

template< typename Type >
_void TSoundFile< Type >::Unload( )
{
}

template< typename Type >
_ubool TSoundFile< Type >::IsStreaming( ) const
{
	return _false;
}

template< typename Type >
const SoundID3TagsInfo& TSoundFile< Type >::GetID3TagsInfo( ) const
{
	return mID3TagsInfo;
}

template< typename Type >
const SoundHeaderInfo& TSoundFile< Type >::GetHeaderInfo( ) const
{
	return mHeaderInfo;
}

}