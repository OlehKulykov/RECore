/*
 *   Copyright (c) 2012 - 2015 Kulykov Oleh <info@resident.name>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */


#ifndef __REMAP_H__
#define __REMAP_H__


#include "RECore.h"

#include <string.h>

#if defined(HAVE_ASSERT_H)
#include <assert.h>
#endif

/**
 @brief Map class template.
 */
template <typename TK, typename TV>
class __RE_PUBLIC_CLASS_API__ REMap
{
public:
	/**
	 @brief Class of map node.
	 */
	class Node;

private:
	class NodeBase
	{
	public:
		Node * next;
		Node * previous;
		NodeBase() : next(NULL), previous(NULL) { }
	};

public:
	/**
	 @brief Map node class. Containes key and value object.
	 */
	class Node : public NodeBase
	{
	public:
		TK key;
		TV value;
		Node(const TK & newKey, const TV & newValue) : NodeBase(), key(newKey), value(newValue) { }
	};


	/**
	 @brief Node pointer type.
	 */
	typedef Node * NodePtr;


	/**
	 @brief Node creator callback type. With key and value.
	 @param Key value.
	 @param Value.
	 */
	typedef NodePtr (*CreateNodeCallback)(const TK & newKey, const TV & newValue);


	/**
	 @brief Release node callback type.
	 @param Node pointer.
	 */
	typedef void (*ReleaseNodeCallback)(NodePtr);
private:
	CreateNodeCallback _createNode;
	ReleaseNodeCallback _releaseNode;
	union
	{
		NodeBase * _head;
		Node * _castHead;
	};
protected:
	Node * addNewNodeWithKeyValue(const TK & newKey, const TV & newValue)
	{
		Node * newNode = _createNode(newKey, newValue);
		if (newNode)
		{
			newNode->previous = _head->previous;
			newNode->previous->next = newNode;
			_head->previous = newNode;
			newNode->next = _castHead;
		}
		return newNode;
	}
public:
	/**
	 @brief Default node creator callback.
	 @detailed Create node with "new" operator.
	 @param newKey Node key.
	 @param newValue Node value.
	 @return Pointer to created node.
	 */
	static NodePtr newNode(const TK & newKey, const TV & newValue)
	{
		return (new Node(newKey, newValue));
	}


	/**
	 @brief Default node release callback.
	 @detailed Release node with "delete" operator.
	 @param node Node pointer.
	 */
	static void deleteNode(NodePtr node)
	{
		delete node;
	}


	/**
	 @brief Node allocator callback.
	 @detailde Create node with "malloc" function.
	 @param newKey Node key.
	 @param newValue Node value.
	 @return Pointer to created node.
	 */
	static NodePtr allocateNode(const TK & newKey, const TV & newValue)
	{
		NodePtr node = (NodePtr)malloc(sizeof(Node));
#if defined(HAVE_ASSERT_H)
		assert(node);
#endif
		if (node)
		{
			node->key = newKey;
			node->value = newValue;
		}
		return node;
	}


	/**
	 @brief Node release callback.
	 @detailed Release node with "free" function.
	 @param node Node pointer.
	 */
	static void freeNode(NodePtr node)
	{
		free(node);
	}

public:
	/**
	 @brief Map iterator class.
	 */
	class Iterator
	{
	private:
		Node * _head;
		Node * _node;
	public:
		/**
		 @brief Move to next map key-pair.
		 @return True if moved to next key-pari, othervice false.
		 */
		bool next()
		{
			_node = _node ? _node->next : this->_head->next;
			return _node != this->_head;
		}


		/**
		 @brief Getter for current node pointer.
		 @return Current node pointer.
		 */
		Node * node() const
		{
			return _node;
		}


		/**
		 @brief Getter for current node key object.
		 @return Address of the key.
		 */
		const TK & key() const
		{
			return _node->key;
		}


		/**
		 @brief Getter for current node value.
		 @return Address of the value.
		 */
		const TV & value() const
		{
			return _node->value;
		}


		/**
		 @brief Constructs iterator with another iterator object.
		 @param it Another iterator object.
		 */
		Iterator(const Iterator & it) :
		_head(it._head),
		_node(NULL)
		{

		}


