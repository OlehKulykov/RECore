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


#ifndef __REBUFFERRW_H__
#define __REBUFFERRW_H__

#include "REBufferR.h"
#include "REMutableBuffer.h"
#include "IREFileReadable.h"
#include "IREFileWritable.h"


class __RE_PUBLIC_CLASS_API__ REBufferRW : public REBufferR, public IREFileWritable
{
protected:
	bool resize(const RESizeT newSize, bool isCopyPrevData);

public:
	virtual RESizeT fileWrite(const void * bufferForWrite, const RESizeT dataSizeToWrite);

	REBufferRW(const char * string);
	REBufferRW(const REMutableBuffer & buffer);
	REBufferRW(const REBufferRW & buffer);
	REBufferRW(const REBuffer & buffer);
	REBufferRW(const REBufferR & buffer);
	REBufferRW(const void * memory, const RESizeT size);
	REBufferRW(const RESizeT size);
	REBufferRW();
	virtual ~REBufferRW();
};

#endif 

