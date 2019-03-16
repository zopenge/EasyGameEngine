#include "EGEEngine.h"

iosAnalyticsCenterFlurry::iosAnalyticsCenterFlurry( UStringPtr app_key )
	: mAppKey( app_key )
{
	[Flurry startSession:[NSString stringWithUTF8String:mAppKey.Str( )]];
}

iosAnalyticsCenterFlurry::~iosAnalyticsCenterFlurry( )
{

}

_void iosAnalyticsCenterFlurry::SetUserID( UStringPtr user_id )
{
	[Flurry setUserID:[NSString stringWithUTF8String:user_id.Str( )]];
}

_void iosAnalyticsCenterFlurry::SetAge( _dword age )
{
	[Flurry setAge:age];
}

_void iosAnalyticsCenterFlurry::SetGender( _GENDER gender )
{
	switch ( gender )
	{
	case _GENDER_FEMALE:
		{
			[Flurry setGender:@"f"];
		}
		break;
	case _GENDER_MALE:
		{
			[Flurry setGender:@"m"];
		}
		break;
	}
}

_void iosAnalyticsCenterFlurry::Enable( _ubool enable )
{

}

_void iosAnalyticsCenterFlurry::LogEvent( UStringPtr event_id, const Map< UString, UString >& parameters )
{
    NSMutableDictionary* dictionary = [[NSMutableDictionary alloc] init];
    for ( Map<UString, UString>::Iterator it = parameters.GetHeadIterator( ); it.IsValid( ); ++ it )
    {
        [dictionary setObject:[NSString stringWithUTF8String:it.GetObject( ).Str( )] forKey:[NSString stringWithUTF8String:it.GetKey( ).Str( )]];
    }
    
	[Flurry logEvent:[NSString stringWithUTF8String:event_id.Str( )] withParameters:dictionary];
}

_void iosAnalyticsCenterFlurry::LogEvent( UStringPtr event_id, UStringPtr desc )
{
    
}

_void iosAnalyticsCenterFlurry::Error( UStringPtr error_id, UStringPtr error_msg, UStringPtr error_class )
{
	[Flurry logError:[NSString stringWithUTF8String:error_id.Str( )] message:[NSString stringWithUTF8String:error_msg.Str( )] exception:nil];
}