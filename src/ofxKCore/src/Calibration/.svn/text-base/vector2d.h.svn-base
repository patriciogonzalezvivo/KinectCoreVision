#ifndef __TOUCHLIB_VECTOR2D__
#define __TOUCHLIB_VECTOR2D__


#include <math.h>

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


	const float  GRAD_PI = 180.0f / 3.14159f;
	const float  GRAD_PI2 = 3.14159f / 180.0f;
	//const float  PI = 3.14159f;
	const float  ROUNDING_ERROR = 0.0001f;


	template <class T> 
	class vector2d
	{
	public:

		vector2d(): X(0), Y(0) {};
		vector2d(T nx, T ny) : X(nx), Y(ny) {};
		vector2d(const vector2d<T>& other)	:X(other.X), Y(other.Y) {};

		// operators

		vector2d<T> operator-() const { return vector2d<T>(-X, -Y);   }

		vector2d<T>& operator=(const vector2d<T>& other)	{ X = other.X; Y = other.Y; return *this; }

		vector2d<T> operator+(const vector2d<T>& other) const { return vector2d<T>(X + other.X, Y + other.Y);	}
		vector2d<T>& operator+=(const vector2d<T>& other)	{ X+=other.X; Y+=other.Y; return *this; }

		vector2d<T> operator-(const vector2d<T>& other) const { return vector2d<T>(X - other.X, Y - other.Y);	}
		vector2d<T>& operator-=(const vector2d<T>& other)	{ X-=other.X; Y-=other.Y; return *this; }

		vector2d<T> operator*(const vector2d<T>& other) const { return vector2d<T>(X * other.X, Y * other.Y);	}
		vector2d<T>& operator*=(const vector2d<T>& other)	{ X*=other.X; Y*=other.Y; return *this; }
		vector2d<T> operator*(const T v) const { return vector2d<T>(X * v, Y * v);	}
		vector2d<T>& operator*=(const T v) { X*=v; Y*=v; return *this; }

		vector2d<T> operator/(const vector2d<T>& other) const { return vector2d<T>(X / other.X, Y / other.Y);	}
		vector2d<T>& operator/=(const vector2d<T>& other)	{ X/=other.X; Y/=other.Y; return *this; }
		vector2d<T> operator/(const T v) const { return vector2d<T>(X / v, Y / v);	}
		vector2d<T>& operator/=(const T v) { X/=v; Y/=v; return *this; }

		bool operator==(const vector2d<T>& other) const { return other.X==X && other.Y==Y; }
		bool operator!=(const vector2d<T>& other) const { return other.X!=X || other.Y!=Y; }

		// functions

		void set(const T& nx, const T& ny) {X=nx; Y=ny; }
		void set(const vector2d<T>& p) { X=p.X; Y=p.Y;}

		//! Returns the length of the vector
		//! \return Returns the length of the vector.
		float getLength() const { return sqrt(X*X + Y*Y); }
		float getLengthSQ() const { return (X*X + Y*Y); }

		//! Returns the dot product of this vector with an other.
		T dotProduct(const vector2d<T>& other) const
		{
			return X*other.X + Y*other.Y;
		}

		//! Calculates the cross product with another vector
		T crossProduct(const vector2d<T>& p) const
		{
			return X * p.Y - Y * p.X;
		}


		//! Returns distance from an other point. Here, the vector is interpreted as
		//! point in 2 dimensional space.
		float getDistanceFrom(const vector2d<T>& other) const
		{
			float vx = X - other.X; float vy = Y - other.Y;
			return sqrt(vx*vx + vy*vy);
		}

		//! Returns distance from an other point. Here, the vector is interpreted as
		//! point in 2 dimensional space.
		float getDistanceFromSQ(const vector2d<T>& other) const
		{
			float vx = X - other.X; 
			float vy = Y - other.Y;

			return (vx*vx + vy*vy);
		}

		//! rotates the point around a center by an amount of degrees.
		void rotateBy(float degrees, const vector2d<T>& center)
		{
			degrees *= GRAD_PI2;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);

			X -= center.X;
			Y -= center.Y;

			set(X*cs - Y*sn, X*sn + Y*cs);

			X += center.X;
			Y += center.Y;
		}

		//! normalizes the vector.
		vector2d<T>& normalize()
		{
			T l = (T)getLength();
			if (l == 0)
				return *this;

			l = (T)1.0 / l;
			X *= l;
			Y *= l;
			return *this;
		}

		//! Calculates the angle of this vector in grad in the trigonometric sense.
		//! This method has been suggested by Pr3t3nd3r.
		//! \return Returns a value between 0 and 360.
		inline float getAngleTrig() const
		{
			if (X == 0.0)
				return Y < 0.0 ? 270.0 : 90.0;
			else
			if (Y == 0)
				return X < 0.0 ? 180.0 : 0.0;

			if ( Y > 0.0)
				if (X > 0.0)
					return atan(Y/X) * GRAD_PI;
				else
					return 180.0-atan(Y/-X) * GRAD_PI;
			else
				if (X > 0.0)
					return 360.0-atan(-Y/X) * GRAD_PI;
				else
					return 180.0+atan(-Y/-X) * GRAD_PI;
		} 

		//! Calculates the angle of this vector in grad in the counter trigonometric sense.
		//! \return Returns a value between 0 and 360.
		inline float getAngle() const
		{
			if (Y == 0.0)  // corrected thanks to a suggestion by Jox
				return X < 0.0 ? 180.0 : 0.0; 
			else if (X == 0.0) 
				return Y < 0.0 ? 90.0 : 270.0;

			float tmp = Y / sqrt(X*X + Y*Y);
			tmp = atan(sqrt(1 - tmp*tmp) / tmp) * GRAD_PI;

			if (X>0.0 && Y>0.0)
				return tmp + 270;
			else
			if (X>0.0 && Y<0.0)
				return tmp + 90;
			else
			if (X<0.0 && Y<0.0)
				return 90 - tmp;
			else
			if (X<0.0 && Y>0.0)
				return 270 - tmp;

			return tmp;
		}

		//! Calculates the angle between this vector and another one in grad.
		//! \return Returns a value between 0 and 90.
		inline float getAngleWith(const vector2d<T>& b) const
		{
			float tmp = X*b.X + Y*b.Y;

			if (tmp == 0.0)
				return 90.0;

			tmp = tmp / sqrt((X*X + Y*Y) * (b.X*b.X + b.Y*b.Y));
			if (tmp < 0.0) tmp = -tmp;

			return atan(sqrt(1 - tmp*tmp) / tmp) * GRAD_PI;
		}


		//! returns interpolated vector
		//! \param other: other vector to interpolate between
		//! \param d: value between 0.0f and 1.0f.
		vector2d<T> getInterpolated(const vector2d<T>& other, float d) const
		{
			float inv = 1.0f - d;
			return vector2d<T>(other.X*inv + X*d,
							   other.Y*inv + Y*d);
		}

		//! Returns if this vector interpreted as a point is on a line between two other points.
		/** It is assumed that the point is on the line. */
		bool isBetweenPoints(const vector2d<T>& begin, const vector2d<T>& end) const
		{
			float f = (float)(end - begin).getLengthSQ();
			return (float)getDistanceFromSQ(begin) < f && 
				(float)getDistanceFromSQ(end) < f;
		}

		static bool isOnSameSide(vector2d<T> p1, vector2d<T> p2, vector2d<T> a, vector2d<T> b)
		{
			vector2d<T> ba = b - a;

			float cp1 = ba.crossProduct(p1-a);
			float cp2 = ba.crossProduct(p2-a);

			if (cp1*cp2 >= 0.0f) 
				return true;
			else 
				return false;
		}


		// member variables
		T X, Y;
	};

	//! Typedef for float 2d vector.
	typedef vector2d<float> vector2df;
	//! Typedef for integer 2d vector.
	typedef vector2d<int> vector2di;

#endif
