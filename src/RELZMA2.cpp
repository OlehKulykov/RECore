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
#include "../include/REMutableBuffer.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#include <assert.h>
#include <string.h>

#if defined(RE_BUILD_WITH_LZMA2)
#include "../lzma/Lzma2Enc.h"
#include "../lzma/Lzma2Dec.h"

typedef struct RELZMA2ISeqOutStreamStruct : public ISeqOutStream
{
	REMutableBuffer buffer;

	size_t write(const void * buf, size_t size)
	{
		return buffer.append(buf, size) ? size : 0;
	}
} RELZMA2ISeqOutStream;

typedef struct RELZMA2ISeqInStreamStruct : public ISeqInStream
{
	const void * buff;
	RESizeT size;
	RESizeT pos;

	SRes read(void * b, size_t * s)
	{
		*s = MIN(*s, size - pos);
		if (*s)
		{
			const uint8_t * cBuff = (const uint8_t *)buff;
			cBuff += pos;
			memcpy(b, cBuff, *s);
		}
		pos += *s;
		return SZ_OK;
	}

} RELZMA2ISeqInStream;

static size_t RELZMA2ImplWrite(void * p, const void * buf, size_t size)
{
	RELZMA2ISeqOutStreamStruct * stream = static_cast<RELZMA2ISeqOutStreamStruct *>(p);
	return stream->write(buf, size);
}

static SRes RELZMA2ImplRead(void * p, void * buf, size_t * size)
{
	RELZMA2ISeqInStream * stream = static_cast<RELZMA2ISeqInStream *>(p);
	return stream->read(buf, size);
}

static void * RELZMA2ImplAlloc(void * p, size_t size)
{
	return malloc(size);
}

static void RELZMA2ImplFree(void * p, void * address)
{
	if (address) free(address);
}
#endif

const void * RELZMA2Compressor::data() const
{
#if defined(RE_BUILD_WITH_LZMA2)
	RELZMA2ISeqOutStream * stream = static_cast<RELZMA2ISeqOutStream *>(_outStream);
	return stream ? stream->buffer.buffer() : NULL;
#else
	return NULL;
#endif
}

RESizeT RELZMA2Compressor::size() const
{
#if defined(RE_BUILD_WITH_LZMA2)
	RELZMA2ISeqOutStream * stream = static_cast<RELZMA2ISeqOutStream *>(_outStream);
	return stream ? stream->buffer.size() : 0;
#else
	return 0;
#endif
}

RESizeT RELZMA2Compressor::compress(const void * inBuffer, const RESizeT inBufferSize)
{
#if defined(RE_BUILD_WITH_LZMA2)
	this->cleanupStreams();

	RELZMA2ISeqInStream * inStream = new RELZMA2ISeqInStream();
	RELZMA2ISeqOutStream * outStream = new RELZMA2ISeqOutStream();
	if (!inStream || !outStream)
	{
		if (inStream) delete inStream;
		if (outStream) delete outStream;
		return 0;
	}
	_inStream = static_cast<void *>(inStream);
	_outStream = static_cast<void *>(outStream);

	ISzAlloc allc, allcBig;
	allc.Alloc = allcBig.Alloc = RELZMA2ImplAlloc;
	allc.Free = allcBig.Free = RELZMA2ImplFree;

	CLzma2EncHandle enc = Lzma2Enc_Create(&allc, &allcBig);

	CLzma2EncProps props;
	Lzma2EncProps_Init(&props);
	props.lzmaProps.writeEndMark = 1; // !!! need mark for extract
	props.lzmaProps.level = 9;
	props.lzmaProps.numThreads = 1;
	props.numTotalThreads = 1;

	SRes res = Lzma2Enc_SetProps(enc, &props);
	assert(res == SZ_OK);

	outStream->buffer.resize(sizeof(Byte) + sizeof(uint32_t), false);

	Byte * outBytes = (Byte *)outStream->buffer.buffer();
	*outBytes = Lzma2Enc_WriteProperties(enc);
	outBytes += sizeof(Byte);
	*((uint32_t *)outBytes) = (uint32_t)inBufferSize;

	outStream->Write = RELZMA2ImplWrite;

	inStream->Read = RELZMA2ImplRead;
	inStream->buff = inBuffer;
	inStream->size = inBufferSize;
	inStream->pos = 0;

	res = Lzma2Enc_Encode(enc, outStream, inStream, 0);
	if (res != SZ_OK)
	{
		this->cleanupStreams();
	}

	Lzma2Enc_Destroy(enc);
	return this->size();
#else
	return 0;
#endif
}

void RELZMA2Compressor::cleanupStreams()
{
#if defined(RE_BUILD_WITH_LZMA2)
	if (_inStream)
	{
		RELZMA2ISeqInStream * stream = static_cast<RELZMA2ISeqInStream *>(_inStream);
		delete stream;
		_inStream = NULL;
	}

	if (_outStream)
	{
		RELZMA2ISeqOutStream * stream = static_cast<RELZMA2ISeqOutStream *>(_outStream);
		delete stream;
		_outStream = NULL;
	}
#endif
}

RELZMA2Compressor::RELZMA2Compressor() :
	_inStream(NULL),
	_outStream(NULL)
{

}

RELZMA2Compressor::~RELZMA2Compressor()
{
#if defined(RE_BUILD_WITH_LZMA2)
	this->cleanupStreams();
#endif
}



const void * RELZMA2Decompressor::data() const
{
#if defined(RE_BUILD_WITH_LZMA2)
	return _buffer.buffer();
#else
	return NULL;
#endif
}

RESizeT RELZMA2Decompressor::size() const
{
#if defined(RE_BUILD_WITH_LZMA2)
	return _buffer.size();
#else
	return 0;
#endif
}

RESizeT RELZMA2Decompressor::decompress(const void * inBuffer, const RESizeT inBufferSize)
{
#if defined(RE_BUILD_WITH_LZMA2)
	const Byte * inBytes = (const Byte *)inBuffer;
	const Byte properties = *inBytes;
	inBytes += sizeof(Byte);

	const uint32_t uncompressedSize = *((const uint32_t *)inBytes);
	inBytes += sizeof(uint32_t);

	if (!_buffer.resize(uncompressedSize, false))
	{
		return 0;
	}

	CLzma2Dec dec;
	Lzma2Dec_Construct(&dec);

	ISzAlloc allc;
	allc.Alloc = RELZMA2ImplAlloc;
	allc.Free = RELZMA2ImplFree;

	SRes res = Lzma2Dec_Allocate(&dec, properties, &allc);
	assert(res == SZ_OK);

    Lzma2Dec_Init(&dec);

	ELzmaStatus status = LZMA_STATUS_NOT_SPECIFIED;
	while (status != LZMA_STATUS_FINISHED_WITH_MARK)
	{
		SizeT outSize = _buffer.size();
		SizeT inSize = inBufferSize - 5;
		res = Lzma2Dec_DecodeToBuf(&dec,
								   (Byte *)_buffer.buffer(),
								   &outSize,
								   inBytes,
								   &inSize,
								   LZMA_FINISH_END,
								   &status);
	}

	if ((status != LZMA_STATUS_FINISHED_WITH_MARK) || (res != SZ_OK))
	{
		_buffer.clear();
	}

	Lzma2Dec_Free(&dec, &allc);

	return _buffer.size();
#else
	return 0;
#endif
}

RELZMA2Decompressor::RELZMA2Decompressor()
{

}

RELZMA2Decompressor::~RELZMA2Decompressor()
{

}

