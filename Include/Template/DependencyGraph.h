#pragma once

namespace EGE {

/// <summary>
///	The edge for dependency graph.
/// </summary>
struct DependencyGraphEdge {
	//!	The connection flag
	enum class Flag {
		//!	Unknown connection
		Unknown,
		//! The prerequisite connection
		Prerequisite,
		//! The subsequent connection
		Subsequent,
	};

	//!	The connection flag
	Flag mConnectionFlag;
	//!	The pass flag, true indicates we can pass this edge ( connection )
	_ubool mCanPass;

	_ubool operator==(const DependencyGraphEdge& edge) const {
		if (mConnectionFlag != edge.mConnectionFlag)
			return _false;

		if (mCanPass != edge.mCanPass)
			return _false;

		return _true;
	}
	_ubool operator!=(const DependencyGraphEdge& edge) const {
		if (mConnectionFlag == edge.mConnectionFlag)
			return _false;

		if (mCanPass == edge.mCanPass)
			return _false;

		return _true;
	}

	DependencyGraphEdge(Flag flag = Flag::Unknown, _ubool pass = _false)
	    : mConnectionFlag(flag), mCanPass(pass) {
	}
};

/// <summary>
/// The node of dependency graph.
/// </summary>
template <typename Type, typename Edge, typename Key>
class DependencyGraphNode {
public:
	typedef GraphNode<DependencyGraphNode, Edge, Key> TGraphNodeType;
	typedef Graph<DependencyGraphNode, Edge, Key> TGraphType;
	typedef typename TGraphType::TGraphNode::ConnectionMap::Iterator ConnectionMapIterator;
	typedef typename TGraphNodeType::ConnectionPair TConnectionPair;
	typedef typename Edge::Flag EdgeFlag;

public:
	//!	The iterator of of dependency-graph node's connection
	struct ConnectionIterator {
		//!	The edge flag
		EdgeFlag mEdgeFlag;
		//!	The connection iterator
		ConnectionMapIterator mConnectionMapIterator;
		//!	The graph-node
		TGraphNodeType* mGraphNode;

		//! Constructor, create an iterator of the node.
		ConnectionIterator()
		    : mEdgeFlag(Edge::Unknown), mGraphNode(_null) {
		}
		//! Constructor, create an iterator of the node.
		ConnectionIterator(EdgeFlag edge_flag, const ConnectionMapIterator& connection_it, TGraphNodeType* graph_node)
		    : mEdgeFlag(edge_flag), mConnectionMapIterator(connection_it), mGraphNode(graph_node) {
		}

		//! Decrease the iterator, point to the previous node.
		//! @param		none
		_void operator--() {
			// Find the node by enumeration flag
			for (--mConnectionMapIterator; mConnectionMapIterator.IsValid(); mConnectionMapIterator--) {
				const Edge& edge = mConnectionMapIterator.GetObject().mObject2;

				// Skip for the none-compatible connections
				if (mEdgeFlag != Edge::_CONNECTION_FLAG_UNKNOWN && edge.mConnectionFlag != mEdgeFlag)
					continue;

				// We found the node
				return;
			}
		}
		//! Increase the iterator, point to the next node.
		//! @param		none
		_void operator++() {
			// Find the node by enumeration flag
			for (++mConnectionMapIterator; mConnectionMapIterator.IsValid(); ++mConnectionMapIterator) {
				const Edge& edge = mConnectionMapIterator.GetObject().mObject2;

				// Skip for the none-compatible connections
				if (mEdgeFlag != Edge::_CONNECTION_FLAG_UNKNOWN && edge.mConnectionFlag != mEdgeFlag)
					continue;

				// We found the node
				return;
			}
		}

		//! Type conversion, get the element.
		operator Type&() {
			return GetGraphNode()->GetElement().mElement;
		}
		//! Type conversion, get the element.
		operator const Type&() const {
			return GetGraphNode()->GetElement().mElement;
		}

