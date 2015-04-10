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


#ifndef __RESTRING_H__
#define __RESTRING_H__

#include "REStringBase.h"


class REMutableString;
class REWideString;

#include <wchar.h>

/**
 @brief Class of the immutable string.
 */
class __RE_PUBLIC_CLASS_API__ REString : public REStringBase
{
public:
	/**
	 @brief Return mutable string object, string buffer will be copyed.
	 @return New mutable string.
	 */
	REMutableString mutableString() const;


	/**
	 @brief Creates and return wide string object. During creating converting to wide string presentation could be.
	 @return Wide string object.
	 */
	REWideString wideString() const;


	/**
	 @brief Pointer to UTF8 string.
	 @return Pointer to string or NULL if string is empty.
	 */
	const char * UTF8String() const;


	/**
	 @brief Length of the string.
	 @return Length of the string, this is not count of the UTF8 characters.
	 */
	RESizeT length() const;


	/**
	 @brief Check is string containes non ASCII symbols.
	 @return True if containes, othervice false.
	 */
	bool isContainsNonASCII() const;


	/**
	 @brief Check string containes UTF8 string. Case sensitive.
	 @param utf8String The UTF8 string to search.
	 @return True if containes, othervice false.
	 */
	bool isContaines(const char * utf8String) const;


	/**
	 @brief Check string containes wide string. Case sensitive.
	 @detailed BEfore searching wide string will be converted to UTF8 presentation.
	 @param wideString The wide string to search.
	 @return True if containes, othervice false.
	 */
	bool isContaines(const wchar_t * wideString) const;


	/**
	 @brief Check is string is digit presentation.
	 @detailed Checked for +/- and dot.
	 @return True if digit, othervice false.
	 */
	bool isDigit() const;


	/**
	 @brief Check is string is equal to another string. Case sensitive.
	 @param anotherString Wide string object.
	 @return True is equal, othervice false.
	 */
	bool isEqual(const REWideString & anotherString) const;


	/**
	 @brief Check is string is equal to another string. Case sensitive.
	 @param anotherString String object.
	 @return True is equal, othervice false.
	 */
	bool isEqual(const REString & anotherString) const;


	/**
	 @brief Check is string is equal to another string. Case sensitive.
	 @param anotherString String object.
	 @return True is equal, othervice false.
	 */
	bool isEqual(const REMutableString & anotherString) const;


	/**
	 @brief Check is string is equal to UTF8 string. Case sensitive.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 @return True is equal, othervice false.
	 */
	bool isEqual(const char * utf8String, const RESizeT utf8StringLength = RENotFound) const;


	/**
	 @brief Check is string is equal to UTF8 string. Case sensitive.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 @return True is equal, othervice false.
	 */
	bool isEqual(const wchar_t * wideString, const RESizeT wideStringLength = RENotFound) const;


	/**
	 @brief Assign operator with UTF8 string;
	 @param utf8String The UTF8 string.
	 @return Address of this string.
	 */
	REString & operator=(const char * utf8String);


	/**
	 @brief Assign operator with wide string;
	 @param wideString The wide string.
	 @return Address of this string.
	 */
	REString & operator=(const wchar_t * wideString);


	/**
	 @brief Assign operator with wide string object;
	 @param anotherString The wide string object.
	 @return Address of this string.
	 */
	REString & operator=(const REWideString & anotherString);


	/**
	 @brief Assign operator with string object;
	 @param anotherString The string object.
	 @return Address of this string.
	 */
	REString & operator=(const REString & anotherString);


	/**
	 @brief Assign operator with mutable string object;
	 @param anotherString The mutable string object.
	 @return Address of this string.
	 */
	REString & operator=(const REMutableString & anotherString);


	/**
	 @brief Equal operator.
	 @param s The string object for compare.
	 @return True if equal, othervice false.
	 */
	bool operator==(const REString & s) const;


	/**
	 @brief const char * type operator.
	 */
	operator const char* () { return this->UTF8String(); }


	/**
	 @brief const char * type operator.
	 */
	operator const char* () const { return this->UTF8String(); }


	/**
	 @brief Path extension.
	 @return String with path extension without dot char.
	 */
	REString pathExtension() const;


	/**
	 @brief Last path component.
	 @return Returns string with last path componect.
	 */
	REString lastPathComponent() const;


	/**
	 @brief Try find first integer value from the string.
	 @param isOk Pointer to flag which indicates successfull conversion.
	 @return Integer value or zero.
	 */
	REInt64 integerValue(bool * isOk = NULL) const;


	/**
	 @brief Try find first float value from the string.
	 @param isOk Pointer to flag which indicates successfull conversion.
	 @return Float value or zero.
	 */
	REFloat64 floatValue(bool * isOk = NULL) const;


	/**
	 @brief Contructs empty string object.
	 */
	REString();


	/**
	 @brief Constructs string object with UTF8 string and/or it's len.
	 @detailed New string buffer will be created.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 */
	REString(const char * utf8String, const RESizeT utf8StringLength = RENotFound);


	/**
	 @brief Constructs string object with wide string and/or it's len.
	 @detailed New string buffer will be created.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 */
	REString(const wchar_t * wideString, const RESizeT wideStringLength = RENotFound);


	/**
	 @brief Constructs string object with onother wide string object.
	 @detailed New string buffer will be created and wide string will be converted to UTF8.
	 @param anotherString Wide string object.
	 */
	REString(const REWideString & anotherString);


	/**
	 @brief Constructs string object with onother string object.
	 @detailed String buffer will be retained.
	 @param anotherString The string object.
	 */
	REString(const REString & anotherString);


	/**
	 @brief Constructs string object with mutable string object.
	 @detailed New string buffer will be created.
	 @param anotherString The tring object.
	 */
	REString(const REMutableString & anotherString);


	/**
	 @brief Constructs string object with autopointer to UTF8 string buffer.
	 @detailed String buffer will be retained. NULL terminated character should be present at the end.
	 @param utf8StringBuffer The UTF8 string buffer.
	 */
	REString(const REPtr<REBuffer> & utf8StringBuffer);


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REString();


	/**
	 @brief Create new formated string.
	 @detailed Max size for the result string is 1024.
	 @param format The format UTF8 string, same as for sprintf functions.
	 @return New string.
	 */
	static REString createWithFormat(const char * format, ...);
};

#endif

