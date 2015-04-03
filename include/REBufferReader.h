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


#ifndef __REBUFFERREADER_H__
#define __REBUFFERREADER_H__

#include "RECore.h"

#include <string.h>

class __RE_PUBLIC_CLASS_API__ REBufferReader
{
protected:
	REUByte * _buff;
	RESizeT _size;

public:
	REUByte * buffer() const { return _buff; }

	RESizeT size() const { return _size; }

	template<typename T> T read()
	{
		T resValue;
		const RESizeT valueSize = sizeof(T);

		if (_size < valueSize)
		{
			memset(&resValue, 0, valueSize);
			return resValue;
		}

		memcpy(&resValue, _buff, valueSize);

		_buff += valueSize;
		_size -= valueSize;

		return resValue;
	}

	template<typename T> T readSwaped()
	{
		T resValue;
		const RESizeT valueSize = sizeof(T);

		if (_size < valueSize)
		{
			memset(&resValue, 0, valueSize);
			return resValue;
		}

		REUByte * from = _buff;
		from += valueSize;

		REUByte * to = (REUByte *)&resValue;

		for (RESizeT i = 0; i < valueSize; i++)
		{
			from--;
			*to = *from;
			to++;
		}

		_buff += valueSize;
		_size -= valueSize;

		return resValue;
	}


	REBufferReader(REUByte * buffer, const RESizeT size) : _buff(buffer), _size(size) { }

	virtual ~REBufferReader() { }
};

#endif
