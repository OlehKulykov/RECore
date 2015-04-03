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


#ifndef __RESTRINGLIST_H__
#define __RESTRINGLIST_H__


#include "REList.h"
#include "REString.h"


/**
 @brief Subclass of list for holding strings objects.
 */
class __RE_PUBLIC_CLASS_API__ REStringList : public REList<REString>
{
public:
	/**
	 @brief Basic assignment operator.
	 @detailed Copy all strings to this list.
	 @param list Another string list.
	 @return Address of this list.
	 */
	REStringList & operator=(const REStringList & list);


	/**
	 @brief Append strings list with single string.
	 @param string String for appending.
	 @return Address of this list.
	 */
	REStringList & operator+=(const REString & string);


	/**
	 @brief Constructs list object with content of another list.
	 @param list
	 */
	REStringList(const REStringList & list);


	/**
	 @brief Constructs empty list object.
	 */
	REStringList();


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REStringList();
};

#endif

