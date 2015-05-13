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
#include "../include/REMutableBuffer.h"
#include "../include/REStringBase.h"

#include <string.h>

#include <wchar.h>

class REStringUtilsPrivate
{
private:
	static int charsToWide(const char * charsString, int charsStringLengthOrNegative, wchar_t * wideString);

	static int wideToChars(const wchar_t * wideString, int wideStringLength, char * charsString);

	static REMutableBuffer * newBufferWithSize(const RESizeT newSize);
public:
	static REStringBuffer newBuffForUTF8String(const char * utf8String, const RESizeT utf8StringLength = RENotFound);

	static REStringBuffer newBuffForWideString(const wchar_t * wideString, const RESizeT wideStringLength = RENotFound);

	static REStringBuffer getWideFromUTF8(const REStringBuffer & utf8StringBuffer);

	static REStringBuffer getUTF8FromWide(const REStringBuffer & wideStringBuffer);

	static REStringBuffer getWideFromUTF8(const char * utf8String, const RESizeT utf8StringLength);

	static REStringBuffer getUTF8FromWide(const wchar_t * wideString, const RESizeT wideStringLength);

	static REStringBuffer makeCopy(const REStringBuffer & sourceBuffer);

	static RESizeT UTF8StringLength(const char * utf8String)
	{
		return utf8String ? strlen(utf8String) : 0;
	}

	static RESizeT wideStringLength(const wchar_t * wideString)
	{
		return wideString ? wcslen(wideString) : 0;
	}

	static bool isStringExists(const REStringBuffer & stringBuffer)
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

	static RESizeT stringLengthFromUTF8Buffer(const REStringBuffer & utf8StringBuffer);

	static RESizeT stringLengthFromWideBuffer(const REStringBuffer & wideStringBuffer);

	static REStringBuffer getAppendedWithPathComponent(const REStringBuffer & utf8Buffer,
													   const char * comp);

	static REStringBuffer getRemovedPathExtension(const REStringBuffer & utf8Buffer);

	static REStringBuffer getPathExtension(const REStringBuffer & utf8Buffer);

	static REStringBuffer getLastPathComponent(const REStringBuffer & utf8Buffer);

	static REStringBuffer getRemovedLastPathComponent(const REStringBuffer & utf8Buffer);

	static bool isBuffersEqual(const REStringBuffer & b1, const REStringBuffer & b2);

	static bool readFirstNumber(const char * str, REInt64 * i64vOrNull, REFloat64 * f64vOrNull);

	static RESizeT getUTF8Len(const char byte)
	{
		const unsigned char u = (unsigned char)byte;

		if (u < 0x80) return 1;

		if (0x80 <= u && u <= 0xBF)
		{
			return 0;
		}
		else if (u == 0xC0 || u == 0xC1)
		{
			return 0;
		}
		else if (0xC2 <= u && u <= 0xDF)
		{
			return 2;
		}
		else if (0xE0 <= u && u <= 0xEF)
		{
			return 3;
		}
		else if (0xF0 <= u && u <= 0xF4)
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}
};



#endif /* __RESTRINGUTILSPRIVATE_H__  */

