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


#include "../include/REString.h"
#include "../include/REMutableString.h"
#include "../include/REWideString.h"
#include "../include/REStringList.h"

#include "REStringUtilsPrivate.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#if defined(RE_HAVE_STDARG_H)
#include <stdarg.h>
#endif


REString & REString::operator=(const char * utf8String)
{
	this->setFromUTF8String(utf8String,
							RENotFound,
							REStringTypeUTF8);

	return (*this);
}

REString & REString::operator=(const wchar_t * wideString)
{
	this->setFromWideString(wideString,
							RENotFound,
							REStringTypeUTF8);

	return (*this);
}

REString & REString::operator=(const REWideString & anotherString)
{
	this->setFromWideString(anotherString.wideChars(),
							anotherString.length(),
							REStringTypeUTF8);
	return (*this);
}

REString & REString::operator=(const REString & anotherString)
{
	_p = anotherString._p;
	return (*this);
}

REString & REString::operator=(const REMutableString & anotherString)
{
	_p = REStringUtilsPrivate::makeCopy(anotherString._p);
	return (*this);
}

bool REString::operator==(const REString & s) const
{
	return this->isEqual(s);
}

REMutableString REString::mutableString() const
{
	return REMutableString( REStringUtilsPrivate::makeCopy(_p) );
}

REWideString REString::wideString() const
{
	return REWideString( REStringUtilsPrivate::getWideFromUTF8(_p) );
}

const char * REString::UTF8String() const
{
	return _p.isNotEmpty() ? (const char *)_p->buffer() : NULL;
}

RESizeT REString::length() const
{
	return REStringUtilsPrivate::stringLengthFromUTF8Buffer(_p);
}

bool REString::isContainsNonASCII() const
{
	return REStringUtilsPrivate::isContainsNonASCII(_p);
}

bool REString::isContaines(const char * utf8String) const
{
	if (utf8String)
	{
		const char * thisUTF8String = this->UTF8String();
		if (thisUTF8String)
		{
			return (strstr(thisUTF8String, utf8String) != 0);
		}
	}
	return false;
}

REStringList REString::split(const char * delimeterString) const
{
	REStringList list;
	if (delimeterString)
	{
		const char * src = this->UTF8String();
		if (src)
		{
			const RESizeT delLen = strlen(delimeterString);
			const char * sub = strstr(src, delimeterString);
			RESizeT count = 0;
			while (sub)
			{
				const RESizeT len = (RESizeT)((REUIdentifier)sub - (REUIdentifier)src);
				REString part(src, len);
				list.add(part);
				count++;
				src = sub;
				src += delLen;
				sub = strstr(src, delimeterString);
			}
			if (count > 0)
			{
				// add last if available
				const RESizeT leftLen = (*src) ? strlen(src) : 0;
				if (leftLen > 0)
				{
					REString part(src, leftLen);
					list.add(part);
				}
			}
		}
	}
	return list;
}

bool REString::isContaines(const wchar_t * wideString) const
{
	if (wideString)
	{
		REStringBuffer utf8Buff = REStringUtilsPrivate::getUTF8FromWide(wideString,
																		 RENotFound);

		const RESizeT len = REStringUtilsPrivate::stringLengthFromUTF8Buffer(utf8Buff);
		if (len)
		{
			return this->isContaines((const char *)utf8Buff->buffer());
		}
	}
	return false;
}

bool REString::isDigit() const
{
	const char * ch = this->UTF8String();
	if (ch)
	{
		REUInt32 processed = 0;
		while (*ch)
		{
			const int dig = *ch++;
			processed++;
			if (!isdigit(dig))
			{
				if ((dig != '+') || (dig != '-') || (dig != '.'))
				{
					return false;
				}
			}
		}
		return (processed > 0);
	}
	return false;
}

bool REString::isEqual(const REWideString & anotherString) const
{
	REString utf8String(anotherString);
	return REStringUtilsPrivate::isBuffersEqual(_p, utf8String._p);
}

bool REString::isEqual(const REString & anotherString) const
{
	return REStringUtilsPrivate::isBuffersEqual(_p, anotherString._p);
}

bool REString::isEqual(const REMutableString & anotherString) const
{
	return REStringUtilsPrivate::isBuffersEqual(_p, anotherString._p);
}

bool REString::isEqual(const char * utf8String,
						 const RESizeT utf8StringLength) const
{
	const RESizeT len = REStringUtilsPrivate::actualUTF8StringLength(utf8String, utf8StringLength);
	if (len == this->length())
	{
		if (len > 0)
		{
			return (memcmp(this->UTF8String(), utf8String, len) == 0);
		}
		return true;
	}
	return false;
}

bool REString::isEqual(const wchar_t * wideString,
						 const RESizeT wideStringLength) const
{
	REStringBuffer p = REStringUtilsPrivate::getUTF8FromWide(wideString, wideStringLength);
	return REStringUtilsPrivate::isBuffersEqual(_p, p);
}

REString REString::pathExtension() const
{
	return REString( REStringUtilsPrivate::getPathExtension(_p) );
}

REString REString::lastPathComponent() const
{
	return REString( REStringUtilsPrivate::getLastPathComponent(_p) );
}

REInt64 REString::integerValue(bool * isOk) const
{
	REInt64 value = 0;
	bool reslt = false;
	const char * str = (const char *)this->stringBuffer();
	if (str && (this->length() > 0))
	{
		reslt = REStringUtilsPrivate::readFirstNumber(str, &value, NULL);
	}
	if (isOk) *isOk = reslt;
	return value;
}

REFloat64 REString::floatValue(bool * isOk) const
{
	REFloat64 value = 0.0;
	bool reslt = false;
	const char * str = (const char *)this->stringBuffer();
	if (str && (this->length() > 0))
	{
		reslt = REStringUtilsPrivate::readFirstNumber(str, NULL, &value);
	}
	if (isOk) *isOk = reslt;
	return value;
}

REString::REString() : REStringBase()
{

}

REString::REString(const wchar_t * wideString, const RESizeT wideStringLength) :
REStringBase(wideString, wideStringLength, REStringTypeUTF8)
{

}

REString::REString(const char * utf8String, const RESizeT utf8StringLength) :
REStringBase(utf8String, utf8StringLength, REStringTypeUTF8)
{

}

REString::REString(const REWideString & anotherString) :
REStringBase(anotherString.wideChars(), anotherString.length(), REStringTypeUTF8)
{

}

REString::REString(const REString & anotherString) :
REStringBase(anotherString._p)
{

}

REString::REString(const REMutableString & anotherString) :
REStringBase(anotherString.UTF8String(), anotherString.length(), REStringTypeUTF8)
{

}

REString::REString(const REStringBuffer & utf8StringBuffer) :
REStringBase(utf8StringBuffer)
{

}

REString::~REString()
{

}

REString REString::createWithFormat(const char * format, ...)
{
	if (format)
	{
		va_list args;
		va_start(args, format);
		char strBuff[1024];

#if defined(RE_HAVE_FUNCTION_VSNPRINTF)
		const int writed = vsnprintf(strBuff, 1024, format, args);
#elif defined(RE_HAVE_FUNCTION_VSPRINTF_S)
		const int writed = vsprintf_s(strBuff, format, args);
#else
		const int writed = vsprintf(strBuff, format, args);
#endif
		va_end(args);
		if (writed > 0)
		{
			strBuff[writed] = 0;
			return REString(strBuff, (REUInt32)writed);
		}
	}
	return REString();
}


