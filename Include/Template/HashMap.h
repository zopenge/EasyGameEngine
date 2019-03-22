//! @file     HashMap.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// HashKeyConverterBase
//----------------------------------------------------------------------------

class HashKeyConverterBase {
public:
	template <typename Key>
	_dword operator()(const Key& key) const {
		return (_dword)key;
	}
};

//----------------------------------------------------------------------------
// HashStringKeyConverter
//----------------------------------------------------------------------------

class HashStringKeyConverter {
public:
	template <typename Key>
	_dword operator()(const Key& key) const {
		return key.GetCRCValue();
	}
};

//----------------------------------------------------------------------------
// HashRefStringObjKeyConverter
//----------------------------------------------------------------------------

class HashRefStringObjKeyConverter {
public:
	template <typename Key>
	_dword operator()(const Key& key) const {
		return key.GetID();
	}
};

//----------------------------------------------------------------------------
// HashMap
//----------------------------------------------------------------------------

//! This class is template container class, represents a hash table.
template <typename Type, typename Key, typename KeyConverter = HashKeyConverterBase>
class HashMap : public CountOf<> {
private:
	typedef Pair<Key, Type*> NodeInfoPair;
	typedef Array<NodeInfoPair> NodeInfoArray;

public:
	//!	The base iterator of hash
	struct IteratorBase {
		_int indexOfNodes;
		_int mNodesArrayIndex;
		HashMap* mHashMap;

		//! Constructor, create an iterator of the hash.
		IteratorBase(_int index_of_nodes = -1, _int index_of_nodes_array = -1, HashMap* hash_map = _null)
		    : indexOfNodes(index_of_nodes), mNodesArrayIndex(index_of_nodes_array), mHashMap(hash_map) {
		}

		//! Check the iterator if it is valid ( points to an available element ).
		//! @param		none
		//! @return		True if the iterator is valid, false otherwise.
		_ubool IsValid() const {
			return indexOfNodes != -1;
		}

		//! Type conversion, get the key reference.
		//! @param		none
		//! @return		Reference of the key.
		Key& GetKey() {
			return mHashMap->mNodeArrayChunks[mNodesArrayIndex][indexOfNodes].mObject1;
		}
		//! Type conversion, get the key reference.
		//! @param		none
		//! @return		Reference of the key.
		const Key& GetKey() const {
			return mHashMap->mNodeArrayChunks[mNodesArrayIndex][indexOfNodes].mObject1;
		}

		//! Type conversion, get the object reference.
		//! @param		none
		//! @return		Reference of the object.
		Type& GetObject() {
			return *mHashMap->mNodeArrayChunks[mNodesArrayIndex][indexOfNodes].mObject2;
		}
		//! Type conversion, get the object reference.
		//! @param		none
		//! @return		Reference of the object.
		const Type& GetObject() const {
			return *mHashMap->mNodeArrayChunks[mNodesArrayIndex][indexOfNodes].mObject2;
		}
	};

	//!	The iterator of hash
	struct Iterator : public IteratorBase {
		//! Constructor, create an iterator of the hash.
		Iterator(_int index_of_nodes = -1, _int index_of_nodes_array = -1, HashMap* hash_map = _null)
		    : IteratorBase(index_of_nodes, index_of_nodes_array, hash_map) {
		}

		//! Decrease the iterator, point to the previous element.
		//! @param		none
		_void operator--(_int) {
			if (this->indexOfNodes == -1)
				return;

			if (this->indexOfNodes == 0) {
				if (this->mNodesArrayIndex == 0) {
					this->indexOfNodes = -1;
				} else {
					while (this->mNodesArrayIndex >= 0) {
						if (this->mHashMap->mNodeArrayChunks[--this->mNodesArrayIndex].Number() > 0) {
							// Find the previous chunk array
							this->indexOfNodes = this->mHashMap->mNodeArrayChunks[this->mNodesArrayIndex].Number() - 1;
							return;
						}
					}

					// Finished
					this->mNodesArrayIndex = -1;
				}
			} else {
				this->indexOfNodes--;
			}
		}