		//! Type conversion, get the node.
		TGraphNodeType* GetGraphNode() {
			return mConnectionMapIterator.GetObject().mObject1;
		}
		//! Type conversion, get the node.
		const TGraphNodeType* GetGraphNode() const {
			return mConnectionMapIterator.GetObject().mObject1;
		}

		//!	Get the edge data.
		Edge& GetEdgeData() {
			return mConnectionMapIterator.GetObject().mObject2;
		}
		//!	Get the edge data.
		const Edge& GetEdgeData() const {
			return mConnectionMapIterator.GetObject().mObject2;
		}

		//!	Get the connection ID.
		_dword GetConnectionID() const {
			return mConnectionMapIterator.GetKey();
		}

		//! Check the iterator if it is valid.
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mConnectionMapIterator.IsValid();
		}
	};

public:
	/// <summary>
	/// The status of node.
	/// </summary>
	enum class Status {
		Suspend,
		Processing,
		Finished
	};

private:
	//!	The status
	Status mStatus;
	//!	The graph node
	TGraphNodeType* mGraphNode;
	//!	The element
	Type mElement;
	//!	The key
	Key mKey;

	//!	The graph
	TGraphType* mGraph;

public:
	DependencyGraphNode()
	    : mStatus(Status::Suspend), mGraphNode(_null), mGraph(_null) {
	}
	DependencyGraphNode(const Type& element, const Key& key, TGraphType* graph)
	    : mStatus(Status::Suspend), mGraphNode(_null), mElement(element), mKey(key), mGraph(graph) {
	}

public:
	//!	Bind graph node
	_void BindGraphNode(TGraphNodeType* node) {
		mGraphNode = node;
	}
	//!	Bind element.
	_void BindElement(const Type& element) {
		mElement = element;
	}

	//!	Get the connection iterator.
	ConnectionIterator GetConnectionIterator(EdgeFlag flags) const {
		for (ConnectionIterator it = mGraphNode->GetConnections().GetHeadIterator(); it.IsValid(); ++it) {
			const Edge& edge_data = it.GetObject().mObject2;

			if (edge_data.mConnectionFlag == flags)
				return ConnectionIterator(flags, it, mGraphNode);
		}

		return ConnectionIterator();
	}
	//!	Get the prerequisite iterator.
	ConnectionIterator GetPrerequisiteIterator() const {
		return GetConnectionIterator(EdgeFlag::Prerequisite);
	}
	//!	Get the subsequent iterator.
	ConnectionIterator GetSubsequentIterator() const {
		return GetConnectionIterator(EdgeFlag::Subsequent);
	}

	//! Finished.
	//! @param		none.
	//! @return		none.
	_void Finished() {
		// We finished this node ( passed )
		mStatus = Status::Finished;
	}
	//!	Start.
	//! @param		none.
	//! @return		none.
	_void Start() {
		mStatus = Status::Processing;
	}
	//!	Suspend.
	//! @param		none.
	//! @return		none.
	_void Suspend() {
		mStatus = Status::Suspend;
	}

	//!	Get the prerequisite nodes number.
	_dword GetPrerequisiteNodesNumber() const {
		// The activated node number
		_dword number = 0;

		// Put new targets into the array
		ConnectionIterator it = GetPrerequisiteIterator();
		for (; it.IsValid(); ++it) {
			// Get the child node
			TGraphNodeType* child_node = it.GetGraphNode();
			EGE_ASSERT(child_node != _null);

			// Check whether can start this node or not
			if (child_node->mElement->AllDependencyFinished()) {
				// Increase the activated nodes number
				number++;
			}
		}

		return number;
	}
	//!	Get the subsequent nodes number.
	_dword GetSubsequentNodesNumber() const {
		// The activated node number
		_dword number = 0;

		// Put new targets into the array
		ConnectionIterator it = GetSubsequentIterator();
		for (; it.IsValid(); ++it) {
			// Get the child node
			TGraphNodeType* child_node = it.GetGraphNode();
			EGE_ASSERT(child_node != _null);

			// Check whether can start this node or not
			if (child_node->mElement->AllDependencyFinished()) {
				// Increase the activated nodes number
				number++;
			}
		}

		return number;
	}

