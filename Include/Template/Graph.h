#pragma once

namespace EGE {

/// <summary>
/// This class is template container class, represents a graph node.
/// </summary>
template <typename Type, typename Edge, typename Key>
class GraphNode {
public:
	// Target Node, Connection/Edge data
	typedef Pair<GraphNode*, Edge> ConnectionPair;
	typedef Map<ConnectionPair, _dword> ConnectionMap;

private:
	//!	The node element
	Type mElement;
	//!	The node key
	Key mKey;

	//!	The connection ID counter
	_dword mConnectionID;
	//!	The connections
	ConnectionMap mConnections;

public:
	//! Constructor, create an empty node.
	//! @param		none.
	GraphNode() {
		mConnectionID = 0;
	}
	//! Constructor, create an node with element.
	//! @param		element		The graph node element.
	GraphNode(const Type& element, const Key& key)
	    : mElement(element), mKey(key) {
		mConnectionID = 0;
	}
	//! Copy-Constructor, create a graph node by copy from another one.
	//! @param		node		The other graph node.
	GraphNode(const GraphNode<Type, Edge, Key>& node)
	    : mElement(node.mElement), mKey(node.mKey), mConnections(node.mConnections) {
		mConnectionID = node.mConnectionID;
	}

	//! Destructor, delete the graph node, and release the memory used by nodes.
	//! @param		none
	~GraphNode() {
	}

public:
	//!	Clear connections.
	_void ClearConnections() {
		mConnectionID = 0;

		mConnections.Clear();
	}
	//!	Get the existing connection ID.
	//!	@param		target_node	The target node.
	//!	@param		edge		The connection/edge data.
	//!	@return		The connection ID, 0 indicates it's not existing.
	_dword GetConnection(const GraphNode* target_node, const Edge& edge) const {
		for (typename ConnectionMap::Iterator it = mConnections.GetHeadIterator(); it.IsValid(); ++it) {
			const ConnectionPair& connection = it.GetObject();

			if (connection.mObject1 != target_node)
				continue;

			if (connection.mObject2 != edge)
				continue;

			return it.GetKey();
		}

		return 0;
	}
	//!	Add a connection from this node to another node.
	//!	@param		target_node	The target node.
	//!	@param		edge		The connection/edge data.
	//!	@return		none.
	_void AddConnection(GraphNode* target_node, const Edge& edge) {
		EGE_ASSERT(target_node != _null);

		// Skip for the duplicate connection
		_dword connection_id = GetConnection(target_node, edge);
		if (connection_id != 0)
			return;

		// Add new connection
		mConnections[++mConnectionID] = ConnectionPair(target_node, edge);
	}
	//! Remove a connection.
	//!	@param		id		The connection ID.
	//!	@return		none.
	_ubool RemoveConnection(_dword id) {
		return mConnections.Remove(id);
	}
	//! Remove all connections by target node.
	//!	@param		target_node	The target node.
	//!	@return		none.
	_void RemoveConnectionsByTargetNode(const GraphNode* target_node) {
		for (typename ConnectionMap::Iterator it = mConnections.GetHeadIterator(); it.IsValid(); ++it) {
			const ConnectionPair& connection = it.GetObject();

			if (connection.mObject1 == target_node) {
				mConnections.Remove(it);
				return;
			}
		}
	}

	//!	Get the node's connections/edges number.
	_dword GetConnectionNumber() const {
		return mConnections.Number();
	}
	//!	Get the connections/edges.
	const ConnectionMap& GetConnections() const {
		return mConnections;
	}

	//!	Get the target node by connection/edge.
	//!	@param		id		The connection ID.
	//!	@return		The graph node.
	GraphNode* GetTargetNodeByConnectionID(_dword id) {
		ConnectionPair* connection = mConnections.Search(id);
		if (connection == _null)
			return _null;

		return connection->mObject1;
	}
	//!	Get the target node by connection/edge.
	//!	@param		id		The connection ID.
	//!	@return		The graph node.
	const GraphNode* GetTargetNodeByConnectionID(_dword id) const {
		const ConnectionPair* connection = mConnections.Search(id);
		if (connection == _null)
			return _null;

		return connection->mObject1;
	}
	//!	Get the edge data.
	//!	@param		id		The connection ID.
	//!	@return		The edge data info.
	Edge& GetEdgeData(_dword id) {
		ConnectionPair* connection = mConnections.Search(id);
		EGE_ASSERT(connection != _null);

		return connection->mObject2;
	}
	//!	Get the edge data.
	//!	@param		id		The connection ID.
	//!	@return		The edge data info.
	const Edge& GetEdgeData(_dword id) const {
		const ConnectionPair* connection = mConnections.Search(id);
		EGE_ASSERT(connection != _null);

		return connection->mObject2;
	}

	//!	Get the node's element.
	//!	@param		none.
	//!	@return		The node's element.
	Type& GetElement() {
		return mElement;
	}
	//!	Get the node's element.
	//!	@param		none.
	//!	@return		The node's element.
	const Type& GetElement() const {
		return mElement;
	}

	//!	Get the node's key.
	//!	@param		none.
	//!	@return		The node's key.
	const Key& GetKey() const {
		return mKey;
	}
};

/// <summary>
/// This class is template container class, represents a graph.
/// </summary>
template <typename Type, typename Edge, typename Key>
class Graph {
public:
	typedef Graph<Type, Edge, Key> TSelf;
	typedef GraphNode<Type, Edge, Key> TGraphNode;
	typedef Map<TGraphNode, Key> GraphNodeMap;
	typedef typename GraphNodeMap::Iterator GraphNodeMapIterator;

public:
	//! The iterator of graph class.
	struct Iterator {
		//! The graph reference.
		TSelf* mGraph;
		//!	The iterator of node map
		GraphNodeMapIterator mIteratorOfMap;

