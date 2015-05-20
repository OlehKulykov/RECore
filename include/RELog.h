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


#ifndef __RELOG_H__
#define __RELOG_H__

#include "RECore.h"

/**
 @brief Class using for logining text messages.
 */
class __RE_PUBLIC_CLASS_API__ RELog
{
public:
	/**
	 @brief Log message with arguments.
	 @param logString Format scring, same as for printf
	 */
	static void log(const char * logString, ...);


	/**
	 @brief Log message with arguments list.
	 @param logString Format scring, same as for printf
	 */
	static void logA(const char * logString, va_list arguments);


	/**
	 @brief Log message to log file with arguments.
	 @param logString Format scring, same as for printf
	 */
	static void logF(const char * logString, ...);


	/**
	 @brief Log message log file with arguments list.
	 @param logString Format scring, same as for printf
	 */
	static void logFA(const char * logString, va_list arguments);


	/**
	 @brief Open log file for logining.
	 @param logFilePath Full log file path.
	 @return True if already opened or create/open, othervise false.
	 */
	static bool openLogFile(const char * logFilePath);


	/**
	 @brief Close log file if it's opened.
	 */
	static void closeLogFile();
};


#if defined(DEBUG) || defined(_DEBUG)
#define RE_DEBUG_LOG(s) RELog::log(s);
#define RE_DEBUG_LOGA(s, ...) RELog::log(s, __VA_ARGS__);
#define RE_DEBUG_LOGF(s) RELog::logF(s);
#define RE_DEBUG_LOGFA(s, ...) RELog::logF(s, __VA_ARGS__);
#else
#define RE_DEBUG_LOG(s)
#define RE_DEBUG_LOGA(s, ...)
#define RE_DEBUG_LOGF(s)
#define RE_DEBUG_LOGFA(s, ...)
#endif



#endif


