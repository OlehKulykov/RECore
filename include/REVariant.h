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


#ifndef __REVARIANT_H__
#define __REVARIANT_H__

#include "REString.h"

#include <wchar.h>

class REVariantList;
class REVariantMap;

/**
 @brief Class of variant for storing base types, such as integers, reals, strings, lists and maps.
 */
class __RE_PUBLIC_CLASS_API__ REVariant
{
public:
	typedef enum _variantType
	{
		/**
		 @brief Variant type is undefined.
		 */
		TypeNone,


		/**
		 @brief Type is signed integer, used 64 bit signed int for storing values.
		 */
		TypeInteger,


		/**
		 @brief Type is unsigned integer, used 64 bit unsigned int for storing values.
		 */
		TypeUnsignedInteger,


		/**
		 @brief Type is real, used double type for storing values.
		 */
		TypeReal,


		/**
		 @brief Type is boolean, used bool type for storing values.
		 */
		TypeBool,


		/**
		 @brief Type is string object.
		 */
		TypeString,


		/**
		 @brief Type is map object.
		 */
		TypeMap,


		/**
		 @brief Type is list object.
		 */
		TypeList
	}
	/**
	 @brief Type of the variant object.
	 */
	VariantType;

protected:
	typedef union _variantUnion
	{
		int64_t int64Value;
		uint64_t uint64Value;
		double doubleValue;
		bool boolValue;
		void * pointerValue;
	}
	/**
	 @brief Union for storing varian data.
	 */
	VariantUnion;


	/**
	 @brief Union with variant data.
	 */
	VariantUnion _u;


	/**
	 @brief Type of the data.
	 */
	VariantType _t;


	/**
	 @brief Cleans the varint object, releases any alloced value and sets type to TypeNone
	 */
	void clean();

public:
	/**
	 @brief Checks union type TypeNone and pointer for NULL, used for detecting strings, lists and maps.
	 @return True if type is TypeNone and pointer is NULL, othervice false.
	 */
	bool isNULL() const;


	/**
	 @brief Checks variant for number type(integers and reals)
	 @return True if varian is integer or real, othervice false.
	 */
	bool isNumber() const;


	/**
	 @brief Getter for type of the variant.
	 */
	VariantType type() const;


	/**
	 @brief Getter for signed int value.
	 @return Signed int for integers or reals, or 0 for other types.
	 */
	int toInt() const;


	/**
	 @brief Getter for unsigned int value.
	 @return Signed int for unintegers or reals, or 0 for other types.
	 */
	unsigned int toUInt() const;


	/**
	 @brief Getter for signed int 64 bit value.
	 @return 64 bit signed int for integers or reals, or 0 for other types.
	 */
	int64_t toInt64() const;


	/**
	 @brief Getter for unsigned int 64 bit value.
	 @return 64 bit unsigned int for integers or reals, or 0 for other types.
	 */
	uint64_t toUInt64() const;


	/**
	 @brief Getter for double value.
	 @return Double value for integers or reals, or 0 for other types.
	 */
	double toDouble() const;


	/**
	 @brief Getter for boolean value.
	 @return True on type is boolean or any digit value is 1, othervice false.
	 */
	bool toBool() const;


	/**
	 @brief Setter operator for the variant with signed int value.
	 @detailed Type of the variant becomes TypeInteger.
	 @return Address of the variant.
	 */
	REVariant & operator=(int v);


	/**
	 @brief Setter operator for the variant with unsigned int value.
	 @detailed Type of the variant becomes TypeUnsignedInteger.
	 @return Address of the variant.
	 */
	REVariant & operator=(unsigned int v);


	/**
	 @brief Setter operator for the variant with float value.
	 @detailed Type of the variant becomes TypeReal.
	 @return Address of the variant.
	 */
	REVariant & operator=(float v);


	/**
	 @brief Setter operator for the variant with double value.
	 @detailed Type of the variant becomes TypeReal.
	 @return Address of the variant.
	 */
	REVariant & operator=(double v);


	/**
	 @brief Setter operator for the variant with long long value.
	 @detailed Type of the variant becomes TypeInteger.
	 @return Address of the variant.
	 */
	REVariant & operator=(long long v);


	/**
	 @brief Setter operator for the variant with unsigned long long value.
	 @detailed Type of the variant becomes TypeUnsignedInteger.
	 @return Address of the variant.
	 */
	REVariant & operator=(unsigned long long v);


	/**
	 @brief Setter operator for the variant with long double value.
	 @detailed Type of the variant becomes TypeReal and value will be truncated to double value.
	 @return Address of the variant.
	 */
	REVariant & operator=(long double v);


	/**
	 @brief Setter operator for the variant with long double value.
	 @detailed Type of the variant becomes TypeReal.
	 @return Address of the variant.
	 */
	REVariant & operator=(bool v);


	/**
	 @brief Setter operator for the variant string value if not NULL.
	 @detailed Type of the variant becomes TypeString.
	 @return Address of the variant.
	 */
	REVariant & operator=(const REString & s);


	/**
	 @brief Setter operator for the variant C string value if not NULL.
	 @detailed Type of the variant becomes TypeString.
	 @return Address of the variant.
	 */
	REVariant & operator=(const char * s);


