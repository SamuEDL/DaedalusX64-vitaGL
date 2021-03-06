#ifndef MATH_VECTOR3_H_
#define MATH_VECTOR3_H_

// Note: For Vita build we make this to be a Vector4 in order to take advantage of NEON
#ifdef DAEDALUS_VITA
extern "C" {
#include <math_neon.h>
};
#endif

#include "Math/Math.h"	// VFPU Math

class v3
{
public:
	v3() {}
#ifdef DAEDALUS_VITA
	v3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ), w( 0.0f ) {}
#else
	v3( float _x, float _y, float _z ) : x( _x ), y( _y ), z( _z ) {}
#endif

	v3 operator+( const v3 & v ) const
	{
		return v3( x + v.x, y + v.y, z + v.z );
	}

	v3 operator-( const v3 & v ) const
	{
		return v3( x - v.x, y - v.y, z - v.z );
	}

	v3 operator+() const
	{
		return *this;
	}

	v3 operator-() const
	{
		return v3( -x, -y, -z );
	}

	v3 operator*( float s ) const
	{
		return v3( x * s, y * s, z * s );
	}

	inline friend v3 operator*( float s, const v3 & v )
	{
		return v3( v.x * s, v.y * s, v.z * s );
	}

	v3 operator/( float s ) const
	{
		float r( 1.0f / s );
		return v3( x * r, y * r, z * r );
	}

	const v3 & operator+=( const v3 & rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	const v3 & operator*=( float s )
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

#ifdef DAEDALUS_PSP//Corn
	void Normalise()
	{
		vfpu_norm_3Dvec(&x, &y, &z);
	}
#elif defined(DAEDALUS_VITA)
	void Normalise()
	{
		normalize4_neon(f, f);
	}
#else
	void Normalise()
	{
		float	len_sq( LengthSq() );
		if(len_sq > 0.0f)
		{
			float r( InvSqrt( len_sq ) );
			x *= r;
			y *= r;
			z *= r;
		}
	}
#endif

	float Length() const
	{
		return sqrtf( (x*x)+(y*y)+(z*z) );
	}

	float LengthSq() const
	{
		return (x*x)+(y*y)+(z*z);
	}

	float MinComponent() const
	{
		if(x < y && x < z)
		{
			return x;
		}
		else if(y < z)
		{
			return y;
		}
		else
		{
			return z;
		}
	}

	float Dot( const v3 & rhs ) const
	{
#ifdef DAEDALUS_VITA
		return dot4_neon((float*)f, (float*)rhs.f);
#else
		return (x*rhs.x) + (y*rhs.y) + (z*rhs.z);
#endif
	}

#ifdef DAEDALUS_VITA
	union {
		struct { float x, y, z, w; };
		float f[4];
	};
#else
	union {
		struct { float x, y, z; };
		float f[3];
	};
#endif
};

#endif // MATH_VECTOR3_H_
