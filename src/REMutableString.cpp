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


#include "../include/REMutableString.h"
#include "../include/REWideString.h"

#include "REStringUtilsPrivate.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#if defined(HAVE_STDARG_H)
#include <stdarg.h>
#endif

#include <string.h>

REMutableString & REMutableString::operator=(const char * utf8String)
{
	_p = REStringUtilsPrivate::newBuffForUTF8String(utf8String);
	return (*this);
}

REMutableString & REMutableString::operator=(const wchar_t * wideString)
{
	_p = REStringUtilsPrivate::getUTF8FromWide(wideString,
											   REStringUtilsPrivate::wideStringLength(wideString));
	return (*this);
}

REMutableString & REMutableString::operator=(const REWideString & anotherString)
{
	_p = REStringUtilsPrivate::getUTF8FromWide(anotherString.wideChars(),
											   anotherString.length());
	return (*this);
}

REMutableString & REMutableString::operator=(const REString & anotherString)
{
	_p = REStringUtilsPrivate::newBuffForUTF8String(anotherString.UTF8String(),
													anotherString.length());
	return (*this);
}

REMutableString & REMutableString::operator=(const REMutableString & anotherString)
{
	_p = REStringUtilsPrivate::makeCopy(anotherString._p);
	return (*this);
}

REMutableString & REMutableString::toLower()
{
	if (_p.isNotEmpty())
	{
		if (this->isContainsNonASCII())
		{
			REWideString wide(*this);
			const RESizeT len = wide.length();
			if (len > 0)
			{
				wchar_t * s = (wchar_t *)wide.wideChars();
				while (*s)
				{
					*s = (wchar_t)towlower(*s);
					s++;
				}
				this->setFromWideString(s, len, REStringTypeUTF8);
			}
		}
		else
		{
			char * s = (char *)this->UTF8String();
			while (*s)
			{
				*s = (char)tolower(*s);
				s++;
			}
		}
	}
	return (*this);
}

REMutableString & REMutableString::toUpper()
{
	if (_p.isNotEmpty())
	{
		if (this->isContainsNonASCII())
		{
			REWideString wide(*this);
			const RESizeT len = wide.length();
			if (len > 0)
			{
				wchar_t * s = (wchar_t *)wide.wideChars();
				while (*s)
				{
					*s = (wchar_t)towupper(*s);
					s++;
				}
				this->setFromWideString(s, len, REStringTypeUTF8);
			}
		}
		else
		{
			char * s = (char *)this->UTF8String();
			while (*s)
			{
				*s = (char)toupper(*s);
				s++;
			}
		}
	}
	return (*this);
}

REMutableString & REMutableString::append(const char * utf8String,
										  const RESizeT utf8StringLength)
{
	const RESizeT len = REStringUtilsPrivate::actualUTF8StringLength(utf8String, utf8StringLength);
	if (len)
	{
		const RESizeT thisLen = this->length();
		const RESizeT newLen = len + thisLen;
		REMutableBuffer * newBuffer = new REMutableBuffer();
		if (newBuffer)
		{
			if (newBuffer->resize(newLen + 1, false))
			{
				char * newData = (char *)newBuffer->buffer();
				if (thisLen > 0)
				{
					memcpy(newData, this->UTF8String(), thisLen);
				}
				memcpy(&newData[thisLen], utf8String, len);
				newData[newLen] = 0;
				_p = REStringBuffer(newBuffer);
				return (*this);
			}
			delete newBuffer;
		}
	}
	return (*this);
}

REMutableString & REMutableString::append(const wchar_t * wideString,
										  const RESizeT wideStringLength)
{
	REString utf8(wideString, wideStringLength);
	if (utf8.isNotEmpty())
	{
		return this->append((const char *)utf8.UTF8String(), utf8.length());
	}
	return (*this);
}

REMutableString & REMutableString::appendFormat(const char * format, ...)
{
	if (format)
	{
		va_list args;
		va_start(args, format);
		char strBuff[1024];

#if defined(HAVE_FUNCTION_VSNPRINTF)
		const int writed = vsnprintf(strBuff, 1024, format, args);
#elif defined(HAVE_FUNCTION_VSPRINTF_S) && !defined(__RE_COMPILER_MINGW__)
		const int writed = vsprintf_s(strBuff, format, args);
#else
		const int writed = vsprintf(strBuff, format, args);
#endif
		if (writed > 0)
		{
			this->append((const char *)strBuff, (REUInt32)writed);
		}
		va_end(args);
	}
	return (*this);
}

