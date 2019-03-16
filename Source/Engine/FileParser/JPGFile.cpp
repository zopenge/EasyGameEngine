//! @file     JPGFile.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Helpful Structures
//----------------------------------------------------------------------------

struct JpegErrorManager : public jpeg_error_mgr
{
	// For return to caller
	jmp_buf mJumpBuffer;
};

struct JpegSourceManager : public jpeg_source_mgr
{
	// Initialized flag
	_ubool			mInitialized;
	// Start of buffer
	JOCTET*			mBuffer;
	// Data stream
	IStreamReader*	mStreamReader;
};

struct JpegDestinationManager : public jpeg_destination_mgr
{
	// Start of buffer
	JOCTET*			mBuffer;
	// Data stream
	IStreamReader*	mStreamReader;
};

//----------------------------------------------------------------------------
// JPGFile Helpful Functions Implementation
//----------------------------------------------------------------------------

//!	LibJPEG ErrorManager's callback functions.
static _void OnErrorExit( j_common_ptr jpegcommon )
{
	// Always display the message
	(*jpegcommon->err->output_message)( jpegcommon );
}

//!	LibJPEG SourceManager's callback functions.
static _void OnInitializeSource( j_decompress_ptr jpegdecompress )
{
	( (JpegSourceManager*) jpegdecompress->src )->mInitialized = _true;
}

static boolean OnFillInputBuffer( j_decompress_ptr jpegdecompress )
{
	JpegSourceManager* sourcemanager = (JpegSourceManager*) jpegdecompress->src;

	// Read the image buffer
	_dword read_bytes = sourcemanager->mStreamReader->ReadBuffer( sourcemanager->mBuffer, 4 KB );
	if ( read_bytes == 0 )
	{
		// The Jpeg image buffer is invalid, now send warning message
		WARNMS( jpegdecompress, JWRN_JPEG_EOF );

		// Insert a fake EOI marker
		sourcemanager->mBuffer[0] = (JOCTET) 0xFF;
		sourcemanager->mBuffer[1] = (JOCTET) JPEG_EOI;

		return FALSE;
	}

	sourcemanager->next_input_byte = sourcemanager->mBuffer;
	sourcemanager->bytes_in_buffer = read_bytes;

	return TRUE;
}

static _void OnSkipInputData( j_decompress_ptr jpegdecompress, long bytes )
{
	if ( bytes <= 0 )
		return;

	JpegSourceManager* sourcemanager = (JpegSourceManager*) jpegdecompress->src;

	while ( bytes > (long) sourcemanager->bytes_in_buffer ) 
	{
		bytes -= (long) sourcemanager->bytes_in_buffer;

		OnFillInputBuffer( jpegdecompress );
	}

	sourcemanager->next_input_byte += (size_t) bytes;
	sourcemanager->bytes_in_buffer -= (size_t) bytes;
}

static _void OnTermSource( j_decompress_ptr jpegdecompress )
{
}

//!	LibJPEG DestinationManager's callback functions.
static _void OnInitializeDestination( j_compress_ptr jpegcompress )
{
}

static boolean OnEmptyOutputBuffer( j_compress_ptr jpegcompress )
{
	return TRUE;
}

static _void OnTermDestination( j_compress_ptr jpegcompress )
{
}

//!	Initialize Jpeg error manager.
//!	@param		jpegdecompress		The jpeg decompress.
//! @return		True indicates success, false indicates failure.
static _ubool InitializeJpegErrorManager( j_decompress_ptr jpegdecompress )
{
	// Allocate memory for the buffer, what is released automatically in the end
	jpegdecompress->err = (jpeg_error_mgr*) (*jpegdecompress->mem->alloc_small)( (j_common_ptr) jpegdecompress, JPOOL_PERMANENT, sizeof( JpegErrorManager ) );
	if ( jpegdecompress->err == _null )
		return _false;

	// Initialize by the standard error manager
	::jpeg_std_error( jpegdecompress->err );

	// Get the JPEG error manager
	JpegErrorManager* jpegerrormanager = (JpegErrorManager*) jpegdecompress->err;

	// Initialize the JPEG error manager
	jpegerrormanager->error_exit = OnErrorExit;

	return _true;
}