		//! Increase the iterator, point to the next element.
		//! @param		none
		_void operator++(_int) {
			if (this->indexOfNodes == -1)
				return;

			if (this->indexOfNodes == (_int)this->mHashMap->mNodeArrayChunks[this->mNodesArrayIndex].Number() - 1) {
				if (this->mNodesArrayIndex == (_int)this->mHashMap->mDivisor - 1) {
					this->indexOfNodes = -1;
				} else {
					while (this->mNodesArrayIndex < (_int)this->mHashMap->mDivisor) {
						if (this->mHashMap->mNodeArrayChunks[++this->mNodesArrayIndex].Number() > 0) {
							// Find the next chunk array
							this->indexOfNodes = 0;
							return;
						}
					}

					// Finished
					this->mNodesArrayIndex = -1;
				}
			} else {
				this->indexOfNodes++;
			}
		}
	};

	//!	The chunk iterator of hash
	struct ChunkIterator : public IteratorBase {
		//! Constructor, create an iterator of the hash.
		ChunkIterator(_int index_of_nodes = -1, _int index_of_nodes_array = -1, HashMap* hash_map = _null)
		    : IteratorBase(index_of_nodes, index_of_nodes_array, hash_map) {
		}

		//! Decrease the iterator, point to the previous element.
		//! @param		none
		_void operator--(_int) {
			if (this->indexOfNodes == -1)
				return;

			if (this->indexOfNodes == 0)
				this->indexOfNodes = -1;
			else
				this->indexOfNodes--;
		}

		//! Increase the iterator, point to the next element.
		//! @param		none
		_void operator++(_int) {
			if (this->indexOfNodes == -1)
				return;

			if (this->indexOfNodes == (_int)this->mHashMap->mNodeArrayChunks[this->mNodesArrayIndex].Number() - 1)
				this->indexOfNodes = -1;
			else
				this->indexOfNodes++;
		}
	};

private:
	//! The divisor of the hash table, used to find a hash bucket.
	_dword mDivisor;
	//!	The node chunks
	NodeInfoArray* mNodeArrayChunks;

public:
	//! Constructor, create an empty hash table.
	//! @param		divisor		The divisor of the hash table.
	HashMap(_dword divisor);
	//! Copy-Constructor, create a hash table by copy from another one.
	HashMap(const HashMap<Type, Key, KeyConverter>& hash);
	//! Destructor, delete the hash table, and release the memory used by nodes.
	//! @param		none
	~HashMap();

public:
	//! Copy elements from another hash table.
	//! @param		hash		The other hash table.
	//! @return		The reference of current hash table.
	HashMap<Type, Key, KeyConverter>& operator=(const HashMap<Type, Key, KeyConverter>& hash);

	//! Get a mutable element reference by element key.
	//! @param		key			The key of element.
	//! @return		The mutable element reference.
	Type& operator[](const Key& key);

	//! Get the head iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get the tail iterator.
	//! @param		none
	//! @return		The head iterator.
	Iterator GetTailIterator() const;
	//! Get an iterator by the key of an element.
	//! @param		key			The key of element.
	//! @return		An iterator reference to the element.
	ChunkIterator GetIterator(const Key& key) const;

	//! Insert an element into the hash table by hash code that calculated from element key.
	//! @param		key			The key of element.
	//! @return		The new element.
	Type* Insert(const Key& key);
	//! Insert an element into the hash table by hash code that calculated from element key.
	//! @param		element		The new element to be inserted into.
	//! @param		key			The key of element.
	//! @return		The new element.
	Type* Insert(const Type& element, const Key& key);
	//! Remove an element from the hash table, the element is specified by an iterator.
	//! @param		iterator	The iterator specifies a position.
	//!	@return		none.
	Iterator Remove(Iterator& iterator);
	//! Remove an element from the hash table, the element is specified by element key.
	//! @param		key			The key of element.
	//!	@return		none.
	Iterator Remove(const Key& key);

