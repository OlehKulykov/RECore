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


#include "../include/REBufferR.h"
#include "../include/REMutableBuffer.h"
#include "../include/REBufferRW.h"

#include <string.h>

RESizeT REBufferR::fileRead(void * bufferForReading, const RESizeT dataSizeToRead)
{
	if (_constCharBuffer && _size && bufferForReading && dataSizeToRead)
	{
		const char * buff = _constCharBuffer;
		RESizeT sizeToRead = dataSizeToRead;
		const RESizeT avaiableSize = _size - _offset;
		if (avaiableSize < sizeToRead)
		{
			sizeToRead = avaiableSize;
		}
		buff += _offset;
		memcpy(bufferForReading, buff, sizeToRead);
		_offset += sizeToRead;
		return sizeToRead;
	}
	return 0;
}

RESizeT REBufferR::fileTell()
{
	return _offset;
}

RESizeT REBufferR::fileSeek(const RESizeT fileOffset, int origin)
{
	RESizeT resultOffset = fileOffset;

	switch (origin)
	{
		case SEEK_CUR:
			resultOffset += _offset;
			break;

		case SEEK_END:
			if (_size < fileOffset)
			{
				return 2; // out of bounds
			}
			resultOffset = (_size - fileOffset);
			break;

		default:
			break;
	}

	if (resultOffset > _size) // common for SEEK_CUR && SEEK_SET
	{
		return 3; // out of bounds
	}

	_offset = resultOffset;
	return 0;
}

RESizeT REBufferR::fileSeekFromEndFile(const RESizeT fileOffset)
{
	return this->fileSeek(fileOffset, SEEK_END);
}

RESizeT REBufferR::fileSeekFromBeginFile(const RESizeT fileOffset)
{
	return this->fileSeek(fileOffset, SEEK_SET);
}

RESizeT REBufferR::fileSeekFromCurrentFilePos(const RESizeT fileOffset)
{
	return this->fileSeek(fileOffset, SEEK_CUR);
}

RESizeT REBufferR::fileFError()
{
	return 0;
}

RESizeT REBufferR::fileClose()
{
	return 0;
}

bool REBufferR::isEndOfFile()
{
	return (_size == _offset);
}

RESizeT REBufferR::offset() const
{
	return _offset;
}

REBufferR::REBufferR(const char * string)  : REBuffer(string),
	_offset(0)
{

}

REBufferR::REBufferR(const REBuffer & buffer) : REBuffer(buffer),
	_offset(0)
{

}

REBufferR::REBufferR(const REBufferR & buffer) : REBuffer(buffer),
	_offset(0)
{

}

REBufferR::REBufferR(const REMutableBuffer & buffer) : REBuffer(buffer),
	_offset(0)
{

}

REBufferR::REBufferR(const REBufferRW & buffer) : REBuffer(buffer),
	_offset(0)
{

}

REBufferR::REBufferR(const void * memory, const RESizeT size) : REBuffer(memory, size),
	_offset(0)
{

}

REBufferR::REBufferR(const RESizeT size) : REBuffer(size),
	_offset(0)
{

}

REBufferR::REBufferR() : REBuffer(),
	_offset(0)
{

}

REBufferR::~REBufferR()
{

}

