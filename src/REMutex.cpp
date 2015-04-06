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


#include "../include/REMutex.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif


#if !defined(__RE_HAVE_THREADS__) && defined(__RE_OS_WINDOWS__)
#include <Windows.h>
#define __RE_THREADING_WINDOWS__ 1
#define __RE_HAVE_THREADS__ 1
#endif

#if !defined(__RE_HAVE_THREADS__) && defined(HAVE_PTHREAD_H)
#include <pthread.h>
#define __RE_THREADING_PTHREAD__ 1
#define __RE_HAVE_THREADS__ 1
#endif


void REMutex::lock()
{
#if defined(__RE_THREADING_PTHREAD__)
	if (_m) pthread_mutex_lock((pthread_mutex_t *)_m);
#elif defined(__RE_THREADING_WINDOWS__)
	if (_m) TryEnterCriticalSection((LPCRITICAL_SECTION)_m);
#endif
}

void REMutex::unlock()
{
#if defined(__RE_THREADING_PTHREAD__)
	if (_m) pthread_mutex_unlock((pthread_mutex_t *)_m);
#elif defined(__RE_THREADING_WINDOWS__)
	if (_m) LeaveCriticalSection((LPCRITICAL_SECTION)_m);
#endif
}

#if defined(__RE_THREADING_PTHREAD__)
bool remutex_init_recursive_private(pthread_mutex_t * m)
{
	bool isInit = false;
	pthread_mutexattr_t attr;
	if (pthread_mutexattr_init(&attr) == 0)
	{
		if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) == 0)
			isInit = (pthread_mutex_init(m, &attr) == 0);
		pthread_mutexattr_destroy(&attr);
	}
#if defined(HAVE_ASSERT_H)
	assert(isInit);
#endif
	return isInit;
}
#endif

REMutex::REMutex() : _m(NULL)
{
#if defined(__RE_THREADING_PTHREAD__)
	void * m = malloc(sizeof(pthread_mutex_t));
	if (m)
	{
		if (remutex_init_recursive_private((pthread_mutex_t *)m)) _m = m;
		else free(m);
	}
#elif defined(__RE_THREADING_WINDOWS__)
	_m = malloc(sizeof(CRITICAL_SECTION));
	if (_m) InitializeCriticalSection((LPCRITICAL_SECTION)_m);
#endif
}

REMutex::~REMutex()
{
	if (_m)
	{
#if defined(__RE_THREADING_PTHREAD__)
		pthread_mutex_destroy((pthread_mutex_t *)_m);
#elif defined(__RE_THREADING_WINDOWS__)
		DeleteCriticalSection((LPCRITICAL_SECTION)_m);
#endif
		free(_m);
	}
}


