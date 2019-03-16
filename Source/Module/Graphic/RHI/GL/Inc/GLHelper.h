//! @file     GLHelper.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLHelper
//----------------------------------------------------------------------------

class GLHelper
{
public:
	//!	Find the internal format and type.
	//!	@param		format			The pixel format.
	//!	@param		internalformat	The internal pixel format.
	//!	@param		type			The pixel type.
	//! @return		True indicates success, false indicates failure.
	static _ubool FindInternalFormatAndType( _PIXEL_FORMAT& format, GLenum& internalformat, GLenum& type );
	//!	Find the primitive type.
	//!	@param		type			The primitive type.
	//!	@return		The OpenGL draw/primitive mode.
	static GLenum FindPrimitiveType( _PRIMITIVE_TYPE type );
	//!	Initialize pixel formats.
	//!	@param		none.
	//!	@return		none.
	static _void InitPixelFormats( );

	//!	Convert internal format to string.
	//!	@param		format			The GL format.
	//!	@return		none.
	static AStringPtr ConvertInternalFormat2String( GLenum format );
};

}