//!	Initialize Jpeg source manager.
//!	@param		jpegdecompress		The jpeg decompress.
//!	@param		stream_reader		The stream reader.
//! @return		True indicates success, false indicates failure.
static _ubool InitializeJpegSourceManager( j_decompress_ptr jpegdecompress, IStreamReader* stream_reader )
{
	// Allocate memory for the buffer, what is released automatically in the end
	jpegdecompress->src = (jpeg_source_mgr*) (*jpegdecompress->mem->alloc_small)( (j_common_ptr) jpegdecompress, JPOOL_PERMANENT, sizeof( JpegSourceManager ) );
	if ( jpegdecompress->src == _null )
		return _false;

	JpegSourceManager* jpegsourcemanager = (JpegSourceManager*) jpegdecompress->src;

	// Allocate buffer data for store the image buffer
	jpegsourcemanager->mBuffer = (JOCTET*) (*jpegdecompress->mem->alloc_small)( (j_common_ptr) jpegdecompress, JPOOL_PERMANENT, 4096 * sizeof( JOCTET ) );
	if ( jpegsourcemanager->mBuffer == _null )
		return _false;

	// Initialize the jpeg pointer struct with pointers to functions
	jpegsourcemanager->mStreamReader		= stream_reader;
	jpegsourcemanager->init_source			= OnInitializeSource;
	jpegsourcemanager->fill_input_buffer	= OnFillInputBuffer;
	jpegsourcemanager->skip_input_data		= OnSkipInputData;
	jpegsourcemanager->resync_to_restart	= jpeg_resync_to_restart;	// use default method 
	jpegsourcemanager->term_source			= OnTermSource;
	jpegsourcemanager->bytes_in_buffer		= 0;						// forces fill_input_buffer on first read 
	jpegsourcemanager->next_input_byte		= _null;					// until buffer loaded 

	return _true;
}

//!	Initialize Jpeg destination manager.
//!	@param		jpegcompress		The jpeg compress.
//! @return		True indicates success, false indicates failure.
static _ubool InitializeJpegDestinationManager( j_compress_ptr jpegcompress )
{
	// Allocate memory for the buffer, what is released automatically in the end
	jpegcompress->dest = (jpeg_destination_mgr*) (*jpegcompress->mem->alloc_small)( (j_common_ptr) jpegcompress, JPOOL_PERMANENT, sizeof( JpegDestinationManager ) );
	if ( jpegcompress->dest == _null )
		return _false;

	JpegDestinationManager* jpegdestinationmanager = (JpegDestinationManager*) jpegcompress->dest;

	// Initialize the jpeg pointer struct with pointers to functions
	jpegdestinationmanager->init_destination	= OnInitializeDestination;
	jpegdestinationmanager->empty_output_buffer = OnEmptyOutputBuffer;
	jpegdestinationmanager->term_destination	= OnTermDestination;

	return _true;
}

//----------------------------------------------------------------------------
// JPGFile Implementation
//----------------------------------------------------------------------------

JPGFile::JPGFile( )
{
}

JPGFile::~JPGFile( )
{
	Unload( );
}

_FILE_FORMAT JPGFile::GetFileID( ) const
{
	return _FF_JPG;
}

_ubool JPGFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// The JPEG common object
	jpeg_decompress_struct jpegdecompress;

	// Create JPEG decompression object
	::jpeg_create_decompress( &jpegdecompress );

	// Initialize JPEG error manager and source manager object
	if ( InitializeJpegErrorManager( &jpegdecompress ) == _false || InitializeJpegSourceManager( &jpegdecompress, stream_reader ) == _false )
	{
		::jpeg_destroy_decompress( &jpegdecompress );
		return _false;
	}

	// Read JPEG header
	::jpeg_read_header( &jpegdecompress, _true );

	// Set the decode option
	jpegdecompress.scale_num			= 1;
	jpegdecompress.scale_denom			= 1;
	jpegdecompress.dct_method			= JDCT_IFAST;
	jpegdecompress.do_fancy_upsampling	= _false;

	// Start decompressor and calculate output width and height
	::jpeg_start_decompress( &jpegdecompress );

	// We only support the RGB color mode
	if ( jpegdecompress.num_components == 3 && jpegdecompress.out_color_space == JCS_RGB )
	{
		// Set the image width and height
		mImageWidth		= jpegdecompress.output_width;
		mImageHeight	= jpegdecompress.output_height;
		mImagePitch		= mImageWidth * 3;

		// Set the image pixel format
		mImagePixelFormat = _PF_R8G8B8;

		// Check whether decode pixel buffer
		if ( HasFlags( _FLAG_HEADER_ONLY ) == _false )
		{
			// Create the image pixel buffer
			mImagePixelBuffer = new _byte[ mImagePitch * mImageHeight ];

			// Read the image scan lines
			while ( jpegdecompress.output_scanline < jpegdecompress.output_height )
			{
				JSAMPROW samples = mImagePixelBuffer + mImagePitch * jpegdecompress.output_scanline;

				::jpeg_read_scanlines( &jpegdecompress, &samples, 1 );
			}
		}
	}

	// Finish decompression
	::jpeg_finish_decompress( &jpegdecompress );

	// Release JPEG decompression object
	::jpeg_destroy_decompress( &jpegdecompress );

	return _true;
}

_void JPGFile::Unload( )
{
	BaseClass::Unload( );
}