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


#include "../include/RELZMA2.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

const REBuffer & RELZMA2Compressor::buffer() const
{
	return _compressedBuffer;
}

const void * RELZMA2Compressor::data() const
{
	return _compressedBuffer.buffer();
}

RESizeT RELZMA2Compressor::size() const
{
	return _compressedBuffer.size();
}

RESizeT RELZMA2Compressor::compress(const void * inBuffer, unsigned int inBufferSize)
{

	return 0;
}

RELZMA2Compressor::RELZMA2Compressor()
{

}

RELZMA2Compressor::~RELZMA2Compressor()
{

}

