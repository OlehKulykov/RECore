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


#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <string.h>

#if defined(CMAKE_BUILD)
#undef CMAKE_BUILD
#endif

#if defined(__BUILDING_RECORE_DYNAMIC_LIBRARY__)
#undef __BUILDING_RECORE_DYNAMIC_LIBRARY__
#endif

#define HAVE_ASSERT_H 1

#include "../include/RECore.h"


#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif


#if defined(CMAKE_BUILD)
#undef CMAKE_BUILD
#endif

#include "../include/REUUIDv4.h"
#include "../include/RELog.h"
#include "../include/RESwap.h"

typedef union _UDIGIT
{
	REUInt32 value;
	char string[4];
} UDIGIT;

int testSwap1()
{
	REUByte b1 = 124;
	if (RESwap<REUByte>(b1) != 124)
	{
		return EXIT_FAILURE;
	}

	UDIGIT d1;
	memcpy(d1.string, "helo", 4);

	UDIGIT d2;
	d2.value = RESwap<REUInt32>(d1.value);
	if (memcmp(d2.string, "oleh", 4) != 0)
	{
		return EXIT_FAILURE;
	}

	d2.value = RESwap<REUInt32>(d2.value);
	if (d2.value != d1.value)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	RELog::log("Test Swap1 ...");
	int test = testSwap1();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test Swap1 OK");

	RELog::log("All tests OK");

	return EXIT_SUCCESS;
}

