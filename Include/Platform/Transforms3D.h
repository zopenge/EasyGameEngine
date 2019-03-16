
#pragma once

namespace EGE
{
	//----------------------------------------------------------------------------
	// Transforms3D
	//----------------------------------------------------------------------------

	class Transforms3D
	{
	public:
		//! The rotation of transform3d
		Quaternion	mRotation;
		//! The translate of transform3d
		Vector3		mTranslate;
		
	public:
		//! The identity Transforms3D.
		static const Transforms3D cIdentity;


	public:
		//! Constructor, create a Transforms3D without sets rotation and translate components.
		//! @param		none
		inline Transforms3D( );
		//! Constructor, create a quaternion and sets rotation and translate components.
		//! @param		rotation	rotation component of the Transforms3D.
		//! @param		scale		scale component of the Transforms3D.
		//! @param		translate	translate component of the Transforms3D.
		inline Transforms3D( const Quaternion& rotation, const Vector3& translate );

		//! Multiply a Transforms3D to current Transforms3D, and save result in current one.
		//! @param		Transforms3D		The Transforms3D to multiply.
		//! @return		The result Transforms3D of multiplication.
		Transforms3D& operator *= ( const Transforms3D& transform );

		//! Multiply a Transforms3D to current Transforms3D, return a new Transforms3D to save result.
		//! @param		Transforms3D		The Transforms3D to multiply.
		//! @return		The result Transforms3D of multiplication.
		Transforms3D operator * ( const Transforms3D& transform ) const;
	};


	//----------------------------------------------------------------------------
	// Transforms3D Implementation
	//----------------------------------------------------------------------------

	Transforms3D::Transforms3D( )
	{
	}

	Transforms3D::Transforms3D( const Quaternion& rotation, const Vector3& translate )
		: mRotation( rotation )
		, mTranslate( translate )
	{
	}
}