	/**
	 @brief Setter operator for the variant wide string value if not NULL.
	 @detailed Type of the variant becomes TypeString.
	 @return Address of the variant.
	 */
	REVariant & operator=(const wchar_t * s);


	/**
	 @brief Setter operator for the variant map value.
	 @detailed Type of the variant becomes TypeMap.
	 @return Address of the variant.
	 */
	REVariant & operator=(const REVariantMap & m);


	/**
	 @brief Setter operator for the variant list value.
	 @detailed Type of the variant becomes TypeList.
	 @return Address of the variant.
	 */
	REVariant & operator=(const REVariantList & l);


	/**
	 @brief Setter operator for the variant value.
	 @detailed Type of the variant becomes same as setted variant.
	 @return Address of the variant.
	 */
	REVariant & operator=(const REVariant & v);


	/**
	 @brief Checks variant is string value.
	 @detailed Checks type for TypeString.
	 @return True if variant is string, othervice false.
	 */
	bool isString() const;


	/**
	 @brief Getter of the string address.
	 @warning Unsequre method. Use this ONLY if variant is string.
	 Check with 'isString()' mathod.
	 @return Const address of the string, or undefined address if not string.
	 */
	const REString & toString() const;


	/**
	 @brief Getter of the string address.
	 @warning Unsequre method. Use this ONLY if variant is string.
	 Check with 'isString()' mathod.
	 @return Address of the string, or undefined address if not string.
	 */
	REString & toString();


	/**
	 @brief Checks variant is map value.
	 @detailed Checks type for TypeMap.
	 @return True if variant is map, othervice false.
	 */
	bool isMap() const;


	/**
	 @brief Getter of the map address.
	 @warning Unsequre method. Use this ONLY if variant is map.
	 Check with 'isMap()' method.
	 @return Const address of the map, or undefined address if not map.
	 */
	const REVariantMap & toMap() const;


	/**
	 @brief Getter of the map address.
	 @warning Unsequre method. Use this ONLY if variant is map.
	 Check with 'isMap()' method.
	 @return Address of the map, or undefined address if not map.
	 */
	REVariantMap & toMap();


	/**
	 @brief Checks variant is list value.
	 @detailed Checks type for TypeList.
	 @return True if variant is list, othervice false.
	 */
	bool isList() const;


	/**
	 @brief Getter of the list address.
	 @warning Unsequre method. Use this ONLY if variant is list.
	 Check with 'isList()' method.
	 @return Const address of the list, or undefined address if not list.
	 */
	const REVariantList & toList() const;


	/**
	 @brief Getter of the list address.
	 @warning Unsequre method. Use this ONLY if variant is list.
	 Check with 'isList()' method.
	 @return Address of the list, or undefined address if not list.
	 */
	REVariantList & toList();


	/**
	 @brief Checks is variants are equal.
	 */
	bool isEqualToVariant(const REVariant & v) const;


	/**
	 @brief Checks is variants are equal.
	 */
	bool operator==(const REVariant & v) const;


	/**
	 @brief Checks is variants not equal.
	 */
	bool operator!=(const REVariant & v) const;


	/**
	 @brief Constructs empty variant object.
	 */
	REVariant();


	/**
	 @brief Constructs variant object with int value.
	 @param v The int value.
	 */
	REVariant(int v);


	/**
	 @brief Constructs variant object with unsigned int value.
	 @param v The unsigned int value.
	 */
	REVariant(unsigned int v);


	/**
	 @brief Constructs variant object with float value.
	 @param v The float value.
	 */
	REVariant(float v);


	/**
	 @brief Constructs variant object with double value.
	 @param v The double value.
	 */
	REVariant(double v);


	/**
	 @brief Constructs variant object with long double value.
	 @param v The long double value.
	 */
	REVariant(long double v);


	/**
	 @brief Constructs variant object with long long value.
	 @param v The long long value.
	 */
	REVariant(long long v);


	/**
	 @brief Constructs variant object with unsigned long long value.
	 @param v The unsigned long long value.
	 */
	REVariant(unsigned long long v);


	/**
	 @brief Constructs variant object with boolean value.
	 @param v The boolean value.
	 */
	REVariant(bool v);


	/**
	 @brief Constructs variant object with C string pointer.
	 @param v The C string pointer.
	 */
	REVariant(const char * v);


	/**
	 @brief Constructs variant object with wide string pointer.
	 @param v The wide string pointer.
	 */
	REVariant(const wchar_t * v);


	/**
	 @brief Constructs variant object with string object.
	 @param v The string object.
	 */
	REVariant(const REString & v);


	/**
	 @brief Constructs variant object with map object.
	 @param v The map object.
	 */
	REVariant(const REVariantMap & v);


	/**
	 @brief Constructs variant object with list object.
	 @param v The list object.
	 */
	REVariant(const REVariantList & v);


	/**
	 @brief Constructs variant object with variant object.
	 @param v The variant object.
	 */
	REVariant(const REVariant & v);


	/**
	 @brief Default virtual destructor.
	 */
	virtual ~REVariant();
};

#endif

