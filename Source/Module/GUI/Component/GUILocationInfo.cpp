#include "EGEGUI.h"

GUILocationInfo::GUILocationInfo( )
	: mSizeType( _GUI_SIZE_CONSTANT )
	, mAnchorType( _GUI_ANCHOR_CENTER )
	, mLogicSize( 0.0f )
	, mLogicPosition( 0.0f )
	, mAnchorPosition( 0.0f )
	, mLogicScale( 1.0f )
{
	mUnionSize.mUnionSize = 0.0f;
}

GUILocationInfo::~GUILocationInfo( )
{

}

_void GUILocationInfo::CopyFrom( const GUILocationInfo& location_info )
{
	mSizeType		= location_info.mSizeType;
	mAnchorType		= location_info.mAnchorType;
	mLogicSize		= location_info.mLogicSize;	
	mUnionSize		= location_info.mUnionSize;		
	mLogicPosition	= location_info.mLogicPosition;
	mAnchorPosition	= location_info.mAnchorPosition;	
	mLogicScale		= location_info.mLogicScale;
}

IObject* GUILocationInfo::CloneTo( ) const
{
	GUILocationInfo* location_info	= new GUILocationInfo( );
	location_info->CopyFrom( *this );

	return location_info;
}

_ubool GUILocationInfo::UpdateUnionSize( _float parentsize )
{
	_ubool result = _true;
	switch ( mSizeType )
	{
	case _GUI_SIZE_PERCENT:
		{
			if ( parentsize != 0.0f )
			{
				mUnionSize.mPercentSize = mLogicSize / parentsize;
			}
			else
			{
				WLOG_ERROR( L"Set GUIControl SizeType Error!" );
				result = _false;
			}
		}
		break;
	case _GUI_SIZE_LOCKONESIDE:
		{
			mUnionSize.mLockSize = parentsize - mLogicSize - mAnchorPosition;
		}
		break;
	case _GUI_SIZE_CONSTANT:
		{
			mUnionSize.mConstantSize = mLogicSize;
		}
		break;
	default:
		break;
	}
	return result;
}

_ubool GUILocationInfo::UpdateLogicSize( _float parentsize )
{
	_ubool result = _true;
	_float backup = mLogicSize;
	switch ( mSizeType )
	{
	case _GUI_SIZE_PERCENT:
		{
			mLogicSize = mUnionSize.mPercentSize * parentsize;
		}
		break;
	case _GUI_SIZE_LOCKONESIDE:
		{
			mLogicSize = parentsize - mAnchorPosition - mUnionSize.mLockSize;
		}
		break;
	case _GUI_SIZE_CONSTANT:
		{
			mLogicSize = mUnionSize.mConstantSize;
		}
		break;
	default:
		result = _false;
		break;
	}
	if ( backup == mLogicSize )
		result = _false;
	return result;
}

_ubool GUILocationInfo::UpdateAnchorPosition( _float parentsize )
{
	switch ( mAnchorType )
	{
	case _GUI_ANCHOR_L_OR_T:
		{
			if ( mSizeType == _GUI_SIZE_LOCKONESIDE )
				mAnchorPosition = mLogicPosition * 2.0f + mUnionSize.mLockSize;
			else
				mAnchorPosition = ( parentsize - mLogicSize ) * 0.5f + mLogicPosition;
		}
		break;
	case _GUI_ANCHOR_CENTER:
		{
			mAnchorPosition = mLogicPosition;
		}
		break;
	case _GUI_ANCHOR_R_OR_B:
		{
			if ( mSizeType == _GUI_SIZE_LOCKONESIDE )
				mAnchorPosition = mLogicPosition * 2.0f + mUnionSize.mLockSize;
			else
				mAnchorPosition = ( parentsize - mLogicSize ) * 0.5f - mLogicPosition;
		}
		break;
	}
	return _true;
}

