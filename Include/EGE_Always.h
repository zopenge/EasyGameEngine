//! @file     EGE_Always.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

// Platform Config Files
#include "Platform/PlatformConfig.h"

// Standard Files
#if defined(_PLATFORM_WINDOWS_)
#include "Platform/OS/windows/Win32Headers.h"
#include "Platform/OS/windows/Win32Macros.h"
#elif defined(_PLATFORM_IOS_)
// Only work for OBJ-C mode.
#ifdef __OBJC__
#import <Availability.h>
#import <Foundation/Foundation.h>
#endif
#elif defined(_PLATFORM_ANDROID_)
#include <jni.h>
#endif
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>

// External Files
#include "External/auto_index_MACROS.h"

// EasyGameEngine Configures
#include "EGE_Compile.h"
#include "EGE_Config.h"
#include "EGE_Values.h"

// Log Files
#undef DEFINE_MODULE
#define DEFINE_MODULE GetModuleManager()->
#include "EGE_Logs.h"

// Type Define Headers
#include "EGE_Typedef.h"
// Type Define Checker Headers
#include "EGE_TypeChecker.h"

// EasyGameEngine Basic Headers
#include "EGE_Enums.h"
#include "EGE_Memory.h"
#include "EGE_Structs.h"
#include "EGE_Template.h"

// Network OS Header
#include "Platform/OS/NetworkOSHeader.h"

// The Platform Files
#include "EGE_Platform.h"

// Global messages and events
#include "EGE_Events.h"
using namespace EGE::Events;

namespace EGE {

// Here we make sure the 'wchar_t' is 2 bytes
#ifdef _DEBUG
EGE_STATIC_ASSERT(sizeof(wchar_t) == 2, "We use UTF-16 as wchar_t, not UTF-32");
#endif

//!	Convert point to point
inline PointF ConvertPointI2PointF(const PointI& pos) {
  return PointF((_float)pos.x, (_float)pos.y);
}
inline PointF ConvertPointU2PointF(const PointU& pos) {
  return PointF((_float)pos.x, (_float)pos.y);
}
inline PointU ConvertPointF2PointU(const PointF& pos) {
  return PointU((_dword)pos.x, (_dword)pos.y);
}
inline PointI ConvertPointF2PointI(const PointF& pos) {
  return PointI((_int)pos.x, (_int)pos.y);
}

//!	Convert point to vector
inline Vector2 ConvertPoint2Vector2(const PointI& pos) {
  return Vector2((_float)pos.x, (_float)pos.y);
}
inline Vector2 ConvertPoint2Vector2(const PointU& pos) {
  return Vector2((_float)pos.x, (_float)pos.y);
}
inline Vector2 ConvertPoint2Vector2(const PointF& pos) {
  return Vector2(pos.x, pos.y);
}

//!	Convert vector to point
inline PointI ConvertVector2PointI(const Vector2& pos) {
  return PointI((_int)pos.x, (_int)pos.y);
}
inline PointU ConvertVector2PointU(const Vector2& pos) {
  return PointU((_dword)pos.x, (_dword)pos.y);
}
inline PointF ConvertVector2PointF(const Vector2& pos) {
  return PointF(pos.x, pos.y);
}

//!	Convert Rect
inline RectU ConvertRectF2RectU(const RectF& rect) {
  return RectU((_dword)rect.l, (_dword)rect.t, (_dword)rect.r, (_dword)rect.b);
}
inline RectF ConvertRectU2RectF(const RectU& rect) {
  return RectF((_float)rect.l, (_float)rect.t, (_float)rect.r, (_float)rect.b);
}

//!	Convert rect to vertex.
template <typename RectType>
_void ConvertRectToVertex(Vector2& lt, Vector2& rt, Vector2& rb, Vector2& lb,
                          const RectType& rect) {
  // Build vertex position
  lt.x = (_float)rect.l;
  lt.y = (_float)rect.t;
  rt.x = (_float)rect.r - 1;
  rt.y = (_float)rect.t;
  rb.x = (_float)rect.r - 1;
  rb.y = (_float)rect.b - 1;
  lb.x = (_float)rect.l;
  lb.y = (_float)rect.b - 1;
}
template <typename RectType>
_void ConvertRectToVertex(Vector3& lt, Vector3& rt, Vector3& rb, Vector3& lb,
                          const RectType& rect) {
  // Build vertex position
  lt.x = (_float)rect.l;
  lt.y = (_float)rect.t;
  lt.z = 0.0f;
  rt.x = (_float)rect.r - 1;
  rt.y = (_float)rect.t;
  rt.z = 0.0f;
  rb.x = (_float)rect.r - 1;
  rb.y = (_float)rect.b - 1;
  rb.z = 0.0f;
  lb.x = (_float)rect.l;
  lb.y = (_float)rect.b - 1;
  lb.z = 0.0f;
}

}  // namespace EGE
