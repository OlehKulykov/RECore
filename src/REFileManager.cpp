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


#include "../include/REFileManager.h"
#include "../include/REWideString.h"
#include "../include/RERandomizer.h"


#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#if defined(RE_HAVE_BOOST_FILESYSTEM_HPP)
#include <boost/filesystem.hpp>
#endif

#if defined(RE_HAVE_SYS_STAT_H)
#include <sys/stat.h>
#endif

#if defined(RE_HAVE_FCNTL_H)
#include <fcntl.h>
#endif

#if defined(RE_HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(RE_HAVE_ERRNO_H)
#include <errno.h>
#endif

#if defined(RE_HAVE_SYS_ERRNO_H)
#include <sys/errno.h>
#endif

#if defined(RE_HAVE_IO_H)
#include <io.h>
#endif

#if defined(RE_HAVE_DIRECT_H)
#include <direct.h>
#endif

#include <ctype.h>

bool REFileManager::moveFile(const wchar_t * sourceFilePath, const wchar_t * destinationFilePath)
{
	//TODO: .....
	return false;
}

bool REFileManager::moveFile(const char * sourceFilePath, const char * destinationFilePath)
{
	if (sourceFilePath && destinationFilePath)
	{
		const int r = rename(sourceFilePath, destinationFilePath);
		return (r == 0);
	}
	return false;
}

bool REFileManager::moveFile(const REString & sourceFilePath, const REString & destinationFilePath)
{
#if defined(__RE_OS_WINDOWS__)
	if (sourceFilePath.isContainsNonASCII() || destinationFilePath.isContainsNonASCII())
	{
		REWideString s(sourceFilePath);
		REWideString d(destinationFilePath);
		return this->moveFile((const wchar_t *)s.wideChars(), (const wchar_t *)d.wideChars());
	}
#endif

	return this->moveFile((const char *)sourceFilePath.UTF8String(), (const char *)destinationFilePath.UTF8String());
}




bool REFileManager::isExistsAtPath(const wchar_t & path, bool * isDirectory) const
{
	//TODO: .....
	return false;
}

bool REFileManager::isExistsAtPath(const char * path, bool * isDirectory) const
{
	if (isDirectory) *isDirectory = false;
	if (!path) return false;

#if defined(RE_HAVE_STRUCT__STAT) && defined(RE_HAVE_FUNCTION__STAT)
	struct _stat statbuf;
	if (_stat(path, &statbuf) != 0) return false;
#elif defined(RE_HAVE_STRUCT_STAT) && defined(RE_HAVE_FUNCTION_STAT)
	struct stat statbuf;
	if (stat(path, &statbuf) != 0) return false;
#else
#warning "UNIMPLEMENTED REFileManager::isFileExistsAtPath"
#endif

	if (isDirectory)
	{
#if (defined(RE_HAVE_STRUCT__STAT) && defined(RE_HAVE_FUNCTION__STAT)) || (defined(RE_HAVE_STRUCT_STAT) && defined(RE_HAVE_FUNCTION_STAT))
		if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		{
			*isDirectory = true;
		}
#endif
	}

	return true;
}

bool REFileManager::isExistsAtPath(const REString & path, bool * isDirectory) const
{
	if (isDirectory) *isDirectory = false;
	if (path.isEmpty()) return false;

#if defined(__RE_OS_WINDOWS__)
	if (path.isContainsNonASCII())
	{
		REWideString p(path);
		return this->isExistsAtPath(p.wideChars(), isDirectory);
	}
	else
	{
		return this->isExistsAtPath(path.UTF8String(), isDirectory);
	}
#else
	return this->isExistsAtPath(path.UTF8String(), isDirectory);
#endif

}

REString REFileManager::randomName(const RESizeT nameLength)
{
	REPtr<REBuffer> buff = REPtr<REBuffer>(new REBuffer(nameLength + 1));
	if (buff.isNotEmpty())
	{
		char * b = (char *)buff->buffer();
		RERandomizer r;
		RESizeT index = 0;
		while (index++ <= nameLength) *b++ = (char)r.intValueInRange('a', 'z');
		*b = (char)0;
	}
	return REString(buff);
}

REFileManager::REFileManager()
{

}

REFileManager::~REFileManager()
{

}












#if 0

bool REFileManager::isReadableFileAtPath(const char * path) const
{
	if (path)
	{
#if defined(HAVE_FUNCTION_ACCESS)
		if (access(path, R_OK) == 0)
		{
			return true;
		}
#elif defined(HAVE_FUNCTION__ACCESS)
		if (_access(path, R_OK) == 0)
		{
			return true;
		}
#elif defined(__RE_OS_WINDOWS__)
		const DWORD dwAttrs = GetFileAttributesA(path);
		if (dwAttrs == INVALID_FILE_ATTRIBUTES) 
		{
			return false;
		}
		return true; 
#else
#error "Unimplemented REFileManager::isReadableFileAtPath"
#endif	
	}
	return false;
}

