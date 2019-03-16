//! @file     Serializer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Serializer
//----------------------------------------------------------------------------

class Serializer : public INTERFACE_OBJECT_IMPL( ISerializer )
{
private:
	template< typename Type >
	_ubool TImport( ISerializableNode* node, WStringPtr name, Type& value ) const
	{
		if ( node == _null )
			return _false;

		return node->Read( name, value );
	}

	template< typename Type >
	_ubool TExport( ISerializableNode* node, WStringPtr name, const Type& value ) const
	{
		if ( node == _null )
			return _false;

		return node->Write( name, value );
	}

public:
	Serializer( );
	virtual ~Serializer( );

// ISerializer Interface
public:
	virtual _ubool HasProperty( ISerializableNode* node, WStringPtr name ) const override;

	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _byte& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _word& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _long& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _dword& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _float& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, _double& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, WString& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, Time& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, MD5Code& value ) const override;
	virtual _ubool Read( ISerializableNode* node, WStringPtr name, WStringObjRef& string ) override;
	virtual _ubool Read( ISerializableNode* node, WString& text ) const override;
	virtual _ubool Read( ISerializableNode* node, Vector3& vector ) const override;
	virtual _ubool Read( ISerializableNode* node, Color& color ) const override;
	virtual _ubool ReadFlag( ISerializableNode* node, WStringPtr name, FlagsObject& flags, _dword flag ) const override;
	virtual _ubool ReadEnum( ISerializableNode* node, WStringPtr name, _dword& value, OnQueryEnumValue funcpointer, const VoidParameters2& parameters = VoidParameters2::cNull ) const override;

	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _long value ) const override;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _dword value ) const override;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _float value ) const override;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, _double value ) const override;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, WStringPtr value ) const override;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, const Time& value ) const override;
	virtual _ubool Write( ISerializableNode* node, WStringPtr name, const MD5Code& value ) const override;
};

}