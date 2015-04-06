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


#ifndef __REDATE_H__
#define __REDATE_H__

#include "RECore.h"
#include "REPtr.h"

class REDateInternal;
class REString;

/// Class presents date object.
class __RE_PUBLIC_CLASS_API__ REDate
{
private:
	REPtr<REDateInternal> _t;
	
public:
	const RETimeInterval difference(const REDate & anotherDate) const;
	
	const RETimeInterval minimumDifference(const REDate & anotherDate) const;
	
	RETimeInterval timeIntervalSince1970() const;
	
	/// Using defaultFormatString
	REString toString() const;
	
	bool isEqualToDate(const REDate & anotherDate) const;
	
	/// Getter for year.
	const REUInt32 year() const;
	
	/// Getter for month.
	const REUInt32 month() const;
	
	/// Getter for day.
	const REUInt32 day() const;
	
	/// Getter for hour.
	const REUInt32 hour() const;
	
	/// Getter for minutes.
	const REUInt32 minutes() const;
	
	/// Getter for seconds.
	const RETimeInterval seconds() const;
	
	/// Getter for milliseconds.
	const REUInt32 milliseconds() const;
	
	/// Getter for microseconds.
	const REUInt32 microseconds() const;
	
	/// Setting date year.
	void setYear(const REUInt32 year);
	
	/// Setting date month.
	void setMonth(const REUInt32 month);
	
	/// Setting date day.
	void setDay(const REUInt32 day);
	
	/// Setting date hour.
	void setHour(const REUInt32 hour);
	
	/// Setting date minutes.
	void setMinutes(const REUInt32 minutes);
	
	/// Setting date seconds.
	void setSeconds(const RETimeInterval seconds);
	
	/// Assing operator.
	REDate & operator=(const REDate & anotherDate);
	
	/// Constructs date from another date object.
	REDate(const REDate & anotherDate);
	
	/// Constructs empty date.
	REDate();
	
	/// Desctructor.
	virtual ~REDate();
	
	/// Returns days count of month for year.
	static REUInt32 getDaysPerMonth(const REUInt32 month, const REUInt32 year);
	
	/// Checks is year leap.
	static bool isLeapYear(const REUInt32 year);
	
	static const char * formatString();
};

#endif /* __REDATE_H__ */


