#ifndef __TOUCHLIB_RECT2D__
#define __TOUCHLIB_RECT2D__

#include "vector2d.h"

	// The following code was originally written by Nikolaus Gebhardt as part of Irrlicht.
	// See www.irrlicht3d.org

    // The Irrlicht Engine License
    // Copyright © 2002-2005 Nikolaus Gebhardt
    // This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held 
    // liable for any damages arising from the use of this software.
    //
    // Permission is granted to anyone to use this software for any purpose, including commercial applications, and to 
    // alter it and redistribute it freely, subject to the following restrictions:
    //
    // 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. 
    //    If you use this software in a product, an acknowledgment in the product documentation would be appreciated but 
    //    is not required.
    // 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    // 3. This notice may not be removed or altered from any source distribution.

	//!	Rectangle template.



    template <class T>
	class rect
	{
	public:

		rect()
			: upperLeftCorner(0,0), lowerRightCorner(0,0) {};


		rect(T x, T y, T x2, T y2)
			: upperLeftCorner(x,y), lowerRightCorner(x2,y2) {};


		rect(const vector2d<T>& upperLeft, const vector2d<T>& lowerRight)
			: upperLeftCorner(upperLeft), lowerRightCorner(lowerRight) {};

		inline void addPoint(const vector2d<T> &pt)
		{
			if(upperLeftCorner == vector2d<T>(0,0) && lowerRightCorner == vector2d<T>(0,0))
			{
				upperLeftCorner = pt;
				lowerRightCorner = pt;
				return;
			}

			if(pt.X < upperLeftCorner.X)
				upperLeftCorner.X = pt.X;
			if(pt.Y < upperLeftCorner.Y)
				upperLeftCorner.Y = pt.Y;

			if(pt.X > lowerRightCorner.X)
				lowerRightCorner.X = pt.X;
			if(pt.Y > lowerRightCorner.Y)
				lowerRightCorner.Y = pt.Y;
		};

		inline void addPoint(T x, T y)
		{
			if(upperLeftCorner == vector2d<T>(0,0) && lowerRightCorner == vector2d<T>(0,0))
			{
				upperLeftCorner.X = x;
				upperLeftCorner.Y = y;
				lowerRightCorner.X = x;
				lowerRightCorner.Y = y;
				return;
			}

			if(x < upperLeftCorner.X)
				upperLeftCorner.X = x;
			if(y < upperLeftCorner.Y)
				upperLeftCorner.Y = y;

			if(x > lowerRightCorner.X)
				lowerRightCorner.X = x;
			if(y > lowerRightCorner.Y)
				lowerRightCorner.Y = y;
		};


		void reset(const vector2d<T> &pt)
		{
			upperLeftCorner = pt;
			lowerRightCorner = pt;
		}

		bool isPointInside(const vector2d<T>& pos) const
		{
			return upperLeftCorner.X <= pos.X && upperLeftCorner.Y <= pos.Y &&
				lowerRightCorner.X >= pos.X && lowerRightCorner.Y >= pos.Y;
		}

		//! Returns if the rectangle collides with an other rectangle.
		bool isRectCollided(const rect<T>& other) const
		{
			return (lowerRightCorner.Y > other.upperLeftCorner.Y && upperLeftCorner.Y < other.lowerRightCorner.Y &&
					lowerRightCorner.X > other.upperLeftCorner.X && upperLeftCorner.X < other.lowerRightCorner.X);
		}

		//! Returns if the rectangle collides with an other rectangle.
		bool isBoxInside(const rect<T>& other) const
		{
			//return (this->isPointInside(other.upperLeftCorner) && this->isPointInside(other.lowerRightCorner));
			return (other.upperLeftCorner.Y >= upperLeftCorner.Y && other.upperLeftCorner.X >= upperLeftCorner.X &&
				other.lowerRightCorner.Y <= lowerRightCorner.Y && other.lowerRightCorner.X <= lowerRightCorner.X);
		}

		//! Returns width of rectangle.
		T getWidth() const
		{
			return lowerRightCorner.X - upperLeftCorner.X;
		}

		//! Returns height of rectangle.
		T getHeight() const
		{
			return lowerRightCorner.Y - upperLeftCorner.Y;
		}

		//! Returns the center of the rectangle
		vector2d<T> getCenter() const
		{
			return vector2d<T>((upperLeftCorner.X + lowerRightCorner.X) / 2,
				(upperLeftCorner.Y + lowerRightCorner.Y) / 2);
		}

		T getArea() const
		{
			return getHeight() * getWidth();
		}


		//! Clips this rectangle with another one.
		void clipAgainst(const rect<T>& other) 
		{
			if (other.lowerRightCorner.X < lowerRightCorner.X)
				lowerRightCorner.X = other.lowerRightCorner.X;
			if (other.lowerRightCorner.Y < lowerRightCorner.Y)
				lowerRightCorner.Y = other.lowerRightCorner.Y;

			if (other.upperLeftCorner.X > upperLeftCorner.X)
				upperLeftCorner.X = other.upperLeftCorner.X;
			if (other.upperLeftCorner.Y > upperLeftCorner.Y)
				upperLeftCorner.Y = other.upperLeftCorner.Y;

			// correct possible invalid rect resulting from clipping
            if (upperLeftCorner.Y > lowerRightCorner.Y)
                upperLeftCorner.Y = lowerRightCorner.Y;
            if (upperLeftCorner.X > lowerRightCorner.X)
                upperLeftCorner.X = lowerRightCorner.X;
		}



		vector2d<T> upperLeftCorner;
		vector2d<T> lowerRightCorner;
	};

	//! Typedef for float 2d vector.
	typedef rect<float> rect2df;

#endif
