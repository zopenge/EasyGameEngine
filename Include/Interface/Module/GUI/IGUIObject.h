//! @file     IGUIObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIObject
//----------------------------------------------------------------------------

class IGUIObject : public IObjectTree< IResNameObject< IUserDataObject2< IShowableObject< IGUIComponentGroup > > >, IGUIObject >
{
public:
	//!	Check whether it's control.
	//!	@param		none.
	//!	@return		True indicates it's control.
	virtual _ubool IsControl( ) const PURE;
	//!	Check whether it's container.
	//!	@param		none.
	//!	@return		True indicates it's container.
	virtual _ubool IsContainer( ) const PURE;
	//!	Check whether it's application.
	//!	@param		none.
	//!	@return		True indicates it's application.
	virtual _ubool IsApplication( ) const PURE;

	//!	Get the level number.
	//!	@param		none.
	//!	@return		none.
	virtual _dword GetLevelNumber( ) const PURE;

	//!	Set layer number ( draw from low to high ).
	//!	@param		layer		The layer number.
	//!	@return		none.
	virtual _void SetLayerNumber( _long layer ) PURE;
	//!	Get layer number ( draw from low to high ).
	//!	@param		none.
	//!	@return		The layer number.
	virtual _long GetLayerNumber( ) const PURE;

	//!	Get the control path.
	//!	@param		none.
	//!	@return		The control path.
	virtual WString GetControlPath( ) const PURE;

	//!	Focus on/off.
	//!	@param		focus		True indicates focus on, otherwise indicates focus off.
	//!	@return		none.
	virtual _void Focus( _ubool focus ) PURE;

	//!	Get the extend states.
	//!	@param		none.
	//!	@return		The object extend states, @see _GUI_OBJECT_STATE_EX.
	virtual FlagsObject& GetStatesEx( ) PURE;
	//!	Get the extend states.
	//!	@param		none.
	//!	@return		The object extend states, @see _GUI_OBJECT_STATE_EX.
	virtual const FlagsObject& GetStatesEx( ) const PURE;

	//!	Get the attributes.
	//!	@param		none.
	//!	@return		The object attributes, @see _GUI_ATTRIBUTE.
	virtual FlagsObject& GetAttributes( ) PURE;
	//!	Get the attributes.
	//!	@param		none.
	//!	@return		The object attributes, @see _GUI_ATTRIBUTE.
	virtual const FlagsObject& GetAttributes( ) const PURE;

	//!	Set the component group.
	//!	@param		group_component		The component group.
	//!	@return		none.
	virtual _void SetComponentGroup( IGUIComponentGroup* group_component ) PURE;
	//!	Get the component group.
	//!	@param		none.
	//!	@return		The component group.
	virtual IGUIComponentGroup* GetComponentGroup( ) PURE;
	//!	Get the component group.
	//!	@param		none.
	//!	@return		The component group.
	virtual const IGUIComponentGroup* GetComponentGroup( ) const PURE;

	//!	Get the parent application.
	//!	@param		none.
	//!	@return		The GUI application interface.
	virtual IGUIApplication* GetParentApplication( ) PURE;
	virtual const IGUIApplication* GetParentApplication( ) const PURE;
	virtual _ubool FindParentObject( IGUIObject* parent ) const PURE;

	//!	Check whether the position is in the region of control and sub-controls or not.
	//! param		origin_position		The position.
	//!	@param		position			The position.	position may be modify by 3d gui object
	//!	@param		transform			The transform.
	//! @param		flags				The flags ( see _GUI_TESTPOINT_FLAGS ).
	//!	@param		relative_position	The relative position to feedback.
	//!	@return		The GUI object what test the position successful.
	virtual IGUIObject* TestPoint( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags, Vector2* relative_position ) PURE;
	//!	Check whether the position is in the region of control and sub-controls or not.
	//! param		origin_position		The position.
	//!	@param		position			The position.	position may be modify by 3d gui object
	//!	@param		transform			The transform.
	//! @param		flags				The flags ( see _GUI_TESTPOINT_FLAGS ).
	//!	@return		The GUI object what test the position successful.
	virtual IGUIObjectRefArray TestPointByReturnList( const Vector2& origin_position, const Vector2& position, const Matrix3& transform, const FlagsObject& flags ) PURE;
	//!	Check whether the region is hit the region of control and sub-controls or not.
	//!	@param		region		The region.
	//!	@param		transform	The transform.
	//! @param		flags		The flags ( see _GUI_TESTPOINT_FLAGS ).
	//!	@return		The GUI object what test the position successful.
	virtual IGUIObject* GetIntersectObject( const RectF& region, const Matrix3& transform, const FlagsObject& flags ) PURE;
	virtual _ubool Intersect( const RectF& clip_rect, const Matrix3& world_transform ) const PURE;
	virtual RectF GetIntersectRect( const RectF& clip_rect, const Matrix3& world_transform ) const PURE;
	virtual IGUIObjectRefArray GetIntersectObjects( IGUIContainer* container ) const PURE;
	virtual _ubool RelativePointInControl( const Vector2& position ) PURE;

	//! Get the position in screen.
	//!	@param		none.
	//!	@return		The screen position.
	virtual Vector2 GetScreenPosition( IObject* viewport, _float* zsort ) const PURE;
	//!	Get the self world transform.
	//!	@param		none.
	//!	@return		The world transform.
	virtual Matrix3 GetWorldTransform( ) const PURE;
	//!	Get the child world transform from self.
	//!	@param		none.
	//!	@return		The world transform.
	virtual Matrix3 GetChildWorldTransform( ) const PURE;
	//!	Get the self relative transform.
	//!	@param		none.
	//!	@return		The relative transform.
	virtual Matrix3 GetRelativeTransform( ) const PURE;
	//!	Get the child relative transform.
	//!	@param		none.
	//!	@return		The relative transform.
	virtual Matrix3 GetChildRelativeTransform( ) const PURE;

	//!	Get the world transforms from root to self.
	//!	@param		transforms	The world transforms.
	//!	@return		none.
	virtual _void GetWorldTransformsFromRoot( Matrix3Array& transforms ) const PURE;
	//!	Get the child world transforms from root to self.
	//!	@param		transforms	The world transforms.
	//!	@return		none.
	virtual _void GetChildWorldTransformsFromRoot( Matrix3Array& transforms ) const PURE;

	//! Get the mixed color.
	//! @param		color		The color to mix.
	//! @return		The mixed color.
	virtual Color MixColor( const Color& color ) const PURE;
	virtual _void ResetControlAnimationInfo( _ubool deep = _false ) PURE;

	virtual _ubool IsClickableObject( ) const PURE;
	virtual _void UpdateClickableState( ) PURE;
	virtual _ubool IsCaptureMoveObject( ) const PURE;

	virtual _void BeginTestPoint3DInUI( const Matrix3& world_transform ) PURE;
	virtual _void EndTestPoint3DInUI( ) PURE;
};

}