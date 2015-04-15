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


#ifndef __RESTRINGUTILSPRIVATE_H__
#define __RESTRINGUTILSPRIVATE_H__

#include "../include/REPtr.h"
#include "../include/REBuffer.h"

#include <string.h>

#include <wchar.h>

class REStringUtilsPrivate
{
private:
	static int charsToWide(const char * charsString, int charsStringLengthOrNegative, wchar_t * wideString);

	static int wideToChars(const wchar_t * wideString, int wideStringLength, char * charsString);

	static REBuffer * newBufferWithSize(const RESizeT newSize);
public:
	static REPtr<REBuffer> newBuffForUTF8String(const char * utf8String, const RESizeT utf8StringLength = RENotFound);

	static REPtr<REBuffer> newBuffForWideString(const wchar_t * wideString, const RESizeT wideStringLength = RENotFound);

	static REPtr<REBuffer> getWideFromUTF8(const REPtr<REBuffer> & utf8StringBuffer);

	static REPtr<REBuffer> getUTF8FromWide(const REPtr<REBuffer> & wideStringBuffer);

	static REPtr<REBuffer> getWideFromUTF8(const char * utf8String, const RESizeT utf8StringLength);

	static REPtr<REBuffer> getUTF8FromWide(const wchar_t * wideString, const RESizeT wideStringLength);

	static REPtr<REBuffer> makeCopy(const REPtr<REBuffer> & sourceBuffer);

	static RESizeT UTF8StringLength(const char * utf8String)
	{
		return utf8String ? strlen(utf8String) : 0;
	}

	static RESizeT wideStringLength(const wchar_t * wideString)
	{
		return wideString ? wcslen(wideString) : 0;
	}

	static bool isStringExists(const REPtr<REBuffer> & stringBuffer)
	{
		if (stringBuffer.isNotEmpty())
		{
			return stringBuffer->buffer() ? true : false;
		}
		return false;
	}

	static RESizeT actualUTF8StringLength(const char * utf8String, const RESizeT utf8StringLength = RENotFound)
	{
		const RESizeT len = (utf8StringLength == RENotFound) ? REStringUtilsPrivate::UTF8StringLength(utf8String) : utf8StringLength;
		return ( (len > 0) && (len != RENotFound) ) ? len : 0;
	}

	static RESizeT actualWideStringLength(const wchar_t * wideString, const RESizeT wideStringLength = RENotFound)
	{
		const RESizeT len = (wideStringLength == RENotFound) ? REStringUtilsPrivate::wideStringLength(wideString) : wideStringLength;
		return ( (len > 0) && (len != RENotFound) ) ? len : 0;
	}

	static RESizeT stringLengthFromUTF8Buffer(const REPtr<REBuffer> & utf8StringBuffer);

	static RESizeT stringLengthFromWideBuffer(const REPtr<REBuffer> & wideStringBuffer);

	static REPtr<REBuffer> getAppendedWithPathComponent(const REPtr<REBuffer> & utf8Buffer,
														const char * comp);

	static REPtr<REBuffer> getRemovedPathExtension(const REPtr<REBuffer> & utf8Buffer);

	static REPtr<REBuffer> getPathExtension(const REPtr<REBuffer> & utf8Buffer);

	static REPtr<REBuffer> getLastPathComponent(const REPtr<REBuffer> & utf8Buffer);

	static REPtr<REBuffer> getRemovedLastPathComponent(const REPtr<REBuffer> & utf8Buffer);

	static bool isBuffersEqual(const REPtr<REBuffer> & b1, const REPtr<REBuffer> & b2);

	static bool readFirstNumber(const char * str, REInt64 * i64vOrNull, REFloat64 * f64vOrNull);

	static RESizeT getUTF8Len(const char byte)
	{
		const unsigned char u = (unsigned char)byte;

		if(u < 0x80)
			return 1;

		if(0x80 <= u && u <= 0xBF) {
			/* second, third or fourth byte of a multi-byte
			 sequence, i.e. a "continuation byte" */
			return 0;
		}
		else if(u == 0xC0 || u == 0xC1) {
			/* overlong encoding of an ASCII byte */
			return 0;
		}
		else if(0xC2 <= u && u <= 0xDF) {
			/* 2-byte sequence */
			return 2;
		}

		else if(0xE0 <= u && u <= 0xEF) {
			/* 3-byte sequence */
			return 3;
		}
		else if(0xF0 <= u && u <= 0xF4) {
			/* 4-byte sequence */
			return 4;
		}
		else { /* u >= 0xF5 */
			/* Restricted (start of 4-, 5- or 6-byte sequence) or invalid
			 UTF-8 */
			return 0;
		}
	}
};



#endif /* __RESTRINGUTILSPRIVATE_H__  */

