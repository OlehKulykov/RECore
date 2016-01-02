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
#include "../include/REMutableString.h"
#include "../include/REString.h"


int testPathExtension()
{
	REMutableString path;

	path = "/dir/file";
	if (path.pathExtension().isNotEmpty()) return EXIT_FAILURE;

	path = "/dir/file.ext";
	if (!path.pathExtension().isEqual("ext")) return EXIT_FAILURE;

	path = "/dir/file.bak.ext";
	if (!path.pathExtension().isEqual("ext")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("/dir/file.bak")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("/dir/file")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("/dir/file")) return EXIT_FAILURE;


	
	path = "/file";
	if (path.pathExtension().isNotEmpty()) return EXIT_FAILURE;

	path = "/file.ext";
	if (!path.pathExtension().isEqual("ext")) return EXIT_FAILURE;

	path = "/file.bak.ext";
	if (!path.pathExtension().isEqual("ext")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("/file.bak")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("/file")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("/file")) return EXIT_FAILURE;



	path = "file";
	if (path.pathExtension().isNotEmpty()) return EXIT_FAILURE;

	path = "file.ext";
	if (!path.pathExtension().isEqual("ext")) return EXIT_FAILURE;

	path = "file.bak.ext";
	if (!path.pathExtension().isEqual("ext")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("file.bak")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("file")) return EXIT_FAILURE;

	path.removePathExtension();
	if (!path.isEqual("file")) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int testGetLastPathComponent()
{
	REMutableString path;

	path = "/dir/file";
	if (!path.lastPathComponent().isEqual("file")) return EXIT_FAILURE;

	path = "/dir/file.ext";
	if (!path.lastPathComponent().isEqual("file.ext")) return EXIT_FAILURE;

	path = "/dir/file.ext.txt";
	if (!path.lastPathComponent().isEqual("file.ext.txt")) return EXIT_FAILURE;

	path = "/dir/";
	if (path.lastPathComponent().isNotEmpty()) return EXIT_FAILURE;




	path = "/file";
	if (!path.lastPathComponent().isEqual("file")) return EXIT_FAILURE;

	path = "/file.ext";
	if (!path.lastPathComponent().isEqual("file.ext")) return EXIT_FAILURE;

	path = "/file.ext.txt";
	if (!path.lastPathComponent().isEqual("file.ext.txt")) return EXIT_FAILURE;

	path = "/";
	if (path.lastPathComponent().isNotEmpty()) return EXIT_FAILURE;

	path = "";
	if (path.lastPathComponent().isNotEmpty()) return EXIT_FAILURE;

	path = "file";
	if (!path.lastPathComponent().isEqual("file")) return EXIT_FAILURE;

	path = "file.ext";
	if (!path.lastPathComponent().isEqual("file.ext")) return EXIT_FAILURE;

	path = "file.ext.txt";
	if (!path.lastPathComponent().isEqual("file.ext.txt")) return EXIT_FAILURE;

	path = "f";
	if (!path.lastPathComponent().isEqual("f")) return EXIT_FAILURE;

	path = ".ext";
	if (!path.lastPathComponent().isEqual(".ext")) return EXIT_FAILURE;

	path = "/.ext";
	if (!path.lastPathComponent().isEqual(".ext")) return EXIT_FAILURE;

	path = "/dir/.ext";
	if (!path.lastPathComponent().isEqual(".ext")) return EXIT_FAILURE;

	path = ".";
	if (!path.lastPathComponent().isEqual(".")) return EXIT_FAILURE;

	path = "/.";
	if (!path.lastPathComponent().isEqual(".")) return EXIT_FAILURE;

	path = "/dir/.";
	if (!path.lastPathComponent().isEqual(".")) return EXIT_FAILURE;

	REString s;

	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	RELog::log("Test PathExtension ...");
	int test = testPathExtension();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test PathExtension OK");

	RELog::log("Test GetLastPathComponent ...");
	test = testGetLastPathComponent();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test GetLastPathComponent OK");

	RELog::log("All tests OK");

	return EXIT_SUCCESS;
}

