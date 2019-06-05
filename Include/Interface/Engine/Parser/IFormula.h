#pragma once

namespace EGE {

/// <summary>
/// The formula interface.
/// </summary>
class IFormula : public IObject {
public:
	//! The Error Codes
	enum class ErrorType {
		NoError,
		Parenthesis,
		WrongChar,
		DivideByZero
	};

public:
	//!	Calculate the expression.
	//!	@param		expression	The expression string.
	//!	@param		err_code	The error code.
	//!	@return		The result of expression.
	virtual _double Calculate(WStringPtr expression, ErrorType* err_code = _null) const PURE;
};

} // namespace EGE