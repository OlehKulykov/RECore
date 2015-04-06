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


#ifndef __REBUFFERNOCOPY_H__
#define __REBUFFERNOCOPY_H__

#include "REBuffer.h"

/**
 @brief Class of buffer which only hold pointer to buffer without copying.
 */
class __RE_PUBLIC_CLASS_API__ REBufferNoCopy : public REBuffer
{
public:
	typedef void(*FreeOriginalBuff)(void * mem);

private:
	REBufferNoCopy::FreeOriginalBuff _freeOriginalBuff;
	bool _isNeedToFreeOriginalBuff;

protected:
	virtual void freeMemory(void * mem);

public:
	/**
	 @brief Contructs buffer.
	 @param originalBuff Pointer to some buffer with data.
	 @param buffSize Size of buffer.
	 @param freeOriginalBuff Callback for delete buffer pointer.
	 */
	REBufferNoCopy(const void * originalBuff, const RESizeT buffSize, REBufferNoCopy::FreeOriginalBuff freeOriginalBuff);


	/**
	 @brief Default vitual destructor.
	 */
	virtual ~REBufferNoCopy();
};


#endif