	//!	Check whether all dependency nodes have finished.
	//!	@param		none.
	//!	@return		True indicates all dependency nodes have finished.
	_ubool AllDependencyFinished() const {
		// Check whether all dependency had finished
		ConnectionIterator iterator = GetPrerequisiteIterator();
		for (; iterator.IsValid(); ++iterator) {
			// Get the prerequisite node
			const TGraphNodeType* node = iterator.GetGraphNode();
			EGE_ASSERT(node != _null);

			// Get the node status
			Status status = node->GetElement().GetStatus();
			ASSERT(status == Status::Suspend || status == Status::Processing || status == Status::Finished);

			// Check whether did we pass it or not
			if (status != Status::Finished)
				return _false;
		}

		return _true;
	}
	//!	Check whether all subsequents have finished.
	//!	@param		none.
	//!	@return		True indicates all subsequents have finished.
	_ubool AllSubsequentsFinished() const {
		// Check whether all dependency had finished
		ConnectionIterator iterator = GetSubsequentIterator();
		for (; iterator.IsValid(); ++iterator) {
			// Get the subsequent node
			const TGraphNodeType* node = iterator.GetGraphNode();
			EGE_ASSERT(node != _null);

			// Get the node status
			Status status = node->GetElement().GetStatus();
			ASSERT(status == Status::Suspend || status == Status::Processing || status == Status::Finished);

			// Check whether did we pass it or not
			if (status != Status::Finished)
				return _false;
		}

		return _true;
	}

	//!	Get the node's element.
	Type& GetElement() {
		return mElement;
	}
	//!	Get the node's element.
	const Type& GetElement() const {
		return mElement;
	}

	//!	Get the node's key.
	const Key& GetKey() const {
		return mKey;
	}
};

/// <summary>
/// This class is template container class, represents a dependency-graph.
/// </summary>
template <typename Type, typename Edge, typename Key>
class DependencyGraph {
	NO_COPY_OPERATIONS(DependencyGraph)

public:
	typedef DependencyGraph<Type, Edge, Key> TDependencyGraphType;
	typedef DependencyGraphNode<Type, Edge, Key> TDependencyGraphNode;
	typedef GraphNode<TDependencyGraphNode, Edge, Key> TGraphNodeType;
	typedef Array<TDependencyGraphNode*> TDependencyGraphNodePtrArray;
	typedef Graph<TDependencyGraphNode, Edge, Key> TGraphType;
	typedef DependencyGraphEdge::Flag EdgeFlag;

public:
	//! The iterator of graph class.
	struct Iterator {
		//!	The iterator of graph
		typename TGraphType::Iterator mIteratorOfGraph;

		//! Constructor, create an iterator of the graph.
		//! @param		none.
		Iterator() {
		}
		//! Constructor, create an iterator of the graph.
		//! @param		graph		The graph reference.
		//! @param		node		The graph node.
		Iterator(typename TGraphType::Iterator it_of_graph)
		    : mIteratorOfGraph(it_of_graph) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return ((TDependencyGraphNode&)mIteratorOfGraph).GetElement();
		}
		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator const Type&() const {
			return ((const TDependencyGraphNode&)mIteratorOfGraph).GetElement();
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return mIteratorOfGraph.IsValid();
		}

		//! decrease the iterator, point to the previous element of the graph.
		//! @param		none
		_void operator--() {
			--mIteratorOfGraph;
		}
		//! Increase the iterator, point to the next element of the graph.
		//! @param		none
		_void operator++() {
			++mIteratorOfGraph;
		}
	};

protected:
	//!	The internal dependency-graph
	TGraphType mGraph;

	//!	The root node of dependency-graph
	TDependencyGraphNode* mRootNode;

	//!	The none dependent nodes
	TDependencyGraphNodePtrArray mNoneDependentNodes;

protected:
	//!	Create root node.
	_void CreateRootNode();

	//!	Add none dependent node.
	_void AddNoneDependentNode(TDependencyGraphNode* node);

public:
	//! Constructor, create an empty graph.
	//! @param		none.
	DependencyGraph();
	//! Destructor, delete the graph, and release the memory used by nodes.
	//! @param		none
	~DependencyGraph();

