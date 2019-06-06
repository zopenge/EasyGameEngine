#pragma once

namespace EGE {

/// <summary>
/// The player.
/// </summary>
class IPlayer : public IObject {
public:
	//!	Play.
	//!	@param		none.
	//!	@return		none.
	virtual _void Play() PURE;
	//!	Stop.
	//!	@param		none.
	//!	@return		none.
	virtual _void Stop() PURE;
	//!	Pause.
	//!	@param		none.
	//!	@return		none.
	virtual _void Pause() PURE;
	//!	Resume.
	//!	@param		none.
	//!	@return		none.
	virtual _void Resume() PURE;
	//!	Reset.
	//!	@param		none.
	//!	@return		none.
	virtual _void Reset() PURE;
};

} // namespace EGE