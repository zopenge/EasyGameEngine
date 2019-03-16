//! @file     androidAppXML.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

// --------------------------------------------------------------------------------------------------------------
// androidAppXML Implementation
// --------------------------------------------------------------------------------------------------------------

androidAppXML::androidAppXML( )
{
	mHasLoaded	= _false;
	mInitOK		= _false;
}

androidAppXML::~androidAppXML( )
{
}

androidAppXML::ResGroupInfo::_TYPE androidAppXML::OnQueryResGroupInfoTypeValue( WStringPtr name )
{
	if ( name.IsEqual( L"Any", _true ) )
		return ResGroupInfo::_TYPE_ANY;

	return ResGroupInfo::_TYPE_NORMAL;
}

_ubool androidAppXML::CheckGroupAny( const ResGroupInfo& cur_group_info, const ResGroupInfo& config_group_info )
{
	EGE_ASSERT( cur_group_info.mResources.Number( ) == config_group_info.mResources.Number( ) );

	for ( _dword i = 0; i < cur_group_info.mResources.Number( ); i ++ )
	{
		const ResInfo& cur_res_info		= cur_group_info.mResources[i];
		const ResInfo& config_res_info	= config_group_info.mResources[i];

		if ( cur_res_info.mMD5Code == config_res_info.mMD5Code )
		{
			return _true;
		}
		// It it's VIP file then we are failed still ...
		else if ( cur_res_info.mStrict )
		{
			WLOG_ERROR_4( L"Resource '%s' and '%s' MD5 is invalid '%s' != '%s'", cur_res_info.mFileName.Str( ), config_res_info.mFileName.Str( ),
				cur_res_info.mMD5Code.ToWString( _false ).Str( ), config_res_info.mMD5Code.ToWString( _false ).Str( ) );

			return _false;
		}
	}

	return _false;
}

_ubool androidAppXML::CheckGroup( const ResGroupInfo& cur_group_info, const ResGroupInfo& config_group_info )
{
	EGE_ASSERT( cur_group_info.mResources.Number( ) == config_group_info.mResources.Number( ) );

	for ( _dword i = 0; i < cur_group_info.mResources.Number( ); i ++ )
	{
		const ResInfo& cur_res_info		= cur_group_info.mResources[i];
		const ResInfo& config_res_info	= config_group_info.mResources[i];

		if ( cur_res_info.mMD5Code != config_res_info.mMD5Code )
		{
			WLOG_ERROR_4( L"Resource '%s' and '%s' MD5 is invalid '%s' != '%s'", cur_res_info.mFileName.Str( ), config_res_info.mFileName.Str( ),
				cur_res_info.mMD5Code.ToWString( _false ).Str( ), config_res_info.mMD5Code.ToWString( _false ).Str( ) );

			return _false;
		}
	}

	return _true;
}

_void androidAppXML::ClearResources( )
{
	mCurAppInfo.mResourceGroups.Clear( );

	mConfigureAppInfo.mResourceGroups.Clear( );
	mConfigureAppInfo.mAPKSignature.Clear( );
}

_ubool androidAppXML::LoadAPKSignature( )
{
	// Here use the native way to get the APK signature
	mCurAppInfo.mAPKSignature = GetPlatform( )->GetSignature( );
	if ( mCurAppInfo.mAPKSignature.IsEmpty( ) )
	{
		ALOG_ERROR( "Load APK signature in native failed, it's empty string" );
		return _false;
	}

	ALOG_TRACE_1( "Load APK signature '%s'", mCurAppInfo.mAPKSignature.Str( ) );

	return _true;
}

