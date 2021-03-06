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
 
/*--------------------------------------------------------------------------
 * This file is autogenerated from recore_config.h.in 
 * during the cmake configuration of your project. If you need to make changes
 * edit the original file NOT THIS FILE.
 * For enabling something define variable as 1, for disabling comment
 * --------------------------------------------------------------------------*/
 
#ifndef __RECORE_CONFIG_H__ 
#define __RECORE_CONFIG_H__ 


/* Build number, if avaiable */
/* #undef RECORE_BUILD_NUMBER */


/* Build with RELZMA2 compression/decompression support  */
#define RE_BUILD_WITH_LZMA2 1 


/* CoreFoundation/CoreFoundation.h */
/* #undef RE_HAVE_COREFOUNDATION_FRAMEWORK */


/* libwebsockets.h */
/* #undef RE_HAVE_LIBWEBSOCKETS_H */


/* jansson.h */
#define RE_HAVE_JANSSON_H 1


/* Windows OS */
/* #undef __RE_OS_WINDOWS__ */


/* Using the MinGW compiler in Windows and flag __RE_OS_WINDOWS__ defined */
/* #undef __RE_COMPILER_MINGW__ */


/* stdlib.h */
#define RE_HAVE_STDLIB_H 1 


/* inttypes.h */
#define RE_HAVE_INTTYPES_H 1


/* sys/types.h */
#define RE_HAVE_SYS_TYPES_H 1


/* stddef.h */
#define RE_HAVE_STDDEF_H 1


/* stdbool.h */
#define RE_HAVE_STDBOOL_H 1


/* stdint.h */
#define RE_HAVE_STDINT_H 1


/* stdarg.h */
#define RE_HAVE_STDARG_H 1


/* limits.h */
#define RE_HAVE_LIMITS_H 1


/* float.h */
#define RE_HAVE_FLOAT_H 1


/* mach/mach_time.h */
#define RE_HAVE_MACH_MACH_TIME_H 1


/* sys/time.h */
#define RE_HAVE_SYS_TIME_H 1


/* time.h */
#define RE_HAVE_TIME_H 1


/* locale.h */
#define RE_HAVE_LOCALE_H 1


/* assert.h */
#define RE_HAVE_ASSERT_H 1


/* sys/stat.h */
#define RE_HAVE_SYS_STAT_H 1


/* fcntl.h */
#define RE_HAVE_FCNTL_H 1


/* pthread.h */
#define RE_HAVE_PTHREAD_H 1


/* sys/resource.h */
#define RE_HAVE_SYS_RESOURCE_H 1


/* direct.h */
/* #undef RE_HAVE_DIRECT_H */


/* wchar.h */
#define RE_HAVE_WCHAR_H 1


/* memory.h */
#define RE_HAVE_MEMORY_H 1


/* string.h */
#define RE_HAVE_STRING_H 1


/* math.h */
#define RE_HAVE_MATH_H 1


/* malloc.h */ 
/* #undef RE_HAVE_MALLOC_H */


/* errno.h */
#define RE_HAVE_ERRNO_H 1


/* sys/errno.h */
#define RE_HAVE_SYS_ERRNO_H 1


/* io.h */
/* #undef RE_HAVE_IO_H */


/* signal.h */
/* #undef RE_HAVE_SIGNAL_H */


/* setjmp.h */
/* #undef RE_HAVE_SETJMP_H */


/* unistd.h */
#define RE_HAVE_UNISTD_H 1


/* dispatch/dispatch.h */
#define RE_HAVE_DISPATCH_DISPATCH_H 1


/* arm_neon.h */
/* #undef RE_HAVE_ARM_NEON_H */


/* includes */
#if defined(RE_HAVE_SYS_TYPES_H)
#include <sys/types.h>
#endif

#if defined(RE_HAVE_MALLOC_H)
#include <malloc.h>
#endif


/* sizes */
/* int8_t */
/* #undef RE_SIZEOF_INT8_T */

/* uint8_t */
/* #undef RE_SIZEOF_UINT8_T */

/* int16_t */
/* #undef RE_SIZEOF_INT16_T */

/* uint16_t */
/* #undef RE_SIZEOF_UINT16_T */

/* int32_t */
/* #undef RE_SIZEOF_INT32_T */

/* uint32_t */
/* #undef RE_SIZEOF_UINT32_T */

/* int64_t */
/* #undef RE_SIZEOF_INT64_T */

/* uint64_t */
/* #undef RE_SIZEOF_UINT64_T */

/* uintptr_t */
#define RE_SIZEOF_UINTPTR_T 8

/* char */
/* #undef RE_SIZEOF_CHAR */

/* long int */
#define RE_SIZEOF_LONG_INT 8

/* long long int */
#define RE_SIZEOF_LONG_LONG_INT 8

/* float */
#define RE_SIZEOF_FLOAT 4

/* double */
#define RE_SIZEOF_DOUBLE 8 

/* long double */
#define RE_SIZEOF_LONG_DOUBLE 16 

