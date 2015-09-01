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


#ifndef __REJSONUTILSPRIVATE_H__
#define __REJSONUTILSPRIVATE_H__

#include "../include/REVariantMap.h"
#include "../include/REVariantList.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#if defined(RE_HAVE_JANSSON_H) 

#include <jansson.h>

class REJanssonParser
{
private:
	json_t * _json;
	static void jsonToMap(json_t * json, REVariantMap & map);
	static void jsonToList(json_t * json, REVariantList & list);

public:
	bool isMap() const;
	bool isList() const;
	bool toMap(REVariantMap & map);
	bool toList(REVariantList & list);
	REJanssonParser(const char * text);
	~REJanssonParser();
};

class REJanssonGenerator
{
private:
	char * _string;
	static json_t * jsonObjectFromList(const REVariantList & list);
	static json_t * jsonObjectFromValue(const REVariant & value);
	static void addMapToJson(const REVariantMap & map, json_t * json);
	static char * jsonStringFromMap(const REVariantMap & message);
	static char * jsonStringFromList(const REVariantList & message);

public:
	const char * string() const;
	REJanssonGenerator(const REVariantMap & map);
	REJanssonGenerator(const REVariantList & list);
	~REJanssonGenerator();
};

#endif

#endif
