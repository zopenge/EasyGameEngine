
#pragma once

namespace EGE
{
	union UnionSize
	{
		_float							mUnionSize;
		_float							mConstantSize;
		_float							mPercentSize;
		_float							mLockSize;
	};

	class GUILocationInfo : public TSerializable< TObject< IGUILocationInfo > >
	{
	private:
		typedef TSerializable< TObject< IGUILocationInfo > > BaseClass;
	public:
		GUILocationInfo( );
		~GUILocationInfo( );

	public:
		_void CopyFrom( const GUILocationInfo& location_info );

		// IObject Interface
	public:
		virtual IObject*			CloneTo( ) const override;

		// IGUILocationInfo Interface
	public:
		virtual _void					SetSizeType( _GUI_SIZE_TYPE sizetype, _float parentsize ) override;
		virtual _void					SetAnchorType( _GUI_ANCHOR_TYPE anchortype, _float parentsize ) override;
		virtual _ubool					SetLogicSize( _float logicsize, _float parentsize ) override;
		virtual _ubool					SetPercentSize( _float percentsize, _float parentsize ) override;
		virtual _ubool					SetLockSize( _float locksize, _float parentsize ) override;
		virtual _ubool					SetLogicPosition( _float position, _float parentsize ) override;
		virtual _ubool					SetAnchorPosition( _float position, _float parentsize ) override;
		virtual _void					SetLogicScale( _float scale ) override;

		virtual _GUI_SIZE_TYPE			GetSizeType( ) const override;
		virtual _GUI_ANCHOR_TYPE		GetAnchorType( ) const override;
		virtual _float					GetLogicSize( ) const override;
		virtual _float					GetPercentSize( ) const override;
		virtual _float					GetLockSize( ) const override;
		virtual _float					GetLogicPosition( ) const override;
		virtual _float					GetAnchorPosition( ) const override;
		virtual _float					GetLogicScale( ) const override;

		virtual _ubool					UpdateLogicSize( _float parentsize ) override;
		virtual _ubool					UpdateLogicPosition( _float parentsize ) override;

		// ISerializable Interface
	public:
		virtual _ubool					Import( ISerializableNode* node ) override;
		virtual _ubool					Export( ISerializableNode* node ) const override;

	private:
		_ubool							UpdateUnionSize( _float parentsize );
		_ubool							UpdateAnchorPosition( _float parentsize );

	private:
		_GUI_SIZE_TYPE					mSizeType;
		_GUI_ANCHOR_TYPE				mAnchorType;
		_float							mLogicSize;
		UnionSize						mUnionSize;
		_float							mLogicPosition;
		_float							mAnchorPosition;
		_float							mLogicScale;
	};
}