	//! Clear hash table and delete all memory used by nodes.
	//! @param		none
	//!	@return		none.
	_void Clear();
	//! Clear hash table and delete all memory used by nodes.
	//! @param		divisor		The divisor of the hash table.
	//!	@return		none.
	_void Clear(_dword divisor);
};

//----------------------------------------------------------------------------
// Hash Implementation
//----------------------------------------------------------------------------

template <typename Type, typename Key, typename KeyConverter>
HashMap<Type, Key, KeyConverter>::HashMap(_dword divisor) {
	EGE_ASSERT(divisor > 0);

	mDivisor = divisor;
	mNodeArrayChunks = new NodeInfoArray[mDivisor];
}

template <typename Type, typename Key, typename KeyConverter>
HashMap<Type, Key, KeyConverter>::HashMap(const HashMap<Type, Key, KeyConverter>& hash) {
	mDivisor = hash.mDivisor;
	mNumber = hash.mNumber;
	mNodeArrayChunks = new NodeInfoArray[mDivisor];

	for (_dword i = 0; i < mDivisor; i++) {
		NodeInfoArray& des_nodes = mNodeArrayChunks[i];
		const NodeInfoArray& src_nodes = hash.mNodeArrayChunks[i];

		for (_dword j = 0; j < src_nodes.Number(); j++) {
			Type* element = new Type(src_nodes[j].mObject2);

			des_nodes.Append(NodeInfoPair(src_nodes[j].mObject1, element));
		}
	}
}

template <typename Type, typename Key, typename KeyConverter>
HashMap<Type, Key, KeyConverter>::~HashMap() {
	for (_dword i = 0; i < mDivisor; i++) {
		NodeInfoArray& nodes = mNodeArrayChunks[i];

		for (_dword j = 0; j < nodes.Number(); j++)
			EGE_DELETE(nodes[j].mObject2);
	}

	EGE_DELETE_ARRAY(mNodeArrayChunks);
}

template <typename Type, typename Key, typename KeyConverter>
HashMap<Type, Key, KeyConverter>& HashMap<Type, Key, KeyConverter>::operator=(const HashMap<Type, Key, KeyConverter>& hash) {
	Clear(hash.mDivisor);

	mNumber = hash.mNumber;

	for (_dword i = 0; i < mDivisor; i++) {
		NodeInfoArray& des_nodes = mNodeArrayChunks[i];
		const NodeInfoArray& src_nodes = hash.mNodeArrayChunks[i];

		for (_dword j = 0; j < src_nodes.Number(); j++) {
			Type* element = new Type(src_nodes[j].mObject2);

			des_nodes.Append(NodeInfoPair(src_nodes[j].mObject1, element));
		}
	}

	return *this;
}

template <typename Type, typename Key, typename KeyConverter>
Type& HashMap<Type, Key, KeyConverter>::operator[](const Key& key) {
	// Search for the existing element
	ChunkIterator it = GetIterator(key);
	if (it.IsValid())
		return it.GetObject();

	// Insert a new element
	Type* element = Insert(key);
	EGE_ASSERT(element != _null);

	return *element;
}

template <typename Type, typename Key, typename KeyConverter>
typename HashMap<Type, Key, KeyConverter>::Iterator HashMap<Type, Key, KeyConverter>::GetHeadIterator() const {
	for (_dword i = 0; i < mDivisor; i++) {
		NodeInfoArray& nodes = mNodeArrayChunks[i];

		if (nodes.Number() == 0)
			continue;

		return Iterator(0, i, (HashMap*)this);
	}

	return Iterator();
}

template <typename Type, typename Key, typename KeyConverter>
typename HashMap<Type, Key, KeyConverter>::Iterator HashMap<Type, Key, KeyConverter>::GetTailIterator() const {
	for (_int i = (_int)mDivisor - 1; i >= 0; i--) {
		NodeInfoArray& nodes = mNodeArrayChunks[i];

		if (nodes.Number() == 0)
			continue;

		return Iterator(nodes.Number() - 1, i, (HashMap*)this);
	}

	return Iterator();
}