public:
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

	//!	Get the none dependent nodes.
	//!	@param		none.
	//!	@return		The none dependent nodes.
	TDependencyGraphNodePtrArray& GetNoneDependentNodes();
	//!	Get the none dependent nodes.
	//!	@param		none.
	//!	@return		The none dependent nodes.
	const TDependencyGraphNodePtrArray& GetNoneDependentNodes() const;

	//!	Remove iterator.
	//!	@param		it		The iterator.
	//!	@return		The next iterator.
	Iterator RemoveIterator(Iterator it);

	//!	Get the root node.
	//! @param		none.
	//! @return		The root node.
	TDependencyGraphNode* GetRootNode();
	//!	Get the root node.
	//! @param		none.
	//! @return		The root node.
	const TDependencyGraphNode* GetRootNode() const;

	//!	Add a node.
	//! @param		element		The new element to be added.
	//! @param		key			The element key.
	//! @return		The graph node.
	TDependencyGraphNode* AddNode(const Type& element, const Key& key);
	//!	Remove node.
	//! @param		key				The element key.
	//! @param		auto_connect	Auto connect all subsequent nodes to prerequisite nodes.
	//! @return		True indicates removed successful.
	_ubool RemoveNode(const Key& key, _ubool auto_connect = true);

	//!	Get the node by key.
	//! @param		key			The element key.
	//! @return		The graph node.
	TDependencyGraphNode* GetNode(const Key& key);
	//!	Get the node by key.
	//! @param		key			The element key.
	//! @return		The graph node.
	const TDependencyGraphNode* GetNode(const Key& key) const;

	//!	Active node.
	//! @param		node	The target node.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool ActiveNode(TDependencyGraphNode* node);
	//!	Add prerequisite node.
	//! @param		target_node	The target node.
	//!	@param		node		The prerequisite node.
	//!	@param		passed		True indicates this node can be passed.
	//! @return		none.
	_void AddPrerequisiteNode(TDependencyGraphNode* target_node, TDependencyGraphNode* node, _ubool passed);

	//! Clear.
	//! @param		none.
	//!	@return		none.
	_void Clear();
};

template <typename Type, typename Edge, typename Key>
DependencyGraph<Type, Edge, Key>::DependencyGraph() {
	CreateRootNode();
	EGE_ASSERT(mRootNode != _null);
}

template <typename Type, typename Edge, typename Key>
DependencyGraph<Type, Edge, Key>::~DependencyGraph() {
	Clear();
}

template <typename Type, typename Edge, typename Key>
_void DependencyGraph<Type, Edge, Key>::CreateRootNode() {
	TGraphNodeType* node = mGraph.AddNode(TDependencyGraphNode(Type(), Key(), &mGraph), Key());
	EGE_ASSERT(node != _null);

	// Bind to dependency-graph-node
	mRootNode = &mGraph.GetNode(Key())->GetElement();
	mRootNode->BindGraphNode(node);

	// The root node is always in finished status
	mRootNode->Finished();
}

template <typename Type, typename Edge, typename Key>
_void DependencyGraph<Type, Edge, Key>::AddNoneDependentNode(TDependencyGraphNode* node) {
	EGE_ASSERT(node != _null);

	if (mNoneDependentNodes.Search(node).IsValid() == _false)
		mNoneDependentNodes.Append(node);
}

template <typename Type, typename Edge, typename Key>
_dword DependencyGraph<Type, Edge, Key>::Number() const {
	return mGraph.Number();
}

template <typename Type, typename Edge, typename Key>
typename DependencyGraph<Type, Edge, Key>::Iterator DependencyGraph<Type, Edge, Key>::GetHeadIterator() const {
	// Get the head iterator
	typename TGraphType::Iterator it_in_graph = mGraph.GetHeadIterator();
	if (it_in_graph.IsValid() == _false)
		return Iterator();

	// Skip for the root node
	if (it_in_graph.mIteratorOfMap.GetKey() == Key())
		++it_in_graph;

	return it_in_graph;
}

