#pragma once

namespace EGE {

/// <summary>
/// The view based application.
/// </summary>
class IViewBasedApplication : public IApplication {
public:
	//!	Make the application position to the center of the screen.
	//!	@param		none.
	//!	@return		none.
	virtual _void Center() PURE;

	//!	Set the application size.
	//!	@param		width			The application window width.
	//!	@param		height			The application window height.
	//!	@return		none.
	virtual _void SetSize(_dword width, _dword height) PURE;
	//!	Get the application size.
	//!	@param		none.
	//!	@return		The application window size.
	virtual PointU GetSize() const PURE;

	//! Get the orientation mode.
	//!	@param		none.
	//!	@return		The orientation mode of application.
	virtual OrientationMode GetOrientation() const PURE;
};

} // namespace EGE