template <typename Type, typename Key, typename KeyConverter>
typename HashMap<Type, Key, KeyConverter>::ChunkIterator HashMap<Type, Key, KeyConverter>::GetIterator(const Key& key) const {
	// Calculate hash code from key
	_dword hashcode = (_dword)KeyConverter()(key);
	_dword index_of_arrays = hashcode % mDivisor;

	// Get the nodes by hash code
	NodeInfoArray& nodes = mNodeArrayChunks[index_of_arrays];

	// Find node by key
	for (_dword i = 0; i < nodes.Number(); i++) {
		if (nodes[i].mObject1 == key)
			return ChunkIterator(i, index_of_arrays, (HashMap*)this);
	}

	return ChunkIterator();
}

template <typename Type, typename Key, typename KeyConverter>
Type* HashMap<Type, Key, KeyConverter>::Insert(const Key& key) {
	// Calculate hash code from key
	_dword hashcode = (_dword)KeyConverter()(key);
	_dword index_of_arrays = hashcode % mDivisor;

	// Get the nodes by hash code
	NodeInfoArray& nodes = mNodeArrayChunks[index_of_arrays];

	// Append element
	Type* element = new Type();
	nodes.Append(NodeInfoPair(key, element));

	// Increase the number of nodes
	CountOf<>::Increase();

	return element;
}

template <typename Type, typename Key, typename KeyConverter>
Type* HashMap<Type, Key, KeyConverter>::Insert(const Type& element, const Key& key) {
	// Calculate hash code from key
	_dword hashcode = (_dword)KeyConverter()(key);
	_dword index_of_arrays = hashcode % mDivisor;

	// Get the nodes by hash code
	NodeInfoArray& nodes = mNodeArrayChunks[index_of_arrays];

	// Append element
	Type* new_element = new Type(element);
	nodes.Append(NodeInfoPair(key, new_element));

	// Increase the number of nodes
	CountOf<>::Increase();

	return element;
}

template <typename Type, typename Key, typename KeyConverter>
typename HashMap<Type, Key, KeyConverter>::Iterator HashMap<Type, Key, KeyConverter>::Remove(Iterator& iterator) {
	return Remove(iterator.GetKey());
}

template <typename Type, typename Key, typename KeyConverter>
typename HashMap<Type, Key, KeyConverter>::Iterator HashMap<Type, Key, KeyConverter>::Remove(const Key& key) {
	// Calculate hash code from key
	_dword hashcode = (_dword)KeyConverter()(key);
	_dword index_of_arrays = hashcode % mDivisor;

	// Get the nodes by hash code
	NodeInfoArray& nodes = mNodeArrayChunks[index_of_arrays];

	// Remove it from array
	for (_dword i = 0; i < nodes.Number(); i++) {
		if (nodes[i].mObject1 == key) {
			EGE_DELETE(nodes[i].mObject2);
			nodes.RemoveByIndex(i);

			// Decrease the number of nodes
			CountOf<>::Decrease();

			return Iterator(index_of_arrays, i, this);
		}
	}

	return Iterator();
}

template <typename Type, typename Key, typename KeyConverter>
_void HashMap<Type, Key, KeyConverter>::Clear() {
	Clear(mDivisor);
}

template <typename Type, typename Key, typename KeyConverter>
_void HashMap<Type, Key, KeyConverter>::Clear(_dword divisor) {
	// Clear arrays
	for (_dword i = 0; i < mDivisor; i++) {
		NodeInfoArray& nodes = mNodeArrayChunks[i];

		for (_dword j = 0; j < nodes.Number(); j++)
			EGE_DELETE(nodes[j].mObject2);
	}

	EGE_DELETE_ARRAY(mNodeArrayChunks);

	mDivisor = divisor;
	mNodeArrayChunks = new NodeInfoArray[mDivisor];

	CountOf<>::Clear();
}

} // namespace EGE