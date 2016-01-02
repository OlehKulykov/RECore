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
#include "../include/REVariantList.h"
#include "../include/REVariantMap.h"
#include "../include/REVariant.h"

int testJSONList()
{
	REVariantList list;

	list.fromJSONString("");
	if (!list.isEmpty()) return EXIT_FAILURE;

	list.fromJSONString("[]");
	if (!list.isEmpty()) return EXIT_FAILURE;

	list.fromJSONString("{}");
	if (!list.isEmpty()) return EXIT_FAILURE;

	list.fromJSONString("[1, -1, 0, null, \"hello\"]");
	if (list.isEmpty()) return EXIT_FAILURE;

	if (!list.isContaines(1)) return EXIT_FAILURE;
	if (!list.isContaines(-1)) return EXIT_FAILURE;
	if (!list.isContaines(0)) return EXIT_FAILURE;
	if (!list.isContaines(REVariant())) return EXIT_FAILURE;
	if (!list.isContaines("hello")) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int testJSONMap()
{
	REVariantMap map;

	map.fromJSONString("");
	if (!map.isEmpty()) return EXIT_FAILURE;

	map.fromJSONString("[]");
	if (!map.isEmpty()) return EXIT_FAILURE;

	map.fromJSONString("{}");
	if (!map.isEmpty()) return EXIT_FAILURE;

	map.fromJSONString("{ \"k1\" : 1, \"k2\" : [1], \"k3\" : null }");
	if (map.isEmpty()) return EXIT_FAILURE;

	REVariantList list1;
	list1 += 1;
	if (map["k1"] != 1) return EXIT_FAILURE;
	if (map["k2"] != list1) return EXIT_FAILURE;
	if (map["k3"] != REVariant()) return EXIT_FAILURE;
	if (!map["k3"].isNULL()) return EXIT_FAILURE;

	REVariantMap map2;
	map2.fromJSONString("{ \"k1\" : 1, \"k2\" : [1], \"k3\" : null }");
	if (map != map2) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	RELog::log("Test JSONList ...");
	int test = testJSONList();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test JSONList OK");


	RELog::log("Test JSONMap ...");
	test = testJSONMap();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test JSONMap OK");


	RELog::log("All tests OK");

	return EXIT_SUCCESS;
}