template <typename Type, typename Edge, typename Key>
typename DependencyGraph<Type, Edge, Key>::Iterator DependencyGraph<Type, Edge, Key>::GetTailIterator() const {
	// Get the tail iterator
	typename TGraphType::Iterator it_in_graph = mGraph.GetTailIterator();
	if (it_in_graph.IsValid() == _false)
		return Iterator();

	// Skip for the root node
	if (it_in_graph.mIteratorOfMap.GetKey() == Key())
		--it_in_graph;

	return it_in_graph;
}

template <typename Type, typename Edge, typename Key>
typename DependencyGraph<Type, Edge, Key>::Iterator DependencyGraph<Type, Edge, Key>::GetIterator(const Key& key) {
	return Iterator(mGraph.GetIterator(key));
}

template <typename Type, typename Edge, typename Key>
typename DependencyGraph<Type, Edge, Key>::TDependencyGraphNodePtrArray& DependencyGraph<Type, Edge, Key>::GetNoneDependentNodes() {
	return mNoneDependentNodes;
}

template <typename Type, typename Edge, typename Key>
const typename DependencyGraph<Type, Edge, Key>::TDependencyGraphNodePtrArray& DependencyGraph<Type, Edge, Key>::GetNoneDependentNodes() const {
	return mNoneDependentNodes;
}

template <typename Type, typename Edge, typename Key>
typename DependencyGraph<Type, Edge, Key>::Iterator DependencyGraph<Type, Edge, Key>::RemoveIterator(Iterator it) {
	Iterator next_it = it;
	++next_it;

	RemoveNode(it.mIteratorOfGraph.mIteratorOfMap.GetKey(), _true);

	return next_it;
}

template <typename Type, typename Edge, typename Key>
DependencyGraphNode<Type, Edge, Key>* DependencyGraph<Type, Edge, Key>::GetRootNode() {
	return mRootNode;
}

template <typename Type, typename Edge, typename Key>
const DependencyGraphNode<Type, Edge, Key>* DependencyGraph<Type, Edge, Key>::GetRootNode() const {
	return mRootNode;
}

template <typename Type, typename Edge, typename Key>
DependencyGraphNode<Type, Edge, Key>* DependencyGraph<Type, Edge, Key>::AddNode(const Type& element, const Key& key) {
	TGraphNodeType* node = mGraph.AddNode(TDependencyGraphNode(element, key, &mGraph), key);
	if (node == _null) {
		mGraph.RemoveNode(key);
		return _null;
	}

	// Bind to dependency-graph-node
	TDependencyGraphNode& dependency_node = mGraph.GetNode(key)->GetElement();
	dependency_node.BindGraphNode(node);

	return &dependency_node;
}

template <typename Type, typename Edge, typename Key>
_ubool DependencyGraph<Type, Edge, Key>::RemoveNode(const Key& key, _ubool auto_connect) {
	TDependencyGraphNode* node = GetNode(key);
	EGE_ASSERT(node != _null);

	// Remove it from none dependent nodes
	mNoneDependentNodes.Remove(node);

	// Remove it and auto connect all subsequent nodes to prerequisite nodes
	if (auto_connect) {
		// Get the prerequisite and subsequent iterators
		typename TDependencyGraphNode::ConnectionIterator prerequisite_it = node->GetPrerequisiteIterator();
		typename TDependencyGraphNode::ConnectionIterator subsequent_it = node->GetSubsequentIterator();

		// Connect prerequisite nodes to subsequent nodes
		for (; prerequisite_it.IsValid(); ++prerequisite_it) {
			TGraphNodeType* prerequisite_node = prerequisite_it.GetGraphNode();
			EGE_ASSERT(prerequisite_node != _null);

			// Remove all connections to node
			prerequisite_node->RemoveConnectionsByTargetNode(node->GetGraphNode());

			// Build a new connection between subsequent nodes and prerequisite node
			typename TDependencyGraphNode::ConnectionIterator subsequent_it_temp = subsequent_it;
			for (; subsequent_it_temp.IsValid(); ++subsequent_it_temp) {
				TGraphNodeType* subsequent_node = subsequent_it_temp.GetGraphNode();
				EGE_ASSERT(subsequent_node != _null);

				// Remove all connections to node
				subsequent_node->RemoveConnectionsByTargetNode(node->GetGraphNode());
				AddPrerequisiteNode(&subsequent_node->GetElement(), &prerequisite_node->GetElement(), prerequisite_node->GetElement().AllDependencyFinished());

				// Update node dependent nodes
				if (subsequent_node->GetElement().AllDependencyFinished())
					AddNoneDependentNode(&subsequent_node->GetElement());
			}
		}

		// Remove the specified node but skip to remove connections, because we have deal with that
		mGraph.RemoveNode(key);
	}
	// Remove all subsequent nodes
	else {
		// Get the subsequent iterator
		typename TDependencyGraphNode::ConnectionIterator it = node->GetSubsequentIterator();

		// Remove all subsequent nodes recursively
		for (; it.IsValid(); ++it) {
			TGraphNodeType* node = it.GetGraphNode();
			EGE_ASSERT(node != _null);

			if (RemoveNode(node->GetElement().GetKey(), auto_connect) == _false)
				return _false;
		}

		// Remove the specified node but skip to remove connections, because we have deal with that
		mGraph.RemoveNode(key);
	}

	return _true;
}

