//! @file     GUIGlobals.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The GUI enumerations
//----------------------------------------------------------------------------

//!	The GUI object state.
enum _GUI_OBJECT_STATE
{
	_GUI_STATE_UNKNOWN			= -1,
	_GUI_STATE_NORMAL			= 0x00000000, //! Normal/Default state (Default as base attribute)
	_GUI_STATE_FOCUS			= 0x00000001, //! Focus state (Default as base attribute)
	_GUI_STATE_HOVER			= 0x00000002, //! Hover state (Default as base attribute)
	_GUI_STATE_DISABLE			= 0x00000003, //! Disable state (Default as base attribute)
	_GUI_STATE_CHECKED			= 0x00000004, //! Checked state (Default as base attribute)
	_GUI_STATE_CHECKED_FOCUS	= 0x00000405, //! Checked-Focus state (Checked->Default as base attribute) 
	_GUI_STATE_CHECKED_HOVER	= 0x00000406, //! Checked-Hover state (Checked->Default as base attribute) 
	_GUI_STATE_CHECKED_DISABLE	= 0x00000307, //! Checked-Disable state (Disable->Default as base attribute) 

	_GUI_STATE_MAXNUMBER		= 8,
};

//!	The GUI object extend state.
enum _GUI_OBJECT_STATE_EX
{
	_GUI_STATE_EX_SHOW			= 1 << 0, //! It's visible.
	_GUI_STATE_EX_DROPPING		= 1 << 1, //! It's dropping.
	_GUI_STATE_EX_DELAY_RENDER	= 1 << 2, //! It's delay render control
	_GUI_STATE_EX_MODAL			= 1 << 3, //! It's modal control
	_GUI_STATE_EX_PAUSING		= 1 << 4, //! GUI object do not tick
	_GUI_STATE_EX_DELAY_LOAD	= 1 << 5, //! GUI delay load
	_GUI_STATE_EX_TEMP_MODAL	= 1 << 6,
};

//!	The GUI object attributes
enum _GUI_ATTRIBUTE
{
	_GUI_ATTRIBUTE_DROPPABLE			= 1 << 0, //! The control can be dropped.
	_GUI_ATTRIBUTE_CAPTURABLE			= 1 << 1, //! The control can capture the input event, even though the out of its region.
	_GUI_ATTRIBUTE_CLIPCHILD			= 1 << 2, //! The control can clip child.
	_GUI_ATTRIBUTE_DONT_CLIPSELF		= 1 << 3, //! The control can not clip self.
	_GUI_ATTRIBUTE_CHECKABLE			= 1 << 4, //! The control can be checked.
	_GUI_ATTRIBUTE_RADIO				= 1 << 5, //! The control is radio
	_GUI_ATTRIBUTE_EDITBOX				= 1 << 6, //! The control is edit box
	_GUI_ATTRIBUTE_CANCEL				= 1 << 7, //! The control is cancel button
	_GUI_ATTRIBUTE_DEFAULT				= 1 << 8, //! The control is default control
	_GUI_ATTRIBUTE_UI3D					= 1 << 9,
	_GUI_ATTRIBUTE_SCENE3D				= 1 << 10,
	_GUI_ATTRIBUTE_TEST_POINT_ALWAYS	= 1 << 11,
	_GUI_ATTRIBUTE_MANUAL_CHECK			= 1 << 12,
};

//!	The GUI message deliver type
enum _GUI_MESSAGE_DELIVER_TYPE
{
	_GUI_MESSAGE_DELIVER_PARENT	= 1 << 0, //! Send the message to parent.
	_GUI_MESSAGE_DELIVER_CHILD	= 1 << 1, //! Send the message to child.
	_GUI_MESSAGE_SKIP_HOOKER	= 1 << 2, //! Skip to invoke GUI hooker.
};

//! The GUI object size type
enum _GUI_SIZE_TYPE
{
	_GUI_SIZE_CONSTANT,		//!	Constant value
	_GUI_SIZE_PERCENT,		//!	Percentage size by parent control
	_GUI_SIZE_LOCKONESIDE,	//! The distance to parent's side, only works with anchor left/top and right/bottom flags.
};

//! The GUI anchor type
enum _GUI_ANCHOR_TYPE
{
	_GUI_ANCHOR_CENTER,		//!	Anchor to other control's center position
	_GUI_ANCHOR_L_OR_T,		//!	Anchor to other control's left or top position
	_GUI_ANCHOR_R_OR_B,		//!	TODO::: Let the anchor can arrange to left or right ( proprity bigger than size type )
};

//! The GUI layout direction
enum _GUI_LAYOUT_DIRECTION
{
	_GUI_LAYOUT_HORZ,	//!	Horz layout style.
	_GUI_LAYOUT_VERT,	//!	Vert layout style.
};

