//! @file     WEBMFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// WEBMMkvReader Implementation
//----------------------------------------------------------------------------

WEBMMkvReader::WEBMMkvReader( IStreamReader* stream_reader )
{
	mStreamReader = stream_reader;
}

WEBMMkvReader::~WEBMMkvReader( )
{

}

int WEBMMkvReader::Read( long long pos, long len, unsigned char* buf )
{
	if ( pos < 0 )
		return -1;

	if ( len < 0 )
		return -1;

	if ( len == 0 )
		return 0;

	if ( pos >= mStreamReader->GetSize( ) )
		return -1;

	mStreamReader->Seek( _SEEK_BEGIN, (_long)pos );

	long read_size = mStreamReader->ReadBuffer( buf, len );
	if ( read_size < len )
		return -1;

	// OK
	return 0;
}

int WEBMMkvReader::Length( long long* total, long long* available )
{
	if ( mStreamReader.IsNull( ) )
		return -1;

	if ( total )
		*total = mStreamReader->GetSize( );

	if ( available )
		*available = mStreamReader->GetSize( );

	// OK
	return 0;
}

//----------------------------------------------------------------------------
// WEBMFileBlockEntry Implementation
//----------------------------------------------------------------------------

WEBMFileBlockEntry::WEBMFileBlockEntry( const mkvparser::Track* track )
{
	mTrack			= track;
	mCurBlockEntry	= _null;
	mNextBlockEntry	= _null;
	mStopBlockEntry	= track->GetEOS( );

	mBaseTimeNS		= 0;
}

WEBMFileBlockEntry::~WEBMFileBlockEntry( )
{

}

_ubool WEBMFileBlockEntry::InitCurBlock( )
{
	if ( mCurBlockEntry != _null )
		return _true;

	const mkvparser::Segment* segment = mTrack->m_pSegment;
	EGE_ASSERT( segment != _null );

	if ( segment->GetCount( ) <= 0 )
		return _false;

	const mkvparser::BlockEntry* cur_block_entry = _null;
	if ( mTrack->GetFirst( cur_block_entry ) == mkvparser::E_BUFFER_NOT_FULL )
		return _false;

	EGE_ASSERT( cur_block_entry );

	mCurBlockEntry = cur_block_entry;

	const mkvparser::Cluster* first_cluster = segment->GetFirst( );
	EGE_ASSERT( first_cluster );
	EGE_ASSERT( !first_cluster->EOS( ) );

	mBaseTimeNS = first_cluster->GetFirstTime( );

	return _true;
}

_void WEBMFileBlockEntry::Reset( )
{
	mCurBlockEntry = _null;
}

_ubool WEBMFileBlockEntry::BeginPopulateSample( )
{
	if ( InitCurBlock( ) == _false )
		return _false;

	if ( mStopBlockEntry == _null && mCurBlockEntry->EOS( ) )
		return _false;
	else if ( mCurBlockEntry == mStopBlockEntry )
		return _false;

	EGE_ASSERT( !mCurBlockEntry->EOS( ) );

	if ( mTrack->GetNext( mCurBlockEntry, mNextBlockEntry ) == mkvparser::E_BUFFER_NOT_FULL )
		return _false;

	EGE_ASSERT( mNextBlockEntry );

	const mkvparser::Block* const cur_block = mCurBlockEntry->GetBlock( );

	const mkvparser::Cluster* const cur_cluster = mCurBlockEntry->GetCluster( );
	EGE_ASSERT( cur_cluster );

	const _qword start_ns = cur_block->GetTime( cur_cluster );
	EGE_ASSERT( start_ns >= 0 );

	if ( start_ns < mBaseTimeNS )
		return _false;

	return _true;
}

_void WEBMFileBlockEntry::EndPopulateSample( )
{
	mCurBlockEntry = mNextBlockEntry;
}

_qword WEBMFileBlockEntry::GetCurTime( ) const
{
	if ( mCurBlockEntry == _null )
		return 0;

	if ( mCurBlockEntry->EOS( ) )
		return -1;

	const mkvparser::Block* block = mCurBlockEntry->GetBlock( );
	if ( block == _null )
		return -1;

	const _qword ns = block->GetTime( mCurBlockEntry->GetCluster( ) );
	EGE_ASSERT( ns >= 0 );

	const _qword reftime = ns / 100;  //100-ns ticks

	return reftime;
}

