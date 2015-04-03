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


#include "../include/REBufferNoCopy.h"


void REBufferNoCopy::freeMemory(void * mem)
{
	if (_isNeedToFreeOriginalBuff)
	{
		_freeOriginalBuff(mem);
		_isNeedToFreeOriginalBuff = false;
	}
	else
	{
		REBuffer::defaultFree(mem);
	}
}

REBufferNoCopy::REBufferNoCopy(const void * originalBuff, const RESizeT buffSize, REBufferNoCopy::FreeOriginalBuff freeOriginalBuff) : REBuffer(),
_freeOriginalBuff(freeOriginalBuff),
_isNeedToFreeOriginalBuff(false)
{
	if (_freeOriginalBuff)
	{
		if (originalBuff && buffSize)
		{
			void * ob = const_cast<void *>(originalBuff);
			if (originalBuff == ob)
			{
				_buff = ob;
				_size = buffSize;
				_isNeedToFreeOriginalBuff = true;
			}
		}
	}
	else
	{
		this->set(originalBuff, buffSize);
	}
}

REBufferNoCopy::~REBufferNoCopy()
{
	if (_isNeedToFreeOriginalBuff)
	{
		_freeOriginalBuff(_buff);
		_isNeedToFreeOriginalBuff = false;
	}
	else
	{
		REBuffer::defaultFree(_buff);
	}
	_buff = NULL;
	_size = 0;
}


