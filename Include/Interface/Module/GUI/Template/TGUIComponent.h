//! @file     TGUIComponent.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TGUIComponent
//----------------------------------------------------------------------------

template< typename Type >
class TGUIComponent : public TSerializable< TDynamicResObject< TObject< Type > > >
{
protected:
	//!	The state
	_GUI_OBJECT_STATE	mComponentObjState;

	//!	The GUI object
	IGUIObject*			mGUIObject;

	//!	The sort index
	_dword				mSortIndex;

	//!	True indicates it's sleep
	_ubool				mIsSleep;

protected:
	_void CopyFrom( const TGUIComponent* src_object );

protected:
	//!	Check whether need to skip the sort index attribute.
	virtual _ubool OnIsNeedExportSortIndex() const { return _true; }

protected:
	TGUIComponent( IGUIObject* gui_object );
	virtual ~TGUIComponent( );

// ISerializable Interface
public:
	virtual _ubool				Import( ISerializableNode* node ) override;
	virtual _ubool				Export( ISerializableNode* node ) const override;

// IGUIComponent Interface
public:
	virtual IGUIObject*			GetGUIObject( ) const override;

	virtual _void				SetSleep( _ubool sleep ) override;
	virtual _ubool				IsSleep( ) const override;

	virtual _GUI_OBJECT_STATE	GetComponentObjStateID( ) const override;
	virtual _void				SetComponentObjStateID( _GUI_OBJECT_STATE state ) override;

	virtual _void				SetComponentSortIndex( _dword index ) override;
	virtual _dword				GetComponentSortIndex( ) const override;

	virtual WStringPtr			GetComponentObjStateName( ) const override;

	virtual _ubool				ImportEvent( ISerializableNode* node, WStringPtr event_name ) override;
	virtual _ubool				ImportEventFromXMLString( WStringPtr xml_string, WStringPtr event_name, _ubool locate_at_first_child = _true ) override;
	virtual _ubool				ExportEvent( ISerializableNode* node, WStringPtr event_name ) const override;
	virtual _ubool				ExportEventToXMLString( WStringPtr root_name, WStringPtr tag_name, WStringPtr event_name, WString& xml_string ) override;

	virtual _ubool				IsResident( ) const override;
	virtual _ubool				IsSupportKeys( ) const override;

	virtual _ubool				DoTick( ) const override;
	virtual _ubool				DoRender( ) const override;
	virtual _ubool				DoAfterChildRender() const override;
	virtual _ubool				DoHandleEvent( ) const override;
	virtual _ubool				DoIsHandleEvent( ) const override;
	virtual _ubool				DoTestRegion( ) const override;
	virtual _ubool				DoExport( ) const override;

	virtual _ubool				IsHandleEvent( _dword event_id ) const override;

	virtual _ubool				HandleEvent( const EventBase& event, const FlagsObject& flags ) override;
	virtual _void				Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;
	virtual _void				RenderAfterChild( IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test ) override;
	virtual _void				RenderAfterRootApplication( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect ) override;

	virtual _GUI_TESTPOINT_RESULT_TYPE	PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position ) override;
	virtual _ubool				RegionInControl( const RectF& region, const Matrix3& transform ) override;
};

//----------------------------------------------------------------------------
// TGUIComponent Implementation
//----------------------------------------------------------------------------

template< typename Type >
TGUIComponent< Type >::TGUIComponent( IGUIObject* gui_object )
{
	mComponentObjState	= _GUI_STATE_NORMAL;

	mGUIObject			= gui_object;

	mSortIndex			= 0;

	mIsSleep			= _false;
}

template< typename Type >
TGUIComponent< Type >::~TGUIComponent( )
{
}

template< typename Type >
_void TGUIComponent< Type >::CopyFrom( const TGUIComponent* src_object )
{
	EGE_ASSERT( src_object != _null );

	SetSleep( src_object->IsSleep( ) );

	this->mComponentObjState	= src_object->mComponentObjState;
	this->mSortIndex			= src_object->mSortIndex;
}

template< typename Type >
_ubool TGUIComponent< Type >::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	node->Read( L"sort_index", mSortIndex );

	node->ReadEnum( L"gui_state", (_dword&)mComponentObjState, _false, OnQueryGUIStateEnumValue );

	return _true;
}