bool REFileManager::isReadableFileAtPath(const REString & path) const
{
	if ( path.isEmpty() ) 
	{
		return false;
	}
	
#if defined(HAVE_FUNCTION__WACCESS)	
	REWideString wideString(path);
	if (_waccess(wideString.wideChars(), R_OK) == 0)
	{
		return true;
	}
#else
	return this->isReadableFileAtPath(path.UTF8String());
#endif	
}

bool REFileManager::isWritableFileAtPath(const char * path) const
{
	if (path) 
	{
#if defined(HAVE_FUNCTION_ACCESS)		
		if (access(path, W_OK) == 0)
		{
			return true;
		}
#elif defined(HAVE_FUNCTION__ACCESS)
		if (_access(path, W_OK) == 0)
		{
			return true;
		}
#elif defined(__RE_OS_WINDOWS__)		
		const DWORD dwAttrs = GetFileAttributesA(path);
		if (dwAttrs == INVALID_FILE_ATTRIBUTES) 
		{
			return false;
		}
		if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) 
		{ 
			return true; 
		} 
#else
#error "Unimplemented REFileManager::isWritableFileAtPath"
#endif		
	}
	return false;

}

bool REFileManager::isWritableFileAtPath(const REString & path) const
{
	if ( path.isEmpty() ) 
	{
		return false;
	}

#if defined(HAVE_FUNCTION__WACCESS)	
	REWideString wideString(path);
	if (_waccess(wideString.wideChars(), W_OK) == 0)
	{
		return true;
	}
	return false;
#elif defined(__RE_OS_WINDOWS__)
	REWideString wideString(path);
	const DWORD dwAttrs = GetFileAttributesW(wideString.wideChars());
	if (dwAttrs == INVALID_FILE_ATTRIBUTES) 
	{
		return false;
	}
	if (!(dwAttrs & FILE_ATTRIBUTE_READONLY)) 
	{ 
		return true; 
	} 
	return false;
#else
	return this->isWritableFileAtPath(path.UTF8String());
#endif	
	
}

bool REFileManager::createFileAtPath(const char * path, REData * withFileData) const
{
	if (path) 
	{
		FILE * f = REFile::fileOpen(REString(path), "wb+");
		if (f)
		{
			size_t dwBytesToWrite = 0;
			size_t dwBytesWritten = 0;
			if (withFileData)
			{
				if ( !withFileData->isEmpty() )
				{
					dwBytesToWrite = withFileData->size();
					dwBytesWritten = fwrite(withFileData->bytes(), 1, dwBytesToWrite, f);
				}
			}
			fclose(f);
			return (dwBytesToWrite == dwBytesWritten);
		}
	}
	return false;
}

bool REFileManager::createFileAtPath(const REString & path, REData * withFileData) const
{
	if ( path.isEmpty() ) 
	{
		return false;
	}

#ifndef __RE_OS_WINDOWS__	
	return this->createFileAtPath(path.UTF8String(), withFileData);
#endif /* NOT WIN */
	
#ifdef __RE_OS_WINDOWS__
	FILE * f = REFile::fileOpen(path, "wb+");
	if (f)
	{
		size_t dwBytesToWrite = 0;
		size_t dwBytesWritten = 0;
		if (withFileData)
		{
			if ( !withFileData->IsEmpty() )
			{
				dwBytesToWrite = withFileData->GetSize();
				dwBytesWritten = fwrite(withFileData->GetBytes(), 1, dwBytesToWrite, f);
			}
		}
		fclose(f);
		return (dwBytesToWrite == dwBytesWritten);
	}
	return false;
#endif	/* WIN */ 
}

bool REFileManager::isFileExistsAtPath(const char * path, bool * isDirectory) const
{
    if (isDirectory)
    {
        *isDirectory = false;
    }
    if ( path == NULL )
    {
        return false;
    }

#if defined(HAVE_STRUCT__STAT)	&& defined(HAVE_FUNCTION__STAT)
	struct _stat statbuf;
    if (_stat(path, &statbuf) != 0)
    {
        return false;
    }
#elif defined(HAVE_STRUCT_STAT) && defined(HAVE_FUNCTION_STAT)
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
	{
		return false;
	}
#else	
#error "Unimplemented REFileManager::isFileExistsAtPath"
#endif
	
    if (isDirectory)
    {
        if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
        {
            *isDirectory = true;
        }
    }

	return true;
}

