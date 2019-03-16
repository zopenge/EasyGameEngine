#pragma once

namespace EGE
{

	template< typename Type, typename Info >
	class ITAnimationUpdater : public ISerializable
	{
	protected:
		typedef RefPtr< Info >					InfoRef;

	public:
		virtual InfoRef							GetInfo( ) const PURE;
		virtual _ANIMATION_STATUS				GetPlayingStatus( ) const PURE;
		virtual _float							GetCurrentTime( ) const PURE;
		virtual _dword							GetCurrentKeyFrame( ) const PURE;
		virtual _ANIMATION_DIRECTION			GetDirection( ) const PURE;

		virtual _ubool							Tick( _dword elapse ) PURE;
		virtual _void							Reset( _ubool reset_status ) PURE;
		virtual _void							Stop( ) PURE;
		virtual _ubool							SetCurrentTime( _dword frame ) PURE;

		virtual _ubool							Tick( _dword elapse, _void* result_value ) PURE;
		virtual _void							Reset( _ubool reset_status, _void* result_value ) PURE;
		virtual _void							Stop( _void* result_value ) PURE;
		virtual _ubool							SetCurrentTime( _dword frame, _void* result_value ) PURE;

		virtual _void							Play( ) PURE;
		virtual _void							Pause( ) PURE;
		virtual _void							Resume( ) PURE;

		virtual _void							SetInfo( Info* animationinfo ) PURE;
		virtual _ubool							CloneFrom( const Type* src ) PURE;
	protected:
		virtual _ubool							_Tick( _dword elapse ) PURE;
		virtual _ubool							_Tick( _dword elapse, _void* result_value ) PURE;
		virtual _ubool							_SetValue( _dword index, _void* result_value ) PURE;

	};

}