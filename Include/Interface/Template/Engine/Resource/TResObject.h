//! @file     TResObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TResObject
//----------------------------------------------------------------------------

template< typename Type >
class TResObject : public TObject< Type >
{
protected:
	//!	The resource name
	WStringObj	mResName;

protected:
	//!	When get node name.
	virtual WStringPtr OnGetNodeName( ) const PURE;

	//!	When export properties.
	virtual _ubool OnExportToNode( ISerializableNode* node ) const PURE;

protected:
	TResObject( );
	virtual ~TResObject( );

// IResNameObject Interface
public:
	virtual _void				SetResName( const WStringObj& name ) override;
	virtual const WStringObj&	GetResName( ) const override;

	virtual _ubool				AreAllResourcesLoaded( ) const override;
	virtual DwordRange			GetResourcesLoadedProgression( ) const override;

	virtual _ubool				ExportToFile( WStringPtr filename ) const override;
	virtual _ubool				ExportToFile( WStringPtr filename, WStringPtr root_name ) const override;
	virtual _ubool				ExportToXMLString( WString& xml_string ) const override;
	virtual _ubool				ExportToXMLString( WStringPtr root_name, WString& xml_string ) const override;
};

//----------------------------------------------------------------------------
// TResObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TResObject< Type >::TResObject( )
{
}

template< typename Type >
TResObject< Type >::~TResObject( )
{
}

template< typename Type >
_void TResObject< Type >::SetResName( const WStringObj& name )
{
	mResName = name;
}

template< typename Type >
const WStringObj& TResObject< Type >::GetResName( ) const
{
	return mResName;
}

template< typename Type >
_ubool TResObject< Type >::AreAllResourcesLoaded( ) const
{
	return GetResourcesLoadedProgression( ).IsFinish( );
}

template< typename Type >
DwordRange TResObject< Type >::GetResourcesLoadedProgression( ) const
{
	return DwordRange::cNull;
}

template< typename Type >
_ubool TResObject< Type >::ExportToFile( WStringPtr filename ) const
{
	return ExportToFile( filename, OnGetNodeName( ) );
}

template< typename Type >
_ubool TResObject< Type >::ExportToFile( WStringPtr filename, WStringPtr root_name ) const
{
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->CreateXMLFile( root_name );
	if ( xml_file.IsNull( ) )
		return _false;

	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file );
	if ( node.IsNull( ) )
		return _false;

	if ( node->SetNodeName( OnGetNodeName( ) ) == _false )
		return _false;

	if ( OnExportToNode( node ) == _false )
		return _false;

	if ( xml_file->SaveToFile( filename ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TResObject< Type >::ExportToXMLString( WString& xml_string ) const
{
	return ExportToXMLString( OnGetNodeName( ), xml_string );
}

template< typename Type >
_ubool TResObject< Type >::ExportToXMLString( WStringPtr root_name, WString& xml_string ) const
{
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->CreateXMLFile( root_name );
	if ( xml_file.IsNull( ) )
		return _false;

	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file );
	if ( node.IsNull( ) )
		return _false;

	if ( OnExportToNode( node ) == _false )
		return _false;

	xml_string = xml_file->GetRootElement( )->DumpToString( );

	return _true;
}

}