template< typename Type >
_ubool TGUIComponent< Type >::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	if ( OnIsNeedExportSortIndex( ) )
		node->Write( L"sort_index", mSortIndex );

	node->WriteEnum( L"gui_state", mComponentObjState, _false, OnQueryGUIStateEnumName );

	return _true;
}

template< typename Type >
IGUIObject* TGUIComponent< Type >::GetGUIObject( ) const
{
	return mGUIObject;
}

template< typename Type >
_void TGUIComponent< Type >::SetSleep( _ubool sleep )
{
	mIsSleep = sleep;
}

template< typename Type >
_ubool TGUIComponent< Type >::IsSleep( ) const
{
	return mIsSleep;
}

template< typename Type >
_GUI_OBJECT_STATE TGUIComponent< Type >::GetComponentObjStateID( ) const
{
	return mComponentObjState;
}

template< typename Type >
_void TGUIComponent< Type >::SetComponentObjStateID( _GUI_OBJECT_STATE state )
{
	mComponentObjState = state;
}

template< typename Type >
WStringPtr TGUIComponent< Type >::GetComponentObjStateName( ) const
{
	return OnQueryGUIStateEnumName( mComponentObjState, QwordParameters2::cNull );
}

template< typename Type >
_ubool TGUIComponent< Type >::ImportEvent( ISerializableNode* node, WStringPtr event_name )
{
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::ImportEventFromXMLString( WStringPtr xml_string, WStringPtr event_name, _ubool locate_at_first_child )
{
	UString string_utf8;
	string_utf8.FromString( xml_string );

	IStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( (const _byte*) string_utf8.Str( ), string_utf8.GetLength( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( stream_reader.IsNull( ) )
		return _false;

	ISerializableNodeRef res_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader, locate_at_first_child );
	if ( res_node.IsNull( ) )
		return _false;

	if ( this->ImportEvent( res_node, event_name ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TGUIComponent< Type >::ExportEvent( ISerializableNode* node, WStringPtr event_name ) const
{
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::ExportEventToXMLString( WStringPtr root_name, WStringPtr tag_name, WStringPtr event_name, WString& xml_string )
{
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->CreateXMLFile( root_name );
	if ( xml_file.IsNull( ) )
		return _false;

	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file );
	if ( node.IsNull( ) )
		return _false;

	if ( tag_name.IsEmpty( ) == _false )
	{
		node = node->InsertChildNode( tag_name, L"", _false );
		if ( node.IsNull( ) )
			return _false;
	}

	if ( this->ExportEvent( node, event_name ) == _false )
		return _false;

	xml_string = xml_file->GetRootElement( )->DumpToString( );

	return _true;
}

template< typename Type >
_void TGUIComponent< Type >::SetComponentSortIndex( _dword index )
{
	mSortIndex = index;
}

template< typename Type >
_dword TGUIComponent< Type >::GetComponentSortIndex( ) const
{
	return mSortIndex;
}

template< typename Type >
_ubool TGUIComponent< Type >::IsResident( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::IsSupportKeys( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoTick( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoRender( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoAfterChildRender() const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoHandleEvent( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoIsHandleEvent( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoTestRegion( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::DoExport( ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::IsHandleEvent( _dword event_id ) const
{
	return _false;
}

template< typename Type >
_ubool TGUIComponent< Type >::HandleEvent( const EventBase& event, const FlagsObject& flags )
{
	return _false;
}

template< typename Type >
_void TGUIComponent< Type >::Render( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test )
{
}

template< typename Type >
_void TGUIComponent< Type >::RenderAfterChild( IObject* viewport, const Matrix3& transform, Color color, const RectF& clip_rect, _ubool in_clip_state, _ubool skip_region_test )
{
	EGE_ASSERT(0);
}

template< typename Type >
_void TGUIComponent< Type >::RenderAfterRootApplication( IObject* viewport, const Matrix3& transform, const Color& color, const RectF& clip_rect )
{
}

template< typename Type >
_GUI_TESTPOINT_RESULT_TYPE TGUIComponent< Type >::PointInControl( const Vector2& position, const Matrix3& transform, Vector2* relative_position )
{
	return _GTRT_IN;
}

template< typename Type >
_ubool TGUIComponent< Type >::RegionInControl( const RectF& region, const Matrix3& transform )
{
	return _true;
}

}