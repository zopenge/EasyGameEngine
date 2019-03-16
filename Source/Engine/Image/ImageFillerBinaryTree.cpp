//! @file     ImageFillerBinaryTree.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// ImageFillerBinaryTree Implementation
//----------------------------------------------------------------------------

ImageFillerBinaryTree::ImageFillerBinaryTree( const PointU& size, const PointU& space ) : BaseClass( size, space )
{
	mRootNode.mRect.InitWithSize( 0, 0, size.x, size.y );
}

ImageFillerBinaryTree::~ImageFillerBinaryTree( )
{
	ClearAllImages( );
}

ImageFillerBinaryTree::Node* ImageFillerBinaryTree::InsertNode( Node* node, const PointU& size )
{
	if ( node->IsLeaf( ) )
	{
		// Make sure it's free node
		if ( node->mIsFree == _false )
			return _null;

		// The size is too big
		if ( node->mRect.GetWidth( ) < size.x || node->mRect.GetHeight( ) < size.y )
			return _null;

		// It just equal to node's size
		if ( node->mRect.GetWidth( ) == size.x && node->mRect.GetHeight( ) == size.y )
		{
			node->mIsFree = _false;
			return node;
		}

		_int dw = (_int) node->mRect.GetWidth( ) - (_int) size.x;
		_int dh = (_int) node->mRect.GetHeight( ) - (_int) size.y;

		if ( dw > dh )
		{
			node->mNodes[0] = new Node( node, RectU( ).InitWithSize( node->mRect.l, node->mRect.t, size.x, node->mRect.GetHeight( ) ) );
			node->mNodes[1] = new Node( node, RectU( ).InitWithSize( node->mRect.l + size.x, node->mRect.t, dw, node->mRect.GetHeight( ) ) );
		}
		else
		{
			node->mNodes[0] = new Node( node, RectU( ).InitWithSize( node->mRect.l, node->mRect.t, node->mRect.GetWidth( ), size.y ) );
			node->mNodes[1] = new Node( node, RectU( ).InitWithSize( node->mRect.l, node->mRect.t + size.y, node->mRect.GetWidth( ), dh ) );
		}

		return InsertNode( node->mNodes[0], size );
	}
	else
	{
		Node* new_node = InsertNode( node->mNodes[0], size );
		if ( new_node != _null )
			return new_node;

		return InsertNode( node->mNodes[1], size );
	}
}

ImageFillerBinaryTree::Node* ImageFillerBinaryTree::FindNode( Node* node, const RectU& rect )
{
	if ( node->mRect == rect )
		return node;

	if ( node->IsLeaf( ) == _false )
	{
		Node* match_node = FindNode( node->mNodes[0], rect );
		if ( match_node != _null )
			return match_node;

		match_node = FindNode( node->mNodes[1], rect );
		if ( match_node != _null )
			return match_node;
	}

	return _null;
}

_ubool ImageFillerBinaryTree::OnAddImage( _dword width, _dword height, RectU& rect )
{
	Node* node = InsertNode( &mRootNode, PointU( width, height ) );
	if ( node == _null )
		return _false;

	rect = node->mRect;

	return _true;
}

_ubool ImageFillerBinaryTree::OnFreeImage( const RectU& rect )
{
	Node* node = FindNode( &mRootNode, rect );
	if ( node == _null )
		return _false;

	// It's must be leaf node
	if ( node->IsLeaf( ) == _false )
		return _false;

	// Start to free node
	while ( _true )
	{
		// Free it
		node->Free( );

		// Get the parent node
		Node* parent_node = node->mParent;
		if ( parent_node == _null )
			break;

		// If the parent node is all free then remove recursively
		if ( parent_node->IsFree( ) )
			node = parent_node;
		else
			break; // Free node finished
	}

	return _true;
}

_void ImageFillerBinaryTree::ClearAllImages( )
{
	mRootNode.Free( );

	BaseClass::ClearAllImages( );
}