void REMutableString::replaceWithLen(const char * charsStringValue,
									 const char * withCharsStringValue,
									 const RESizeT firstLen,
									 const RESizeT secondLen)
{
	if (firstLen)
	{
		const RESizeT length = this->length();
		REUInt32 ocurencesCount = 0;
		char * mainString = (char *)_p->buffer();
		while ( (mainString = strstr(mainString, charsStringValue)) )
		{
			ocurencesCount++;
			mainString += firstLen;
		}

		if (ocurencesCount)
		{
			const RESizeT resultLen = (length + (ocurencesCount * secondLen)) - (ocurencesCount * firstLen);
			REMutableBuffer * newBuffer = new REMutableBuffer();
			if (!newBuffer) return;
			if (!newBuffer->resize(resultLen + 1, false)) return;

			char * newData = (char *)newBuffer->buffer();
			mainString = (char *)_p->buffer();
			char * srcString = (char *)_p->buffer();
			char * dstString = newData;
			while ( (mainString = strstr(mainString, charsStringValue)) )
			{
				while (srcString != mainString)
				{
					*dstString++ = *srcString++;
				}
				REUByte * addString = (REUByte *)withCharsStringValue;
				RESizeT addLen = secondLen;
				while (addLen)
				{
					*dstString++ = *addString++;
					addLen--;
				}
				mainString += firstLen;
				srcString += firstLen;
			}
			while (*srcString)
			{
				*dstString++ = *srcString++;
			}
			newData[resultLen] = 0;
			_p = REStringBuffer(newBuffer);
		}
	}
}


REMutableString & REMutableString::replace(const char * utf8String,
										   const char * withUTF8StringOrNULL)
{
	if (this->isNotEmpty())
	{
		const RESizeT firstLen = REStringUtilsPrivate::UTF8StringLength(utf8String);
		const RESizeT secondLen = REStringUtilsPrivate::UTF8StringLength(withUTF8StringOrNULL);
		this->replaceWithLen(utf8String, withUTF8StringOrNULL, firstLen, secondLen);
	}
	return (*this);
}

REMutableString & REMutableString::replace(const char needChar, const char targetChar)
{
	if (this->isNotEmpty())
	{
		char * mainString = (char *)_p->buffer();
		while (*mainString)
		{
			if (*mainString == needChar)
			{
				*mainString = targetChar;
			}
			mainString++;
		}
	}
	return (*this);
}

REMutableString & REMutableString::replace(const wchar_t * wideString,
										   const wchar_t * withWideStringOrNULL)
{
	if (this->isNotEmpty())
	{
		REString s1(wideString);
		REString s2(withWideStringOrNULL);
		this->replaceWithLen(s1.UTF8String(), s2.UTF8String(), s1.length(), s2.length());
	}
	return (*this);
}

REMutableString & REMutableString::appendPathComponent(const char * pComponent)
{
	_p = REStringUtilsPrivate::getAppendedWithPathComponent(_p, pComponent);
	return (*this);
}

REMutableString & REMutableString::removeLastPathComponent()
{
	_p = REStringUtilsPrivate::getRemovedLastPathComponent(_p);
	return (*this);
}

REMutableString & REMutableString::removePathExtension()
{
	_p = REStringUtilsPrivate::getRemovedPathExtension(_p);
	return (*this);
}

REMutableString::REMutableString() :
REString()
{

}

REMutableString::REMutableString(const char * utf8String,
								 const REUInt32 utf8StringLength) :
REString(utf8String, utf8StringLength)
{

}

REMutableString::REMutableString(const wchar_t * wideString,
								 const REUInt32 wideStringLength) :
REString(wideString, wideStringLength)
{

}

REMutableString::REMutableString(const REWideString & anotherString) :
REString(anotherString.wideChars(), anotherString.length())
{

}

REMutableString::REMutableString(const REString & anotherString) :
REString(anotherString.UTF8String(), anotherString.length())
{

}

REMutableString::REMutableString(const REMutableString & anotherString) :
REString(anotherString.UTF8String(), anotherString.length())
{

}

REMutableString::REMutableString(const REStringBuffer & utf8StringBuffer) :
REString(utf8StringBuffer)
{

}

REMutableString::~REMutableString()
{

}