_ubool GUILocationInfo::UpdateLogicPosition( _float parentsize )
{
	switch ( mAnchorType )
	{
	case _GUI_ANCHOR_L_OR_T:
		{
			mLogicPosition = ( mLogicSize - parentsize ) * 0.5f + mAnchorPosition;
		}
		break;
	case _GUI_ANCHOR_CENTER:
		{
			mLogicPosition = mAnchorPosition;
		}
		break;
	case _GUI_ANCHOR_R_OR_B:
		{
			mLogicPosition = ( parentsize - mLogicSize ) * 0.5f - mAnchorPosition;
		}
		break;
	}
	
	return _true;
}

_void GUILocationInfo::SetSizeType( _GUI_SIZE_TYPE sizetype, _float parentsize )
{
	if ( mSizeType == sizetype )
		return;

// 	if ( sizetype == _GUI_SIZE_LOCKONESIDE && mAnchorType == _GUI_ANCHOR_CENTER )
// 		return;

	mSizeType = sizetype;
	//UpdateUnionSize( parentsize );
	UpdateLogicSize( parentsize );
}

_void GUILocationInfo::SetAnchorType( _GUI_ANCHOR_TYPE anchortype, _float parentsize )
{
	if ( mAnchorType == anchortype )
		return;

// 	if ( mSizeType == _GUI_SIZE_LOCKONESIDE && anchortype == _GUI_ANCHOR_CENTER )
// 		return;

	mAnchorType = anchortype;
	//UpdateAnchorPosition( parentsize );
	UpdateLogicPosition( parentsize );

	if ( mSizeType == _GUI_SIZE_LOCKONESIDE && anchortype != _GUI_ANCHOR_CENTER )
		UpdateLogicSize( parentsize );
}

_ubool GUILocationInfo::SetLogicSize( _float logicsize, _float parentsize )
{
	mLogicSize = logicsize;
	UpdateUnionSize( parentsize );
	UpdateLogicPosition( parentsize );
	//handle event
	return _true;
}

_ubool GUILocationInfo::SetPercentSize( _float percentsize, _float parentsize )
{
	if ( mSizeType == _GUI_SIZE_PERCENT )
	{
		mUnionSize.mPercentSize = percentsize;
		UpdateLogicSize( parentsize );
		UpdateLogicPosition( parentsize );
		// handle event
		return _true;
	}
	return _false;
}

_ubool GUILocationInfo::SetLockSize( _float locksize, _float parentsize )
{
	if ( mSizeType == _GUI_SIZE_LOCKONESIDE )
	{
		mUnionSize.mLockSize = locksize;
		UpdateLogicSize( parentsize );
		UpdateLogicPosition( parentsize );
		// handle event
		return _true;
	}
	return _false;
}

_ubool GUILocationInfo::SetLogicPosition( _float position, _float parentsize )
{
	mLogicPosition = position;
	if ( mSizeType == _GUI_SIZE_LOCKONESIDE )
	{
		UpdateAnchorPosition( parentsize );
		UpdateLogicSize( parentsize );
		// handle event
		return _true;
	}
	else
	{
		UpdateAnchorPosition( parentsize );
		return _false;
	}
	return _false;
}

_ubool GUILocationInfo::SetAnchorPosition( _float position, _float parentsize )
{
	mAnchorPosition = position;
	if ( mSizeType == _GUI_SIZE_LOCKONESIDE )
	{
		UpdateLogicSize( parentsize );
		UpdateLogicPosition( parentsize );
		// handle event
		return _true;
	}
	else
	{
		UpdateLogicPosition( parentsize );
		return _false;
	}
	return _false;
}

_void GUILocationInfo::SetLogicScale( _float scale )
{
	mLogicScale = scale;
}

_GUI_SIZE_TYPE GUILocationInfo::GetSizeType( ) const
{
	return mSizeType;
}

_GUI_ANCHOR_TYPE GUILocationInfo::GetAnchorType( ) const
{
	return mAnchorType;
}

_float GUILocationInfo::GetLogicSize( ) const
{
	return mLogicSize;
}

_float GUILocationInfo::GetPercentSize( ) const
{
	return mUnionSize.mPercentSize;
}

_float GUILocationInfo::GetLockSize( ) const
{
	return mUnionSize.mLockSize;
}

_float GUILocationInfo::GetLogicPosition( ) const
{
	return mLogicPosition;
}

