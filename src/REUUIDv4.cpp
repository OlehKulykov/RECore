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


#include "../include/REUUIDv4.h"
#include "../include/RERandomizer.h"

const char * REUUIDv4::uuid() const
{
	return (const char *)&_u[0];
}

unsigned int REUUIDv4::length()
{
	return 36;
}

REUUIDv4::REUUIDv4(bool isLowercase)
{
	RERandomizer r;

	const char * format = isLowercase ? "%x" : "%X";

	char * s = (char *)&_u[0];
	const unsigned int len = REUUIDv4::length();
	for (unsigned int i = 0; i < len; i++)
	{
		switch (i)
		{
			case 8:
			case 13:
			case 18:
			case 23:
				*s++ = '-';
				break;

			case 14:
				*s++ = '4';
				break;

			case 19:
				sprintf(s++, format, r.intValueInRange(8, 11));
				break;

			default:
				sprintf(s++, format, r.intValueInRange(0, 16));
				break;
		}

	}

	*s = (char)0;
}

