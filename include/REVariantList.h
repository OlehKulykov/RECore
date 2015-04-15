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


#ifndef __REVARIANTLIST_H__
#define __REVARIANTLIST_H__

#include "REVariant.h"
#include "REList.h"

/**
 @brief Class of the list containes variants objects.
 */
class __RE_PUBLIC_CLASS_API__ REVariantList : public REList<REVariant>
{
public:
	/**
	 @brief Add variant to the list with int value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(int v);


	/**
	 @brief Add variant to the list with unsigned int value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(unsigned int v);


	/**
	 @brief Add variant to the list with float value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(float v);


	/**
	 @brief Add variant to the list with double value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(double v);


	/**
	 @brief Add variant to the list with long long value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(long long v);


	/**
	 @brief Add variant to the list with unsigned long long value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(unsigned long long v);


	/**
	 @brief Add variant to the list with long double value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(long double v);


	/**
	 @brief Add variant to the list with boolean value.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(bool v);


	/**
	 @brief Add variant to the list with string object.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(const REString & s);


	/**
	 @brief Add variant to the list with C string.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(const char * s);


	/**
	 @brief Add variant to the list with wide string.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(const wchar_t * s);


	/**
	 @brief Add variant to the list with map object.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(const REVariantMap & m);


	/**
	 @brief Add variant to the list with list object.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(const REVariantList & l);


	/**
	 @brief Add variant to the list with varing object.
	 @return Address of this list object.
	 */
	REVariantList & operator+=(const REVariant & v);


	/**
	 @brief Set variant objects from another list.
	 @return Address of this list object.
	 */
	REVariantList & operator=(const REVariantList & list);


	/**
	 @brief Generate JSON string.
	 @return JSON string or empty if not implemented.
	 */
	REString jsonString() const;


	/**
	 @brief Clear list and parse json string
	 */
	void fromJSONString(const REString & jsonString);


	/**
	 @brief Constructs list with objects from another list.
	 */
	REVariantList(const REVariantList & list);


	/**
	 @brief Constructs empty list.
	 */
	REVariantList();


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REVariantList();
};

#endif

