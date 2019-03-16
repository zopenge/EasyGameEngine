//! @file     Math.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

_void ValueEncoder::EncodeTransform3D( const Transform3D& transform, const AxisAlignedBox& bounding_box, _qword& encode_q, _dword& encode_d )
{
 _qword code_quat = EncodeQuaternion<_qword>( transform.mRotation, 15 );
 _qword code_pos = EncodeVector3<_qword>( transform.mTranslate, bounding_box.mMinVector, bounding_box.mMaxVector, 16 );

 encode_q = ( code_pos << 16 ) | ( ( code_quat >> 32 ) & 0xFFFF );
 encode_d = (_dword) ( code_quat & 0xFFFFFFFF );
}

Transform3D ValueEncoder::DecodeTransform3D( const AxisAlignedBox& bounding_box, _qword encode_q, _dword encode_d )
{
 Transform3D transform;

 _qword code_pos = encode_q >> 16;
 _qword code_quat = ( ( encode_q & 0xFFFF ) << 32 ) | (_qword) encode_d;

 transform.mTranslate = DecodeVector3<_qword>( code_pos, bounding_box.mMinVector, bounding_box.mMaxVector, 16 );
 transform.mRotation = DecodeQuaternion<_qword>( code_quat, 15 );

 return transform;
}