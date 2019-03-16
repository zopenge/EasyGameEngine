//! @file     ICommandLineParser.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ICommandLineParser
//----------------------------------------------------------------------------

class ICommandLineParser : public IObject
{
public:
	//! The argument data
	struct ArgData : public FlagsObject
	{
		enum _FLAG
		{
			_FLAG_OPTIONAL	= 1 << 0, //! Indicates it's optional, and use '/name' argument style
		};

		//!	The configure key name
		WString	mKeyName;
		//!	The configure value
		WString	mValue;

		//!	Check whether it's optional argument or not.
		_ubool IsOptional( ) const
		{
			return HasFlags( _FLAG_OPTIONAL );
		}
		//!	Check whether it's string argument only.
		_ubool IsString( ) const
		{
			if ( GetFlags( ) != 0 )
				return _false;

			if ( mKeyName.IsEmpty( ) == _false )
				return _false;

			if ( mValue.IsEmpty( ) )
				return _false;

			return _true;
		}

		//!	Get the boolean value.
		_ubool GetBool( ) const
		{
			if ( mValue.IsEqual( L"true", _true ) )
				return _true;
			else
				return _false;
		}
		//!	Get the value.
		_int GetValue( _dword radix ) const
		{
			return mValue.ToLong( radix );
		}
		//!	Get the region.
		RectI GetRegionI( ) const
		{
			RectI region = RectI::cNull;
			StringFormatter::ParseString( mValue.Str( ), L"%d,%d,%d,%d", region.l, region.t, region.r, region.b );

			return region;
		}
		//!	Get the region.
		RectF GetRegionF( ) const
		{
			RectF region = RectF::cNull;
			StringFormatter::ParseString( mValue.Str( ), L"%f,%f,%f,%f", region.l, region.t, region.r, region.b );

			return region;
		}
		//!	Get the point.
		PointI GetPointI( ) const
		{
			PointI pos = PointI::cZeroPoint;
			StringFormatter::ParseString( mValue.Str( ), L"%d,%d", pos.x, pos.y );

			return pos;
		}
		//!	Get the point.
		PointF GetPointF( ) const
		{
			PointF pos = PointF::cZeroPoint;
			StringFormatter::ParseString( mValue.Str( ), L"%f,%f", pos.x, pos.y );

			return pos;
		}

		//!	Get the value from variable name if the key name matched.
		_int GetValueByKeyName( WStringPtr name, _ubool ignorecase, _dword radix = 10 ) const
		{
			if ( mKeyName.IsEqual( name, ignorecase ) )
				return mValue.ToLong( radix );
            
            return 0;
		}
		//!	Get the integer value from variable name if the key name matched in bounds.
		_int GetValueByKeyName( WStringPtr name, _ubool ignorecase, _int min, _int max, _dword radix = 10 ) const
		{
			if ( mKeyName.IsEqual( name, ignorecase ) )
				return Math::Clamp< _int >( mValue.ToLong( radix ), min, max );

            return 0;
        }
	};

public:
	//!	Initialize.
	//!	@param		cmdline		The command line string.
	//!	@return		none.
	virtual _void Initialize( AStringPtr cmdline ) PURE;
	//!	Initialize.
	//!	@param		cmdline		The command line string.
	//!	@return		none.
	virtual _void Initialize( WStringPtr cmdline ) PURE;
	//!	Initialize.
	//!	@param		argc		The argument number.
	//!	@param		argv		The arguments.
	//!	@return		none.
	virtual _void Initialize( _dword argc, const _chara* argv[] ) PURE;
	//!	Initialize.
	//!	@param		argc		The argument number.
	//!	@param		argv		The arguments.
	//!	@return		none.
	virtual _void Initialize( _dword argc, const _charw* argv[] ) PURE;
	//!	Initialize..
	//!	@param		argc		The argument number.
	//!	@param		argn		The argument names.
	//!	@param		argv		The argument values.
	//!	@return		none.
	virtual _void Initialize( _dword argc, const _chara* argn[], const _chara* argv[] ) PURE;
	//!	Initialize..
	//!	@param		argc		The argument number.
	//!	@param		argn		The argument names.
	//!	@param		argv		The argument values.
	//!	@return		none.
	virtual _void Initialize( _dword argc, const _charw* argn[], const _charw* argv[] ) PURE;