_float GUILocationInfo::GetAnchorPosition( ) const
{
	return mAnchorPosition;
}

_float GUILocationInfo::GetLogicScale( ) const
{
	return mLogicScale;
}

_dword OnQueryGUISizeEnumValue( WStringPtr name, const QwordParameters2& parameters )
{
	if ( name == L"constant" )
		return _GUI_SIZE_CONSTANT;
	else if ( name == L"percent" )
		return _GUI_SIZE_PERCENT;
	else if ( name == L"lock_one_side" )
		return _GUI_SIZE_LOCKONESIDE;

	return 0;
}

const _charw* OnQueryGUISizeEnumName( _dword value, const QwordParameters2& parameters )
{
	switch ( value )
	{
	case _GUI_SIZE_CONSTANT:
		return L"constant";
	case _GUI_SIZE_PERCENT:
		return L"percent";
	case _GUI_SIZE_LOCKONESIDE:
		return L"lock_one_side";
	}
	return L"";
}

_dword OnQueryGUIAnchorEnumValue( WStringPtr name, const QwordParameters2& parameters )
{
	if ( name == L"center" )
		return _GUI_ANCHOR_CENTER;
	else if ( name == L"l_or_t" )
		return _GUI_ANCHOR_L_OR_T;
	else if ( name == L"r_or_b" )
		return _GUI_ANCHOR_R_OR_B;

	return 0;
}

const _charw* OnQueryGUIAnchorEnumName( _dword value, const QwordParameters2& parameters )
{
	switch ( value )
	{
	case _GUI_ANCHOR_CENTER:
		return L"center";
	case _GUI_ANCHOR_L_OR_T:
		return L"l_or_t";
	case _GUI_ANCHOR_R_OR_B:
		return L"r_or_b";
	}
	return L"";
}


_ubool GUILocationInfo::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	_dword enumvalue = 0;
	if ( node->ReadEnum( L"sizetype", enumvalue, _false, OnQueryGUISizeEnumValue ) == _false )
		return _false;
	mSizeType = (_GUI_SIZE_TYPE)enumvalue;

	if ( node->ReadEnum( L"anchortype", enumvalue, _false, OnQueryGUIAnchorEnumValue ) == _false )
		return _false;
	mAnchorType = (_GUI_ANCHOR_TYPE)enumvalue;

	switch( mSizeType )
	{
	case _GUI_SIZE_CONSTANT:
		{
			if ( node->Read( L"size", mUnionSize.mConstantSize ) == _false )
				return _false;
			mLogicSize = mUnionSize.mConstantSize;
		}
		break;
	case _GUI_SIZE_LOCKONESIDE:
		{
			if ( node->Read( L"size", mUnionSize.mLockSize ) == _false )
				return _false;
		}
		break;
	case _GUI_SIZE_PERCENT:
		{
			if ( node->Read( L"size", mUnionSize.mPercentSize ) == _false )
				return _false;
		}
		break;
	}

	if ( node->Read( L"anchorpos", mAnchorPosition ) == _false )
		return _false;

	return _true;
}

_ubool GUILocationInfo::Export( ISerializableNode* node ) const
{
	if( node == _null )
		return _false;

	if ( node->WriteEnum( L"sizetype", mSizeType, _false, OnQueryGUISizeEnumName ) == _false )
		return _false;

	if ( node->WriteEnum( L"anchortype", mAnchorType, _false, OnQueryGUIAnchorEnumName ) == _false )
		return _false;

	switch( mSizeType )
	{
	case _GUI_SIZE_CONSTANT:
		{
			if ( node->Write( L"size", mLogicSize ) == _false )
				return _false;
		}
		break;
	case _GUI_SIZE_LOCKONESIDE:
		{
			if ( node->Write( L"size", mUnionSize.mLockSize ) == _false )
				return _false;
		}
		break;
	case _GUI_SIZE_PERCENT:
		{
			if ( node->Write( L"size", mUnionSize.mPercentSize ) == _false )
				return _false;
		}
		break;
	}

	if ( node->Write( L"anchorpos", mAnchorPosition ) == _false )
		return _false;

	return _true;
}