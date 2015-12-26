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


#include "../include/REBufferRW.h"

#include <string.h>

bool REBufferRW::resize(const RESizeT newSize, bool isCopyPrevData)
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

RESizeT REBufferRW::fileWrite(const void * bufferForWrite, const RESizeT dataSizeToWrite)
{
	if (bufferForWrite && dataSizeToWrite)
	{
		const RESizeT avaiableSize = _size - _offset;
		if (avaiableSize < dataSizeToWrite)
		{
			const RESizeT need = dataSizeToWrite - avaiableSize;
			if (!this->resize(_size + need, true)) return 0;
		}

		char * buff = (char *)_buff;
		if (buff && _size)
		{
			buff += _offset;
			memcpy(buff, bufferForWrite, dataSizeToWrite);
			_offset += dataSizeToWrite;
			return dataSizeToWrite;
		}

	}
	return 0;
}

REBufferRW::REBufferRW(const char * string) : REBufferR(string)
{

}

REBufferRW::REBufferRW(const REMutableBuffer & buffer) : REBufferR(buffer)
{

}

REBufferRW::REBufferRW(const REBufferRW & buffer) : REBufferR(buffer)
{

}

REBufferRW::REBufferRW(const REBuffer & buffer) : REBufferR(buffer)
{

}

REBufferRW::REBufferRW(const REBufferR & buffer) : REBufferR(buffer)
{

}

REBufferRW::REBufferRW(const void * memory, const RESizeT size) : REBufferR(memory, size)
{

}

REBufferRW::REBufferRW(const RESizeT size) : REBufferR(size)
{

}

REBufferRW::REBufferRW() : REBufferR()
{

}

REBufferRW::~REBufferRW()
{

}