		/**
		 @brief Contructs iterator node pointer.
		 @param listHead Pointer to node.
		 */
		Iterator(Node * listHead) :
		_head(listHead),
		_node(NULL)
		{

		}
	};


	/**
	 @brief Creates new iterator object.
	 @return New iterator.
	 */
	Iterator iterator() const
	{
		return Iterator(this->_castHead);
	}

	/**
	 @brief Check is map has no key-pairs.
	 @return True if there is no key-pairs, othervice false.
	 */
	bool isEmpty() const
	{
		return (this->_head->next == this->_head);
	}


	/**
	 @brief Removes all key-pairs from map.
	 */
	void clear()
	{
		Node * node = this->_head->next;
		while (node != this->_head)
		{
			node = this->removeNode(node);
		}
	}


	/**
	 @brief Calculates count of the list by iterating all elements.
	 @return Count of the elements.
	 */
	RESizeT count() const
	{
		RESizeT c = 0;
		Node * next = this->_head->next;
		while (next != this->_head)
		{
			c++;
			next = next->next;
		}
		return c;
	}


	/**
	 @brief Find node by key object.
	 @detailed Comparing key objects using "==" operator.
	 @param key The key object.
	 @return Node pointer or NULL if not found.
	 */
	Node * findNode(const TK & key) const
	{
		Node * next = this->_head->next;
		while (next != this->_head)
		{
			if (next->key == key)
			{
				return next;
			}
			next = next->next;
		}
		return NULL;
	}


	/**
	 @brief Check map containes key-pair by key object.
	 @detailed Comparing key objects using "==" operator.
	 @param key The key object.
	 @return True if have key-pair with the key, othervice false.
	 */
	bool isContainesKey(const TK & key) const
	{
		return this->findNode(key) ? true : false;
	}


	/**
	 @brief Removes node from map and returns next node pointer.
	 @detailed Can be used during iterating.
	 @param node The node pointer for remove.
	 @return Next node pointer.
	 */
	Node * removeNode(Node * node)
	{
		if (node != this->_head)
		{
			Node * next = node->next;
			node->previous->next = node->next;
			node->next->previous = node->previous;
			_releaseNode(node);
			return next;
		}
		return this->_castHead;
	}


	/**
	 @brief Set new value for key-pair by key or create new key-pair.
	 @param newKey The key.
	 @param newValue The value.
	 @return True if value by key is updated or successfully created and added new key-pair.
	 */
	bool setKeyValue(const TK & newKey, const TV & newValue)
	{
		Node * node = this->findNode(newKey);
		if (node)
		{
			node->value = newValue;
			return true;
		}
		return this->add(newKey, newValue);
	}


	/**
	 @brief Add new key-pair to map without checking existance key-pair with specific key object.
	 @param newKey The key.
	 @param newValue The value.
	 @return True if added new key-pair, othervice false.
	 */
	bool add(const TK & newKey, const TV & newValue)
	{
		return this->addNewNodeWithKeyValue(newKey, newValue) ? true : false;
	}


	/**
	 @brief Constructs new map.
	 @param nodeCreator Map node creator callback, if no assigned - using default callback with "new" operator.
	 @param nodeReleaser Map node release callback, if no assigned - using default callback with "new" operator.
	 */
	REMap(CreateNodeCallback nodeCreator = &newNode,
		  ReleaseNodeCallback nodeReleaser = &deleteNode) :
	_createNode(nodeCreator),
	_releaseNode(nodeReleaser),
	_head(NULL)
	{
		NodeBase * newHead = (NodeBase *)malloc(sizeof(NodeBase));
#if defined(HAVE_ASSERT_H)
		assert(newHead);
#endif
		if (newHead)
		{
			this->_head = newHead;
			this->_head->next = this->_castHead;
			this->_head->previous = this->_castHead;
		}
	}


	/**
	 @brief Default map virtual desctructor.
	 */
	virtual ~REMap()
	{
		this->clear();
		if (this->_head)
		{
			free(this->_head);
		}
	}
};

#endif

