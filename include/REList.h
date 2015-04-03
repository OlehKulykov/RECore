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


#ifndef __RELIST_H__
#define __RELIST_H__

#include "RECore.h"

/**
 @brief Class template for list.
 */
template <typename T>
class __RE_PUBLIC_CLASS_API__ REList
{
public:
	/**
	 @brief Class of list node.
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
	 @brief Class of list node.
	 @detailed Holds value and pointer to prev. & next nodes.
	 */
	class Node : public NodeBase
	{
	public:
		T value;
		Node(const T & newValue) : NodeBase(), value(newValue) { }
	};


	/**
	 @brief Type of list values comparation results.
	 */
	typedef enum
	{
		/**
		 @brief Left operand is lest then right.
		 */
		Descending = -1,


		/**
		 @brief Left and right operands are the same.
		 */
		Same = 0,


		/**
		 @brief Left operand is greater then right.
		 */
		Ascending = 1
	}
	/**
	 @brief Type of list values comparation results.
	 */
	ValueCompareResult;


	/**
	 @brief Define pointer to list node.
	 */
	typedef Node * NodePtr;


	/**
	 @brief Define node creator callback function with default value.
	 @param newValue Const address to new node value.
	 */
	typedef NodePtr (*CreateNodeCallback)(const T & newValue);


	/**
	 @brief Define node destructor callback function with node pointer.
	 @param Pointer to list node.
	 */
	typedef void (*ReleaseNodeCallback)(NodePtr);


	/**
	 @brief Define node values comparator callback function.
	 @param left Pointer to left value.
	 @param right Pointer to right value.
	 */
	typedef ValueCompareResult (*NodeValuesComparator)(const T * left, const T * right);


	/**
	 @brief Define node values comparator callback function.
	 @param left Pointer to left value.
	 @param right Pointer to custom right value.
	 */
	typedef ValueCompareResult (*CustomNodeValueComparator)(const T * nodeValue, void * customValue);
private:
	CreateNodeCallback _createNode;
	ReleaseNodeCallback _releaseNode;
	union
	{
		NodeBase * _head;
		Node * _castHead;
	};

public:
	/**
	 @brief Default node creator static method callback.
	 @detailed Create node with "new" operator.
	 @param newValue Default node value.
	 @return Pointer to created node with value.
	 */
	static NodePtr newNode(const T & newValue)
	{
		return (new Node(newValue));
	}


	/**
	 @brief Default node destructor static method callback.
	 @detailed Release node with "delete" operator.
	 @param node Pointer to node.
	 */
	static void deleteNode(NodePtr node)
	{
		delete node;
	}


	/**
	 @brief Node creator static method callback.
	 @detailed Allocate node with "malloc" function.
	 @param newValue Default node value.
	 @return Pointer to allocated node with value.
	 */
	static NodePtr allocateNode(const T & newValue)
	{
		NodePtr node = (NodePtr)malloc(sizeof(Node));
		if (node)
		{
			node->value = newValue;
		}
		return node;
	}


	/**
	 @brief Node destructor static method callback.
	 @detailed Release node with "free" function.
	 @param node Pointer to node.
	 */
	static void freeNode(NodePtr node)
	{
		free(node);
	}

public:
	/**
	 @brief Iterator class for list values.
	 */
	class Iterator
	{
	private:
		Node * _head;
		Node * _node;
	public:
		/**
		 * @brief Move to next list node.
		 * @return True if moved next, othervice false.
		 */
		bool next()
		{
			_node = _node ? _node->next : this->_head->next;
			return _node != this->_head;
		}


		/**
		 @brief Getter for node pointer.
		 @return Pointer to current list node.
		 */
		Node * node() const
		{
			return _node;
		}


		/**
		 @brief Getter for current node value.
		 @return Const address for current value.
		 */
		const T & value() const
		{
			return _node->value;
		}


