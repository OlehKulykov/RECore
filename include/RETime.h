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


#ifndef __RETIME_H__
#define __RETIME_H__

#include "RECore.h"

/**
 @brief Class using for getting time.
 @detailed No matter how many instances of the class will still be used static methods.
 */
class __RE_PUBLIC_CLASS_API__ RETime
{
public:
	/**
	 @brief Returns current time.
	 @return Result value will be same as RETime::time();
	 */
	const RETimeInterval getTime() const;


	/**
	 @brief Pausing time functionality.
	 @detailed Result value will be same as RETime::pause();
	 @return Returns true if paused otherwise returns false on error of if already paused.
	 */
	bool pauseTime();


	/**
	 @brief Resuming time functionality.
	 @detailed Result value will be same as RETime::resume();
	 @return Returns true if resumed otherwise returns false on error of if already resumed or not paused.
	 */
	bool resumeTime();


	/**
	 @brief Checks is time functionality paused.
	 @return Result value will be same as RETime::isPaused();
	 */
	bool isTimePaused() const;


	/**
	 @return Returns current time in seconds.
	 */
	static const RETimeInterval time();


	/**
	 @brief Pausing time functionality.
	 @return Returns true if paused otherwise returns false on error of if already paused.
	 */
	static bool pause();


	/**
	 @brief Resuming time functionality.
	 @return Returns true if resumed otherwise returns false on error of if already resumed or not paused.
	 */
	static bool resume();


	/**
	 @brief Checks is time functionality paused.
	 */
	static bool isPaused();


	/**
	 @brief Converts seconds to milliseconds.
	 @param seconds Time in seconds.
	 @return Time in milliseconds.
	 */
	static const REUInt64 convertSecondsToMilliseconds(const RETimeInterval seconds);


	/**
	 @brief Converts seconds to microseconds.
	 @param seconds Time in seconds.
	 @return Time in microseconds.
	 */
	static const REUInt64 convertSecondsToMicroseconds(const RETimeInterval seconds);
};


#endif /* __RETIME_H__ */

