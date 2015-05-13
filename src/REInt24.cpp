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


#include "../include/REInt24.h"

#if defined(HAVE_RECORE_CONFIG_H) 
#include "recore_config.h"
#endif

#include <string.h>

REInt24::REInt24()
{
	memset(_data, 0, 3);
}

REInt24::REInt24(const REInt32 v)
{
	this->set(v);
}

REInt24::REInt24(const REInt24 & v)
{
	this->set(v);
}

REInt32 REInt24::get() const
{
	if (_data[2] & 0x80)
	{
		return (0xff << 24) | (_data[2] << 16) | (_data[1] << 8) | (_data[0] << 0);
	}
	else
	{
		return (_data[2] << 16) | (_data[1] << 8) | (_data[0] << 0);
	}
}

REInt24 & REInt24::set(const REInt24 & v)
{
	memcpy(_data, v._data, 3);
	return (*this);
}

REInt24 & REInt24::set(const REInt32 v)
{
	memcpy(_data, &v, 3);
	return (*this);
}

REInt24 & REInt24::operator=(const REInt24 & v)
{
	return this->set(v);
}

REInt24 & REInt24::operator=(const REInt32 v)
{
	return this->set(v);
}

REInt24 REInt24::operator+(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return REInt24((REInt32)(v1 + v2));
}

REInt24 REInt24::operator-(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return REInt24((REInt32)(v1 - v2));
}

REInt24 REInt24::operator*(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return REInt24((REInt32)(v1 * v2));
}

REInt24 REInt24::operator/(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return REInt24((REInt32)(v1 / v2));
}

REInt24 REInt24::operator+(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return REInt24((REInt32)(v1 + v));
}

REInt24 REInt24::operator-(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return REInt24((REInt32)(v1 - v));
}

REInt24 REInt24::operator*(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return REInt24((REInt32)(v1 * v));
}

REInt24 REInt24::operator/(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return REInt24((REInt32)(v1 / v));
}

REInt24 & REInt24::operator+=(const REInt24 & v)
{
	REInt32 r = this->get();
	r += v.get();

	return this->set(r);
}

REInt24 & REInt24::operator-=(const REInt24 & v)
{
	REInt32 r = this->get();
	r -= v.get();

	return this->set(r);
}

REInt24 & REInt24::operator*=(const REInt24 & v)
{
	REInt32 r = this->get();
	r *= v.get();

	return this->set(r);
}

REInt24 & REInt24::operator/=(const REInt24 & v)
{
	REInt32 r = this->get();
	r /= v.get();

	return this->set(r);
}

REInt24 & REInt24::operator+=(const REInt32 v)
{
	REInt32 r = this->get();
	r += v;

	return this->set(r);
}

REInt24 & REInt24::operator-=(const REInt32 v)
{
	REInt32 r = this->get();
	r -= v;

	return this->set(r);
}

REInt24 & REInt24::operator*=(const REInt32 v)
{
	REInt32 r = this->get();
	r *= v;

	return this->set(r);
}

REInt24 & REInt24::operator/=(const REInt32 v)
{
	REInt32 r = this->get();
	r /= v;

	return this->set(r);
}

REInt24 REInt24::operator>>(const REInt32 v) const
{
	const REInt32 v1 = this->get();
	const REInt32 r = v1 >> v;

	return REInt24(r);
}

REInt24 REInt24::operator<<(const REInt32 v) const
{
	const REInt32 v1 = this->get();
	const REInt32 r = v1 << v;

	return REInt24(r);
}

REInt24 & REInt24::operator>>=(const REInt32 v)
{
	const REInt32 v1 = this->get();
	const REInt32 r = v1 >> v;

	return this->set(r);
}

REInt24 & REInt24::operator<<=(const REInt32 v)
{
	const REInt32 v1 = this->get();
	const REInt32 r = v1 << v;

	return this->set(r);
}

REInt24 REInt24::operator-()
{
	const REInt32 v1 = this->get();

	return REInt24(-v1);
}

bool REInt24::operator==(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return (v1 == v2);
}

bool REInt24::operator!=(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return (v1 != v2);
}

bool REInt24::operator>=(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return (v1 >= v2);
}

bool REInt24::operator<=(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return (v1 <= v2);
}

bool REInt24::operator>(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return (v1 > v2);
}

bool REInt24::operator<(const REInt24 & v) const
{
	const REInt32 v1 = this->get();
	const REInt32 v2 = v.get();

	return (v1 < v2);
}

bool REInt24::operator==(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return (v1 == v);
}

bool REInt24::operator!=(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return (v1 != v);
}

bool REInt24::operator>=(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return (v1 >= v);
}

bool REInt24::operator<=(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return (v1 <= v);
}

bool REInt24::operator>(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return (v1 > v);
}

bool REInt24::operator<(const REInt32 v) const
{
	const REInt32 v1 = this->get();

	return (v1 < v);
}