_ubool androidAppXML::LoadAppXML( IMarkupLangFile* xml_file )
{
	ClearResources( );

	WLOG_TRACE( L"Start to load app xml ..." );

	// Get root
	IMarkupLangElement* root = xml_file->GetRootElement( );
	if ( root == _null )
	{	
		WLOG_TRACE( L"The app xml root element is null" );
		return _false;
	}

	// Load signature
	IMarkupLangElement* signature_element = root->GetChildElementByName( L"Signature" );
	if ( signature_element != _null )
	{
		WString signature;
		if ( signature_element->GetAttributeString( L"id", signature ) )
			mConfigureAppInfo.mAPKSignature.FromString( signature );
	}

	// Load resources
	IMarkupLangElement* resources_element = root->GetChildElementByName( L"Resources" );
	if ( resources_element != _null )
	{
		_ubool ret = _true;

		// Get the APK file name
		AStringPtr apk_filename = gAndroidViewbasedApp.GetAndroidAppInfo( ).mSourceDir;

		// Open APK file
		IFileStreamReaderRef apk_file = GetInterfaceFactory( )->CreateFileStreamReader( WString( ).FromString( apk_filename ) );
		if ( apk_file.IsNull( ) )
		{
			ALOG_ERROR_1( "Open the '%s' VIP file failed", apk_filename.Str( ) );
			return _false;
		}

		// Parse APK file
		IZIPFileRef zip_file = GetInterfaceFactory( )->ParseZipFile( apk_file, L"", IZIPFile::_FLAG_SKIP_TO_BUILD_ITEMS );
		if ( zip_file.IsNull( ) )
		{
			ALOG_ERROR_1( "Unzip the '%s' VIP file failed", apk_filename.Str( ) );
			return _false;
		}

		// Load each resource
		for ( IMarkupLangElement* group_element = resources_element->GetFirstChildElement( ); group_element != _null; group_element = group_element->GetNextElement( ) )
		{
			ResGroupInfo group_info;

			WString type_string;
			if ( group_element->GetAttributeString( L"type", type_string ) )
				group_info.mType = OnQueryResGroupInfoTypeValue( type_string );

			mCurAppInfo.mResourceGroups.Append( group_info );
			mConfigureAppInfo.mResourceGroups.Append( group_info );

			for ( IMarkupLangElement* file_element = group_element->GetFirstChildElement( ); file_element != _null; file_element = file_element->GetNextElement( ) )
			{
				WString filename, md5;
				ret &= file_element->GetAttributeString( L"name", filename );
				ret &= file_element->GetAttributeString( L"md5", md5 );
				if ( ret == _false )
					return _false;

				// Read optional
				_ubool strict = _false;
				file_element->GetAttributeBool( L"strict", strict );

				// Get the file from APK file
				IStreamReaderRef file_stream = zip_file->GetFile( filename );
				if ( file_stream.IsValid( ) )
				{
					// The configure resource info
					ResInfo config_res_info;
					config_res_info.mStrict		= strict;
					config_res_info.mFileName	= filename;
					config_res_info.mMD5Code.ParseFromString( md5 );
					mConfigureAppInfo.mResourceGroups.GetTailElement( ).mResources.Append( config_res_info );

					WLOG_TRACE_2( L"Add configure 'name: %s, md5: %s' resource", filename.Str( ), config_res_info.mMD5Code.ToWString( _false ).Str( ) );

					// Get the file from APK file
					IStreamReaderRef file_stream = zip_file->GetFile( filename );
					if ( file_stream.IsNull( ) )
					{
						WLOG_ERROR_1( L"Load file from APK failed: 'name: %s' resource", filename.Str( ) );
						return _false;
					}

					// Build resource info
					ResInfo res_info;
					res_info.mStrict	= strict;
					res_info.mFileName	= filename;
					res_info.mMD5Code	= MD5::BuildFromBuffer( file_stream->GetBuffer( ), file_stream->GetSize( ) );
					mCurAppInfo.mResourceGroups.GetTailElement( ).mResources.Append( res_info );

					WLOG_TRACE_2( L"Add 'name: %s, md5: %s' resource", filename.Str( ), res_info.mMD5Code.ToWString( _false ).Str( ) );
				}
				else
				{
					WLOG_TRACE_1( L"The 'name: %s' resource is not existing in APK, now skip it", filename.Str( ) );
				}
			}
		}
	}

	WLOG_TRACE( L"Finished load app xml" );

	return _true;
}

_ubool androidAppXML::Initialize( )
{
	WLOG_TRACE( L"Initialize android App-XML ..." );

	if ( LoadAPKSignature( ) == _false )
	{
		WLOG_TRACE( L"Initialize android App-XML failed, due to load APK signature failed" );
		return _false;
	}

	mInitOK = _true;

	WLOG_TRACE( L"Initialize android App-XML OK" );

	return _true;
}

