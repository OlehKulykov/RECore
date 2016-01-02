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


#include "../include/RELog.h"

#if defined(HAVE_RECORE_CONFIG_H) 
#include "recore_config.h"
#endif


#if defined(RE_HAVE_STDARG_H)
#include <stdarg.h>
#endif

#if defined(RE_HAVE_ANDROID_LOG_H)
#include <android/log.h>
#define LOG_TAG "RECore"
#endif

#if defined(RE_HAVE_QT)
#include <QDebug>
#endif

#include <stdio.h>
#include <time.h>



void RELog::log(const char * logString, ...)
{
	if (logString)
	{
		va_list args;
		va_start(args, logString);

#if defined(RE_HAVE_ANDROID_LOG_H)
		__android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, logString, args);
#else
		RELog::logA(logString, args);
#endif

		va_end(args);
	}
}


void RELog::logA(const char * logString, va_list arguments)
{
	if (logString)
	{
#if defined(RE_HAVE_ANDROID_LOG_H)
		__android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, logString, arguments);
#elif defined(RE_HAVE_QT)
		char buff[1024*2] = { 0 };
		vsprintf(buff, logString, arguments);
		qDebug() << buff;
#else
		vfprintf(stdout, logString, arguments);
		fprintf(stdout, "\n");
		fflush(stdout);
#endif
	}
}

static FILE * _RELogPrivateLogFile = NULL;

void RELog::logF(const char * logString, ...)
{
	FILE * f = _RELogPrivateLogFile;
	if (f && logString)
	{
		va_list args;
		va_start(args, logString);

		RELog::logFA(logString, args);

		va_end(args);
	}
}

void RELog::logFA(const char * logString, va_list arguments)
{
	FILE * f = _RELogPrivateLogFile;
	if (f && logString)
	{
		vfprintf(f, logString, arguments);
		fprintf(f, "\n");
		fflush(f);
	}
}

bool RELog::openLogFile(const char * logFilePath)
{
	if (!logFilePath) return false;

	FILE * f = _RELogPrivateLogFile;
	if (f) return true;

	f = fopen(logFilePath, "w+b");
	if (!f) return false;

	_RELogPrivateLogFile = f;
	return true;
}

void RELog::closeLogFile()
{
	FILE * f = _RELogPrivateLogFile;
	_RELogPrivateLogFile = NULL;
	if (f)
	{
		fclose(f);
	}
}


