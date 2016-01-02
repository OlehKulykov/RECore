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


#ifndef __REFILEMANAGER_H__
#define __REFILEMANAGER_H__

#include "REString.h"

#include <wchar.h>

/**
 @brief Class used for creating, checking files and directories
 */
class __RE_PUBLIC_CLASS_API__ REFileManager
{
private:

public:
	bool moveFile(const wchar_t * sourceFilePath, const wchar_t * destinationFilePath) const;
	bool moveFile(const char * sourceFilePath, const char * destinationFilePath) const;
	bool moveFile(const REString & sourceFilePath, const REString & destinationFilePath) const;

	bool isExistsAtPath(const wchar_t * path, bool * isDirectory) const;
	bool isExistsAtPath(const char * path, bool * isDirectory) const;
	bool isExistsAtPath(const REString & path, bool * isDirectory) const;

	REString randomName(const RESizeT nameLength = 8);

	REFileManager();

	virtual ~REFileManager();
};

#endif /* __REFILEMANAGER_H__ */