bool REFileManager::isFileExistsAtPath(const REString & path, bool * isDirectory) const
{
	if ( path.isEmpty() ) 
	{
		if ( isDirectory ) 
		{
			*isDirectory = false;
		}
		return false;
	}
	
#ifndef __RE_OS_WINDOWS__	
	return this->isFileExistsAtPath(path.UTF8String(), isDirectory);
#endif /* NOT WIN */	
	
#ifdef __RE_OS_WINDOWS__
	REStringPresentation p(path.UTF8String());
	const wchar_t * widePath = p.WideString();
	if (p.GetWideLength() && widePath) 
	{
		if (isDirectory) 
		{
			*isDirectory = false;
		}
		
        struct _stat statbuf;
        if (_wstat(widePath, &statbuf) != 0)
        {
            return false;
        }

        if (isDirectory)
        {
            if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
            {
                *isDirectory = true;
            }
        }

        return true;
	}
	return false;
#endif /* WIN */	
}

bool REFileManager::createDir(const char * path)
{
#if defined(HAVE_FUNCTION_MKDIR)
	if (mkdir(path, 777) == 0) //created
	{
		return true;
	}
#elif defined(HAVE_FUNCTION__MKDIR)
	if (_mkdir(path) == 0) //created
	{
		return true;
	}
#else
#error "Unimplemented REFileManager::createDir"
#endif
		
	const int mkResult = errno;
	if (mkResult == EEXIST) //allready exists - return true
	{
		return true;
	}
	
	return false;
}

#ifdef __RE_OS_WINDOWS__ 
/// Wide char string version of CreateDir.
bool REFileManager::CreateDir(const wchar_t * path)
{
	if (_wmkdir(path) == 0) //created
	{
		return true;
	}	
	const int mkResult = errno;
	if (mkResult == EEXIST) //allready exists - return true
	{
		return true;
	}
	
	return false;
}
#endif /* WIN */	

bool REFileManager::createDirectoryAtPath(const char * path, bool isCreateIntermediates)
{
	if (path == NULL) 
	{
		return false;
	}
	
	if (isCreateIntermediates) 
	{
		const REUInt32 len = (REUInt32)strlen(path);
		if (len == 0) { return false; }
		REBuffer buf(len + 1);
		if (buf.size() == (len + 1)) 
		{
			memcpy(buf.buffer(), path, len);
			char * p = (char *)buf.buffer();
			p[len] = 0;
			while ((*p == '/') || (*p == '\\')) { p++; } // skip first '/'
			while (*p) 
			{
				if ((*p == '/') || (*p == '\\')) 
				{
					*p = 0;
					if ( !this->createDir((const char *)buf.buffer()) )
					{
						return false;
					}
					*p = '/';
				}
				p++;
			}
			return this->createDir((const char *)buf.buffer());
		}
	}
	else
	{
		return this->createDir(path);
	}
	
	return false;
}

bool REFileManager::createDirectoryAtPath(const REString & path, bool isCreateIntermediates)
{
	if ( path.isEmpty() ) 
	{
		return false;
	}
	
#ifndef __RE_OS_WINDOWS__	
	return this->createDirectoryAtPath(path.UTF8String(), isCreateIntermediates);
#endif /* NOT WIN */	

#ifdef __RE_OS_WINDOWS__
	REStringPresentation presentationOfPath(path.UTF8String());
	const wchar_t * widePath = presentationOfPath.WideString();
	if (presentationOfPath.GetWideLength() && widePath) 
	{
		if (isCreateIntermediates) 
		{
			const REUInt32 len = presentationOfPath.GetWideLength();
			wchar_t * buff = const_cast<wchar_t*>(widePath);
			if (buff == NULL) { return false; }
			wchar_t * p = buff;
			p[len] = 0;
			while ((*p == L'/') || (*p == L'\\')) { p++; } // skip first '/'
			while (*p) 
			{
				if ((*p == L'/') || (*p == L'\\')) 
				{
					*p = 0;
					if ( !this->CreateDir((const wchar_t*)buff) )
					{
						return false;
					}
					*p = L'/';
				}
				p++;
			}
			return this->createDir((const wchar_t*)buff);
		}
		else
		{
			return this->createDir(widePath);
		}
	}
	return false;
#endif /* WIN */
}




/*
const char REFileManager::GetPathSeparator()
{
#ifdef __RE_OS_WINDOWS__
	return '\\';
#endif 
	
#if ( defined(__RE_OS_MACOSX__) || defined(__RE_OS_LINUX__) || defined(__RE_OS_IPHONE__) )	
	return '/';	
#endif
	
	return '/';
}
*/

#endif

