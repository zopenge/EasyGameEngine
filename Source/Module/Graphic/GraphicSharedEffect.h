//! @file     GraphicSharedEffect.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSharedEffect
//----------------------------------------------------------------------------

class GraphicSharedEffect : public TGraphicEffectRenderState< TObject< IGraphicEffect > >
{
private:
	//! The initializer base info, because different base info could gen the same shader code, so we save it here
	GraphicEffectBase	mBaseInfo;

	//!	The internal effect
	IGraphicEffectRef	mEffect;

public:
	GraphicSharedEffect( IGraphicEffect* effect, const GraphicEffectBase& base_info );
	GraphicSharedEffect( IGraphicEffect* effect, const GraphicMaterialInfo& info );
	virtual ~GraphicSharedEffect( );

// IGraphicEffect Interface
public:
	virtual WStringPtr					GetName( ) const override;

	virtual const GraphicEffectBase&	GetBaseInfo( ) const override;
	virtual const FlagsObject&			GetEnabledFunctions( ) const override;
	virtual const FlagsObject&			GetEnabledSlotFunctions( _GRAPHIC_LIGHT_SLOT slot ) const override;

	virtual _ubool						IsShared( ) const override;
	virtual IGraphicEffect*				GetInternalEffect( ) const override;

	virtual BoundShaderRHI*				GetBoundShader( ) const override;

	virtual AStringPtr					GetPSCode( ) const override;
	virtual AStringPtr					GetVSCode( ) const override;

	virtual _crcvalue					GetUBOCRCValue( ) override;

	virtual _void						ResetUBOs( ) override;
	virtual const _byte*				GetUBOs( _dword& number, _dword& total_size ) const override;

	virtual _ubool						HasUBO( _GRAPHIC_UBT type ) const override;

	virtual _void						SetUBO( _GRAPHIC_UBT type, _ubool value ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, _int value ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, _float value ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, const Vector2& value ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, const Vector3& value ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, const Vector4& value ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, const Matrix3& transform, _ubool transpose ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, const Matrix4& transform, _ubool transpose ) override;
	virtual _void						SetUBO( _GRAPHIC_UBT type, _UNIFORM_BUFFER_DATA_TYPE data_type, _dword size, const _byte* buffer ) override;
	virtual _void						SetLDRColorUBO( _GRAPHIC_UBT type, const Color& color ) override;
	virtual _void						SetHDRColorUBO( _GRAPHIC_UBT type, const Vector4& color ) override;

	virtual _dword						GetTexSlotIndex( _TEXRES_ID id ) override;
	virtual _void						SynTextureInfo( Texture2DRHI** textures ) override;

	virtual _void						CombineRenderStates( IGraphicEffect* effect ) override;

	virtual _ubool						Compile( ) override;

	virtual GraphicShaderSerializeInfo	GetExportInfo( ) const override;
};

}