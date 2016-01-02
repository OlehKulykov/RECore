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


#include "../include/REVariantMap.h"
#include "../include/REStaticString.h"

#include "REJsonUtilsPrivate.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#if defined(RE_HAVE_ASSERT_H)
#include <assert.h>
#endif


REString REVariantMap::jsonString() const
{
#if defined(RE_HAVE_JANSSON_H)
	REJanssonGenerator generator(*this);
	return REString(generator.string());
#else
	return REString("{}");
#endif
}

void REVariantMap::fromJSONString(const REString & jsonString)
{
	this->clear();

#if defined(RE_HAVE_JANSSON_H)
	REJanssonParser parser(jsonString.UTF8String());
	if (parser.isMap())
	{
		parser.toMap(*this);
	}
#endif
}

bool REVariantMap::isEqualToMap(const REVariantMap & map) const
{
	RESizeT srcCount = 0;
	REVariantMap::Iterator i = this->iterator();
	while (i.next())
	{
		srcCount++;
		Node * node = map.findNode(i.key());
		if (node)
		{
			if (!i.value().isEqualToVariant(node->value))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	const RESizeT dstCount = map.count();
	return (srcCount == dstCount);
}

bool REVariantMap::operator==(const REVariantMap & map) const
{
	return this->isEqualToMap(map);
}

bool REVariantMap::operator!=(const REVariantMap & map) const
{
	return !this->isEqualToMap(map);
}


REVariant * REVariantMap::findTypedValue(const char * key, const REVariant::VariantType type) const
{
	return this->findTypedValue(REStaticString(key), type);
}

REVariant * REVariantMap::findTypedValue(const wchar_t * key, const REVariant::VariantType type) const
{
	return this->findTypedValue(REStaticString(key), type);
}

REVariant * REVariantMap::findTypedValue(const REString & key, const REVariant::VariantType type) const
{
	Node * node = this->findNode(key);
	if (node)
	{
		if (node->value.type() == type)
		{
			return &node->value;
		}
	}
	return NULL;
}

const REVariant REVariantMap::operator[](const char * key) const
{
	return (*this)[REStaticString(key)];
}

const REVariant REVariantMap::operator[](const wchar_t * key) const
{
	return (*this)[REStaticString(key)];
}

const REVariant REVariantMap::operator[](const REString & key) const
{
	Node * node = this->findNode(key);
	return node ? node->value : REVariant();
}

REVariant & REVariantMap::operator[](const char * key)
{
	return (*this)[REString(key)];
}

REVariant & REVariantMap::operator[](const wchar_t * key)
{
	return (*this)[REString(key)];
}

REVariant & REVariantMap::operator[](const REString & key)
{
	Node * node = this->findNode(key);
	if (node) return node->value;

	node = this->addNewNodeWithKeyValue(key, REVariant());

#if defined(RE_HAVE_ASSERT_H)
	assert(node);
#endif

	return node->value;
}

REVariantMap & REVariantMap::operator=(const REVariantMap & map)
{
	this->clear();
	REVariantMap::Iterator i = map.iterator();
	while (i.next())
	{
		this->add(i.key(), i.value());
	}
	return *this;
}

REVariantMap::REVariantMap(const REVariantMap & map)
{
	*this = map;
}

REVariantMap::REVariantMap()
{

}

REVariantMap::~REVariantMap()
{

}

