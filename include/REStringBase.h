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


#ifndef __RESTRINGBASE_H__
#define __RESTRINGBASE_H__


#include "REPtr.h"
#include "REMutableBuffer.h"

#include <string.h>

#include <wchar.h>

/**
 @brief Type of the string.
 */
typedef enum _REStringType
{
	/**
	 @brief UTF8 type. Using "char" as type.
	 */
	REStringTypeUTF8 = 0,


	/**
	 @brief Wide type. Using "whar_t" as type.
	 */
	REStringTypeWide = 1
}
/**
 @brief Type of the string.
 */
REStringType;


typedef REPtr<REBuffer> REStringBuffer;

/**
 @brief Base string class. Holds autopointer to string data buffer.
 @detailed During data assigment strings can be converted between UTF8 and wide char presentation.
 */
class __RE_PUBLIC_CLASS_API__ REStringBase
{
protected:
	REStringBuffer _p;

	const void * stringBuffer() const;
	RESizeT stringBufferSize() const;
public:
	/**
	 @brief Check is string empty.
	 @return True if string is empty, othervice false.
	 */
	bool isEmpty() const;


	/**
	 @brief Check is string not empty.
	 @return True if string not empty(has characters), othervice false.
	 */
	bool isNotEmpty() const;


	/**
	 @brief Clears string. Releases string buffer.
	 */
	void clear();


	/**
	 @brief Set string data with UTF8 string.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 If not assigned than lenght will be calculated with "strlen" function.
	 @param toType Type of the result string buffer type. If not assigned using UTF8 type by default.
	 */
	void setFromUTF8String(const char * utf8String,
						   const RESizeT utf8StringLength = RENotFound,
						   const REStringType toType = REStringTypeUTF8);


	/**
	 @brief Set string data with wide string.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 @param toType Type of the result string buffer type. If not assigned using UTF8 type by default.
	 */
	void setFromWideString(const wchar_t * wideString,
						   const RESizeT wideStringLength = RENotFound,
						   const REStringType toType = REStringTypeUTF8);

	/**
	 @brief Compare byte-to-byte receiver string buffer with another string buffer.
	 @param s Another string.
	 @return True if both string buffers are byte-to-byte equal.
	 */
	bool operator==(const REStringBase & s) const;


	/**
	 @brief Construct empty string object.
	 */
	REStringBase();


	/**
	 @brief Constructs string object with UTF8 string.
	 @param utf8String The UTF8String.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 @param toType Type of the result string buffer type. If not assigned using UTF8 type by default
	 */
	REStringBase(const char * utf8String,
				 const RESizeT utf8StringLength = RENotFound,
				 const REStringType toType = REStringTypeUTF8);


	/**
	 @brief Constructs string object with wide characters string.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 @param toType Type of the result string buffer type. If not assigned using UTF8 type by default.
	 */
	REStringBase(const wchar_t * wideString,
				 const RESizeT wideStringLength = RENotFound,
				 const REStringType toType = REStringTypeUTF8);


	/**
	 @brief Construct string object with autopointer object to string buffer.
	 @detailed Useful for imutable strings basic assigment, just retain buffer without creating new and copy data.
	 @param stringBuffer Autopinter to string buffer.
	 */
	REStringBase(const REStringBuffer & stringBuffer);


	/**
	 @brief Default string desctructor.
	 */
	virtual ~REStringBase();
};

#endif

