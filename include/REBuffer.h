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
#include "REAllocator.h"

class REMutableBuffer;

class __RE_PUBLIC_CLASS_API__ REBuffer
{
protected:
	REAllocator _allocator;
	union
	{
		void * _buff;
		const char * _constCharBuffer;
		const unsigned char * _constUnsignedCharBuffer;
	};
	RESizeT _size;

public:
	/**
	 @brief Checks is buffer equal with another buffer.
	 @return True if this buffer has the same size as another and content is byte-to-byte equal, othervice false.
	 */
	bool isEqualToBuffer(const REBuffer & anotherBuffer) const;


	/**
	 @brief Get raw constant pointer to the buffer memory.
	 @return Constant void pointer to the buffer memory.
	 */
	const void * buffer() const;


	/**
	 @brief Get size of the buffer memory in bytes.
	 @return Size of the buffer memory.
	 */
	RESizeT size() const;

	REBuffer(const char * string);
	REBuffer(const REBuffer & buffer);
	REBuffer(const void * memory, const RESizeT size);
	REBuffer(const RESizeT size);
	REBuffer();
	virtual ~REBuffer();
};

#endif 

