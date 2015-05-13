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


#ifndef __REMUTABLESTRING_H__
#define __REMUTABLESTRING_H__


#include "REString.h"

class REString;
class REWideString;

#include <wchar.h>

/**
 @brief Class of mutable UTF8 string.
 */
class __RE_PUBLIC_CLASS_API__ REMutableString : public REString
{
protected:
	void replaceWithLen(const char * charsStringValue,
						const char * withCharsStringValue,
						const RESizeT firstLen,
						const RESizeT secondLen);
public:
	/**
	 @brief Basic assignment operator with UTF8 C string.
	 @detailed New string buffer will be created.
	 @param utf8String The UTF8 string.
	 @return Address of this string object.
	 */
	REMutableString & operator=(const char * utf8String);


	/**
	 @brief Basic assignment operator with wide character string.
	 @detailed Wide string will be converted to UTF8 and new string buffer be created.
	 @param wideString The wide string.
	 @return Address of this string object.
	 */
	REMutableString & operator=(const wchar_t * wideString);


	/**
	 @brief Basic assignment operator with wide string object.
	 @detailed Wide string will be converted to UTF8 and new string buffer be created.
	 @param anotherString The wide string object.
	 @return Address of this string object.
	 */
	REMutableString & operator=(const REWideString & anotherString);


	/**
	 @brief Basic assignment operator with immutable string object.
	 @detailed New string buffer will be created.
	 @param anotherString The immutable string object.
	 @return Address of this string object.
	 */
	REMutableString & operator=(const REString & anotherString);


	/**
	 @brief Basic assignment operator with mutable string object.
	 @detailed New string buffer will be created.
	 @param anotherString The mutable string object.
	 @return Address of this string object.
	 */
	REMutableString & operator=(const REMutableString & anotherString);


	/**
	 @brief Converts string to it's lower presentation.
	 @return Address of this string object.
	 */
	REMutableString & toLower();


	/**
	 @brief Converts string to it's upper presentation.
	 @return Address of this string object.
		*/
	REMutableString & toUpper();


	/**
	 @brief Append this string with another UTF8 C string.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 @return Address of this string object.
	 */
	REMutableString & append(const char * utf8String, const RESizeT utf8StringLength = RENotFound);


	/**
	 @brief Append this string with another wide string.
	 @detailed During appending wide characters will be converted to UTF8 presentation.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 @return Address of this string object.
	 */
	REMutableString & append(const wchar_t * wideString, const RESizeT wideStringLength = RENotFound);


	/**
	 @brief Append this string with another formated UTF8 C string.
	 @param format The format string used for creating appended string.
	 @return Address of this string object.
	 */
	REMutableString & appendFormat(const char * format, ...);


	/**
	 @brief Search and replace UTF8 substring with another UTF8 string or with NULL - meant remove substring.
	 @detailed During replacement all subscrings will be replaced.
	 @param utf8String The UTF8 string for searching.
	 @param withUTF8StringOrNULL Replace UTF8 string or NULL. In case of NULL substring will be removed.
	 @return Address of this string object.
	 */
	REMutableString & replace(const char * utf8String, const char * withUTF8StringOrNULL = NULL);


	/**
	 @brief Replaces all ocuriences of the char with another char.
	 @param needChar Char for searching.
	 @param targetChar Char for replacing.
	 @return Address of this string object.
	 */
	REMutableString & replace(const char needChar, const char targetChar);


	/**
	 @brief Search and replace wide substring with another wide string or with NULL - meant remove substring.
	 @detailed First of all substring & replace string will be converted to it's UTF8 presentation and during replacement all subscrings will be replaced.
	 @param wideString The wide string for searching.
	 @param withWideStringOrNULL Replace wide string or NULL. In case of NULL substring will be removed.
	 @return Address of this string object.
	 */
	REMutableString & replace(const wchar_t * wideString, const wchar_t * withWideStringOrNULL = NULL);


	/**
	 @brief Appends this string with path component.
	 @param pComponent Path component for appending. File name or folder name.
	 @return Address of this string object.
	 */
	REMutableString & appendPathComponent(const char * pComponent);


	/**
	 @brief Removes last path component. File name or folder name.
	 @return Address of this string object.
	 */
	REMutableString & removeLastPathComponent();


	/**
	 @brief Removes path extension from string if last path component is file name(containes dot before slash).
	 @return Address of this string object.
	 */
	REMutableString & removePathExtension();


	/**
	 @brief Constructs empty mutable string object.
	 */
	REMutableString();


	/**
	 @brief Constructs mutable string object with UTF8 string.
	 @param utf8String The UTF8 string.
	 @param utf8StringLength Length of the UTF8 string, don't include NULL terminated char. This is not count of the UTF8 characters.
	 */
	REMutableString(const char * utf8String, const REUInt32 utf8StringLength = RENotFound);


	/**
	 @brief Constructs mutable string object with wide characters string.
	 @param wideString The wide string.
	 @param wideStringLength Length of the wide string, don't include NULL terminated char.
	 */
	REMutableString(const wchar_t * wideString, const REUInt32 wideStringLength = RENotFound);


	/**
	 @brief Constructs mutable string object with wide string object.
	 @param anotherString Wide string object.
	 */
	REMutableString(const REWideString & anotherString);


	/**
	 @brief Constructs mutable string object with immutable string object.
	 @param anotherString Immutable string object.
	 */
	REMutableString(const REString & anotherString);


	/**
	 @brief Constructs mutable string object with mutable string object.
	 @param anotherString Mutable string object.
	 */
	REMutableString(const REMutableString & anotherString);


	/**
	 @brief Constructs mutable string object with autopointer to string buffer with UTF8 characters.
	 @detailed NULL terminated char should be included.
	 @param utf8StringBuffer autopointer to string buffer with UTF8 characters.
	 */
	REMutableString(const REStringBuffer & utf8StringBuffer);


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REMutableString();
};

#endif

