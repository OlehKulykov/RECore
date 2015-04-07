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

#include <RECore/RECore.h>


#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif


#if defined(CMAKE_BUILD)
#undef CMAKE_BUILD
#endif

#include <RECore/RERandomizer.h>
#include <RECore/RELog.h>


int testInt()
{
	RERandomizer r;

	for (int i = 0; i < 200; i++)
	{
		const REInt32 v = r.intValue();
		if (v < 0 || v > RAND_MAX)
		{
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int testIntRange()
{
	RERandomizer r;

	for (int i = 0; i < 200; i++)
	{
		const REInt32 v = r.intValueInRange(0, 100);
		if (v < 0 || v > 100)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REInt32 v = r.intValueInRange(-100, 0);
		if (v < -100 || v > 0)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REInt32 v = r.intValueInRange(-10, 10);
		if (v < -10 || v > 10)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REInt32 v = r.intValueInRange('a', 'z');
		if (v < 'a' || v > 'z')
		{
			return EXIT_FAILURE;
		}
	}


	for (int i = 0; i < 200; i++)
	{
		const REInt32 v = r.intValueInRange('A', 'Z');
		if (v < 'A' || v > 'Z')
		{
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int testFloat()
{
	RERandomizer r;

	for (int i = 0; i < 200; i++)
	{
		const REFloat32 v = r.floatValue();
		if (v < 0 || v > 1)
		{
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}


int testFloatInRange()
{
	RERandomizer r;

	for (int i = 0; i < 200; i++)
	{
		const REFloat32 v = r.floatValueInRange(0, 10);
		if (v < 0 || v > 10)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REFloat32 v = r.floatValueInRange(0, 1);
		if (v < 0 || v > 1)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REFloat32 v = r.floatValueInRange(-1, 0);
		if (v < -1 || v > 0)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REFloat32 v = r.floatValueInRange(-2, -1);
		if (v < -2 || v > -1)
		{
			return EXIT_FAILURE;
		}
	}

	for (int i = 0; i < 200; i++)
	{
		const REFloat32 v = r.floatValueInRange(-2, 4);
		if (v < -2 || v > 4)
		{
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
	RELog::log("Test testInt ...");
	int test = testInt();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test testInt OK");

	RELog::log("Test testIntRange ...");
	test = testIntRange();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test testIntRange OK");

	RELog::log("Test testFloat ...");
	test = testFloat();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test testFloat OK");

	RELog::log("Test testFloatInRange ...");
	test = testFloatInRange();
	assert(test == EXIT_SUCCESS);
	if (test != EXIT_SUCCESS) return EXIT_FAILURE;
	RELog::log("Test testFloatInRange OK");

	RELog::log("All tests OK");

	return EXIT_SUCCESS;
}

