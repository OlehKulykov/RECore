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


#include "../include/RERandomizer.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#ifndef RAND_MAX
#define	RAND_MAX 0x7fffffff
#endif

#include <time.h>


/* 0 to 32767 */
REInt32 RERandomizer::intValue() const
{
	return rand();
}

/* lowRange to upRange */
REInt32 RERandomizer::intValueInRange(const REInt32 lowRange, const REInt32 upRange) const
{
	return ((rand() % upRange) + lowRange);
}

/* 0.0f to 0.9(9)f */
REFloat32 RERandomizer::floatValue() const
{
	return (REFloat32)((REFloat64)rand() / (REFloat64)(RAND_MAX + 1.0));
}

/* lowRange to upRange */	
REFloat32 RERandomizer::floatValueInRange(const REFloat32 lowRange, const REFloat32 upRange) const
{
	return (REFloat32)((((REFloat64)rand() / (REFloat64)(RAND_MAX + 1.0)) * (upRange - lowRange)) + lowRange);
}

RERandomizer::RERandomizer()
{
	static REBOOL isNeedInitialize = true;
	if (isNeedInitialize) 
	{
		/* initialize random seed: */
		srand ( (unsigned int)time(NULL) );
		isNeedInitialize = false;
	}
}

RERandomizer::~RERandomizer()
{

}

