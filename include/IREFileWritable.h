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


#ifndef __IREFILEWRITABLE_H__
#define __IREFILEWRITABLE_H__

#include "RECore.h"
#include "IREFileReadable.h"

/**
 @brief Interface for classes that can be used for writings some data.
 @detailed Members is simular to 'c FILE' functions.
 */
class __RE_PUBLIC_CLASS_API__ IREFileWritable
{
public:
	/**
	 @brief Write data to object.
	 @param bufferForWrite The buffer for writing data.
	 @param dataSizeToWrite Size in bytes for provided data.
	 @result Returns number of bytes writed.
	 */
	virtual RESizeT fileWrite(const void * bufferForWrite, const RESizeT dataSizeToWrite) = 0;


	/**
	 @brief Default destructor.
	 */
	virtual ~IREFileWritable() { }
};


#endif