template <typename Type, typename Edge, typename Key>
DependencyGraphNode<Type, Edge, Key>* DependencyGraph<Type, Edge, Key>::GetNode(const Key& key) {
	TGraphNodeType* node = mGraph.GetNode(key);
	if (node == _null)
		return _null;

	return &node->GetElement();
}

template <typename Type, typename Edge, typename Key>
const DependencyGraphNode<Type, Edge, Key>* DependencyGraph<Type, Edge, Key>::GetNode(const Key& key) const {
	const TGraphNodeType* node = mGraph.GetNode(key);
	if (node == _null)
		return _null;

	return &node->GetElement();
}

template <typename Type, typename Edge, typename Key>
_ubool DependencyGraph<Type, Edge, Key>::ActiveNode(TDependencyGraphNode* node) {
	if (node == _null)
		return _false;

	// Make sure all the prerequisite nodes has active
	if (node->AllDependencyFinished() == _false)
		return _false;

	// We process this node ( passed )
	if (node->GetStatus() == TDependencyGraphNode::Status::Suspend)
		node->Start();

	// All the subsequent connections can be pass
	typename TDependencyGraphNode::ConnectionIterator subsequent_it = node->GetSubsequentIterator();
	for (; subsequent_it.IsValid(); ++subsequent_it) {
		const TGraphNodeType* subsequent_node = subsequent_it.GetGraphNode();
		EGE_ASSERT(subsequent_node != _null);

		if (subsequent_node->GetElement().AllDependencyFinished() == _false)
			continue;

		subsequent_it.GetEdgeData().mCanPass = _true;
	}

	// Update none dependent nodes except the root node
	if (node != mRootNode)
		AddNoneDependentNode(node);

	return _true;
}

template <typename Type, typename Edge, typename Key>
_void DependencyGraph<Type, Edge, Key>::AddPrerequisiteNode(TDependencyGraphNode* target_node, TDependencyGraphNode* node, _ubool passed) {
	if (target_node == _null || node == _null)
		return;

	// Add in/out-connections
	node->GetGraphNode()->AddConnection(target_node->GetGraphNode(), Edge(EdgeFlag::Prerequisite, passed));
	target_node->GetGraphNode()->AddConnection(node->GetGraphNode(), Edge(EdgeFlag::Subsequent, passed));

	// Update none dependent nodes
	if (target_node->AllDependencyFinished())
		AddNoneDependentNode(target_node);
}

template <typename Type, typename Edge, typename Key>
_void DependencyGraph<Type, Edge, Key>::Clear() {
	mGraph.Clear();
	mNoneDependentNodes.Clear();

	// Add the root node
	CreateRootNode();
	EGE_ASSERT(mRootNode != _null);
}

} // namespace EGE