//! @file     SLAPI.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SL-Marcos
//----------------------------------------------------------------------------

#define SL_CHECK_RESULT(action) do { \
	if (result != SL_RESULT_SUCCESS) { \
		ALOG_ERROR_2( "%s failed: %s", action, SLResultToString(result) ); \
		return; \
	} \
} while (0)

#define SL_CHECK_RESULT_BOOL(action) do { \
	if (result != SL_RESULT_SUCCESS) { \
		ALOG_ERROR_2( "%s failed: %s", action, SLResultToString(result) ); \
		return _false; \
	} \
} while (0)

//----------------------------------------------------------------------------
// SL-Functions
//----------------------------------------------------------------------------

static const _chara* SLResultToString( SLresult result )
{
	switch ( result ) {
#define SLRESULTCASE(x) case x: return #x
	  SLRESULTCASE(SL_RESULT_SUCCESS);
	  SLRESULTCASE(SL_RESULT_PRECONDITIONS_VIOLATED);
	  SLRESULTCASE(SL_RESULT_PARAMETER_INVALID);
	  SLRESULTCASE(SL_RESULT_MEMORY_FAILURE);
	  SLRESULTCASE(SL_RESULT_RESOURCE_ERROR);
	  SLRESULTCASE(SL_RESULT_RESOURCE_LOST);
	  SLRESULTCASE(SL_RESULT_IO_ERROR);
	  SLRESULTCASE(SL_RESULT_BUFFER_INSUFFICIENT);
	  SLRESULTCASE(SL_RESULT_CONTENT_CORRUPTED);
	  SLRESULTCASE(SL_RESULT_CONTENT_UNSUPPORTED);
	  SLRESULTCASE(SL_RESULT_CONTENT_NOT_FOUND);
	  SLRESULTCASE(SL_RESULT_PERMISSION_DENIED);
	  SLRESULTCASE(SL_RESULT_FEATURE_UNSUPPORTED);
	  SLRESULTCASE(SL_RESULT_INTERNAL_ERROR);
	  SLRESULTCASE(SL_RESULT_UNKNOWN_ERROR);
	  SLRESULTCASE(SL_RESULT_OPERATION_ABORTED);
	  SLRESULTCASE(SL_RESULT_CONTROL_LOST);
#undef SLRESULTCASE
	default:
		return "UNKNOWN";
	}
}

}