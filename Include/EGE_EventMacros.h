//! @file     EGE_EventsMacros.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    Globals enumerations and structure
//! Copyright ...

#ifndef EGE_EVENT_OFFSET
#error "You must define 'EGE_EVENT_OFFSET' first
#endif

//!	The event defined helper macro
#define EGE_EVENT_BEGIN_BASE( struct_name, id_value, offset )	\
	CREATE_VALUE_WITH_OFFSET( id_value, offset );				\
	struct struct_name : public EGE::Events::EventBase			\
	{															\
		typedef EGE::Events::EventBase BaseClass;				\
		_dword SizeOfBytes( ) const { return sizeof( *this ); }	\
		struct_name( ) : BaseClass( id_value ) { }				\
		virtual ~struct_name( ) { }

// Clone
#define EGE_EVENT_CLONE_BEGIN( c )		\
	virtual EventBase* CloneTo( ) const	\
	{									\
		c* event		= new c;		\
		event->mEventID	= mEventID;		\
		event->mRet		= mRet;			\
		event->mHandled	= mHandled;
#define EGE_EVENT_CLONE_END( )	return event; }

#define EGE_EVENT( c, id_value ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET )
#define EGE_EVENT_0( c, id_value ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		EGE_EVENT_CLONE_BEGIN( c ) \
		EGE_EVENT_CLONE_END( )
#define EGE_EVENT_1( c, id_value, t1, n1 ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		t1 n1; \
		c( t1 param_##n1 ) : BaseClass( id_value ) { n1 = param_##n1; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		EGE_EVENT_CLONE_END( )
#define EGE_EVENT_2( c, id_value, t1, n1, t2, n2 ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		t1 n1; t2 n2; \
		c( t1 param_##n1, t2 param_##n2 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		EGE_EVENT_CLONE_END( )
#define EGE_EVENT_3( c, id_value, t1, n1, t2, n2, t3, n3 ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		t1 n1; t2 n2; t3 n3; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		EGE_EVENT_CLONE_END( )
#define EGE_EVENT_4( c, id_value, t1, n1, t2, n2, t3, n3, t4, n4 ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		t1 n1; t2 n2; t3 n3; t4 n4; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3, t4 param_##n4 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; n4 = param_##n4; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		event->n4 = n4; \
		EGE_EVENT_CLONE_END( )
#define EGE_EVENT_5( c, id_value, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5 ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		t1 n1; t2 n2; t3 n3; t4 n4; t5 n5; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3, t4 param_##n4, t5 param_##n5 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; n4 = param_##n4; n5 = param_##n5; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		event->n4 = n4; \
		event->n5 = n5; \
		EGE_EVENT_CLONE_END( )
#define EGE_EVENT_6( c, id_value, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6 ) \
		EGE_EVENT_BEGIN_BASE( c, id_value, EGE_EVENT_OFFSET ) \
		t1 n1; t2 n2; t3 n3; t4 n4; t5 n5; t6 n6; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3, t4 param_##n4, t5 param_##n5, t6 param_##n6 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; n4 = param_##n4; n5 = param_##n5; n6 = param_##n6; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		event->n4 = n4; \
		event->n5 = n5; \
		event->n6 = n6; \
		EGE_EVENT_CLONE_END( )

#define EGE_EVENT_END( ) };
#define EGE_EVENT_END_1( c, id_value, t1, n1 ) \
		t1 n1; \
		c( t1 param_##n1 ) : BaseClass( id_value ) { n1 = param_##n1; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		EGE_EVENT_CLONE_END( ) \
		EGE_EVENT_END( )
#define EGE_EVENT_END_2( c, id_value, t1, n1, t2, n2 ) \
		t1 n1; t2 n2; \
		c( t1 param_##n1, t2 param_##n2 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		EGE_EVENT_CLONE_END( ) \
		EGE_EVENT_END( )
#define EGE_EVENT_END_3( c, id_value, t1, n1, t2, n2, t3, n3 ) \
		t1 n1; t2 n2; t3 n3; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		EGE_EVENT_CLONE_END( ) \
		EGE_EVENT_END( )
#define EGE_EVENT_END_4( c, id_value, t1, n1, t2, n2, t3, n3, t4, n4 ) \
		t1 n1; t2 n2; t3 n3; t4 n4; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3, t4 param_##n4 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; n4 = param_##n4; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		event->n4 = n4; \
		EGE_EVENT_CLONE_END( ) \
		EGE_EVENT_END( )
#define EGE_EVENT_END_5( c, id_value, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5 ) \
		t1 n1; t2 n2; t3 n3; t4 n4; t5 n5; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3, t4 param_##n4, t5 param_##n5 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; n4 = param_##n4; n5 = param_##n5; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		event->n4 = n4; \
		event->n5 = n5; \
		EGE_EVENT_CLONE_END( ) \
		EGE_EVENT_END( )
#define EGE_EVENT_END_6( c, id_value, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6  ) \
		t1 n1; t2 n2; t3 n3; t4 n4; t5 n5; t6 n6; \
		c( t1 param_##n1, t2 param_##n2, t3 param_##n3, t4 param_##n4, t5 param_##n5, t6 param_##n6 ) : BaseClass( id_value ) { n1 = param_##n1; n2 = param_##n2; n3 = param_##n3; n4 = param_##n4; n5 = param_##n5; n6 = param_##n6; }	\
		EGE_EVENT_CLONE_BEGIN( c ) \
		event->n1 = n1; \
		event->n2 = n2; \
		event->n3 = n3; \
		event->n4 = n4; \
		event->n5 = n5; \
		event->n6 = n6; \
		EGE_EVENT_CLONE_END( ) \
		EGE_EVENT_END( )

#define EGE_EVENT_SESSION_BEGIN( x1, x2 )	EGE_BEGIN_NAMESPACE_2( x1, x2 ) DECLARE_COUNTER;
#define EGE_EVENT_SESSION_END( )			EGE_END_NAMESPACE_2( )
