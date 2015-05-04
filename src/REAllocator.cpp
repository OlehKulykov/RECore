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


#include "../include/REAllocator.h"

#include <string.h>

void * REMalloc(RESizeT size)
{
	return (size > 0) ? malloc((size_t)size) : NULL;
}

void * REMallocZero(RESizeT size)
{
	void * m = (size > 0) ? malloc((size_t)size) : NULL;
	if (m)
	{
		memset(m, 0, (size_t)size);
	}
	return m;
}

void REFree(void * memory)
{
	if (memory) free(memory);
}

void * REMallocNULL(RESizeT size)
{
	return NULL;
}

void REFreeNULL(void * m)
{

}

REAllocator allocatorMalloc =
{
#if defined(__clang__)
	.allocateMemory = &REMalloc,
	.freeMemory = &REFree
#else
	&REMalloc,
	&REFree
#endif
};

REAllocator allocatorNULL =
{
#if defined(__clang__)
	.allocateMemory = &REMallocNULL,
	.freeMemory = &REFreeNULL
#else
	&REMallocNULL,
	&REFreeNULL
#endif
};

