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


#ifndef __RERANDOMIZER_H__
#define __RERANDOMIZER_H__


#include "RECore.h"

/// Class using for generating random numbers.
class __RE_PUBLIC_CLASS_API__ RERandomizer
{
public:
	/// Return random signed integer number in range [0, 32767]
	REInt32 intValue() const;
	
	/// Return random signed integer number in range ['lowRange', 'upRange']
	REInt32 intValueInRange(const REInt32 lowRange, const REInt32 upRange) const;
	
	/// Return random 32-bit float number in range [0.0f, 0.9(9)f]
	REFloat32 floatValue() const;
	
	/// Return random 32-bit float number in range ['lowRange', 'upRange']
	REFloat32 floatValueInRange(const REFloat32 lowRange, const REFloat32 upRange) const;

	RERandomizer();

	~RERandomizer();
};

#endif