_qword WEBMFileBlockEntry::GetStopTime( ) const
{
	if ( mStopBlockEntry == _null )
		return -1;

	if ( mStopBlockEntry->EOS( ) )
		return -1;

	const mkvparser::Block* block = mStopBlockEntry->GetBlock( );
	EGE_ASSERT( block );

	const _qword ns = block->GetTime( mStopBlockEntry->GetCluster( ) );
	EGE_ASSERT( ns >= 0 );

	const _qword reftime = ns / 100;  //100-ns ticks

	return reftime;
}

_qword WEBMFileBlockEntry::GetDuration( _qword& start_reftime ) const
{
	const mkvparser::Block* const cur_block = mCurBlockEntry->GetBlock( );

	_dword frames = cur_block->GetFrameCount( );

	const mkvparser::Cluster* const cur_cluster = mCurBlockEntry->GetCluster( );
	EGE_ASSERT( cur_cluster );

	const _qword base_ns = mBaseTimeNS;
	EGE_ASSERT( base_ns >= 0 );

	mkvparser::Segment* const segment = mTrack->m_pSegment;

	const _qword start_ns = cur_block->GetTime( cur_cluster );
	EGE_ASSERT( start_ns >= base_ns );

	_qword stop_ns;

	if ( ( mNextBlockEntry ==  _null ) || mNextBlockEntry->EOS( ) )
	{
		//TODO: read duration from block group, if present

		const _qword duration_ns = segment->GetDuration( );

		if ( duration_ns > start_ns )
		{
			stop_ns = duration_ns;
		}
		else
		{
			const mkvparser::VideoTrack* const video_track = static_cast<const mkvparser::VideoTrack*>(mTrack);

			double frame_rate = video_track->GetFrameRate( );

			if ( frame_rate <= 0 )
				frame_rate = 10;  //100ms

			const double ns = 1000000000.0 / frame_rate;
			const _qword ns_per_frame = static_cast<_qword>(ns);

			stop_ns = start_ns + _qword( frames ) * ns_per_frame;
		}
	}
	else
	{
		const mkvparser::Block* const next_block = mNextBlockEntry->GetBlock( );
		EGE_ASSERT( next_block );

		const mkvparser::Cluster* const next_cluster = mNextBlockEntry->GetCluster( );

		stop_ns = next_block->GetTime( next_cluster );
		EGE_ASSERT( stop_ns > start_ns );
	}

	start_reftime = (start_ns - base_ns) / 100;

	const _qword block_stop_reftime = (stop_ns - base_ns) / 100;
	EGE_ASSERT( block_stop_reftime >= start_reftime );

	const _qword block_duration = block_stop_reftime - start_reftime;
	EGE_ASSERT( block_duration >= 0 );

	_qword frame_duration = block_duration / frames;  //reftime units

	if ( frame_duration <= 0 )  //weird: block duration is very small
		frame_duration = 1;

	return frame_duration;
}

_dword WEBMFileBlockEntry::GetFrameNumber( ) const
{
	const mkvparser::Block* const cur_block = mCurBlockEntry->GetBlock( );

	return cur_block->GetFrameCount( );
}

_dword WEBMFileBlockEntry::GetFrameSizeByIndex( _dword index ) const
{
	const mkvparser::Block* const cur_block = mCurBlockEntry->GetBlock( );

	const mkvparser::Block::Frame& frame = cur_block->GetFrame( index );

	return frame.len;
}

_dword WEBMFileBlockEntry::GetFrameDataByIndex( _dword index, _byte* buffer ) const
{
	const mkvparser::Block* const cur_block = mCurBlockEntry->GetBlock( );

	const mkvparser::Block::Frame& frame = cur_block->GetFrame( index );

	mkvparser::Segment* const segment = mTrack->m_pSegment;

	mkvparser::IMkvReader* const mkv_reader = segment->m_pReader;

	const long status = frame.Read( mkv_reader, buffer );
	if ( status != 0 )
		return -1;

	return frame.len;
}

//----------------------------------------------------------------------------
// WEBMFileTrack Implementation
//----------------------------------------------------------------------------

WEBMFileTrack::WEBMFileTrack( const mkvparser::Track* track )
{
	mTrack		= track;

	mBlockEntry = new WEBMFileBlockEntry( track );
}

WEBMFileTrack::~WEBMFileTrack( )
{
	EGE_RELEASE( mBlockEntry );
}

const mkvparser::Track*	WEBMFileTrack::GetMKVTrack( ) const
{
	return mTrack;
}

_MEDIA_TYPE WEBMFileTrack::GetType( ) const
{
	if ( mTrack->GetType( ) == mkvparser::Track::kAudio )
		return _MEDIA_TYPE_AUDIO;
	else if ( mTrack->GetType( ) == mkvparser::Track::kVideo )
		return _MEDIA_TYPE_VIDEO;

	return _MEDIA_TYPE_UNKNOWN;
}

