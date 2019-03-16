//! @file     IScriptFunction.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptFunction
//----------------------------------------------------------------------------

class IScriptFunction : public IObject
{
public:
	//!	Get the name.
	//!	@param		none.
	//!	@return		The name.
	virtual AStringPtr GetName( ) const PURE;

	//!	Invoke in block mode.
	//!	@param		none.
	//! @return		The return variable.
	virtual IScriptValuePassRef Invoke( ) PURE;
	//!	Invoke with parameters in block mode.
	//!	@param		vars	The parameters.
	//! @return		The return variable.
	virtual IScriptValuePassRef InvokeByVars( const VariableArray& vars ) PURE;

public:
	//!	Easy to invoke with parameters.
	IScriptValuePassRef Call( )
	{
		return Invoke( );
	}

	template< typename T1 >
	IScriptValuePassRef Call( const T1& p1 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2, typename T3 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2, const T3& p3 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );
		Variable v3; v3 = p3; vars.Append( v3 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2, typename T3, typename T4 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2, const T3& p3, const T4& p4 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );
		Variable v3; v3 = p3; vars.Append( v3 );
		Variable v4; v4 = p4; vars.Append( v4 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );
		Variable v3; v3 = p3; vars.Append( v3 );
		Variable v4; v4 = p4; vars.Append( v4 );
		Variable v5; v5 = p5; vars.Append( v5 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );
		Variable v3; v3 = p3; vars.Append( v3 );
		Variable v4; v4 = p4; vars.Append( v4 );
		Variable v5; v5 = p5; vars.Append( v5 );
		Variable v6; v6 = p6; vars.Append( v6 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );
		Variable v3; v3 = p3; vars.Append( v3 );
		Variable v4; v4 = p4; vars.Append( v4 );
		Variable v5; v5 = p5; vars.Append( v5 );
		Variable v6; v6 = p6; vars.Append( v6 );
		Variable v7; v7 = p7; vars.Append( v7 );

		return InvokeByVars( vars );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
	IScriptValuePassRef Call( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8 )
	{
		VariableArray vars;
		Variable v1; v1 = p1; vars.Append( v1 );
		Variable v2; v2 = p2; vars.Append( v2 );
		Variable v3; v3 = p3; vars.Append( v3 );
		Variable v4; v4 = p4; vars.Append( v4 );
		Variable v5; v5 = p5; vars.Append( v5 );
		Variable v6; v6 = p6; vars.Append( v6 );
		Variable v7; v7 = p7; vars.Append( v7 );
		Variable v8; v8 = p8; vars.Append( v8 );

		return InvokeByVars( vars );
	}

public:
	//!	Easy to invoke by return boolean.
	_ubool CallZ( )
	{
		IScriptValueRef ret = Call( );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1 >
	_ubool CallZ( const T1& p1 )
	{
		IScriptValueRef ret = Call( p1 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2 >
	_ubool CallZ( const T1& p1, const T2& p2 )
	{
		IScriptValueRef ret = Call( p1, p2 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2, typename T3 >
	_ubool CallZ( const T1& p1, const T2& p2, const T3& p3 )
	{
		IScriptValueRef ret = Call( p1, p2, p3 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2, typename T3, typename T4 >
	_ubool CallZ( const T1& p1, const T2& p2, const T3& p3, const T4& p4 )
	{
		IScriptValueRef ret = Call( p1, p2, p3, p4 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
	_ubool CallZ( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5 )
	{
		IScriptValueRef ret = Call( p1, p2, p3, p4, p5 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
	_ubool CallZ( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6 )
	{
		IScriptValueRef ret = Call( p1, p2, p3, p4, p5, p6 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
	_ubool CallZ( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7 )
	{
		IScriptValueRef ret = Call( p1, p2, p3, p4, p5, p6, p7 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
	_ubool CallZ( const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5, const T6& p6, const T7& p7, const T8& p8 )
	{
		IScriptValueRef ret = Call( p1, p2, p3, p4, p5, p6, p7, p8 );
		if ( ret.IsNull( ) )
			return _false;

		return ret->GetBool( );
	}
};

}