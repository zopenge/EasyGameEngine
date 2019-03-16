//! @file     EGE_Logs.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    Globals enumerations and structure
//! Copyright ...

// DEFINE_MODULE is used by the includer to modify the module definitions.
#ifndef DEFINE_MODULE
	#error "The DEFINE_MODULE marco must be defined"
#endif

//----------------------------------------------------------------------------
// Output String
//----------------------------------------------------------------------------

#define MODULE_OUTPUT_ASTRING( type, string ) \
{ \
	DEFINE_MODULE OutputString( type, string, _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_1( type, format, p1 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_1( format, p1 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_2( type, format, p1, p2 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_2( format, p1, p2 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_3( type, format, p1, p2, p3 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_3( format, p1, p2, p3 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_4( type, format, p1, p2, p3, p4 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_4( format, p1, p2, p3, p4 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_5( type, format, p1, p2, p3, p4, p5 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_5( format, p1, p2, p3, p4, p5 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_6( type, format, p1, p2, p3, p4, p5, p6 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_6( format, p1, p2, p3, p4, p5, p6 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_7( type, format, p1, p2, p3, p4, p5, p6, p7 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_7( format, p1, p2, p3, p4, p5, p6, p7 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_8( type, format, p1, p2, p3, p4, p5, p6, p7, p8 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_9( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_10( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_11( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_12( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_ASTRING_13( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_ASTRING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ), _FILENAME_A, _LINENUMBER ); \
}

#define MODULE_OUTPUT_WSTRING( type, string ) \
{ \
	DEFINE_MODULE OutputString( type, string, _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_1( type, format, p1 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_1( format, p1 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_2( type, format, p1, p2 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_2( format, p1, p2 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_3( type, format, p1, p2, p3 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_3( format, p1, p2, p3 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_4( type, format, p1, p2, p3, p4 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_4( format, p1, p2, p3, p4 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_5( type, format, p1, p2, p3, p4, p5 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_5( format, p1, p2, p3, p4, p5 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_6( type, format, p1, p2, p3, p4, p5, p6 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_6( format, p1, p2, p3, p4, p5, p6 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_7( type, format, p1, p2, p3, p4, p5, p6, p7 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_7( format, p1, p2, p3, p4, p5, p6, p7 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_8( type, format, p1, p2, p3, p4, p5, p6, p7, p8 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_9( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ), _FILENAME_W, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_10( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_11( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_12( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ), _FILENAME_A, _LINENUMBER ); \
}
#define MODULE_OUTPUT_WSTRING_13( type, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) \
{ \
	DEFINE_MODULE OutputString( type, FORMAT_WSTRING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ), _FILENAME_A, _LINENUMBER ); \
}

//----------------------------------------------------------------------------
// Log Debug Output
//----------------------------------------------------------------------------

#if (_ENABLE_LOG_DEBUG == 1)

#define ALOG_DEBUG( string ) MODULE_OUTPUT_ASTRING( _LOG_DEBUG, string )
#define ALOG_DEBUG_1( format, p1 ) MODULE_OUTPUT_ASTRING_1( _LOG_DEBUG, format, p1 )
#define ALOG_DEBUG_2( format, p1, p2 ) MODULE_OUTPUT_ASTRING_2( _LOG_DEBUG, format, p1, p2 )
#define ALOG_DEBUG_3( format, p1, p2, p3 ) MODULE_OUTPUT_ASTRING_3( _LOG_DEBUG, format, p1, p2, p3 )
#define ALOG_DEBUG_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_ASTRING_4( _LOG_DEBUG, format, p1, p2, p3, p4 )
#define ALOG_DEBUG_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_ASTRING_5( _LOG_DEBUG, format, p1, p2, p3, p4, p5 )
#define ALOG_DEBUG_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_ASTRING_6( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6 )
#define ALOG_DEBUG_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_ASTRING_7( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7 )
#define ALOG_DEBUG_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_ASTRING_8( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define ALOG_DEBUG_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_ASTRING_9( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define ALOG_DEBUG_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_ASTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define ALOG_DEBUG_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_ASTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define ALOG_DEBUG_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_ASTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define ALOG_DEBUG_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_ASTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#define WLOG_DEBUG( string ) MODULE_OUTPUT_WSTRING( _LOG_DEBUG, string )
#define WLOG_DEBUG_1( format, p1 ) MODULE_OUTPUT_WSTRING_1( _LOG_DEBUG, format, p1 )
#define WLOG_DEBUG_2( format, p1, p2 ) MODULE_OUTPUT_WSTRING_2( _LOG_DEBUG, format, p1, p2 )
#define WLOG_DEBUG_3( format, p1, p2, p3 ) MODULE_OUTPUT_WSTRING_3( _LOG_DEBUG, format, p1, p2, p3 )
#define WLOG_DEBUG_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_WSTRING_4( _LOG_DEBUG, format, p1, p2, p3, p4 )
#define WLOG_DEBUG_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_WSTRING_5( _LOG_DEBUG, format, p1, p2, p3, p4, p5 )
#define WLOG_DEBUG_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_WSTRING_6( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6 )
#define WLOG_DEBUG_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_WSTRING_7( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7 )
#define WLOG_DEBUG_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_WSTRING_8( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define WLOG_DEBUG_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_WSTRING_9( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define WLOG_DEBUG_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_WSTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define WLOG_DEBUG_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_WSTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define WLOG_DEBUG_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_WSTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define WLOG_DEBUG_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_WSTRING_10( _LOG_DEBUG, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#else

#define ALOG_DEBUG( string ) 
#define ALOG_DEBUG_1( format, p1 ) 
#define ALOG_DEBUG_2( format, p1, p2 ) 
#define ALOG_DEBUG_3( format, p1, p2, p3 ) 
#define ALOG_DEBUG_4( format, p1, p2, p3, p4 ) 
#define ALOG_DEBUG_5( format, p1, p2, p3, p4, p5 ) 
#define ALOG_DEBUG_6( format, p1, p2, p3, p4, p5, p6 ) 
#define ALOG_DEBUG_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define ALOG_DEBUG_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define ALOG_DEBUG_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define ALOG_DEBUG_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define ALOG_DEBUG_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define ALOG_DEBUG_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define ALOG_DEBUG_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#define WLOG_DEBUG( string ) 
#define WLOG_DEBUG_1( format, p1 ) 
#define WLOG_DEBUG_2( format, p1, p2 ) 
#define WLOG_DEBUG_3( format, p1, p2, p3 ) 
#define WLOG_DEBUG_4( format, p1, p2, p3, p4 ) 
#define WLOG_DEBUG_5( format, p1, p2, p3, p4, p5 ) 
#define WLOG_DEBUG_6( format, p1, p2, p3, p4, p5, p6 ) 
#define WLOG_DEBUG_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define WLOG_DEBUG_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define WLOG_DEBUG_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define WLOG_DEBUG_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define WLOG_DEBUG_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define WLOG_DEBUG_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define WLOG_DEBUG_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#endif

//----------------------------------------------------------------------------
// Log Trace Output
//----------------------------------------------------------------------------

#if (_ENABLE_LOG_TRACE == 1)

#define ALOG_TRACE( string ) MODULE_OUTPUT_ASTRING( _LOG_TRACE, string )
#define ALOG_TRACE_1( format, p1 ) MODULE_OUTPUT_ASTRING_1( _LOG_TRACE, format, p1 )
#define ALOG_TRACE_2( format, p1, p2 ) MODULE_OUTPUT_ASTRING_2( _LOG_TRACE, format, p1, p2 )
#define ALOG_TRACE_3( format, p1, p2, p3 ) MODULE_OUTPUT_ASTRING_3( _LOG_TRACE, format, p1, p2, p3 )
#define ALOG_TRACE_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_ASTRING_4( _LOG_TRACE, format, p1, p2, p3, p4 )
#define ALOG_TRACE_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_ASTRING_5( _LOG_TRACE, format, p1, p2, p3, p4, p5 )
#define ALOG_TRACE_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_ASTRING_6( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6 )
#define ALOG_TRACE_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_ASTRING_7( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7 )
#define ALOG_TRACE_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_ASTRING_8( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define ALOG_TRACE_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_ASTRING_9( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define ALOG_TRACE_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_ASTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define ALOG_TRACE_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_ASTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define ALOG_TRACE_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_ASTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define ALOG_TRACE_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_ASTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#define WLOG_TRACE( string ) MODULE_OUTPUT_WSTRING( _LOG_TRACE, string )
#define WLOG_TRACE_1( format, p1 ) MODULE_OUTPUT_WSTRING_1( _LOG_TRACE, format, p1 )
#define WLOG_TRACE_2( format, p1, p2 ) MODULE_OUTPUT_WSTRING_2( _LOG_TRACE, format, p1, p2 )
#define WLOG_TRACE_3( format, p1, p2, p3 ) MODULE_OUTPUT_WSTRING_3( _LOG_TRACE, format, p1, p2, p3 )
#define WLOG_TRACE_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_WSTRING_4( _LOG_TRACE, format, p1, p2, p3, p4 )
#define WLOG_TRACE_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_WSTRING_5( _LOG_TRACE, format, p1, p2, p3, p4, p5 )
#define WLOG_TRACE_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_WSTRING_6( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6 )
#define WLOG_TRACE_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_WSTRING_7( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7 )
#define WLOG_TRACE_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_WSTRING_8( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define WLOG_TRACE_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_WSTRING_9( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define WLOG_TRACE_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_WSTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define WLOG_TRACE_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_WSTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define WLOG_TRACE_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_WSTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define WLOG_TRACE_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_WSTRING_10( _LOG_TRACE, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#else

#define ALOG_TRACE( string ) 
#define ALOG_TRACE_1( format, p1 ) 
#define ALOG_TRACE_2( format, p1, p2 ) 
#define ALOG_TRACE_3( format, p1, p2, p3 ) 
#define ALOG_TRACE_4( format, p1, p2, p3, p4 ) 
#define ALOG_TRACE_5( format, p1, p2, p3, p4, p5 ) 
#define ALOG_TRACE_6( format, p1, p2, p3, p4, p5, p6 ) 
#define ALOG_TRACE_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define ALOG_TRACE_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define ALOG_TRACE_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define ALOG_TRACE_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define ALOG_TRACE_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define ALOG_TRACE_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define ALOG_TRACE_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#define WLOG_TRACE( string ) 
#define WLOG_TRACE_1( format, p1 ) 
#define WLOG_TRACE_2( format, p1, p2 ) 
#define WLOG_TRACE_3( format, p1, p2, p3 ) 
#define WLOG_TRACE_4( format, p1, p2, p3, p4 ) 
#define WLOG_TRACE_5( format, p1, p2, p3, p4, p5 ) 
#define WLOG_TRACE_6( format, p1, p2, p3, p4, p5, p6 ) 
#define WLOG_TRACE_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define WLOG_TRACE_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define WLOG_TRACE_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define WLOG_TRACE_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define WLOG_TRACE_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define WLOG_TRACE_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define WLOG_TRACE_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#endif

//----------------------------------------------------------------------------
// Log Error Output
//----------------------------------------------------------------------------

#if (_ENABLE_LOG_ERROR == 1)

#define ALOG_ERROR( string ) MODULE_OUTPUT_ASTRING( _LOG_ERROR, string )
#define ALOG_ERROR_1( format, p1 ) MODULE_OUTPUT_ASTRING_1( _LOG_ERROR, format, p1 )
#define ALOG_ERROR_2( format, p1, p2 ) MODULE_OUTPUT_ASTRING_2( _LOG_ERROR, format, p1, p2 )
#define ALOG_ERROR_3( format, p1, p2, p3 ) MODULE_OUTPUT_ASTRING_3( _LOG_ERROR, format, p1, p2, p3 )
#define ALOG_ERROR_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_ASTRING_4( _LOG_ERROR, format, p1, p2, p3, p4 )
#define ALOG_ERROR_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_ASTRING_5( _LOG_ERROR, format, p1, p2, p3, p4, p5 )
#define ALOG_ERROR_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_ASTRING_6( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6 )
#define ALOG_ERROR_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_ASTRING_7( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7 )
#define ALOG_ERROR_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_ASTRING_8( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define ALOG_ERROR_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_ASTRING_9( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define ALOG_ERROR_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_ASTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define ALOG_ERROR_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_ASTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define ALOG_ERROR_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_ASTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define ALOG_ERROR_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_ASTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#define WLOG_ERROR( string ) MODULE_OUTPUT_WSTRING( _LOG_ERROR, string )
#define WLOG_ERROR_1( format, p1 ) MODULE_OUTPUT_WSTRING_1( _LOG_ERROR, format, p1 )
#define WLOG_ERROR_2( format, p1, p2 ) MODULE_OUTPUT_WSTRING_2( _LOG_ERROR, format, p1, p2 )
#define WLOG_ERROR_3( format, p1, p2, p3 ) MODULE_OUTPUT_WSTRING_3( _LOG_ERROR, format, p1, p2, p3 )
#define WLOG_ERROR_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_WSTRING_4( _LOG_ERROR, format, p1, p2, p3, p4 )
#define WLOG_ERROR_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_WSTRING_5( _LOG_ERROR, format, p1, p2, p3, p4, p5 )
#define WLOG_ERROR_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_WSTRING_6( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6 )
#define WLOG_ERROR_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_WSTRING_7( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7 )
#define WLOG_ERROR_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_WSTRING_8( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define WLOG_ERROR_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_WSTRING_9( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define WLOG_ERROR_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_WSTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define WLOG_ERROR_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_WSTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define WLOG_ERROR_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_WSTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define WLOG_ERROR_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_WSTRING_10( _LOG_ERROR, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#else

#define ALOG_ERROR( string ) 
#define ALOG_ERROR_1( format, p1 ) 
#define ALOG_ERROR_2( format, p1, p2 ) 
#define ALOG_ERROR_3( format, p1, p2, p3 ) 
#define ALOG_ERROR_4( format, p1, p2, p3, p4 ) 
#define ALOG_ERROR_5( format, p1, p2, p3, p4, p5 ) 
#define ALOG_ERROR_6( format, p1, p2, p3, p4, p5, p6 ) 
#define ALOG_ERROR_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define ALOG_ERROR_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define ALOG_ERROR_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define ALOG_ERROR_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define ALOG_ERROR_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define ALOG_ERROR_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define ALOG_ERROR_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#define WLOG_ERROR( string ) 
#define WLOG_ERROR_1( format, p1 ) 
#define WLOG_ERROR_2( format, p1, p2 ) 
#define WLOG_ERROR_3( format, p1, p2, p3 ) 
#define WLOG_ERROR_4( format, p1, p2, p3, p4 ) 
#define WLOG_ERROR_5( format, p1, p2, p3, p4, p5 ) 
#define WLOG_ERROR_6( format, p1, p2, p3, p4, p5, p6 ) 
#define WLOG_ERROR_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define WLOG_ERROR_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define WLOG_ERROR_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define WLOG_ERROR_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define WLOG_ERROR_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define WLOG_ERROR_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define WLOG_ERROR_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#endif

//----------------------------------------------------------------------------
// Log Warning Output
//----------------------------------------------------------------------------

#if (_ENABLE_LOG_WARNING == 1)

#define ALOG_WARNING( string ) MODULE_OUTPUT_ASTRING( _LOG_WARNING, string )
#define ALOG_WARNING_1( format, p1 ) MODULE_OUTPUT_ASTRING_1( _LOG_WARNING, format, p1 )
#define ALOG_WARNING_2( format, p1, p2 ) MODULE_OUTPUT_ASTRING_2( _LOG_WARNING, format, p1, p2 )
#define ALOG_WARNING_3( format, p1, p2, p3 ) MODULE_OUTPUT_ASTRING_3( _LOG_WARNING, format, p1, p2, p3 )
#define ALOG_WARNING_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_ASTRING_4( _LOG_WARNING, format, p1, p2, p3, p4 )
#define ALOG_WARNING_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_ASTRING_5( _LOG_WARNING, format, p1, p2, p3, p4, p5 )
#define ALOG_WARNING_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_ASTRING_6( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6 )
#define ALOG_WARNING_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_ASTRING_7( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7 )
#define ALOG_WARNING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_ASTRING_8( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define ALOG_WARNING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_ASTRING_9( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define ALOG_WARNING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_ASTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define ALOG_WARNING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_ASTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define ALOG_WARNING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_ASTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define ALOG_WARNING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_ASTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#define WLOG_WARNING( string ) MODULE_OUTPUT_WSTRING( _LOG_WARNING, string )
#define WLOG_WARNING_1( format, p1 ) MODULE_OUTPUT_WSTRING_1( _LOG_WARNING, format, p1 )
#define WLOG_WARNING_2( format, p1, p2 ) MODULE_OUTPUT_WSTRING_2( _LOG_WARNING, format, p1, p2 )
#define WLOG_WARNING_3( format, p1, p2, p3 ) MODULE_OUTPUT_WSTRING_3( _LOG_WARNING, format, p1, p2, p3 )
#define WLOG_WARNING_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_WSTRING_4( _LOG_WARNING, format, p1, p2, p3, p4 )
#define WLOG_WARNING_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_WSTRING_5( _LOG_WARNING, format, p1, p2, p3, p4, p5 )
#define WLOG_WARNING_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_WSTRING_6( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6 )
#define WLOG_WARNING_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_WSTRING_7( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7 )
#define WLOG_WARNING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_WSTRING_8( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define WLOG_WARNING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_WSTRING_9( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define WLOG_WARNING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_WSTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define WLOG_WARNING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_WSTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define WLOG_WARNING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_WSTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define WLOG_WARNING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_WSTRING_10( _LOG_WARNING, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#else

#define ALOG_WARNING( string ) 
#define ALOG_WARNING_1( format, p1 ) 
#define ALOG_WARNING_2( format, p1, p2 ) 
#define ALOG_WARNING_3( format, p1, p2, p3 ) 
#define ALOG_WARNING_4( format, p1, p2, p3, p4 ) 
#define ALOG_WARNING_5( format, p1, p2, p3, p4, p5 ) 
#define ALOG_WARNING_6( format, p1, p2, p3, p4, p5, p6 ) 
#define ALOG_WARNING_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define ALOG_WARNING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define ALOG_WARNING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define ALOG_WARNING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define ALOG_WARNING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define ALOG_WARNING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define ALOG_WARNING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#define WLOG_WARNING( string ) 
#define WLOG_WARNING_1( format, p1 ) 
#define WLOG_WARNING_2( format, p1, p2 ) 
#define WLOG_WARNING_3( format, p1, p2, p3 ) 
#define WLOG_WARNING_4( format, p1, p2, p3, p4 ) 
#define WLOG_WARNING_5( format, p1, p2, p3, p4, p5 ) 
#define WLOG_WARNING_6( format, p1, p2, p3, p4, p5, p6 ) 
#define WLOG_WARNING_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define WLOG_WARNING_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define WLOG_WARNING_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define WLOG_WARNING_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define WLOG_WARNING_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define WLOG_WARNING_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define WLOG_WARNING_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#endif

//----------------------------------------------------------------------------
// Log Fatal Output
//----------------------------------------------------------------------------

#if (_ENABLE_LOG_FATAL == 1)

#define ALOG_FATAL( string ) MODULE_OUTPUT_ASTRING( _LOG_FATAL, string )
#define ALOG_FATAL_1( format, p1 ) MODULE_OUTPUT_ASTRING_1( _LOG_FATAL, format, p1 )
#define ALOG_FATAL_2( format, p1, p2 ) MODULE_OUTPUT_ASTRING_2( _LOG_FATAL, format, p1, p2 )
#define ALOG_FATAL_3( format, p1, p2, p3 ) MODULE_OUTPUT_ASTRING_3( _LOG_FATAL, format, p1, p2, p3 )
#define ALOG_FATAL_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_ASTRING_4( _LOG_FATAL, format, p1, p2, p3, p4 )
#define ALOG_FATAL_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_ASTRING_5( _LOG_FATAL, format, p1, p2, p3, p4, p5 )
#define ALOG_FATAL_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_ASTRING_6( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6 )
#define ALOG_FATAL_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_ASTRING_7( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7 )
#define ALOG_FATAL_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_ASTRING_8( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define ALOG_FATAL_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_ASTRING_9( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define ALOG_FATAL_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_ASTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define ALOG_FATAL_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_ASTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define ALOG_FATAL_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_ASTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define ALOG_FATAL_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_ASTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#define WLOG_FATAL( string ) MODULE_OUTPUT_WSTRING( _LOG_FATAL, string )
#define WLOG_FATAL_1( format, p1 ) MODULE_OUTPUT_WSTRING_1( _LOG_FATAL, format, p1 )
#define WLOG_FATAL_2( format, p1, p2 ) MODULE_OUTPUT_WSTRING_2( _LOG_FATAL, format, p1, p2 )
#define WLOG_FATAL_3( format, p1, p2, p3 ) MODULE_OUTPUT_WSTRING_3( _LOG_FATAL, format, p1, p2, p3 )
#define WLOG_FATAL_4( format, p1, p2, p3, p4 ) MODULE_OUTPUT_WSTRING_4( _LOG_FATAL, format, p1, p2, p3, p4 )
#define WLOG_FATAL_5( format, p1, p2, p3, p4, p5 ) MODULE_OUTPUT_WSTRING_5( _LOG_FATAL, format, p1, p2, p3, p4, p5 )
#define WLOG_FATAL_6( format, p1, p2, p3, p4, p5, p6 ) MODULE_OUTPUT_WSTRING_6( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6 )
#define WLOG_FATAL_7( format, p1, p2, p3, p4, p5, p6, p7 ) MODULE_OUTPUT_WSTRING_7( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7 )
#define WLOG_FATAL_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) MODULE_OUTPUT_WSTRING_8( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8 )
#define WLOG_FATAL_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) MODULE_OUTPUT_WSTRING_9( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9 )
#define WLOG_FATAL_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) MODULE_OUTPUT_WSTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 )
#define WLOG_FATAL_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) MODULE_OUTPUT_WSTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 )
#define WLOG_FATAL_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) MODULE_OUTPUT_WSTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 )
#define WLOG_FATAL_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) MODULE_OUTPUT_WSTRING_10( _LOG_FATAL, format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 )

#else

#define ALOG_FATAL( string ) 
#define ALOG_FATAL_1( format, p1 ) 
#define ALOG_FATAL_2( format, p1, p2 ) 
#define ALOG_FATAL_3( format, p1, p2, p3 ) 
#define ALOG_FATAL_4( format, p1, p2, p3, p4 ) 
#define ALOG_FATAL_5( format, p1, p2, p3, p4, p5 ) 
#define ALOG_FATAL_6( format, p1, p2, p3, p4, p5, p6 ) 
#define ALOG_FATAL_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define ALOG_FATAL_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define ALOG_FATAL_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define ALOG_FATAL_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define ALOG_FATAL_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define ALOG_FATAL_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define ALOG_FATAL_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#define WLOG_FATAL( string ) 
#define WLOG_FATAL_1( format, p1 ) 
#define WLOG_FATAL_2( format, p1, p2 ) 
#define WLOG_FATAL_3( format, p1, p2, p3 ) 
#define WLOG_FATAL_4( format, p1, p2, p3, p4 ) 
#define WLOG_FATAL_5( format, p1, p2, p3, p4, p5 ) 
#define WLOG_FATAL_6( format, p1, p2, p3, p4, p5, p6 ) 
#define WLOG_FATAL_7( format, p1, p2, p3, p4, p5, p6, p7 ) 
#define WLOG_FATAL_8( format, p1, p2, p3, p4, p5, p6, p7, p8 ) 
#define WLOG_FATAL_9( format, p1, p2, p3, p4, p5, p6, p7, p8, p9 ) 
#define WLOG_FATAL_10( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10 ) 
#define WLOG_FATAL_11( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11 ) 
#define WLOG_FATAL_12( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) 
#define WLOG_FATAL_13( format, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 ) 

#endif

//----------------------------------------------------------------------------
// Output Debug String
//----------------------------------------------------------------------------

#if (_ENABLE_DEBUG_STRING == 1)

#define OUTPUT_DEBUG_STRING( x )			Platform::OutputDebugString( x )
#define OUTPUT_DEBUG_STRING_IN_LINE( x )	Platform::OutputDebugStringInLine( x )

#else

#define OUTPUT_DEBUG_STRING( x )
#define OUTPUT_DEBUG_STRING_IN_LINE( x )

#endif