	//!	Get the command line string.
	//!	@param		startindex	The start argument index.
	//!	@return		The command line string.
	virtual WStringR GetString( _dword startindex = 0 ) const PURE;

	//!	Check the argument is existing or not.
	//!	@param		name		The optional argument name.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@return		True indicates the optional argument is existing.
	virtual _ubool HasArgument( WStringPtr name, _ubool ignorecase = _true ) const PURE;

	//!	Get the arguments number.
	//!	@param		none.
	//!	@return		The arguments number.
	virtual _dword GetArgumentsNumber( ) const PURE;
	//!	Get the argument by index.
	//!	@param		index		The argument index.
	//! @return		The argument data, null indicates the index is invalid.
	virtual const ArgData* GetArgumentByIndex( _dword index ) const PURE;
	//!	Get the argument by key name.
	//!	@param		keyname		The key name.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		The argument data, null indicates the index is invalid.
	virtual const ArgData* GetArgumentByKeyName( WStringPtr keyname, _ubool ignorecase = _true ) const PURE;
	//!	Get the argument value by key name.
	//!	@param		keyname		The key name.
	//! @param		radix		The base of value, which must be in the range 2¨C36.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		The argument value.
	virtual _int GetArgumentValueByKeyName( WStringPtr keyname, _dword radix, _ubool ignorecase = _true ) const PURE;
	//!	Get the argument string by key name.
	//!	@param		keyname		The key name.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		The argument string.
	virtual WStringR GetArgumentStringByKeyName( WStringPtr keyname, _ubool ignorecase = _true ) const PURE;

	//!	Begin to get arguments.
	//!	@param		startindex	The start argument index.
	//! @return		True indicates success false indicates failure.
	virtual _ubool BeginGettingArguments( _dword startindex ) PURE;
	//!	Get the current argument.
	//!	@remark		We will jump to the next argument by itself.
	//!	@param		none.
	//!	@return		The argument data, null indicates we finished to get all arguments.
	virtual const ArgData* GetArgument( ) PURE;
	//!	End	to get arguments.
	//!	@param		none.
	//! @return		none.
	virtual _void EndGettingArguments( ) PURE;

	virtual _ubool Read( WStringPtr name, _byte& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _word& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _int& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _dword& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _qword& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _ubool& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _float& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _double& value ) const PURE;
	virtual _ubool Read( WStringPtr name, _time_t& value ) const PURE;
	virtual _ubool Read( WStringPtr name, AString& value ) const PURE;
	virtual _ubool Read( WStringPtr name, UString& value ) const PURE;
	virtual _ubool Read( WStringPtr name, WString& value ) const PURE;
	virtual _ubool Read( WStringPtr name, AStringObj& value ) const PURE;
	virtual _ubool Read( WStringPtr name, UStringObj& value ) const PURE;
	virtual _ubool Read( WStringPtr name, WStringObj& value ) const PURE;
	virtual _ubool Read( WStringPtr name, Time& value ) const PURE;
	virtual _ubool Read( WStringPtr name, MD5Code& value ) const PURE;
	virtual _ubool Read( WStringPtr name, Version& value ) const PURE;
	virtual _ubool Read( WStringPtr name, Color& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeInt& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeDword& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeFloat& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeBool& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeDouble& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeLarge& value ) const PURE;
	virtual _ubool Read( WStringPtr name, SafeQword& value ) const PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, Vector2& vector ) const PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, Vector3& vector ) const PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Vector4& vec4 ) const PURE;
	virtual _ubool Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Quaternion& quaternion ) const PURE;
	virtual _ubool Read( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, Transform2D& transform ) const PURE;
	virtual _ubool Read( WStringPtr min_name, WStringPtr max_name, DwordRange& bounds ) const PURE;
	virtual _ubool Read( WStringPtr min_name, WStringPtr max_name, FloatRange& bounds ) const PURE;
	virtual _ubool Read( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, Color& color ) const PURE;
};

}