//! The GUIObject TestPoint Flags
enum _GUI_TESTPOINT_FLAGS
{
	_GUI_TESTPOINT_CLICKABLE	= 1 << 0, //! The GUI default click action, if it set then will ignore all unclickable controls.
	_GUI_TESTPOINT_TEST_ALWAYS	= 1 << 1, //! If it set then always test control by its region even though the parent's control is missing.
	_GUI_TESTPOINT_CHECK_ALPHA	= 1 << 2, //! If it set then always test alpha of graphic component.
};

//!	The GUI interpolator type
enum _GUI_INTERPOLATOR_TYPE
{
	_GUI_INTERPOLATOR_OFFSET_X,
	_GUI_INTERPOLATOR_OFFSET_Y,
	_GUI_INTERPOLATOR_OFFSET_Z,
	_GUI_INTERPOLATOR_SCALE_X,
	_GUI_INTERPOLATOR_SCALE_Y,
	_GUI_INTERPOLATOR_RADIAN,
	_GUI_INTERPOLATOR_COLOR,
	_GUI_INTERPOLATOR_3DROTATION,

	_GUI_INTERPOLATOR_MAXNUMBER,
};

//! The GUI progress bar direction
enum _GUI_PROGRESSBAR_DIRECTION
{
	_GUI_PROGRESSBAR_RIGHT,
	_GUI_PROGRESSBAR_LEFT,
	_GUI_PROGRESSBAR_TOP,
	_GUI_PROGRESSBAR_BOTTOM,
	_GUI_PROGRESSBAR_CLOCKWISE,
	_GUI_PROGRESSBAR_ANTICLOCKWISE,
};

//!	The GUI process command type
enum _GUI_PROCESS_CMD_TYPE
{
	_GUI_PROCESS_CMD_UNKNOWN,
	//!	Play skeleton animation on GUI object
	_GUI_PROCESS_CMD_PLAY_SKELETON_ANI,

	//!	The custom command type must start from here
	_GUI_PROCESS_CMD_CUSTOM_BEGIN,
};

enum _GUI_ANIMATION_MASK
{
	_GUI_ANIMATION_NONE			= 0,
	_GUI_ANIMATION_OFFSET		= 1 << 0,
	_GUI_ANIMATION_SCALE		= 1 << 1,
	_GUI_ANIMATION_ROTATION		= 1 << 2,
	_GUI_ANIMATION_COLOR		= 1 << 3,
	_GUI_ANIMATION_3D			= 1 << 4,
	_GUI_ANIMATION_ALL			= 0xFFFFFFFF,
};

enum _GUI_RENDER_IN_SCENE_TYPE
{
	_GRIST_OVERLAY,
	_GRIST_SCREEN_BILLBOARD,
	_GRIST_VIEWPORT_BILLBOARD,
	_GRIST_AXIAL_BILLBOARD,
	_GRIST_RECTANGLE,
};

enum _GUI_TESTPOINT_RESULT_TYPE
{
	_GTRT_OUT = 0,
	_GTRT_IN,
	_GTRT_IN_AND_CAPTURE,
};

//----------------------------------------------------------------------------
// The GUI structures
//----------------------------------------------------------------------------

//!	The GUI animation key frame info.
struct GUIAniKeyFrameInfo
{
	Transform2D			mTransform;
	Color				mColor;
	_float				mRotationX;
	_float				mRotationY;
	_float				mPositionZ;
	FlagsObject			mAnimationMask;

	IInterpolatorRef	mInterpolators[ _GUI_INTERPOLATOR_MAXNUMBER ];

	GUIAniKeyFrameInfo( )
	{
		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mColor		= Color::cNull;
		mTransform	= Transform2D::cZero;
		mPositionZ = 0.0f;
		mAnimationMask.CombineFlags( _GUI_ANIMATION_ALL );
	}

	GUIAniKeyFrameInfo( IGUIObject* gui_object );
};


//! The GUI slider animation key frame info
struct GUISliderAniKeyFrameInfo
{
public:
	IInterpolatorRef	mInterpolator;
	Vector2				mOffset;
	GUISliderAniKeyFrameInfo( )
		: mOffset( Vector2::cOrigin )
	{

	}
};

struct GUIRender3DInSceneInfo
{
public:
	Matrix4				mRenderTransform;
	Matrix4				mFinalTransform;
	_float				mZSort;
	_dword				mRenderType;
	Transform3D			mLocalTransform;
	Vector2				mSize;
	Vector3				mAxis;
	GUIRender3DInSceneInfo( )
		: mRenderTransform( Matrix4::cIdentity )
		, mFinalTransform( Matrix4::cIdentity )
		, mZSort( 0.0f )
		, mRenderType( _GRIST_OVERLAY )
		, mLocalTransform( Transform3D::cZero )
		, mSize( Vector2::cIdentity )
		, mAxis( Vector3::cZAxis )
	{

	}
};

