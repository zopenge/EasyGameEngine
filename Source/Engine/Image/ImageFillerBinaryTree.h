//! @file     ImageFillerBinaryTree.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ImageFillerBinaryTree
//----------------------------------------------------------------------------

class ImageFillerBinaryTree : public INTERFACE_IMAGE_FILLER_IMPL( IImageFiller )
{
private:
	typedef INTERFACE_IMAGE_FILLER_IMPL( IImageFiller ) BaseClass;

private:
	//!	The node of tree
	struct Node
	{
		_ubool	mIsFree;
		RectU	mRect;
		Node*	mParent;
		Node*	mNodes[2];

		_ubool IsLeaf( ) const
		{
			return mNodes[0] == _null && mNodes[1] == _null;
		}
		_ubool IsFree( ) const
		{
			return mNodes[0]->mIsFree && mNodes[1]->mIsFree;
		}

		_void Free( )
		{
			mIsFree = _true;

			EGE_DELETE( mNodes[0] );
			EGE_DELETE( mNodes[1] );
		}

		Node( )
		{
			mIsFree		= _true;
			mRect		= RectU::cNull;
			mParent		= _null;
			mNodes[0]	= _null;
			mNodes[1]	= _null;
		}
		Node( Node* parent_node, const RectU& rect )
		{
			mIsFree		= _true;
			mRect		= rect;
			mParent		= parent_node;
			mNodes[0]	= _null;
			mNodes[1]	= _null;
		}
		~Node( )
		{
			Free( );
		}
	};

private:
	//!	The root node.
	Node mRootNode;

private:
	//!	Insert node.
	Node* InsertNode( Node* node, const PointU& size );
	//!	Find node.
	Node* FindNode( Node* node, const RectU& rect );

// TImageFiller interface
private:
	virtual _ubool	OnAddImage( _dword width, _dword height, RectU& rect ) override;
	virtual _ubool	OnFreeImage( const RectU& rect ) override;

public:
	ImageFillerBinaryTree( const PointU& size, const PointU& space );
	virtual ~ImageFillerBinaryTree( );

// IImageFiller Interface
public:
	virtual _void	ClearAllImages( ) override;
};

//----------------------------------------------------------------------------
// ImageFillerBinaryTree Implementation
//----------------------------------------------------------------------------

}