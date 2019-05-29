#pragma once

namespace EGE {

/// <summary>
/// The font face interface.
/// </summary>
class IFontFace : public IObject {
public:
	//!	Check whether has character.
	//!	@param		code	The character code.
	//!	@return		True indicates it has character.
	virtual _ubool HasCharacter(_dword code) const PURE;

	//!	Get the char size.
	//!	@param		code	The character code.
	//!	@return		The char size.
	virtual PointU GetCharSize(_dword code) PURE;
	//!	Get the char max height.
	//!	@param		none.
	//!	@return		The char max height.
	virtual _dword GetCharMaxHeight() const PURE;

	//!	Get the amount between characters.
	//!	@param		first_code	The first code.
	//!	@param		second_code	The second code.
	//!	@return		The amount.
	virtual _int GetAmountBetweenCharacters(_dword first_code, _dword second_code) const PURE;

	//!	Get the font size.
	//!	@param		none.
	//!	@return		The font size.
	virtual _dword GetFontSize() const PURE;
	//!	Set the font size.
	//!	@param		size	The font size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetFontSize(_dword size) PURE;
	//!	Get the font code data.
	//!	@param		code	The character code.
	//!	@param		flags	The character load flags, @see _FONT_FACE_LOAD_FLAGS.
	//!	@param		data	The character code data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetFontCodeData(_dword code, _dword flags, BaseFontFaceCodeData& data) PURE;

	//!	Render character.
	//!	@param		code	The character code.
	//!	@param		data	The character code data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RenderCharacter(_dword code, FontFaceCodeData& data) PURE;
	//!	Render character with stroke and blur effect.
	//!	@param		code		The character code.
	//!	@param		strokeSize	The stroke size.
	//!	@param		blurSize	The blur size.
	//!	@param		blurFactor	The blur factor.
	//!	@param		data		The character code stroke data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool RenderCharacter(_dword code, _dword strokeSize, _dword blurSize, _float blurFactor, FontFaceCodeData& data) PURE;

	//!	Get font image, only works for bitmap font format.
	//!	@param		none.
	//!	@return		The image.
	virtual IImageFilePassRef GetImage() const PURE;
};

} // namespace EGE