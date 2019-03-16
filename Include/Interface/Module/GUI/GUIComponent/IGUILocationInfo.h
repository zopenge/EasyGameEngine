
#pragma once

namespace EGE
{
	class IGUILocationInfo : public ISerializable
	{
	public:
		virtual _void							SetSizeType( _GUI_SIZE_TYPE sizetype, _float parentsize ) PURE;
		virtual _void							SetAnchorType( _GUI_ANCHOR_TYPE anchortype, _float parentsize ) PURE;
		virtual _ubool							SetLogicSize( _float logicsize, _float parentsize ) PURE;
		virtual _ubool							SetPercentSize( _float percentsize, _float parentsize ) PURE;
		virtual _ubool							SetLockSize( _float locksize, _float parentsize ) PURE;
		virtual _ubool							SetLogicPosition( _float position, _float parentsize ) PURE;
		virtual _ubool							SetAnchorPosition( _float position, _float parentsize ) PURE;
		virtual _void							SetLogicScale( _float scale ) PURE;

		virtual _GUI_SIZE_TYPE					GetSizeType( ) const PURE;
		virtual _GUI_ANCHOR_TYPE				GetAnchorType( ) const PURE;
		virtual _float							GetLogicSize( ) const PURE;
		virtual _float							GetPercentSize( ) const PURE;
		virtual _float							GetLockSize( ) const PURE;
		virtual _float							GetLogicPosition( ) const PURE;
		virtual _float							GetAnchorPosition( ) const PURE;
		virtual _float							GetLogicScale( ) const PURE;

		virtual _ubool							UpdateLogicSize( _float parentsize ) PURE;
		virtual _ubool							UpdateLogicPosition( _float parentsize ) PURE;
	};
}