//! @file     androidAppXML.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// androidAppXML
//----------------------------------------------------------------------------

class androidAppXML
{
private:
	//!	The resource info
	struct ResInfo
	{
		_ubool	mStrict;
		WString	mFileName;
		MD5Code	mMD5Code;

		ResInfo( )
		{
			mStrict = _false;
		}
	};
	typedef Array< ResInfo > ResInfoArray;

	//!	The resource group info
	struct ResGroupInfo
	{
		enum _TYPE
		{
			_TYPE_NORMAL,
			_TYPE_ANY,
		};

		//!	The group type
		_TYPE			mType;
		//! The resources list
		ResInfoArray	mResources;

		ResGroupInfo( )
		{
			mType = _TYPE_NORMAL;
		}
	};
	typedef Array< ResGroupInfo > ResGroupInfoArray;

	//!	The application info
	struct AppInfo
	{
		//! The resources list
		ResGroupInfoArray	mResourceGroups;
		//!	The APK signature
		AString				mAPKSignature;
	};

private:
	//!	True indicates XML has loaded
	_ubool	mHasLoaded;
	//!	True indicates it had initialized
	_ubool	mInitOK;

	//!	The current application info
	AppInfo	mCurAppInfo;
	//!	The configure application info
	AppInfo	mConfigureAppInfo;

private:
	//!	Get the group type.
	EGE_INTERNAL static ResGroupInfo::_TYPE OnQueryResGroupInfoTypeValue( WStringPtr name );

	//!	Check group.
	EGE_INTERNAL static _ubool CheckGroupAny( const ResGroupInfo& cur_group_info, const ResGroupInfo& config_group_info );
	EGE_INTERNAL static _ubool CheckGroup( const ResGroupInfo& cur_group_info, const ResGroupInfo& config_group_info );

private:
	//!	Clear resources.
	EGE_INTERNAL _void ClearResources( );
	//!	Load APK signature.
	EGE_INTERNAL _ubool LoadAPKSignature( );

	//!	Load app configure file.
	EGE_INTERNAL _ubool LoadAppXML( IMarkupLangFile* xml_file );

public:
	androidAppXML( );
	virtual ~androidAppXML( );

public:
	//!	Initialize.
	EGE_INTERNAL _ubool Initialize( );
	//!	Load application xml file.
	EGE_INTERNAL _ubool LoadConfigure( AStringPtr key, IStreamReader* app_stream );
	//!	Check whether it's valid.
	EGE_INTERNAL _ubool IsValid( ) const;
};

// --------------------------------------------------------------------------------------------------------------
// androidAppXML Implementation
// --------------------------------------------------------------------------------------------------------------

}