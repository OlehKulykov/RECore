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


#ifndef __REBUFFER_H__
#define __REBUFFER_H__

#include "RECore.h"

#include <string.h>

/**
 @brief Class of memory buffer.
 */
class __RE_PUBLIC_CLASS_API__ REBuffer
{
protected:
	void * _buff;
	RESizeT _size;

	static void * defaultMalloc(const RESizeT size);
	static void defaultFree(void * mem);

	virtual void * mallocNewMemory(const RESizeT size);
	virtual void freeMemory(void * mem);
public:
	/**
	 @brief Checks is buffer equal with another buffer.
	 @return True if this buffer has the same size as another and content is byte-to-byte equal, othervice false.
	 */
	bool isEqualToBuffer(const REBuffer & anotherBuffer) const;


	/**
	 @brief Constant Getter for memory buffer data pointer.
	 @return Void pointer to memory buffer or NULL.
	 */
	void * buffer() const;


	/**
	 @brief Getter for memory buffer data pointer.
	 @return Void pointer to memory buffer or NULL.
	 */
	void * buffer();


	/**
	 @brief Getter for buffer size.
	 @return Buffer size in bytes.
	 */
	RESizeT size() const;


	/**
	 @brief Resizes memory buffer with new size.
	 @param newSize New buffer size in bytes.
	 @param isCopyPrevData Flag indicates copying previous data during resize.
	 @return true if memory was resized to 'newSize', or false if new memory not created.
	 */
	bool resize(const RESizeT newSize, bool isCopyPrevData);


	/**
	 @brief Clear memory buffer.
	 */
	void clear();


	/**
	 @brief Set new size of memory buffer, copy from inputed buffer data with size to destination(this).
	 @param buff Target memory buffer to set.
	 @param buffSize Target memory buffer size in bytes. This size will be copyed to destination(this).
	 @return True if new buffer with size created and target memory was copyed.
	 */
	bool set(const void * buff, const RESizeT buffSize);


	/**
	 @brief Assign operator with from another buffer.
	 @detailed New memory buffer will be created and memory from 'anotherBuff' will be copyed.
	 @return Address of this instance.
	 */
	REBuffer & operator=(const REBuffer & anotherBuff);


	/**
	 @brief Append this memory buffer with another memory.
	 @detailed New memory buffer will be created, cpyed prev memory and appended with new.
	 @param buff Target memory buffer to append.
	 @param buffSize Target memory buffer size in bytes. This size will be appended to destination(this).
	 @return True if new memory created, and appended, othervice false.
	 */
	bool append(const void * buff, const RESizeT buffSize);


	/**
	 @brief Append this memory buffer with another buffer object.
	 @detailed New memory buffer will be created, cpyed prev memory and appended with new.
	 @param anotherBuff Another buffer object to append.
	 @return True if new memory created, and appended, othervice false.
	 */
	bool append(const REBuffer & anotherBuff);


	/**
	 @brief Appends with another buffer object.
	 @detailed New memory buffer will be created, cpyed prev memory and appended with new.
	 @param anotherBuff Another buffer object to append.
	 @return True if new memory created, and appended, othervice false.
	 */
	REBuffer & operator+=(const REBuffer & anotherBuff);


	/**
	 @brief Constructs buffer object with content from another buffer object.
	 */
	REBuffer(const REBuffer & anotherBuff);


	/**
	 @brief Constructs buffer object with content from another buffer with size.
	 */
	REBuffer(const void * buff, const RESizeT buffSize);


	/**
	 @brief Constructs buffer object with memory size.
	 */
	REBuffer(const RESizeT buffSize);


	/**
	 @brief Constructs empty buffer object.
	 */
	REBuffer();


	virtual ~REBuffer();
};


#endif


