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


#ifndef __RESTATICSTRING_H__
#define __RESTATICSTRING_H__


#include "REString.h"

/**
 @brief Immutable string wrapper for holding pointer to UTF8 string without creation new buffer and copying string data.
 @code
 REStaticString helloString("hello"); // no new string buffer & no copy, just holds pointer to const char * C string.
 // do something with helloString & forgot.
 @endcode
 */
class __RE_PUBLIC_CLASS_API__ REStaticString : public REString
{
private:
	static void freeNonCopyBuffMem(void * m);
public:
	/**
	 @brief Constructs string object with UTF8 string and/or it's len.
	 @detailed No creation new string buffer and no copy.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 */
	REStaticString(const char * utf8String, const REUInt32 utf8StringLength = RENotFound);


	/**
	 @brief Constructs string object with wide string and/or it's len.
	 @detailed In this case - new string buffer will be created.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 */
	REStaticString(const wchar_t * wideString, const REUInt32 wideStringLength = RENotFound);

	virtual ~REStaticString();
};


#endif


