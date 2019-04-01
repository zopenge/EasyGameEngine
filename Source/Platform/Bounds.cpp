#include "EGEPlatform.h"

const Bounds Bounds::cNull(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
const Bounds Bounds::cMax(Math::cMinFloat, Math::cMinFloat, Math::cMinFloat, Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat);

Bounds Bounds::Union(const Bounds& box1, const Bounds& box2) {
	Bounds box;
	box.mMinVector.x = MIN(box1.mMinVector.x, box2.mMinVector.x);
	box.mMinVector.y = MIN(box1.mMinVector.y, box2.mMinVector.y);
	box.mMinVector.z = MIN(box1.mMinVector.z, box2.mMinVector.z);
	box.mMaxVector.x = MAX(box1.mMaxVector.x, box2.mMaxVector.x);
	box.mMaxVector.y = MAX(box1.mMaxVector.y, box2.mMaxVector.y);
	box.mMaxVector.z = MAX(box1.mMaxVector.z, box2.mMaxVector.z);

	return box;
}