/* bool */
#define RE_SIZEOF_BOOL 1 

/* float128 */
#define RE_FLOAT128_TYPE long double 

/* int128, uint128 */
#define RE_INT128_TYPE __int128_t
#define RE_UINT128_TYPE __uint128_t



/* structures */
/* struct stat */
#define RE_HAVE_STRUCT_STAT 1 


/* struct _stat */
/* #undef RE_HAVE_STRUCT__STAT */


/* struct tm has member tm_zone */
#define RE_HAVE_STRUCT_TM_TM_ZONE 1


/* functions */
/* posix_memalign */
#define RE_HAVE_FUNCTION_POSIX_MEMALIGN 1 


/* usleep */
#define RE_HAVE_FUNCTION_USLEEP 1 


/* getrlimit */
#define RE_HAVE_FUNCTION_GETRLIMIT 1 


/* pthread_attr_setscope */
#define RE_HAVE_FUNCTION_PTHREAD_ATTR_SETSCOPE 1 


/* pthread_attr_setstacksize */
#define RE_HAVE_FUNCTION_PTHREAD_ATTR_SETSTACKSIZE 1 


/* pthread_cancel */
#define RE_HAVE_FUNCTION_PTHREAD_CANCEL 1


/* pthread_setname_np */
#define RE_HAVE_FUNCTION_PTHREAD_SETNAME_NP 1
 
 
/* pthread_set_name_np */
/* #undef RE_HAVE_FUNCTION_PTHREAD_SET_NAME_NP */


/* _stat */
/* #undef RE_HAVE_FUNCTION__STAT */


/* stat */
#define RE_HAVE_FUNCTION_STAT 1 


/* _wstat */
/* #undef RE_HAVE_FUNCTION__WSTAT */


/* access */
#define RE_HAVE_FUNCTION_ACCESS  1 


/* _access */
/* #undef RE_HAVE_FUNCTION__ACCESS */


/* _waccess */
/* #undef RE_HAVE_FUNCTION__WACCESS */


/* _mkdir */
/* #undef RE_HAVE_FUNCTION__MKDIR */


/* mkdir */
#define RE_HAVE_FUNCTION_MKDIR 1 


/* _wmkdir */
/* #undef RE_HAVE_FUNCTION__WMKDIR */


/* rename */
#define RE_HAVE_FUNCTION_RENAME 1 


/* _wrename */
/* #undef RE_HAVE_FUNCTION__WRENAME */


/* clock_gettime */
/* #undef RE_HAVE_FUNCTION_CLOCK_GETTIME */


/* difftime */ 
#define RE_HAVE_FUNCTION_DIFFTIME 1


/* time */
#define RE_HAVE_FUNCTION_TIME 1


/* localtime */
#define RE_HAVE_FUNCTION_LOCALTIME 1


/* gmtime */
#define RE_HAVE_FUNCTION_GMTIME 1


/* strftime */ 
#define RE_HAVE_FUNCTION_STRFTIME 1


/* fabsf */
/* #undef RE_HAVE_FUNCTION_FABSF */


/* fabs */
/* #undef RE_HAVE_FUNCTION_FABS */


/* floorf */
/* #undef RE_HAVE_FUNCTION_FLOORF */


/* floor */
/* #undef RE_HAVE_FUNCTION_FLOOR */


/* powf */
/* #undef RE_HAVE_FUNCTION_POWF */


/* pow */
/* #undef RE_HAVE_FUNCTION_POW */


/* cosf */
/* #undef RE_HAVE_FUNCTION_COSF */


/* cos */
/* #undef RE_HAVE_FUNCTION_COS */


/* sinf */
/* #undef RE_HAVE_FUNCTION_SINF */


/* sin */
/* #undef RE_HAVE_FUNCTION_SIN */


/* sqrtf */
/* #undef RE_HAVE_FUNCTION_SQRTF */


/* sqrt */
/* #undef RE_HAVE_FUNCTION_SQRT */


/* _wfopen */
/* #undef RE_HAVE_FUNCTION__WFOPEN */


/* _wfopen_s */
/* #undef RE_HAVE_FUNCTION__WFOPEN_S */


/* fopen_s */
/* #undef RE_HAVE_FUNCTION_FOPEN_S */


/* sscanf_s */
/* #undef RE_HAVE_FUNCTION_SSCANF_S */


/* sprintf_s */
/* #undef RE_HAVE_FUNCTION_SPRINTF_S */


/* vsprintf_s */
/* #undef RE_HAVE_FUNCTION_VSPRINTF_S */


/* dispatch_sync */
#define RE_HAVE_FUNCTION_DISPATCH_SYNC 1


/* dispatch_async */
#define RE_HAVE_FUNCTION_DISPATCH_ASYNC 1


/* dispatch_get_global_queue */
#define RE_HAVE_FUNCTION_DISPATCH_GET_GLOBAL_QUEUE 1


/* dispatch_after */
#define RE_HAVE_FUNCTION_DISPATCH_AFTER 1


#endif /* __RECORE_CONFIG_H__ */



