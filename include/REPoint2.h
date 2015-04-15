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


#ifndef __REPOINT2_H__
#define __REPOINT2_H__

#include "RECore.h"

#if defined(HAVE_RECORE_CONFIG_H)
#include "recore_config.h"
#endif

#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H)
#include <arm_neon.h>
#endif


typedef struct _REPoint2Struct
{
	union 
	{ 
		struct 
		{
			REFloat32 x; 
			REFloat32 y; 
		};
		
#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H) 
		float32x2_t armNeonPoint;
#endif	
		
		REFloat32 coords[2]; 
	};
} REPoint2Struct;

/// Class using for presenting 2D Point with 'x' and 'y' float coordinates.
class __RE_PUBLIC_CLASS_API__ REPoint2
{
public:
	union
	{
		struct 
		{
			/// X coordinate.
			REFloat32 x;
			
			/// Y coordinate.
			REFloat32 y;
		};
#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H) 
		/// used for arm optimizations
		float32x2_t armNeonPoint;
#endif		
		/// array of 'x' and 'y'
		REFloat32 values[2];
	};
	
	/// Copy operator. This point will be same as anotherPoint struct.
	REPoint2 & operator=(const REPoint2Struct & anotherPoint)
	{
#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H) 
		armNeonPoint = anotherPoint.armNeonPoint;
#else		
		x = anotherPoint.x;
		y = anotherPoint.y;
#endif		
		return (*this);
	}
	
	/// Copy operator. This point will be same as anotherPoint.
	REPoint2 & operator=(const REPoint2 & anotherPoint)
	{
#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H) 
		armNeonPoint = anotherPoint.armNeonPoint;
#else		
		x = anotherPoint.x;
		y = anotherPoint.y;
#endif		
		return (*this);
	}
	
	/// Constructs 2D Point with 'newX' - X coordinate and 'newY' - Y coordinate.
	REPoint2(const REFloat32 newX, const REFloat32 newY) : x(newX), y (newY) { }

	/// Constructs 2D Point same as anotherPoint struct.
	REPoint2(const REPoint2Struct & anotherPoint) : 
#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H) 
		armNeonPoint(anotherPoint.armNeonPoint) { }
#else	
		x(anotherPoint.x), y(anotherPoint.y) { }
#endif	
	
	/// Constructs 2D Point same as anotherPoint.
	REPoint2(const REPoint2 & anotherPoint) : 
#if defined(__ARM_NEON__) || defined(HAVE_ARM_NEON_H) 
		armNeonPoint(anotherPoint.armNeonPoint) { }
#else	
		x(anotherPoint.x), y(anotherPoint.y) { }
#endif	
	
	/// Constructs 2D Point and sets 'x' and 'y' coordinates to 0.
	REPoint2() : x(0.0f), y(0.0f) { }
	~REPoint2() { }
	
	
/// Objective-c additions
#if (defined(CG_EXTERN) || defined(CG_INLINE)) && defined(CGFLOAT_TYPE)

	CGPoint getCGPoint() const 
	{
		CGPoint p;
		p.x = (CGFloat)x; 
		p.y = (CGFloat)y;
		return p;
	}
	
	REPoint2 & operator=(const CGPoint & anotherPoint)
	{
		x = (REFloat32)anotherPoint.x;
		y = (REFloat32)anotherPoint.y;
		return (*this);
	}

	REPoint2(const CGPoint & anotherPoint) : 
		x((REFloat32)anotherPoint.x), 
		y((REFloat32)anotherPoint.y) 
	{
		
	}
	
#endif

};


#endif /* __REPOINT2_H__ */