		/**
		 @brief Constructs iterator with another iterator.
		 @param it Another iterator.
		 */
		Iterator(const Iterator & it) :
		_head(it._head),
		_node(NULL)
		{

		}


		/**
		 @brief Constructs iterator with pointer to list head node.
		 @detailed Need for internal list implementation.
		 @param listHead Pointer to list head node.
		 */
		Iterator(Node * listHead) :
		_head(listHead),
		_node(NULL)
		{

		}
	};


	/**
	 @brief Creates new list iterator object.
	 @return New iterator.
	 */
	Iterator iterator() const
	{
		return Iterator(this->_castHead);
	}


	/**
	 @brief Check list containes any values.
	 @return True if there is no values, othervice false.
	 */
	bool isEmpty() const
	{
		return (this->_head->next == this->_head);
	}


	/**
	 @brief Removes all list values.
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
	 @brief Locate node with same value described as void pointer.
	 @param customValue Void pointer to searched value.
	 @param comparator Values comparator callback
	 @return Pointer to node contained same value or NULL if there is such values in list.
	 */
	Node * findNode(void * customValue, CustomNodeValueComparator comparator) const
	{
		Node * next = this->_head->next;
		while (next != this->_head)
		{
			if (comparator(&next->value, customValue) == Same)
			{
				return next;
			}
			next = next->next;
		}
		return NULL;
	}


	/**
	 @brief Locate node with same value as parameter.
	 @param value The value to be located in list.
	 @param comparator Conparator callback for comparing 2 values.
	 @return Pointer to node contained same value or NULL if there is such values in list.
	 */
	Node * findNode(const T & value, NodeValuesComparator comparator) const
	{
		Node * next = this->_head->next;
		while (next != this->_head)
		{
			if (comparator(&next->value, &value) == Same)
			{
				return next;
			}
			next = next->next;
		}
		return NULL;
	}


	/**
	 @brief Locate node with same value as parameter.
	 @param value The value to be located in list. For comparing values used "==" operator.
	 @return Pointer to node contained same value or NULL if there is such values in list.
	 */
	Node * findNode(const T & value) const
	{
		Node * next = this->_head->next;
		while (next != this->_head)
		{
			if (next->value == value)
			{
				return next;
			}
			next = next->next;
		}
		return NULL;
	}


	/**
	 @brief Check is list containes some value.
	 @param value The value to be finded in list.
	 @return True if such value containes in list, othervice false.
	 */
	bool isContaines(const T & value) const
	{
		return this->findNode(value) ? true : false;
	}


	/**
	 @brief Removes node from list. Can be removed during iterating.
	 @param node The node pointer.
	 @return Pointer to the next node.
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
	 @brief Adds value to the list.
	 @param newValue The new value to add.
	 @return True if value was added, othervice false.
	 */
	bool add(const T & newValue)
	{
		Node * newNode = _createNode(newValue);
		if (newNode)
		{
			newNode->previous = _head->previous;
			newNode->previous->next = newNode;
			_head->previous = newNode;
			newNode->next = _castHead;
			return true;
		}
		return false;
	}

	/**
	 @brief Construct list object
	 @param nodeCreator Node creator callback, if no assigned will use default callback(create node with "new" operator).
	 @param nodeReleaser Node destructor callback, if no assigned will use default callback(delete node with "delete" operator).
	 */
	REList(CreateNodeCallback nodeCreator = &newNode,
		   ReleaseNodeCallback nodeReleaser = &deleteNode) :
	_createNode(nodeCreator),
	_releaseNode(nodeReleaser),
	_head(NULL)
	{
		NodeBase * newHead = (NodeBase *)malloc(sizeof(NodeBase));
		if (newHead)
		{
			this->_head = newHead;
			this->_head->next = this->_castHead;
			this->_head->previous = this->_castHead;
		}
	}


	/**
	 * @brief Default virtual desctructor.
	 */
	virtual ~REList()
	{
		this->clear();
		if (this->_head)
		{
			free(this->_head);
		}
	}
};


#endif


