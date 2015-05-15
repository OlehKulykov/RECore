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


#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

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
#include "../include/REMutableString.h"
#include "../include/REString.h"
#include "../include/REAllocator.h"


int testAllocator1()
{
	REAllocator allocator = kREAllocatorMalloc;
	if (!allocator.allocateMemory) return EXIT_FAILURE;
	if (!allocator.freeMemory) return EXIT_FAILURE;

	allocator = kREAllocatorNULL;
	if (!allocator.allocateMemory) return EXIT_FAILURE;
	if (!allocator.freeMemory) return EXIT_FAILURE;

	for (size_t size = 1; size <= 131; size++)
	{
		void * mem = REMallocAligned(size);
		if (!mem) return EXIT_FAILURE;
		REFree(mem);

		mem = REMallocAlignedZero(size);
		if (!mem) return EXIT_FAILURE;
		REFree(mem);

		RESizeT asize = 0;
		mem = REMallocAlignedA(size, &asize);
		if (!mem || (asize == 0)) return EXIT_FAILURE;
		REFree(mem);
	}

	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	RELog::log("Test Allocator1 ...");
	int test = testAllocator1();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test Allocator1 OK");

	RELog::log("All tests OK");

	return EXIT_SUCCESS;
}