WStringR WEBMFileTrack::GetName( ) const
{
	return WString( ).FromString( _ENCODING_UTF8, mTrack->GetNameAsUTF8( ) );
}

WStringR WEBMFileTrack::GetCodecName( ) const
{
	return WString( ).FromString( _ENCODING_UTF8, mTrack->GetCodecNameAsUTF8( ) );
}

WStringR WEBMFileTrack::GetCodecID( ) const
{
	return WString( ).FromString( _ENCODING_ANSI, mTrack->GetCodecId( ) );
}

_void WEBMFileTrack::Reset( )
{
	mBlockEntry->Reset( );
}

_ubool WEBMFileTrack::PopulateSample( IMediaFileNotifier* notifier )
{
	if ( notifier == _null )
		return _false;

	if ( mBlockEntry->BeginPopulateSample( ) == _false )
		return _false;

	switch ( GetType( ) )
	{
		case _MEDIA_TYPE_AUDIO: 
		{
			WEBMFileAudioTrack audio_track( this );
			notifier->OnPopulateAudioSample( &audio_track, mBlockEntry ); 
		}
		break;

		case _MEDIA_TYPE_VIDEO: 
		{
			WEBMFileVideoTrack video_track( this );
			notifier->OnPopulateVideoSample( &video_track, mBlockEntry ); 
		}
		break;

		default:
			break;
	}

	mBlockEntry->EndPopulateSample( );

	return _true;
}

//----------------------------------------------------------------------------
// WEBMFileVideoTrack Implementation
//----------------------------------------------------------------------------

WEBMFileVideoTrack::WEBMFileVideoTrack( WEBMFileTrack* track ) : BaseClass( track )
{
}

WEBMFileVideoTrack::~WEBMFileVideoTrack( )
{

}

_dword WEBMFileVideoTrack::GetWidth( ) const
{
	return (_dword)GetTrack< mkvparser::VideoTrack >( )->GetWidth( );
}

_dword WEBMFileVideoTrack::GetHeight( ) const
{
	return (_dword)GetTrack< mkvparser::VideoTrack >( )->GetHeight( );
}

_float WEBMFileVideoTrack::GetFrameRate( ) const
{
	return (_float)GetTrack< mkvparser::VideoTrack >( )->GetFrameRate( );
}

//----------------------------------------------------------------------------
// WEBMFileAudioTrack Implementation
//----------------------------------------------------------------------------

WEBMFileAudioTrack::WEBMFileAudioTrack( WEBMFileTrack* track ) : BaseClass( track )
{
	mVorbisFormatInfo = _null;

	// OGG audio
	WString codec_id = GetCodecID( );
	if ( codec_id == L"A_VORBIS" )
		BuildVorbisFormatInfo( );
}

WEBMFileAudioTrack::~WEBMFileAudioTrack( )
{
	EGE_FREE( mVorbisFormatInfo );
}

_void WEBMFileAudioTrack::BuildVorbisFormatInfo( )
{
	const mkvparser::AudioTrack* const track = GetTrack< mkvparser::AudioTrack >( );

	size_t cp_size;

	const _byte* const cp = track->GetCodecPrivate( cp_size );
	EGE_ASSERT( cp );
	EGE_ASSERT( cp_size > 0 );

	const _byte* const begin = &cp[0];
	const _byte* const end = begin + cp_size;

	const _byte* p = begin;
	EGE_ASSERT( p < end );

	const _byte n = *p++;
	n;
	EGE_ASSERT( n == 2 );
	EGE_ASSERT( p < end );

	const _byte id_len = *p++;  //TODO: don't assume < 255
	EGE_ASSERT( id_len < 255 );
	EGE_ASSERT( id_len > 0 );
	EGE_ASSERT( p < end );

	const _byte comment_len = *p++;  //TODO: don't assume < 255
	EGE_ASSERT( comment_len < 255 );
	EGE_ASSERT( comment_len > 0 );
	EGE_ASSERT( p < end );

	//p points to first header

	const _byte* const id_hdr = p;
	const _byte* const comment_hdr = id_hdr + id_len;
	const _byte* const setup_hdr = comment_hdr + comment_len;
	EGE_ASSERT( setup_hdr < end );

	const ptrdiff_t setup_len_ = end - setup_hdr;
	EGE_ASSERT( setup_len_ > 0 );

	const _dword setup_len = static_cast<_dword>(setup_len_);

	const size_t hdr_len = id_len + comment_len + setup_len;

	const size_t cb = sizeof( SoundVorbisFormatInfo ) + hdr_len;
	_byte* const pb = (_byte*)malloc( cb );

	SoundVorbisFormatInfo& fmt = (SoundVorbisFormatInfo&)(*pb);

	fmt.mChannels = GetChannels( );
	fmt.mSampleRate = GetSampleRate( );
	fmt.mSampleBitSize = GetSampleBitSize( );
	fmt.mHeaderSize[0] = id_len;
	fmt.mHeaderSize[1] = comment_len;
	fmt.mHeaderSize[2] = setup_len;

	EGE_ASSERT( p < end );
	EGE_ASSERT( size_t( end - p ) == hdr_len );

	_byte* const dst = pb + sizeof( SoundVorbisFormatInfo );
	memcpy( dst, p, hdr_len );

	mVorbisFormatInfo = &fmt;
}

