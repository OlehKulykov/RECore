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


#include "../include/REMutableBuffer.h"

#include <string.h>

bool REMutableBuffer::set(const void * buff, const RESizeT buffSize)
{
	this->clear();

	if (buff && buffSize)
	{
		void * newBuff = _allocator.allocateMemory(buffSize);
		if (newBuff)
		{
			memcpy(newBuff, buff, (size_t)buffSize);
			_buff = newBuff;
			_size = buffSize;
			return true;
		}
	}

	return false;
}

REMutableBuffer & REMutableBuffer::operator=(const REBuffer & anotherBuff)
{
	this->set(anotherBuff.buffer(), anotherBuff.size());
	return *this;
}

bool REMutableBuffer::append(const void * buff, const RESizeT buffSize)
{
	if (_size && _buff)
	{
		const RESizeT newSize = _size + buffSize;
		REUByte * newBuff = (REUByte *)_allocator.allocateMemory(newSize);
		if (newBuff)
		{
			memcpy(newBuff, _buff, (size_t)_size);
			memcpy(&newBuff[_size], buff, (size_t)buffSize);
			_allocator.freeMemory(_buff);
			_buff = newBuff;
			_size = newSize;
			return true;
		}
		return false;
	}

	return this->set(buff, buffSize);
}

bool REMutableBuffer::append(const REBuffer & anotherBuff)
{
	return this->append(anotherBuff.buffer(), anotherBuff.size());
}

REMutableBuffer & REMutableBuffer::operator+=(const REBuffer & anotherBuff)
{
	this->append(anotherBuff.buffer(), anotherBuff.size());
	return *this;
}

void REMutableBuffer::clear()
{
	_allocator.freeMemory(_buff);
	_buff = NULL;
	_size = 0;
}

bool REMutableBuffer::resize(const RESizeT newSize, bool isCopyPrevData)
{
	if (_size == newSize)
	{
		return true;
	}

	void * newBuff = _allocator.allocateMemory(newSize);
	if (newBuff)
	{
		if (_buff)
		{
			if (isCopyPrevData)
			{
				const RESizeT copySize = MIN(newSize, _size);
				if (copySize)
				{
					memcpy(newBuff, _buff, (size_t)copySize);
				}
			}

			_allocator.freeMemory(_buff);
		}

		_buff = newBuff;
		_size = newSize;

		return true;
	}

	return false;
}

void * REMutableBuffer::buffer() const
{
	return _buff;
}

REMutableBuffer::REMutableBuffer(const char * string) : REBuffer(string)
{

}

REMutableBuffer::REMutableBuffer(const REMutableBuffer & buffer) : REBuffer(buffer.buffer(), buffer.size())
{

}

REMutableBuffer::REMutableBuffer(const REBuffer & buffer) : REBuffer(buffer.buffer(), buffer.size())
{

}

REMutableBuffer::REMutableBuffer(const void * memory, const RESizeT size) : REBuffer(memory, size)
{

}

REMutableBuffer::REMutableBuffer(const RESizeT size) : REBuffer(size)
{

}

REMutableBuffer::REMutableBuffer() : REBuffer()
{

}

REMutableBuffer::~REMutableBuffer()
{

}

