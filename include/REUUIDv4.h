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


#ifndef __REUUIDV4_H__
#define __REUUIDV4_H__

#include "RECore.h"

/**
 @brief UUID generator.
 @detailed Version 4 UUIDs use a scheme relying only on random numbers
 */
class __RE_PUBLIC_CLASS_API__ REUUIDv4
{
protected:
	char _u[38];

public:
	/**
	 @brief Get C string pointer to generated UUID.
	 @return Generated UUID const C string.
	 */
	const char * uuid() const;


	/**
	 @brief Default const char * C strng operator
	 @return Generated UUID const C string.
	 @code
	 std::cout << REUUIDv4() << std::endl;
	 @endcode
	 */
	operator const char* () const { return this->uuid(); }


	/**
	 @brief Constucts UUID object and generates UUID string.
	 @param isLowercase The flag for selecting lowercase or uppercase generated string. Default is lowercase.
	 */
	REUUIDv4(bool isLowercase = true);
};


#endif


