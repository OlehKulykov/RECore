/*
 *   Copyright (c) 2012 - 2016 Kulykov Oleh <info@resident.name>
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


#include "../include/REBufferNoCopy.h"

#include <string.h>

REBufferNoCopy::REBufferNoCopy(const char * string) : REBuffer()
{
	_allocator = kREAllocatorNULL;
	char * s = string ? const_cast<char *>(string) : NULL;
	if (s)
	{
		_buff = static_cast<void *>(s);
		if (_buff)
		{
			_size = (RESizeT)(strlen(string) + 1);
		}
	}
}

REBufferNoCopy::REBufferNoCopy(const REMutableBuffer & buffer) : REBuffer()
{
	_allocator = kREAllocatorNULL;
	_buff = buffer.buffer();
	_size = buffer.size();
}

REBufferNoCopy::REBufferNoCopy(const REBuffer & buffer) : REBuffer()
{
	_allocator = kREAllocatorNULL;

	const void * b = buffer.buffer();
	const RESizeT s = buffer.size();
	if (b && s)
	{
		_buff = const_cast<void *>(b);
		if (_buff)
		{
			_size = s;
		}
	}
}

REBufferNoCopy::REBufferNoCopy(void * memory, const RESizeT size) : REBuffer()
{
	_allocator = kREAllocatorNULL;
	_buff = memory;
	_size = size;
}

REBufferNoCopy::REBufferNoCopy() : REBuffer()
{
	_allocator = kREAllocatorNULL;
}

REBufferNoCopy::~REBufferNoCopy()
{

}