		//! Constructor, create an iterator of the graph.
		//! @param		none.
		Iterator()
		    : mGraph(_null) {
		}
		//! Constructor, create an iterator of the graph.
		//! @param		graph		The graph reference.
		//! @param		node		The graph node.
		Iterator(TSelf* graph, GraphNodeMapIterator it_of_map)
		    : mGraph(graph), mIteratorOfMap(it_of_map) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return mIteratorOfMap.GetObject().GetElement();
		}
		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator const Type&() const {
			return mIteratorOfMap.GetObject().GetElement();
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mIteratorOfMap.IsValid();
		}

		//! decrease the iterator, point to the previous element of the graph.
		//! @param		none
		_void operator--() {
			--mIteratorOfMap;
		}
		//! Increase the iterator, point to the next element of the graph.
		//! @param		none
		_void operator++() {
			++mIteratorOfMap;
		}
	};

protected:
	//!	The graph node map
	GraphNodeMap mGraphNodes;

public:
	//! Constructor, create an empty graph.
	//! @param		none.
	Graph();
	//! Copy-Constructor, create a graph by copy from another one.
	//! @param		graph		The other graph.
	Graph(const TSelf& graph);
	//! Destructor, delete the graph, and release the memory used by nodes.
	//! @param		none
	~Graph();

public:
	//! Copy elements from another graph.
	//! @param		graph		The other graph.
	//! @return		The reference of current graph.
	TSelf& operator=(const TSelf& graph);

	//! Get the current number of elements in graph.
	//! @param		none
	//! @return		The current number of elements in graph.
	_dword Number() const;

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The tail iterator.
	Iterator GetTailIterator() const;
	//!	Get the element by key.
	//! @param		key		The element key.
	//! @return		An iterator reference to the element.
	Iterator GetIterator(const Key& key);

	//!	Remove iterator.
	//!	@param		it		The iterator.
	//!	@return		The next iterator.
	Iterator RemoveIterator(Iterator it);

	//!	Add a node.
	//! @param		element		The new element to be added.
	//! @param		key			The element key.
	//! @return		The graph node.
	TGraphNode* AddNode(const Type& element, const Key& key);
	//! Remove a node.
	//! @param		key			The element key.
	//!	@return		none.
	_void RemoveNode(const Key& key);

	//!	Get the node by key.
	//! @param		key			The element key.
	//! @return		The graph node.
	TGraphNode* GetNode(const Key& key);
	//!	Get the node by key.
	//! @param		key			The element key.
	//! @return		The graph node.
	const TGraphNode* GetNode(const Key& key) const;

	//! Clear graph.
	//! @param		none.
	//!	@return		none.
	_void Clear();
};

template <typename Type, typename Edge, typename Key>
Graph<Type, Edge, Key>::Graph() {
}

template <typename Type, typename Edge, typename Key>
Graph<Type, Edge, Key>::Graph(const TSelf& graph) {
	mGraphNodes = graph.mGraphNodes;
}

template <typename Type, typename Edge, typename Key>
Graph<Type, Edge, Key>::~Graph() {
}

template <typename Type, typename Edge, typename Key>
Graph<Type, Edge, Key>& Graph<Type, Edge, Key>::operator=(const TSelf& graph) {
	Clear();

	mGraphNodes = graph.mGraphNodes;

	return *this;
}

template <typename Type, typename Edge, typename Key>
_dword Graph<Type, Edge, Key>::Number() const {
	return mGraphNodes.Number();
}

template <typename Type, typename Edge, typename Key>
typename Graph<Type, Edge, Key>::Iterator Graph<Type, Edge, Key>::GetHeadIterator() const {
	return Iterator((Graph*)this, mGraphNodes.GetHeadIterator());
}

template <typename Type, typename Edge, typename Key>
typename Graph<Type, Edge, Key>::Iterator Graph<Type, Edge, Key>::GetTailIterator() const {
	return Iterator((Graph*)this, mGraphNodes.GetTailIterator());
}

template <typename Type, typename Edge, typename Key>
typename Graph<Type, Edge, Key>::Iterator Graph<Type, Edge, Key>::GetIterator(const Key& key) {
	return Iterator(this, mGraphNodes.GetIterator(key));
}

template <typename Type, typename Edge, typename Key>
typename Graph<Type, Edge, Key>::Iterator Graph<Type, Edge, Key>::RemoveIterator(Iterator it) {
	GraphNodeMapIterator next_it = mGraphNodes.Remove(it.mIteratorOfMap);

	return Iterator(this, next_it);
}

template <typename Type, typename Edge, typename Key>
typename Graph<Type, Edge, Key>::TGraphNode* Graph<Type, Edge, Key>::AddNode(const Type& element, const Key& key) {
	if (mGraphNodes.Search(key) != _null)
		return _null;

	return mGraphNodes.Insert(TGraphNode(element, key), key);
}

template <typename Type, typename Edge, typename Key>
_void Graph<Type, Edge, Key>::RemoveNode(const Key& key) {
	mGraphNodes.Remove(key);
}

template <typename Type, typename Edge, typename Key>
typename Graph<Type, Edge, Key>::TGraphNode* Graph<Type, Edge, Key>::GetNode(const Key& key) {
	return mGraphNodes.Search(key);
}

template <typename Type, typename Edge, typename Key>
const typename Graph<Type, Edge, Key>::TGraphNode* Graph<Type, Edge, Key>::GetNode(const Key& key) const {
	return mGraphNodes.Search(key);
}

template <typename Type, typename Edge, typename Key>
_void Graph<Type, Edge, Key>::Clear() {
	mGraphNodes.Clear();
}

} // namespace EGE