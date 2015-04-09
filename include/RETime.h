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

/// Class using for getting time.
/// No matter how many instances of the class will still be used static methods.
class __RE_PUBLIC_CLASS_API__ RETime
{
public:
	/// Returns current time.
	/// Result value will be same as RETime::time();
	const RETimeInterval getTime() const;
	
	/// Pausing time functionality.
	/// Returns true if paused otherwise returns false on error of if already paused.
	/// Result value will be same as RETime::pause();
	bool pauseTime();
	
	/// Resuming time functionality.
	/// Returns true if resumed otherwise returns false on error of if already resumed or not paused.
	/// Result value will be same as RETime::resume();
	bool resumeTime();
	
	/// Checks is time functionality paused.
	/// Result value will be same as RETime::isPaused();
	bool isTimePaused() const;
	
	/// Returns current time.
	static const RETimeInterval time();
	
	/// Pausing time functionality.
	/// Returns true if paused otherwise returns false on error of if already paused.
	static bool pause();
	
	/// Resuming time functionality.
	/// Returns true if resumed otherwise returns false on error of if already resumed or not paused.
	static bool resume();
	
	/// Checks is time functionality paused.
	static bool isPaused();
	
	/// Converts seconds to milliseconds.
	static const REUInt64 convertSecondsToMilliseconds(const RETimeInterval seconds);
	
	/// Converts seconds to microseconds.
	static const REUInt64 convertSecondsToMicroseconds(const RETimeInterval seconds);
};


#endif /* __RETIME_H__ */

