#include "EGEPlatform.h"

const Color Color::cNull(0x00000000);

const Color Color::cRed(0xFFFF0000);
const Color Color::cDarkRed(0xFF8B0000);
const Color Color::cIndianRed(0xFFCD5C5C);
const Color Color::cOrangeRed(0xFFFF4500);

const Color Color::cGreen(0xFF00FF00);
const Color Color::cDarkGreen(0xFF008B00);
const Color Color::cLawnGreen(0xFF7CFC00);
const Color Color::cSeaGreen(0xFF2E8B57);

const Color Color::cBlue(0xFF0000FF);
const Color Color::cDarkBlue(0xFF00008B);
const Color Color::cSkyBlue(0xFF00BFFF);
const Color Color::cMidnightBlue(0xFF191970);

const Color Color::cWhite(0xFFFFFFFF);
const Color Color::cBlack(0xFF000000);
const Color Color::cGray(0xFF808080);
const Color Color::cSilver(0xFFC0C0C0);

const Color Color::cYellow(0xFFFFFF00);
const Color Color::cPurple(0xFF800080);
const Color Color::cTeal(0xFF008080);
const Color Color::cLime(0xFF00FF00);
const Color Color::cTomato(0xFFFF6347);
const Color Color::cOrange(0xFFFFA500);
const Color Color::cBrown(0xFFA52A2A);
const Color Color::cBisque(0xFFFFE4C4);
const Color Color::cPink(0xFFFFC0CB);
const Color Color::cViolet(0xFFEE82EE);
const Color Color::cMagenta(0xFFFF00FF);
const Color Color::cOrchid(0xFFDA70D6);
const Color Color::cChocolate(0xFFD2691E);

//! The int -> float convertion table
static _float sInt2FloatConvertionTable[256];

class Int2FloatConvertionTableInit {
public:
	Int2FloatConvertionTableInit() {
		for (_dword i = 0; i < EGE_ARRAY_NUMBER(sInt2FloatConvertionTable); i++)
			sInt2FloatConvertionTable[i] = _float(i) / 255.0f;
	}
};

static Int2FloatConvertionTableInit sInt2FloatConvertionTableInit;

Color Color::Dot(const Color& color1, const Color& color2) {
	// Be careful the color bound range (0~255)
	_byte color = _byte(_float(color1.r * color2.r) / 255.0f + _float(color1.g * color2.g) / 255.0f + _float(color1.b * color2.b) / 255.0f);

	return Color(color, color, color, color);
}

Color Color::Lerp(const Color& color1, const Color& color2, _float alpha) {
	// Be careful the color bound range (0~255)
	_int a1 = color1.a, a2 = color2.a;
	_int r1 = color1.r, r2 = color2.r;
	_int g1 = color1.g, g2 = color2.g;
	_int b1 = color1.b, b2 = color2.b;

	return Color(
	    _byte(r1 + (r2 - r1) * alpha),
	    _byte(g1 + (g2 - g1) * alpha),
	    _byte(b1 + (b2 - b1) * alpha),
	    _byte(a1 + (a2 - a1) * alpha));
}

Color Color::Mix(const Color& color1, const Color& color2) {
	Color color = Color::Lerp(color1, color2, color2.Alpha());
	color.a = color1.a;

	return color;
}