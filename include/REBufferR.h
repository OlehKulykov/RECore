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


#ifndef __REBUFFERR_H__
#define __REBUFFERR_H__

#include "REBuffer.h"
#include "IREFileReadable.h"

class REMutableBuffer;
class REMutableBufferRW;

class __RE_PUBLIC_CLASS_API__ REBufferR : public REBuffer, public IREFileReadable
{
protected:
	RESizeT _offset;

public:
	/**
	 @brief Reads data from object to the buffer pointer.
	 @detailed Buffer must be at least of 'dataSizeToRead'.
	 @param bufferForReading The buffer for writing data.
	 @param dataSizeToRead Size in bytes for readed data.
	 @result Returns number of bytes readed.
	 */
	virtual RESizeT fileRead(void * bufferForReading, const RESizeT dataSizeToRead);


	/**
	 @brief Read position of the object.
	 @result Return readable position.
	 */
	virtual RESizeT fileTell();


	/**
	 @brief Setting position in bytes of reading.
	 @detailed Apply read offset of the object.
	 @param fileOffset Offset in bytes.
	 @param origin Position used as reference for the fileOffset. SEEK_SET - Beginning of file. SEEK_CUR - Current position of the file pointer. SEEK_END - End of file.
	 @return If successful, the function returns a zero value, otherwise nonzero value.
	 */
	virtual RESizeT fileSeek(const RESizeT fileOffset, int origin);


	/**
	 @brief Setting position in bytes of reading from end of the file.
	 @detailed Apply read offset of the object from end of the file using SEEK_END value.
	 @param fileOffset Offset in bytes.
	 @return If successful, the function returns a zero value, otherwise nonzero value.
	 */
	virtual RESizeT fileSeekFromEndFile(const RESizeT fileOffset);


	/**
	 @brief Setting position in bytes of reading from begining of the file.
	 @detailed Apply read offset of the object from begining of the file using SEEK_SET value.
	 @param fileOffset Offset in bytes.
	 @return If successful, the function returns a zero value, otherwise nonzero value.
	 */
	virtual RESizeT fileSeekFromBeginFile(const RESizeT fileOffset);


	/**
	 @brief Setting position in bytes of reading from current location of the file.
	 @detailed Apply read offset of the object from current location of the file using SEEK_CUR value.
	 @param fileOffset Offset in bytes.
	 @return If successful, the function returns a zero value, otherwise nonzero value.
	 */
	virtual RESizeT fileSeekFromCurrentFilePos(const RESizeT fileOffset);


	/**
	 @brief Checks if the error indicator associated with stream is set.
	 @detailed This indicator is generaly set by a previous operation on the stream that failed.
	 @return Returning a value different from zero if it is.
	 */
	virtual RESizeT fileFError();


	/**
	 @brief Closes the file associated with the stream and disassociates it.
	 @return If the stream is successfully closed, a zero value is returned. On failure, 1 is returned.
	 */
	virtual RESizeT fileClose();


	/**
	 @brief Check if reading position in the end of file.
	 @return True - on the end of the file, othervice false.
	 */
	virtual bool isEndOfFile();


	RESizeT offset() const;
	REBufferR(const char * string);
	REBufferR(const REBuffer & buffer);
	REBufferR(const REBufferR & buffer);
	REBufferR(const REMutableBuffer & buffer);
	REBufferR(const REMutableBufferRW & buffer);
	REBufferR(const void * memory, const RESizeT size);
	REBufferR(const RESizeT size);
	REBufferR();
	virtual ~REBufferR();
};

#endif 

