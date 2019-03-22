//! @file     Map.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

template <typename Key>
_int CompareKeyInMap(const Key& key1, const Key& key2);

//----------------------------------------------------------------------------
// Map
//----------------------------------------------------------------------------

//! This class is template container class, represents a map in red-black tree.
template <typename Type, typename Key>
class Map {
public:
	typedef Pair<Key, Type> PairType;

public:
	//!	The key compare function
	struct CompareFunc : public BinaryFunction<PairType, PairType> {
		//!	Process compare operation.
		_int operator()(const PairType& v1, const PairType& v2) const {
			return CompareKeyInMap(v1.mObject1, v2.mObject1);
		}
		_int operator()(const PairType& v1, const Key& key) const {
			return CompareKeyInMap(v1.mObject1, key);
		}
	};

public:
	typedef RBTree<PairType, CompareFunc> MapRBTree;

public:
	//!	The iterator of map
	struct Iterator : public MapRBTree::Iterator {
		//! Constructor, create an iterator of the map.
		Iterator()
		    : MapRBTree::Iterator(_null, _null) {
		}
		//! Constructor, create an iterator of the map.
		Iterator(typename MapRBTree::Iterator it)
		    : MapRBTree::Iterator(it) {
		}

		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator Type&() {
			return ((PairType&)*this).mObject2;
		}
		//! Type conversion, get the element reference.
		//! @param		none
		//! @return		Reference of the element.
		operator const Type&() {
			return ((const PairType&)*this).mObject2;
		}

		//! Type conversion, get the pair reference.
		//! @param		none
		//! @return		Reference of the pair.
		operator PairType&() {
			return (PairType&)this->mNode->mElement;
		}
		//! Type conversion, get the pair reference.
		//! @param		none
		//! @return		Reference of the pair.
		operator const PairType&() const {
			return (const PairType&)this->mNode->mElement;
		}

		//! Type conversion, get the key reference.
		//! @param		none
		//! @return		Reference of the key.
		Key& GetKey() {
			return ((PairType&)*this).mObject1;
		}
		//! Type conversion, get the key reference.
		//! @param		none
		//! @return		Reference of the key.
		const Key& GetKey() const {
			return ((const PairType&)*this).mObject1;
		}

		//! Type conversion, get the object reference.
		//! @param		none
		//! @return		Reference of the object.
		Type& GetObject() {
			return ((PairType&)*this).mObject2;
		}
		//! Type conversion, get the object reference.
		//! @param		none
		//! @return		Reference of the object.
		const Type& GetObject() const {
			return ((const PairType&)*this).mObject2;
		}
	};

private:
	//!	The RB-Trees of map
	MapRBTree mRBTrees;

public:
	Map();
	Map(const Map<Type, Key>& map);
	~Map();

public:
	//! Copy elements from another map.
	//! @param		map			The other map.
	//! @return		The reference of current map.
	Map<Type, Key>& operator=(const Map<Type, Key>& map);

	//! Get a mutable element reference by element key.
	//! @param		key			The key of element.
	//! @return		The mutable element reference.
	Type& operator[](const Key& key);

	//! Get the current number of elements in the map.
	//! @param		none
	//! @return		The current number of elements in map.
	_dword Number() const;

	//! Get the head iterator.
	//! @param		none.
	//! @return		The head iterator.
	Iterator GetHeadIterator() const;
	//! Get an iterator by the key of an element.
	//! @param		key			The key of element.
	//! @return		An iterator reference to the element.
	Iterator GetIterator(const Key& key);

	//! Check whether has element with specified key.
	//! @param		key			The key of element.
	//! @return		True indicates contains the element with specified key.
	_ubool HasKey(const Key& key) const;

	//! Get an element pointer by element key.
	//! @param		key			The key of element.
	//! @return		The pointer to a element if the key is valid, null otherwise.
	Type* Search(const Key& key);
	//! Get an element pointer by element key.
	//! @param		key			The key of element.
	//! @return		The pointer to a element if the key is valid, null otherwise.
	const Type* Search(const Key& key) const;

	//! Insert an element into the map.
	//! @param		key			The key of element.
	//! @return		The new element.
	Type* Insert(const Key& key);
	//! Insert an element into the map.
	//! @param		element		The new element to be inserted into.
	//! @param		key			The key of element.
	//! @return		The new element.
	Type* Insert(const Type& element, const Key& key);
	//! Remove an element from the map, the element is specified by an iterator.
	//! @param		iterator	The iterator specifies a position.
	//!	@return		The next iterator.
	Iterator Remove(Iterator iterator);
	//! Remove an element from the map, the element is specified by element key.
	//! @param		key			The key of element.
	//!	@return		True indicates remove it successful.
	_ubool Remove(const Key& key);

