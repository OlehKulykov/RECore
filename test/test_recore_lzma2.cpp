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
#include "../include/RELZMA2.h"

int testLZMA2()
{
#if defined(RE_BUILD_WITH_LZMA2)
	const char * inText = "Lorem ipsum dolor sit amet, odio erant ut vis. Libris moderatius reprimique sit ad, sed aeque perfecto an, ius ut porro iudico argumentum. Ei omnis explicari moderatius qui, ad qui quas atqui doctus. Labores propriae persecuti te per, ei cibo nostrud probatus mel, vix commodo nominati ne.";
	const RESizeT len = strlen(inText);

	RELZMA2Compressor compr;
	compr.compress(inText, len);

	RELZMA2Decompressor decompr;
	decompr.decompress(compr.data(), compr.size());

	if (len != decompr.size())
	{
		fprintf(stderr, "Decompression size not equal");
		return EXIT_FAILURE;
	}

	if (strncmp(inText, (const char *)decompr.data(), len) != 0)
	{
		fprintf(stderr, "Decompressed data not same as source");
		return EXIT_FAILURE;
	}
#else
#endif
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	RELog::log("Test LZMA2 ...");
	int test = testLZMA2();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test LZMA2 OK");

	RELog::log("All tests OK");

	return EXIT_SUCCESS;
}

