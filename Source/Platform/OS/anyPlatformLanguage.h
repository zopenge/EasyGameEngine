#pragma once

namespace EGE {

/// <summary>
/// The any-platform language.
/// </summary>
class anyPlatformLanguage {
public:
	static _ubool IsVowelInThai(_charw code);
	static _ubool IsUpperVowelInThai(_charw code);
	static _ubool IsDownVowelInThai(_charw code);
	static _ubool IsToneInThai(_charw code);
};

} // namespace EGE