//! @file     Viewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Viewport
//----------------------------------------------------------------------------

class Viewport
{
public:
 _float x;
 _float y;
 _float w;
 _float h;
 _float minz;
 _float maxz;

public:
 static const Viewport cNull;

public:
 inline Viewport( );
 inline Viewport( _float xx, _float yy, _float ww, _float hh, _float minzz, _float maxzz );

 inline _ubool operator == ( const Viewport& viewport ) const;
 inline _ubool operator != ( const Viewport& viewport ) const;

 //! Get aspect ratio of viewport.
 //! @param none.
 //! @return The aspect ratio.
 inline _float GetAspectRatio( ) const;
 //! Get the left-top position.
 //! @param none.
 //! @return The left-top position.
 inline PointU GetLTPos( ) const;
 //! Get the left-top position.
 //! @param none.
 //! @return The left-top position.
 inline PointF GetLTPosF( ) const;
 //! Get the viewport size.
 //! @param none.
 //! @return The viewport size.
 inline PointU GetSize( ) const;
 //! Get the viewport size.
 //! @param none.
 //! @return The viewport size.
 inline PointF GetSizeF( ) const;
 //! Get the viewport rect.
 //! @param none.
 //! @return The viewport rect.
 inline RectU GetRect( ) const;
 //! Get the viewport rect.
 //! @param none.
 //! @return The viewport rect.
 inline RectF GetRectF( ) const;
};

//----------------------------------------------------------------------------
// Viewport Implementation
//----------------------------------------------------------------------------

Viewport::Viewport( )
{
}

Viewport::Viewport( _float xx, _float yy, _float ww, _float hh, _float minzz, _float maxzz )
 : x( xx ), y( yy ), w( ww ), h( hh ), minz( minzz ), maxz( maxzz )
{
}

_ubool Viewport::operator == ( const Viewport& viewport ) const
{
 return x == viewport.x && y == viewport.y && w == viewport.w && h == viewport.h && minz == viewport.minz && maxz == viewport.maxz;
}

_ubool Viewport::operator != ( const Viewport& viewport ) const
{
 return x != viewport.x || y != viewport.y || w != viewport.w || h != viewport.h || minz != viewport.minz || maxz != viewport.maxz;
}

_float Viewport::GetAspectRatio( ) const
{
 return w / h;
}

PointU Viewport::GetLTPos( ) const
{
 return PointU( (_dword) x, (_dword) y );
}

PointF Viewport::GetLTPosF( ) const
{
 return PointF( x, y );
}

PointU Viewport::GetSize( ) const
{
 return PointU( (_dword) w, (_dword) h );
}

PointF Viewport::GetSizeF( ) const
{
 return PointF( w, h );
}

RectU Viewport::GetRect( ) const
{
 return RectU( ).InitWithSize( (_dword) x, (_dword) y, (_dword) w, (_dword) h );
}

RectF Viewport::GetRectF( ) const
{
 return RectF( ).InitWithSize( x, y, w, h );
}

}