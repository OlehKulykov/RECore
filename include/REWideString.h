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


#ifndef __REWIDESTRING_H__
#define __REWIDESTRING_H__

#include "REStringBase.h"
#include "REMutableString.h"

/**
 @brief String class with wide charecters reperesentation.
 */
class __RE_PUBLIC_CLASS_API__ REWideString : public REStringBase
{
public:
	/**
	 @brief Getter for immutable string with UTF8 string presentation.
	 @return New string object.
	 */
	REString string() const;


	/**
	 @brief Getter for mutable string with UTF8 string presentation.
	 @return New string object.
	 */
	REMutableString mutableString() const;


	/**
	 @brief Getter for wide charaters string presentation.
	 @return Pointer to wide chars string.
	 */
	const wchar_t * wideChars() const;


	/**
	 @brief Getter for the number of wide characters.
	 @detailed NULL terminated character not inluded in this number.
	 @return number of wide characters.
	 */
	RESizeT length() const;


	/**
	 @brief Basic assigment operator with UTF8 string.
	 @detailed During assigment all UTF8 chars will be converted to wide.
	 @param utf8String Pointer to UTF8 string.
	 @return Address of this string object.
	 */
	REWideString & operator=(const char * utf8String);


	/**
	 @brief Basic assigment operator with wide string.
	 @detailed No conversion during assigment, chars copyed as is.
	 @param wideString Pointer to wide character string.
	 @return Address of this string object.
	 */
	REWideString & operator=(const wchar_t * wideString);


	/**
	 @brief Basic assigment operator with wide string.
	 @detailed No conversion or copying. String buffer will be retained.
	 @param anotherString The wide string object.
	 @return Address of this string object.
	 */
	REWideString & operator=(const REWideString & anotherString);


	/**
	 @brief Basic assigment operator with immutable string.
	 @detailed During assigment all UTF8 chars will be converted to wide and new string buffer will be created.
	 @param anotherString The immutable string object.
	 @return Address of this string object.
	 */
	REWideString & operator=(const REString & anotherString);


	/**
	 @brief Basic assigment operator with mutable string.
	 @detailed During assigment all UTF8 chars will be converted to wide and new string buffer will be created.
	 @param anotherString The mutable string object.
	 @return Address of this string object.
	 */
	REWideString & operator=(const REMutableString & anotherString);


	/**
	 @brief Cast operator for wide chars string.
	 @return Pointer to wide chars string.
	 */
	operator const wchar_t* () { return this->wideChars(); }


	/**
	 @brief Cast operator for wide chars string.
	 @return Pointer to wide chars string.
	 */
	operator const wchar_t* () const { return this->wideChars(); }


	/**
	 @brief Constructs empty wide string object.
	 */
	REWideString();


	/**
	 @brief Constructs wide string object with UTF8 string.
	 @detailed UTF8 converts to wide and creates new string buffer.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 */
	REWideString(const char * utf8String, const REUInt32 utf8StringLength = RENotFound);


	/**
	 @brief Constructs wide string object with wide string.
	 @detailed No conversion, string copyed to new string buffer as is.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 */
	REWideString(const wchar_t * wideString, const REUInt32 wideStringLength = RENotFound);


	/**
	 @brief Constructs wide string object with onother wide string object.
	 @detailed String buffer will be retained.
	 @param anotherString Wide string object.
	 */
	REWideString(const REWideString & anotherString);


	/**
	 @brief Constructs wide string object with onother immutable UTF8 string object.
	 @detailed Chars converted to wide and new copyed to new string buffer.
	 @param anotherString The immutable UTF8 string object.
	 */
	REWideString(const REString & anotherString);


	/**
	 @brief Constructs wide string object with onother mutable UTF8 string object.
	 @detailed Chars converted to wide and new copyed to new string buffer.
	 @param anotherString The mutable UTF8 string object.
	 */
	REWideString(const REMutableString & anotherString);


	/**
	 @brief Constructs wide string object with autopointer to string buffer with wide characters.
	 @detailed NULL terminated char should be included.
	 @param wideStringBuffer autopointer to string buffer with wide characters.
	 */
	REWideString(const REPtr<REBuffer> & wideStringBuffer);


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REWideString();
};

#endif


