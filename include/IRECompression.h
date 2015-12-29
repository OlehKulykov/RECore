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


#ifndef __IRECOMPRESSION_H__
#define __IRECOMPRESSION_H__

#include "RECore.h"

/**
 @brief Class interface for compressing data.
 */
class __RE_PUBLIC_CLASS_API__ IRECompressor
{
public:
	/**
	 @brief Pointer to the compressed data.
	 @return Data pointer or NULL.
	 */
	virtual const void * data() const = 0;


	/**
	 @brief Get compressed data size in bytes.
	 @return Size of the compressed data in bytes or 0.
	 */
	virtual RESizeT size() const = 0;


	/**
	 @brief Compress data buffer.
	 @param inBuffer Data pointer to compress.
	 @param inBufferSize Provided data size in bytes.
	 */
	virtual RESizeT compress(const void * inBuffer, const RESizeT inBufferSize) = 0;
	virtual ~IRECompressor() { }
};


/**
 @brief Class interface for decompressing data.
 */
class __RE_PUBLIC_CLASS_API__ IREDecompressor
{
public:
	/**
	 @brief Pointer to the decompressed data.
	 @return Data pointer or NULL.
	 */
	virtual const void * data() const = 0;


	/**
	 @brief Get decompressed data size in bytes.
	 @return Size of the decompressed data in bytes or 0.
	 */
	virtual RESizeT size() const = 0;


	/**
	 @brief Decompress data buffer.
	 @param inBuffer Data pointer to decompress.
	 @param inBufferSize Provided data size in bytes.
	 */
	virtual RESizeT decompress(const void * inBuffer, const RESizeT inBufferSize) = 0;
	virtual ~IREDecompressor() { }
};


#endif 
