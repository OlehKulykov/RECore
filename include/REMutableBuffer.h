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


#ifndef __REMUTABLEBUFFER_H__
#define __REMUTABLEBUFFER_H__

#include "REBuffer.h"

class REMutableBuffer : public REBuffer
{

public:
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
	REMutableBuffer & operator=(const REBuffer & anotherBuff);


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
	REMutableBuffer & operator+=(const REBuffer & anotherBuff);


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

	void * buffer() const;

	REMutableBuffer(const char * string);
	REMutableBuffer(const REMutableBuffer & buffer);
	REMutableBuffer(const REBuffer & buffer);
	REMutableBuffer(const void * memory, const RESizeT size);
	REMutableBuffer(const RESizeT size);
	REMutableBuffer();
	virtual ~REMutableBuffer();
};

#endif 

