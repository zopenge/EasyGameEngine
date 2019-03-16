//! @file     TSoundRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TSoundRecorder
//----------------------------------------------------------------------------

template< typename Type >
class TSoundRecorder : public INTERFACE_OBJECT_IMPL( Type )
{
protected:
	_SOUND_RECORDER_STATE		mState;

	ISoundRecorderNotifierRef	mNotifier;

protected:
	TSoundRecorder( );
	virtual ~TSoundRecorder( );

// ISoundSource Interface
public:
	virtual ISoundRecorderNotifier* GetNotifier( ) override;

	virtual _SOUND_RECORDER_STATE	GetState( ) const override;
};

//----------------------------------------------------------------------------
// TSoundRecorder Implementation
//----------------------------------------------------------------------------

template< typename Type >
TSoundRecorder< Type >::TSoundRecorder( )
{
	mState = _SOUND_RECORDER_STOPPED;
}

template< typename Type >
TSoundRecorder< Type >::~TSoundRecorder( )
{
}

template< typename Type >
ISoundRecorderNotifier* TSoundRecorder< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
_SOUND_RECORDER_STATE TSoundRecorder< Type >::GetState( ) const
{
	return mState;
}

}