_AUDIO_FORMAT WEBMFileAudioTrack::GetFormat( ) const
{
	_dword channels = GetChannels( );
	_dword bit_size	= GetSampleBitSize( );

	if ( channels == 1 )
	{
		if ( bit_size == 8 )
			return _AF_MONO8;
		else if ( bit_size == 16 )
			return _AF_MONO16;
	}
	else if ( channels == 2 )
	{
		if ( bit_size == 8 )
			return _AF_STEREO8;
		else
			return _AF_STEREO16;
	}

	return _AF_UNKNOWN;
}

_dword WEBMFileAudioTrack::GetChannels( ) const
{
	return (_dword)GetTrack< mkvparser::AudioTrack >( )->GetChannels( );
}

_dword WEBMFileAudioTrack::GetSampleBitSize( ) const
{
	return (_dword)GetTrack< mkvparser::AudioTrack >( )->GetBitDepth( );
}

_dword WEBMFileAudioTrack::GetSampleRate( ) const
{
	const _double rate = GetTrack< mkvparser::AudioTrack >( )->GetSamplingRate( );
	EGE_ASSERT( rate > 0 );

	_double intrate_;
	const _double fracrate = modf( rate, &intrate_ );

	const _dword result = static_cast<_dword>(intrate_);
	return result;
}

const SoundVorbisFormatInfo* WEBMFileAudioTrack::GetVorbisFormatInfo( ) const
{
	return mVorbisFormatInfo;
}

//----------------------------------------------------------------------------
// WEBMFile Implementation
//----------------------------------------------------------------------------

WEBMFile::WEBMFile( )
{
	mSegment	= _null;

	mReader		= _null;
}

WEBMFile::~WEBMFile( )
{
	Unload( );
}

_ubool WEBMFile::InitTracks( )
{
	const mkvparser::Tracks* tracks = mSegment->GetTracks( );
	if ( tracks == _null )
		return _false;

	for ( _dword i = 0; i < tracks->GetTracksCount( ); i ++ )
	{
		WEBMFileTrack* track = new WEBMFileTrack( tracks->GetTrackByIndex( i ) );

		mTracks.Append( track );
	}

	return _true;
}

_FILE_FORMAT WEBMFile::GetFileID( ) const
{
	return _FF_WEBM;
}

_ubool WEBMFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Create stream reader
	mReader = new WEBMMkvReader( stream_reader );

	// Parse header
	long long pos = 0;
	mkvparser::EBMLHeader ebml_header;
	if ( ebml_header.Parse( mReader, pos ) )
	{
		WLOG_ERROR( L"Parse webm file failed, due to invalid header" );
		return _false;
	}

	// Create segment parser
	if ( mkvparser::Segment::CreateInstance( mReader, pos, mSegment ) )
	{
		WLOG_ERROR( L"Parse webm file failed, due to create segment failed" );
		return _false;
	}

	// Parse segments
	if ( mSegment->Load( ) )
	{
		WLOG_ERROR( L"Parse webm file failed, due to invalid segment" );
		return _false;
	}

	// Initialize tracks
	if ( InitTracks( ) == _false )
		return _false;

	return _true;
}

_void WEBMFile::Unload( )
{
	BaseClass::Unload( );

	for ( _dword i = 0; i < mTracks.Number( ); i ++ )
	{
		EGE_DELETE( mTracks[i] );
	}

	mTracks.Clear( );

	EGE_DELETE( mSegment );

	EGE_DELETE( mReader );
}

_dword WEBMFile::GetTrackNumber( ) const
{
	return mTracks.Number( );
}

IMediaFileTrack* WEBMFile::GetTrackByIndex( _dword index ) const
{
	if ( index >= mTracks.Number( ) )
		return _null;

	return mTracks[ index ];
}