struct GUI3DInUIInfo
{
public:
	Matrix4				mTransformMatrix;
	Matrix4				mRotationMatrix;
	Matrix3				mRenderMatrix;
	Vector3				mCenterPosition;
public:
	GUI3DInUIInfo( )
		: mTransformMatrix( Matrix4::cIdentity )
		, mRotationMatrix( Matrix4::cIdentity )
		, mRenderMatrix( Matrix3::cIdentity )
		, mCenterPosition( Vector3::cOrigin )
	{

	}
};


//----------------------------------------------------------------------------
// GUIEvent Hooker
//----------------------------------------------------------------------------

//!	The GUIEvent hooker interface
class IGUIEventHooker
{
public:
	virtual ~IGUIEventHooker( ) { }

public:
	//!	Release.
	virtual _void Release( ) { delete this; }
	//!	Invoke the GUI event.
	virtual _ubool Invoke( IGUIObject* object, const EventBase& event, const QwordParameters2& parameters ) const PURE;
	//! Clone to.
	virtual IGUIEventHooker* CloneTo( ) PURE;
};

//!	The delegate to handle/invoke GUI event.
class IGUIEventDelegate : public IObject
{
public:
	//!	Invoke GUI event.
	virtual _ubool Invoke( IGUIObject* object, const EventBase& event, const QwordParameters2& parameters ) PURE;
};

//!	The GUIEvent hooker base
template< typename Type, typename GUIEventType >
class GUIEventHookerBase : public IGUIEventHooker
{
public:
	//! The event hooker function declaration.
	//!	@param		object		The GUI object.
	//!	@param		event		The GUI event.
	//!	@param		parameters	The user defined parameters.
	//!	@return		True indicates skip to pass event to other controls.
	typedef _ubool (Type::*HookerFunc)( IGUIObject* object, const GUIEventType& event, const QwordParameters2& parameters );

private:
	//!	The hooker function pointer
	HookerFunc	mHookerFunc;
	//!	The GUI application delegate to receive the event notify
	Type*		mEventDelegate;

public:
	GUIEventHookerBase( HookerFunc func, Type* delegate ) 
		: mHookerFunc( func ), mEventDelegate( delegate ) { }

// IGUIEventHooker Interface
public:
	virtual _ubool Invoke( IGUIObject* object, const EventBase& event, const QwordParameters2& parameters ) const
	{
		EGE_ASSERT( mEventDelegate != _null && mHookerFunc != _null );
		return (mEventDelegate->*mHookerFunc)( object, (const GUIEventType&) event, parameters );
	}

	virtual IGUIEventHooker* CloneTo( )
	{
		return new GUIEventHookerBase( mHookerFunc, mEventDelegate );
	}
};

//! GUI event hooker
class GUIEventHooker
{
private:
	//!	The GUI event hooker
	IGUIEventHooker*	mEventHooker;

public:
	GUIEventHooker( ) : mEventHooker( _null )
	{
	}

	template< typename Type, typename GUIEventType >
	GUIEventHooker( _ubool (Type::*function)(IGUIObject*, const GUIEventType&, const QwordParameters2&), Type* delegate )
		: mEventHooker( new GUIEventHookerBase<Type, GUIEventType>(function, delegate) )
	{
	}

	~GUIEventHooker( )
	{
		// Here we won't let the destructor to release event hooker, in order to prevent the copy operation BUG with it ( delete duplicate )
	}

public:
	//!	Clear the GUI event hooker.
	_void Clear( )
	{
		EGE_RELEASE( mEventHooker );
	}

	//!	Invoke the hooker function.
	_ubool Invoke( IGUIObject* object, const EventBase& event, const QwordParameters2& parameters ) const
	{
		if ( mEventHooker != _null )
			return mEventHooker->Invoke( object, event, parameters );

		return _false;
	}

	GUIEventHooker CloneTo( ) const
	{
		GUIEventHooker event_hooker;
		if ( mEventHooker != _null )
			event_hooker.mEventHooker = mEventHooker->CloneTo( );

		return event_hooker;
	}
};

//! GUI Component operation enable macros.
#define _GUICOMPONENT_ENABLE_TICK( ) virtual _ubool DoTick( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_RENDER( ) virtual _ubool DoRender( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_AFTER_CHILD_RENDER( ) virtual _ubool DoAfterChildRender( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_HANDLE_EVENT( ) virtual _ubool DoHandleEvent( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_IS_HANDLE_EVENT( ) virtual _ubool DoIsHandleEvent( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_TEST_REGION( ) virtual _ubool DoTestRegion( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_EXPORT( ) virtual _ubool DoExport( ) const { return _true; }
#define _GUICOMPONENT_ENABLE_SUPPORT_KEYS( ) virtual _ubool IsSupportKeys( ) const { return _true; }

}
