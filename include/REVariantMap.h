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


#ifndef __REVARIANTMAP_H__
#define __REVARIANTMAP_H__


#include "REMap.h"
#include "REString.h"
#include "REVariant.h"

#include <wchar.h>

/**
 @brief Class of the variant map. Keys is string objects and values is variants.
 */
class __RE_PUBLIC_CLASS_API__ REVariantMap : public REMap<REString, REVariant>
{
public:
	/**
	 @brief Locates pointer of the variant object by C string key with specific variant type of the value.
	 @param key C string of the key.
	 @param type Type of the finded value.
	 @return Pointer of the variant value or NULL if not finded or wrong type.
	 */
	REVariant * findTypedValue(const char * key, const REVariant::VariantType type) const;


	/**
	 @brief Locates pointer of the variant object by wide string key with specific variant type of the value.
	 @param key Wide string of the key.
	 @param type Type of the finded value.
	 @return Pointer of the variant value or NULL if not finded or wrong type.
	 */
	REVariant * findTypedValue(const wchar_t * key, const REVariant::VariantType type) const;


	/**
	 @brief Locates pointer of the variant object by string object key with specific variant type of the value.
	 @param key String object of the key.
	 @param type Type of the finded value.
	 @return Pointer of the variant value or NULL if not finded or wrong type.
	 */
	REVariant * findTypedValue(const REString & key, const REVariant::VariantType type) const;


	/**
	 @brief Getter operator with key.
	 @param key String key.
	 */
	const REVariant operator[](const char * key) const;


	/**
	 @brief Getter operator with key.
	 @param key String key.
	 */
	const REVariant operator[](const wchar_t * key) const;


	/**
	 @brief Getter operator with key.
	 @param key String key.
	 */
	const REVariant operator[](const REString & key) const;


	/**
	 @brief Getter operator with key.
	 @param key String key.
	 */
	REVariant & operator[](const char * key);


	/**
	 @brief Getter operator with key.
	 @param key String key.
	 */
	REVariant & operator[](const wchar_t * key);


	/**
	 @brief Getter operator with key.
	 @param key String key.
	 */
	REVariant & operator[](const REString & key);


	/**
	 @brief Add key/values from another map.
	 @param map Map object.
	 */
	REVariantMap & operator=(const REVariantMap & map);


	/**
	 @brief Checks is maps are equal.
	 */
	bool isEqualToMap(const REVariantMap & map) const;


	/**
	 @brief Checks is maps are equal.
	 */
	bool operator==(const REVariantMap & map) const;


	/**
	 @brief Checks is maps not equal.
	 */
	bool operator!=(const REVariantMap & map) const;


	/**
	 @brief Generate JSON string.
	 @return JSON string or empty if not implemented.
	 */
	REString jsonString() const;


	/**
	 @brief Clear map and parse json string
	 */
	void fromJSONString(const REString & jsonString);


	/**
	 @brief Contructs map with keys/values from another map.
	 */
	REVariantMap(const REVariantMap & map);


	/**
	 @brief Constructs empty map.
	 */
	REVariantMap();


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REVariantMap();
};


#endif

