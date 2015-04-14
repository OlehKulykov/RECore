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


#ifndef __REINT24_H__
#define __REINT24_H__

#include "RECore.h"

#include <string.h>

#define INT24_MAX (8388607)
#define INT24_MIN (-8388607)


class __RE_PUBLIC_CLASS_API__ REInt24
{
protected:
	REUByte _data[3];
	
public:
	REInt24()
    {
		memset(_data, 0, 3);
    }
	
    REInt24(const REInt32 v)
    {
		this->set(v);
    }
	
    REInt24(const REInt24 & v)
    {
		this->set(v);
    }
	
	REInt32 get() const
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
	
	REInt24 & set(const REInt24 & v)
	{
		memcpy(_data, v._data, 3);
		return (*this);
	}
	
	REInt24 & set(const REInt32 v)
    {
		memcpy(_data, &v, 3);
		return (*this);
    }

    operator REInt32() const
    {
        return this->get();
    }
	
    operator REFloat32() const
    {
        return (REFloat32)this->get();
    }
	
    REInt24 & operator=(const REInt24 & v)
    {
        return this->set(v);
    }
	
    REInt24 & operator=(const REInt32 v)
    {
		return this->set(v);
    }

    REInt24 operator+(const REInt24 & v) const
    {
        return REInt24(this->get() + v.get());
    }
	
    REInt24 operator-(const REInt24 & v) const
    {
        return REInt24(this->get() - v.get());
    }
	
    REInt24 operator*(const REInt24 & v) const
    {
        return REInt24(this->get() * v.get());
    }
	
    REInt24 operator/(const REInt24 & v) const
    {
        return REInt24(this->get() / v.get());
    }
	
    REInt24 operator+(const REInt32 v) const
    {
        return REInt24(this->get() + v);
    }
	
    REInt24 operator-(const REInt32 v) const
    {
        return REInt24(this->get() - v);
    }
	
    REInt24 operator*(const REInt32 v) const
    {
        return REInt24(this->get() * v);
    }
	
    REInt24 operator/(const REInt32 v) const
    {
        return REInt24(this->get() / v);
    }
	
    REInt24 & operator+=(const REInt24 & v)
    {
		return this->set(this->get() + v.get());
    }
	
    REInt24 & operator-=(const REInt24 & v)
    {
		return this->set(this->get() - v.get());
    }
	
    REInt24 & operator*=(const REInt24 & v)
    {
		return this->set(this->get() * v.get());
    }
	
    REInt24 & operator/=(const REInt24 & v)
    {
		return this->set(this->get() / v.get());
    }
	
    REInt24 & operator+=(const REInt32 v)
    {
		return this->set(this->get() + v);
    }
	
    REInt24 & operator-=(const REInt32 v)
    {
		return this->set(this->get() - v);
    }
	
    REInt24 & operator*=(const REInt32 v)
    {
		return this->set(this->get() * v);
    }
	
    REInt24 & operator/=(const REInt32 v)
    {
		return this->set(this->get() / v);
    }
	
    REInt24 operator>>(const REInt32 v) const
    {
        return REInt24(this->get() >> v);
    }
	
    REInt24 operator<<(const REInt32 v) const
    {
        return REInt24(this->get() << v);
    }
	
    REInt24 & operator>>=(const REInt32 v)
    {
		return this->set(this->get() >> v);
    }
	
    REInt24 & operator<<=(const REInt32 v)
    {
		return this->set(this->get() << v);
    }
	
    operator bool() const
    {
        return (this->get() != 0);
    }
	
    bool operator !() const
    {
        return  !this->get();
    }
	
    REInt24 operator-()
    {
        return REInt24(-this->get());
    }
	
    bool operator==(const REInt24 & v) const
    {
		return (this->get() == v.get());
    }
	
    bool operator!=(const REInt24 & v) const
    {
		return (this->get() != v.get());
    }
	
    bool operator>=(const REInt24 & v) const
    {
		return (this->get() >= v.get());
    }
	
    bool operator<=(const REInt24 & v) const
    {
		return (this->get() <= v.get());
    }
	
    bool operator>(const REInt24 & v) const
    {
		return (this->get() > v.get());
    }
	
    bool operator<(const REInt24 & v) const
    {
		return (this->get() < v.get());
    }
	
    bool operator==(const REInt32 v) const
    {
		return (this->get() == v);
    }
	
    bool operator!=(const REInt32 v) const
    {
		return (this->get() != v);
    }
	
    bool operator>=(const REInt32 v) const
    {
		return (this->get() >= v);
    }
	
    bool operator<=(const REInt32 v) const
    {
		return (this->get() <= v);
    }
	
    bool operator>(const REInt32 v) const
    {
		return (this->get() > v);
    }
	
    bool operator<(const REInt32 v) const
    {
		return (this->get() < v);
    }
};

#endif /* __REINT24_H__ */