	//! Clear map and delete all memory used by nodes.
	//! @param		none
	//!	@return		none.
	_void Clear();
};

//----------------------------------------------------------------------------
// Map Implementation
//----------------------------------------------------------------------------

template <typename Type, typename Key>
Map<Type, Key>::Map() {
}

template <typename Type, typename Key>
Map<Type, Key>::Map(const Map<Type, Key>& map) {
	mRBTrees = map.mRBTrees;
}

template <typename Type, typename Key>
Map<Type, Key>::~Map() {
}

template <typename Type, typename Key>
Map<Type, Key>& Map<Type, Key>::operator=(const Map<Type, Key>& map) {
	Clear();

	mRBTrees = map.mRBTrees;

	return *this;
}

template <typename Type, typename Key>
Type& Map<Type, Key>::operator[](const Key& key) {
	// Search for the existing element
	typename MapRBTree::Iterator it = mRBTrees.Search(key);
	if (it.IsValid())
		return ((PairType&)it).mObject2;

	// Insert a new element
	Type* element = Insert(key);
	EGE_ASSERT(element != _null);

	return *element;
}

template <typename Type, typename Key>
_dword Map<Type, Key>::Number() const {
	return mRBTrees.Number();
}

template <typename Type, typename Key>
typename Map<Type, Key>::Iterator Map<Type, Key>::GetHeadIterator() const {
	return Iterator(mRBTrees.GetHeadIterator());
}

template <typename Type, typename Key>
typename Map<Type, Key>::Iterator Map<Type, Key>::GetIterator(const Key& key) {
	// Search the element by key
	typename MapRBTree::Iterator tree_it = mRBTrees.Search(key);
	if (tree_it.IsValid() == _false)
		return Iterator();

	// Feedback the iterator of map
	return Iterator(tree_it);
}

template <typename Type, typename Key>
_ubool Map<Type, Key>::HasKey(const Key& key) const {
	return mRBTrees.Search(key).IsValid();
}

template <typename Type, typename Key>
Type* Map<Type, Key>::Search(const Key& key) {
	typename MapRBTree::Iterator it = mRBTrees.Search(key);
	if (it.IsValid() == _false)
		return _null;

	return &it.mNode->mElement.mObject2;
}

template <typename Type, typename Key>
const Type* Map<Type, Key>::Search(const Key& key) const {
	typename MapRBTree::Iterator it = mRBTrees.Search(key);
	if (it.IsValid() == _false)
		return _null;

	return &it.mNode->mElement.mObject2;
}

template <typename Type, typename Key>
Type* Map<Type, Key>::Insert(const Key& key) {
	EGE_ASSERT(mRBTrees.Search(key).IsValid() == _false);

	// Insert the element into RB-Tree
	typename MapRBTree::Iterator tree_it = mRBTrees.Insert(key);
	if (tree_it.IsValid() == _false)
		return _null;

	return &((PairType&)tree_it).mObject2;
}

template <typename Type, typename Key>
Type* Map<Type, Key>::Insert(const Type& element, const Key& key) {
	EGE_ASSERT(mRBTrees.Search(key).IsValid() == _false);

	// Insert the element into RB-Tree
	typename MapRBTree::Iterator tree_it = mRBTrees.Insert(PairType(key, element));
	if (tree_it.IsValid() == _false)
		return _null;

	return &((PairType&)tree_it).mObject2;
}

template <typename Type, typename Key>
typename Map<Type, Key>::Iterator Map<Type, Key>::Remove(Iterator iterator) {
	EGE_ASSERT(iterator.IsValid());

	typename MapRBTree::Iterator it = mRBTrees.Search(iterator.mNode->mElement);
	if (it.IsValid() == _false)
		return Map<Type, Key>::Iterator();

	return mRBTrees.Remove(it);
}

template <typename Type, typename Key>
_ubool Map<Type, Key>::Remove(const Key& key) {
	return mRBTrees.Remove(key);
}

template <typename Type, typename Key>
_void Map<Type, Key>::Clear() {
	// Clear RB-Tree
	mRBTrees.Clear();
}

} // namespace EGE