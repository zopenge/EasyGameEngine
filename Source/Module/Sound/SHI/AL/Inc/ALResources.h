//! @file     ALResources.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

// Check the AL error
#ifdef _DEBUG
	#define AL_CHECK_ERROR( x ) { x; ALCheckError( _WIDEN( #x ) ); }
#else
	#define AL_CHECK_ERROR( x )	{ x; }
#endif
extern _void ALCheckError( WStringPtr string );

// Generate buffer
extern _void GenBuffer( ResourceSHI* buffer, ALuint& resource );
// Delete buffer
extern _void DelBuffer( ALuint resource );
// Find buffer
extern BufferSHI* FindBuffer( ALuint resource );

// Generate source
extern _void GenSource( ResourceSHI* source, ALuint& resource );
// Delete source
extern _void DelSource( ALuint resource );
// Find source
extern SourceSHI* FindSource( ALuint resource );

// Generate effect
extern _void GenEffect( ResourceSHI* effect, ALuint& resource );
// Delete effect
extern _void DelEffect( ALuint resource );
// Find effect
extern EffectSHI* FindEffect( ALuint resource );

//----------------------------------------------------------------------------
// TALResource
//----------------------------------------------------------------------------

typedef _void (*GenResourceFunction)( ResourceSHI*, ALuint& );
typedef _void (*DelResourceFunction)( ALuint );

template< _SOUND_RESOURCE_TYPE ResourceType, GenResourceFunction _GEN_RESOURCE_FUNC, DelResourceFunction _DEL_RESOURCE_FUNC >
class TALResource : public TDynamicSHIResource< ResourceType >
{
protected:
	//!	The resource ID
	ALuint	mResource;

public:
	TALResource( )
	{
		// Generate resource ID
		_GEN_RESOURCE_FUNC( this, mResource );
	}

	virtual ~TALResource( )
	{
		if ( mResource != 0 )
			_DEL_RESOURCE_FUNC( mResource );
	}

public:
	//!	Get the resource
	EGE_GET_ACCESSOR( ALuint, Resource )
};

typedef TALResource< _SRT_BUFFER, GenBuffer, DelBuffer > ALBuffer;
typedef TALResource< _SRT_SOURCE, GenSource, DelSource > ALSource;
typedef TALResource< _SRT_EFFECT, GenEffect, DelEffect > ALEffect;

//----------------------------------------------------------------------------
// ALResourceManager
//----------------------------------------------------------------------------

class ALResourceManager
{
public:
	//!	It's singleton class.
	SINGLETON( ALResourceManager )

private:
	typedef Map< BufferSHI*, ALuint > BufferMap;
	typedef Map< SourceSHI*, ALuint > SourceMap;
	typedef Map< EffectSHI*, ALuint > EffectMap;

private:
	BufferMap	mBuffers;
	SourceMap	mSources;
	EffectMap	mEffects;

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

	//!	Generate the AL buffer.
	_void GenBuffer( BufferSHI* buffer, ALuint& resource );
	//!	Delete the AL buffer.
	_void DelBuffer( ALuint resource );
	//!	Find the AL buffer.
	BufferSHI* FindBuffer( ALuint resource );

	//!	Generate the AL source.
	_void GenSource( SourceSHI* source, ALuint& resource );
	//!	Delete the AL source.
	_void DelSource( ALuint resource );
	//!	Find the AL source.
	SourceSHI* FindSource( ALuint resource );

	//!	Generate the AL effect.
	_void GenEffect( EffectSHI* effect, ALuint& resource );
	//!	Delete the AL effect.
	_void DelEffect( ALuint resource );
	//!	Find the AL effect.
	EffectSHI* FindEffect( ALuint resource );
};

}