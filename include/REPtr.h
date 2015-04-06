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


#ifndef __REPTR_H__
#define __REPTR_H__

#include "RECore.h"

#include <string.h>

/**
 @brief Class template of autopointer.
 @detailed Holds created pointer and delete when it's need, usually when no referecnces to pointer.
	*/
template <typename PointerType>
class __RE_PUBLIC_CLASS_API__ REPtr
{
private:
	PointerType* _object;
	REInt32* _referenceCount;

	void retain()
	{
		if (_referenceCount)
		{
			*_referenceCount = (*_referenceCount) + 1;
		}
	}

	void deleteObject()
	{
		if (_object)
		{
			delete _object;
		}
		_object = NULL;
	}

public:
	/**
	 @brief Check pointer is NULL.
	 @return True if pointer is NULL, othervice false;
	 */
	bool isEmpty() const
	{
		return (_object == NULL);
	}


	/**
	 @brief Check pointer is not NULL.
	 @return True if not NULL, othervice false.
	 */
	bool isNotEmpty() const
	{
		return (_object != NULL);
	}


	/**
	 @brief Check this class is only one woner of the pointer.
	 @return True is only one owner, othervice false.
	 */
	bool isSingleOwner() const
	{
		return _referenceCount ? ((*_referenceCount) <= 1) : false;
	}


	/**
	 @brief Releases holded pointer.
	 @detailed Decrement reference counter and if there is not references delete's pointer.
	 */
	void release()
	{
		if (_referenceCount)
		{
			*_referenceCount = (*_referenceCount) - 1;
			if ((*_referenceCount) <= 0)
			{
				this->deleteObject();

				free(_referenceCount);
				_referenceCount = NULL;
			}
		}

		_object = NULL;
		_referenceCount = NULL;
	}


	/**
	 @brief Assing operator.
	 @detailed Releases prev. pointer reference, hold another pointer and increments it's reference.
	 @param anotherPtr Another autopointer object.
	 @return Address of this autopointer object.
	 */
	REPtr<PointerType> & operator=(const REPtr<PointerType> & anotherPtr)
	{
		if (this != &anotherPtr)
		{
			this->release();
			if (anotherPtr.isNotEmpty())
			{
				_object = anotherPtr._object;
				_referenceCount = anotherPtr._referenceCount;
				this->retain();
			}
		}
		return (*this);
	}


	/**
	 @brief Structure dereference operator.
	 @return Address(pointer to pointer) to holded object.
	 */
	PointerType* operator->()
	{
		return _object;
	}


	/**
	 @brief Const variant of the structure dereference operator.
	 @return Const address(pointer to pointer) to holded object.
	 */
	const PointerType* operator->() const
	{
		return _object;
	}


	/**
	 @brief Indirection operator.
	 @return Returns object pointer.
	 */
	operator PointerType* ()
	{
		return _object;
	}


	/**
	 @brief Const version of indirection operator.
	 @return Returns object const pointer.
	 */
	operator const PointerType* () const
	{
		return _object;
	}


	/**
	 @brief Default contructor.
	 @detailed Contructs autopointer without any object pointer and reference.
	 */
	REPtr() :
	_object(NULL),
	_referenceCount(NULL)
	{

	}


	/**
	 @brief Contructor with typed pointer to object.
	 @detailed If pointer is not NULL then holds pointer and create reference to it.
	 @param object Pointer to typed object.
	 */
	REPtr(PointerType* object) :
	_object(object),
	_referenceCount(NULL)
	{
		if (_object)
		{
			REInt32 * count = (REInt32 *)malloc(sizeof(REInt32));
#if defined(HAVE_ASSERT_H)
			assert(count);
#endif
			if (count)
			{
				*count = 1;
				_referenceCount = count;
			}
			else
			{
				_object = NULL;
			}
		}
	}


	/**
	 @brief Contructs autopointer with with another autopointer object.
	 @detailed If another autopointer is not empty(holds pointer) than increment reference, othervice created empty autopointer object.
	 @param anotherPtr Another autopointer object.
	 */
	REPtr(const REPtr<PointerType> & anotherPtr) :
	_object(NULL),
	_referenceCount(NULL)
	{
		if (this != &anotherPtr)
		{
			if (anotherPtr.isNotEmpty())
			{
				_object = anotherPtr._object;
				_referenceCount = anotherPtr._referenceCount;
				this->retain();
			}
		}
	}


	/**
	 @brief Default destructor.
	 @detailed Releases holded pointer if available.
		*/
	~REPtr()
	{
		this->release();
	}
};


/**
 @brief Function template for casting objects using "static_cast".
 */
template <typename resultType, typename sourceType>
static resultType* REPtrCast(sourceType* sourcePointer)
{
	return static_cast<resultType*>( static_cast<void*>(sourcePointer) );
}


/**
 @brief Const version of function template for casting objects using "static_cast".
 */
template <typename resultType, typename sourceType>
static const resultType* REPtrCast(const sourceType* sourcePointer)
{
	return static_cast<const resultType*>( static_cast<const void*>(sourcePointer) );
}

#endif