_ubool androidAppXML::LoadConfigure( AStringPtr key, IStreamReader* app_stream )
{
	if ( app_stream == _null )
		return _false;

	WLOG_TRACE( L"Loading app xml configure ..." );

	// Load fake image file
	IImageFileRef image_file = GetInterfaceFactory( )->ParseImageFile( app_stream, _FF_PNG );
	if ( image_file.IsNull( ) )
	{
		WLOG_ERROR( L"Parse invalid image file on loading app xml" );
		return _false;
	}

	// Get the app configure info from png pixel buffer
	const _byte* buffer = image_file->GetPixelBuffer( );
	if ( buffer == _null )
	{
		WLOG_ERROR( L"The image file buffer is invalid on loading app xml" );
		return _false;
	}

	// Get the buffer size
	const _dword size = *(const _dword*) buffer;
	if ( size == 0 )
	{
		WLOG_ERROR( L"The image file size is invalid on loading app xml" );
		return _false;
	}

	// Jump the size info
	buffer += sizeof( _dword );

	// Decrypt app configure info
	IDecryptorRef decryptor = GetInterfaceFactory( )->CreateDecryptor( _ENCRYPTION_DES, key );
	if ( decryptor.IsNull( ) )
	{
		WLOG_ERROR( L"Create decryptor failed on loading app xml" );
		return _false;
	}

	if ( decryptor->ProcessBuffer( size, buffer ) == _false )
	{
		WLOG_ERROR( L"Decrypt stream failed on loading app xml" );
		return _false;
	}

	// Parse the configure info
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->ParseMarkupLangFile( decryptor->GetProcessedStreamReader( ).GetPtr( ) );
	if ( xml_file.IsNull( ) )
	{
		WLOG_ERROR( L"Parse XML file failed on loading app xml" );
		return _false;
	}

	// Load xml file
	if ( LoadAppXML( xml_file ) == _false )
	{
		WLOG_ERROR( L"Load app XML file failed on loading app xml" );
		return _false;
	}

	// Load successful
	mHasLoaded = _true;

	WLOG_TRACE( L"Loaded app xml configure OK" );

	return _true;
}

_ubool androidAppXML::IsValid( ) const
{
	WLOG_TRACE( L"Start to validating android app XML ..." );

	// Check the initialize flags
	if ( mInitOK == _false )
	{
		ALOG_ERROR( "App XML validation failed due to initialize failed" );
		return _false;
	}

	// Check the load flags
	if ( mHasLoaded == _false )
	{
		ALOG_ERROR( "App XML validation failed due to load XML failed" );
		return _false;
	}

	// Check APK signature
	if ( (!mConfigureAppInfo.mAPKSignature.IsEmpty( )) && (mCurAppInfo.mAPKSignature != mConfigureAppInfo.mAPKSignature) )
	{
		ALOG_ERROR_2( "APK signature '%s' != '%s'", mCurAppInfo.mAPKSignature.Str( ), mConfigureAppInfo.mAPKSignature.Str( ) );
		return _false;
	}

	// Check groups number
	if ( mCurAppInfo.mResourceGroups.Number( ) != mConfigureAppInfo.mResourceGroups.Number( ) )
	{
		WLOG_ERROR_2( L"Groups number '%s' != '%s'", mCurAppInfo.mResourceGroups.Number( ), mConfigureAppInfo.mResourceGroups.Number( ) );
		return _false;
	}

	// Check groups
	for ( _dword i = 0; i < mCurAppInfo.mResourceGroups.Number( ); i ++ )
	{
		const ResGroupInfo& cur_group		= mCurAppInfo.mResourceGroups[i];
		const ResGroupInfo& config_group	= mConfigureAppInfo.mResourceGroups[i];

		// Check resources number
		if ( cur_group.mResources.Number( ) != config_group.mResources.Number( ) )
		{
			WLOG_ERROR_2( L"Resources number '%s' != '%s'", cur_group.mResources.Number( ), config_group.mResources.Number( ) );
			return _false;
		}

		// Skip for empty resources checking
		if ( cur_group.mResources.Number( ) == 0 )
			continue;

		// Check resources
		_ubool ret = _false;
		switch ( cur_group.mType )
		{
			case ResGroupInfo::_TYPE_NORMAL:	ret = CheckGroup( cur_group, config_group ); break;
			case ResGroupInfo::_TYPE_ANY:		ret = CheckGroupAny( cur_group, config_group ); break;
			default:
				break;
		}

		if ( !ret )
		{
			WLOG_ERROR( L"The android app XML is invalid" );
			return _false;
		}
	}

	WLOG_TRACE( L"The android app XML is valid" );

	return _true;
}
