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


#include "../include/REBuffer.h"
#include "../include/REMutableBuffer.h"

#include <string.h>

bool REBuffer::isEqualToBuffer(const REBuffer & anotherBuffer) const
{
	if (_size == anotherBuffer._size)
	{
		return _size ? (memcmp(_buff, anotherBuffer._buff, _size) == 0) : true;
	}
	return false;
}

const void * REBuffer::buffer() const
{
	return _buff;
}

RESizeT REBuffer::size() const
{
	return _size;
}

REBuffer::REBuffer(const char * string) :
	_allocator(kREAllocatorMalloc),
	_buff(NULL),
	_size(0)
{
	const size_t len = string ? strlen(string) : 0;
	if (len > 0)
	{
		_buff = _allocator.allocateMemory(len + 1);
		if (_buff)
		{
			_size = (len + 1);
		}
	}
}

REBuffer::REBuffer(const void * memory, const RESizeT size) :
	_allocator(kREAllocatorMalloc),
	_buff(NULL),
	_size(0)
{
	if (memory && size)
	{
		_buff = _allocator.allocateMemory(size);
		if (_buff)
		{
			memcpy(_buff, memory, (size_t)size);
			_size = size;
		}
	}
}

REBuffer::REBuffer(const RESizeT size) :
	_allocator(kREAllocatorMalloc),
	_buff(NULL),
	_size(0)
{
	_buff = _allocator.allocateMemory(size);
	if (_buff)
	{
		_size = size;
	}
}

REBuffer::REBuffer(const REBuffer & buffer) :
	_allocator(kREAllocatorMalloc),
	_buff(NULL),
	_size(0)
{
	if (buffer._buff && buffer._size)
	{
		_buff = _allocator.allocateMemory(buffer._size);
		if (_buff)
		{
			memcpy(_buff, buffer._buff, (size_t)buffer._size);
			_size = buffer._size;
		}
	}
}

REBuffer::REBuffer(const REMutableBuffer & buffer) :
	_allocator(kREAllocatorMalloc),
	_buff(NULL),
	_size(0)
{
	if (buffer._buff && buffer._size)
	{
		_buff = _allocator.allocateMemory(buffer._size);
		if (_buff)
		{
			memcpy(_buff, buffer._buff, (size_t)buffer._size);
			_size = buffer._size;
		}
	}
}

REBuffer::REBuffer() :
	_allocator(kREAllocatorMalloc),
	_buff(NULL),
	_size(0)
{

}

REBuffer::~REBuffer()
{
	_allocator.freeMemory(_buff);
}


