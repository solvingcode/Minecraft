#include "type.h"

namespace gm{

	vec4 mat4::operator*( const vec4& v )
	{
		vec4 result;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 1; j++){
				for(int k = 0; k < 4; k ++){
					result[i] += (columns[i][k] * v[k]);
				}
			}
		}
		return result;
	}

	vec4 vec4::operator*( const mat4& m )
	{
		vec4 result;
		for(int i = 0; i < 1; i++){
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k ++){
					result[j] += (values[k] * m[k][j]);
				}
			}
		}
		return result;
	}

	vec4 vec4::operator*( const float value )
	{
		return vec4(
			values[0] * value,
			values[1] * value,
			values[2] * value,
			values[3]
		);
	}

	vec4 vec4::operator/( const float value )
	{
		return vec4(
			values[0] / value,
			values[1] / value,
			values[2] / value,
			values[3]
		);
	}

	float vec4::Dot( const vec4 &v )
	{
		return values[0]*v[0] + values[1]*v[1] + values[2]*v[2];
	}

	vec4 vec4::Cross( const vec4 &v )
	{
		return gm::vec3(
			values[1]*v[2] - values[2]*v[1],
			values[2]*v[0] - values[0]*v[2],
			values[0]*v[1] - values[1]*v[0]
		);
	}

	vec4 vec4::operator-( const vec4 &v )
	{
		return vec3(values[0]-v[0],values[1]-v[1],values[2]-v[2]);
	}

	bool vec4::operator==( const vec4 &v )
	{
		return values[0] == v[0] && values[1] == v[1] && values[2] == v[2];
	}

	vec4 vec4::operator%( const float value )
	{
		return vec4(
			fmod(values[0],value),
			fmod(values[1],value),
			fmod(values[2],value),
			fmod(values[3],value)
		);
	}

	mat4 mat4::operator*( const mat4& m2 )
	{
		mat4 result(0.0f);
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k ++){
					result[i][j] += (columns[i][k] * m2[k][j]);
				}
			}
		}
		return result;
	}

	bool mat4::operator==( const mat4& m )
	{
		return columns[0] == m[0] && columns[1] == m[1] && columns[2] == m[2];
	}

	mat4 translate(mat4 matrix, vec4 vector){
		matrix[0][3] += vector[0];
		matrix[1][3] += vector[1];
		matrix[2][3] += vector[2];
		return matrix;
	}

	mat4 scale(vec4 vector){
		mat4 matrix;
		matrix[0][0] = vector[0];
		matrix[1][1] = vector[1];
		matrix[2][2] = vector[2];
		return matrix;
	}
	
	mat4 rotate(mat4 matrix, float angle, vec4 vector){
		float angleRadian = angle * PI / 180;
		if(vector[0] == 1){
			mat4 matrixRX(
				vec4(1.0f, 0.0f, 0.0f, 0.0f),
				vec4(0.0f, cos(angleRadian), -1*sin(angleRadian), 0.0f),
				vec4(0.0f, sin(angleRadian), cos(angleRadian), 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 1.0f)
			);
			matrix = matrix * matrixRX;
		}
		if(vector[1] == 1){
			mat4 matrixRY(
				vec4(cos(angleRadian), 0.0f, sin(angleRadian), 0.0f),
				vec4(0.0f, 1.0f, 0.0f, 0.0f),
				vec4(-1*sin(angleRadian), 0.0f, cos(angleRadian), 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 1.0f)
			);
			matrix = matrix * matrixRY;
		}
		if(vector[2] == 1){
			mat4 matrixRZ(
				vec4(cos(angleRadian), -1*sin(angleRadian), 0.0f, 0.0f),
				vec4(sin(angleRadian), cos(angleRadian), 0.0f, 0.0f),
				vec4(0.0f, 0.0f, 1.0f, 0.0f),
				vec4(0.0f, 0.0f, 0.0f, 1.0f)
			);
			matrix = matrix * matrixRZ;
		}
		return matrix;
	}

	mat4 diag(vec4 vector){
		return mat4(
			vec4(vector[0], 0, 0, 0),
			vec4(0, vector[1], 0, 0),
			vec4(0, 0, vector[2], 0),
			vec4(0, 0, 0, vector[3])
		);
	}

}

std::ostream & operator << (std::ostream &out, gm::vec4 &v)
{
	out << "(" << v.values[0] << "," << v.values[1] << "," << v.values[2] << "," << v.values[3] << ")" << std::endl;
	return out;
}