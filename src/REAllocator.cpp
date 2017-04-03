/*
 *   Copyright (c) 2012 - 2017 Kulykov Oleh <info@resident.name>
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

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#include <string.h>

void * REMalloc(RESizeT size) {
	return (size > 0) ? malloc((size_t)size) : NULL;
}

void * REMallocZero(RESizeT size) {
	void * m = (size > 0) ? malloc(size) : NULL;
	if (m) {
		memset(m, 0, size);
	}
	return m;
}

void * REMallocAlignedA(RESizeT size, RESizeT * allocatedSize) {
	if (size > 0) {
#if defined(RE_HAVE_FUNCTION_POSIX_MEMALIGN)
		const size_t alignment = sizeof(void *);
		if (size < alignment) {
			size = alignment;
		} else {
			const size_t left = (size % alignment);
			if (left > 0) {
				size += (alignment - left);
			}
		}

		void * m = NULL;
		if (posix_memalign((void**)&m, alignment, size) == 0) {
			if (allocatedSize) *allocatedSize = size;
			return m;
		}
#else
		void * m = malloc(size);
		if (m) {
			if (allocatedSize) *allocatedSize = size;
			return m;
		}
#endif
	}

	if (allocatedSize) *allocatedSize = 0;
	return NULL;
}

void * REMallocAlignedZero(RESizeT size) {
	RESizeT asize = 0;
	void * m = REMallocAlignedA(size, &asize);
	if (m && asize) {
		memset(m, 0, asize);
	}
	return m;
}

void * REMallocAligned(RESizeT size) {
	return REMallocAlignedA(size, NULL);
}

void REFree(void * memory) {
	if (memory) free(memory);
}

void * REMallocNULL(RESizeT size) {
	return NULL;
}

void REFreeNULL(void * m) {

}

REAllocator kREAllocatorMalloc = {
#if defined(__clang__)
	.allocateMemory = &REMalloc,
	.freeMemory = &REFree
#else
	&REMalloc,
	&REFree
#endif
};

REAllocator kREAllocatorNULL = {
#if defined(__clang__)
	.allocateMemory = &REMallocNULL,
	.freeMemory = &REFreeNULL
#else
	&REMallocNULL,
	&REFreeNULL
#endif
};

