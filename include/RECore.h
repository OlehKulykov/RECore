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


#ifndef __RECORE_H__
#define __RECORE_H__

#define RECORE_VERSION_MAJOR 3
#define RECORE_VERSION_MINOR 0
#define RECORE_VERSION_PATCH 0


#if !defined(__RE_OS_WINDOWS__) && !defined(__RE_OS_ANDROID__)
/* OS not selected, try detect OS */

#if (defined(WIN32) || defined(_WIN32) || defined(WIN32_LEAN_AND_MEAN) || defined(_WIN64) || defined(WIN64))

#define __RE_OS_WINDOWS__ 1


#ifndef WIN32_LEAN_AND_MEAN
/* Exclude rarely-used stuff from Windows headers */
#define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */


#if !defined(__RE_COMPILER_MINGW__)
#if defined(__MINGW32__) || defined(__MINGW64__) || defined(MINGW)
#define __RE_COMPILER_MINGW__ 1
#endif
#endif


#endif /* END CHECKING WINDOWS PLATFORM  */
/***********************************************************************************/


#if defined(ANDROID_NDK) || defined(__ANDROID__) || defined(ANDROID)

#define __RE_OS_ANDROID__ 1

#endif /* END CHECKING ANDROID PLATFORM */
/***********************************************************************************/

#endif /* END DETECT OS */


#if defined(TARGET_OS_MAC) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(__APPLE__)
#ifndef __APPLE__
#define __APPLE__ 1
#endif
#endif


#if defined(__cplusplus) || defined(_cplusplus)
#define __RE_EXTERN__ extern "C"
#else
#define __RE_EXTERN__ extern
#endif


#if defined(__RE_OS_WINDOWS__)
#include <windows.h>

#if defined(CMAKE_BUILD) || defined(__BUILDING_RECORE_DYNAMIC_LIBRARY__)
#	if defined(_MSC_VER) || defined(__RE_COMPILER_MINGW__)
#		define __RE_PUBLIC_CLASS_API__ __declspec(dllexport)
#		define __RE_EXPORT__ __RE_EXTERN__ __declspec(dllexport)
#	elif defined(__GNUC__)
#		define __RE_PUBLIC_CLASS_API__ __attribute__((dllexport))
#		define __RE_EXPORT__ __RE_EXTERN__ __attribute__((dllexport))
#	endif
#else
#	if defined(_MSC_VER) || defined(__RE_COMPILER_MINGW__)
#		define __RE_PUBLIC_CLASS_API__ __declspec(dllimport)
#		define __RE_EXPORT__ __RE_EXTERN__ __declspec(dllimport)
#	elif defined(__GNUC__)
#		define __RE_PUBLIC_CLASS_API__ __attribute__((dllimport))
#		define __RE_EXPORT__ __RE_EXTERN__ __attribute__((dllimport))
#	endif
#endif

#endif /* __RE_OS_WINDOWS__ */



#if defined(__GNUC__)
#	if __GNUC__ >= 4
#		if !defined(__RE_PUBLIC_CLASS_API__)
#			define __RE_PUBLIC_CLASS_API__ __attribute__ ((visibility("default")))
#		endif
#	endif
#endif


#ifndef __RE_EXPORT__
#define __RE_EXPORT__ __RE_EXTERN__
#endif


#ifndef __RE_PUBLIC_CLASS_API__
#define __RE_PUBLIC_CLASS_API__
#endif


/* Standart C Library headers */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>


/* C++ Standard Library header */
#ifndef __RE_OS_ANDROID__
#include <iostream>
#endif


#if defined(__RE_OS_ANDROID__)
#include <setjmp.h>
#include <ctype.h>
#include <cerrno>
#include <cstddef>

#include <sys/types.h>
#include <sys/errno.h>
#endif


#if defined(HAVE_ASSERT_H)
#include <assert.h>
#endif


/**
 @brief 8 bit unsigned byte type.
 @detailed 8 bit unsigned byte with 1 byte size.
 */
typedef uint8_t REUByte;


/**
 @brief 16 bit unsigned integer type.
 @detailed 16 bit unsigned integer with 2 byte size.
 */
typedef uint16_t REUInt16;


/**
 @brief 32 bit unsigned integer type.
 @detailed 32 bit unsigned integer with 4 byte size.
 */
typedef uint32_t REUInt32;


/**
 @brief 64 bit unsigned integer type.
 @detailed 64 bit unsigned integer with 8 byte size.
 */
typedef uint64_t REUInt64;


/**
 @brief 8 bit signed byte type.
 @detailed 8 bit signed byte with 1 byte size.
 */
typedef int8_t REByte;


/**
 @brief 16 bit signed integer type.
 @detailed 16 bit signed integer with 2 byte size.
 */
typedef int16_t REInt16;


/**
 @brief 32 bit signed integer type.
 @detailed 32 bit signed integer with 4 byte size.
 */
typedef int32_t REInt32;


/**
 @brief 64 bit signed integer type.
 @detailed 64 bit signed integer with 8 byte size.
 */
typedef int64_t REInt64;


/**
 @brief Unsinged size type.
 @detailed 64 bit signed integer with 8 byte size.
 */
typedef size_t RESizeT;


/**
 @brief Unsigned identifier integer type.
 @detailed unsigned identifier integer type size is same as pointer.
 */
typedef uintptr_t REUIdentifier;


/**
 @brief Boolean type.
 @detailed Boolean type with possible values: 'true' or 'false'
 */
typedef bool REBOOL;



#if defined(SIZEOF_FLOAT_T)
/**
 @brief 32 bit float type.
 @detailed 32 bit float type with 4 byte size.
 */
typedef float_t REFloat32;
#else
/**
 @brief 32 bit float type.
 @detailed 32 bit float type with 4 byte size.
 */
typedef float REFloat32;
#endif


#if defined(SIZEOF_DOUBLE_T)
/**
 @brief 64 bit float type.
 @detailed 64 bit float type with 8 byte size.
 */
typedef double_t REFloat64;
#else
/**
 @brief 64 bit float type.
 @detailed 64 bit float type with 8 byte size.
 */
typedef double REFloat64;
#endif


/**
 @brief Time interval type.
 @detailed Time interval type with 8 byte size. Used for holding seconds with fractional part
 */
typedef REFloat64 RETimeInterval;


/**
 @brief Define for NULL pointer.
 */
#ifndef NULL
#define NULL 0
#endif


/**
 @brief Define for 32 bit unsigned integer maximum value.
 */
#ifndef UINT32_MAX
#define UINT32_MAX (4294967295u)
#endif


/**
 @brief Define for 32 bit unsigned integer maximum value.
 */
#ifndef REUInt32Max
#define REUInt32Max UINT32_MAX
#endif


/**
 @brief Define for 16 bit unsigned integer maximum value.
 */
#ifndef USHRT_MAX
#define USHRT_MAX (65535u)
#endif


/**
 @brief Define for 16 bit unsigned integer maximum value.
 */
#ifndef REUInt16Max
#define REUInt16Max USHRT_MAX
#endif


/**
 @brief Define for default signed integer(int) maximum value.
 */
#ifndef INT_MAX
#define INT_MAX (2147483647)
#endif


/**
 @brief Define for default signed integer(int) minimum value.
 */
#ifndef INT_MIN
#define INT_MIN (-2147483648)
#endif


/**
 @brief Define for indicating that something can't be found or undefined.
 */
#define RENotFound REUInt32Max


/**
 @brief Define for indicating that index can't be found.
 */
#define REIndexNotFound REUInt32Max


#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif


#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif



#endif

