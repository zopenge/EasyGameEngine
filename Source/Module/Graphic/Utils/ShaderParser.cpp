//! @file     ShaderParser.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// ShaderParser Implementation
//----------------------------------------------------------------------------

ShaderParser::ShaderParser( )
{
}

ShaderParser::~ShaderParser( )
{
}

_ubool ShaderParser::Load( AStringPtr code, _dword level )
{
	if ( level >= _MAX_LEVEL_NUMBER )
	{
		WLOG_ERROR_1( L"The GLSL include files is out of max limited(%d)", level );
		return _false;
	}

	// Get code line by line
	AStringArray strings;
	StringFormatter::SplitString( code, strings, "\n", " \t" );

	// Start to analyze it
	mCode.Clear( );
	for ( _dword i = 0; i < strings.Number( ); i ++ )
	{
		AStringPtr string = strings[i];

		// Check '#include' command
		if ( string.StartsWith( "#include" ) )
		{
			// Get the file name
			AString file_name;
			StringFormatter::ParseString( string.Str( ), "#include%s", file_name );
			file_name.TrimBoth( " \r\n\t\"" );

			// Open shader file
			IStreamReaderRef stream_reader = GetWorkingArchive( )->LoadResourceByName( WString( ).FromString( file_name ) );
			if ( stream_reader.IsNull( ) )
				return _false;

			// Get the include shader code
			AString shader_code( (const _chara*)stream_reader->GetBuffer( ), stream_reader->GetSize( ) );

			// Parse the shader code
			ShaderParser parser;
			if ( parser.Load( shader_code, level + 1 ) == _false )
				return _false;

			mCode += parser.GetShaderCode( );
		}
		else
		{
			mCode += string;
		}

		mCode += "\n";
	}

	return _true;
}

_ubool ShaderParser::Load( AStringPtr code )
{
	if ( Load( code, 0 ) == _false )
		return _false;

	return _true;
}

AStringPtr ShaderParser::GetShaderCode( ) const
{
	return mCode;
}
