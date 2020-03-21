#pragma once

#include <math.h>
#include <iostream>

namespace gm{
	struct mat4;
	const float PI = 3.14159265f;
	struct vec4
	{
		float values[4];

		vec4(float value)
		{
			values[0] = values[1] = values[2] = values[3] = value;
		}

		vec4()
		{
			values[0] = values[1] = values[2] = values[3] = 0;
		}

		vec4( float x, float y, float z, float w )
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
			values[3] = w;
		}

		const float& operator[] ( int index ) const
		{
			return values[index];
		}
		float& operator[] ( int index )
		{
			return values[index];
		}
		float Mag(){
			return sqrt(values[0]*values[0] + values[1]*values[1] + values[2]*values[2]);
		}
		vec4 Normal(){
			float mag = Mag();
			return *(this)/mag;
		}

		float Dot( const vec4& v );
		vec4 Cross( const vec4& v );

		vec4 operator*( const mat4& m );
		vec4 operator-( const vec4& v );
		float operator*( const vec4& v );
		vec4 operator*( const float value );
		vec4 operator%( const float value );
		vec4 operator/( const float value );
		bool operator==( const vec4& v );
	};

	struct vec3 : public vec4{
		vec3(): vec4(0,0,0,0){
		}
		vec3(float x, float y, float z): vec4(x,y,z,1){}
	};

	struct mat4
	{
		vec4 columns[4];

		mat4(float value){
			columns[0] = vec4( value, 0, 0, 0 );
			columns[1] = vec4( 0, value, 0, 0 );
			columns[2] = vec4( 0, 0, value, 0 );
			columns[3] = vec4( 0, 0, 0, value );
		}

		mat4()
		{
			columns[0] = vec4( 1, 0, 0, 0 );
			columns[1] = vec4( 0, 1, 0, 0 );
			columns[2] = vec4( 0, 0, 1, 0 );
			columns[3] = vec4( 0, 0, 0, 1 );
		}

		mat4( vec4 x, vec4 y, vec4 z, vec4 w )
		{
			columns[0] = x;
			columns[1] = y;
			columns[2] = z;
			columns[3] = w;
		}

		const vec4& operator[]( int index ) const
		{
			return columns[index];
		}
		vec4& operator[]( int index )
		{
			return columns[index];
		}
		vec4 operator*( const vec4& v );
		mat4 operator*( const mat4& m2 );
		bool operator==( const mat4& m );
	};

	mat4 translate(mat4 matrix, vec4 vector);
	mat4 scale(vec4 vector);
	mat4 rotate(mat4 matrix, float angle, vec4 vector);
	mat4 diag(vec4 vector);
}


std::ostream & operator << (std::ostream &out, gm::vec4 &v);