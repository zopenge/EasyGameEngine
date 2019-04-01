#include "EGEPlatform.h"

const Box Box::cNull(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

Box& Box::Expand(_float expand_size) {
	Vector3 vx = (mVectors[1] - mVectors[0]).Normalize();
	Vector3 vy = (mVectors[2] - mVectors[0]).Normalize();
	Vector3 vz = (mVectors[4] - mVectors[0]).Normalize();

	mVectors[0] += (-vx - vy - vz) * expand_size;
	mVectors[1] += (vx - vy - vz) * expand_size;
	mVectors[2] += (-vx + vy - vz) * expand_size;
	mVectors[3] += (vx + vy - vz) * expand_size;
	mVectors[4] += (-vx - vy + vz) * expand_size;
	mVectors[5] += (vx - vy + vz) * expand_size;
	mVectors[6] += (-vx + vy + vz) * expand_size;
	mVectors[7] += (vx + vy + vz) * expand_size;

	return *this;
}

Vector3 Box::GetCenter() const {
	Vector3 center = mVectors[0];
	center += mVectors[1];
	center += mVectors[2];
	center += mVectors[3];
	center += mVectors[4];
	center += mVectors[5];
	center += mVectors[6];
	center += mVectors[7];
	center /= 8.0f;
	return center;
}
