#ifndef VEC_HPP
#define VEC_HPP

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

//In case cmath does not define the required contants
#ifndef M_PI
	#define M_PI (3.14159265358979f)
	#define M_PI_2 (M_PI/2.0f)
	#define M_PI_4 (M_PI/4.0f)
	#define M_1_PI (0.31830988618379067154) // 1.0/M_PI
#endif

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtx/transform.hpp>

#include <glm/gtx/compatibility.hpp>

namespace Pulsar
{
using namespace glm;

inline float4 cross(float4 u, float4 v)
{
	return float4(glm::cross(float3(u), float3(v)), 0);
}
// cout float4
inline std::ostream& operator<< (std::ostream& out, const float4 v)
{
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" ;
}

// cout float3
inline std::ostream& operator<< (std::ostream& out, const float3 v)
{
	return out << "(" << v.x << ", " << v.y << ", " << v.z << ")" ;
}

// cout float2
inline std::ostream& operator<< (std::ostream& out, const float2 v)
{
	return out << "(" << v.x << ", " << v.y << ")" ;
}


// input float4
inline std::istream& operator>>(std::istream& is, float4& v)
{
	float x, y, z, w;
	is >> x >> y >> z >> w;
	v = float4(x, y, z, w);
	return is;
}

// input float3
inline std::istream& operator>>(std::istream& is, float3& v)
{
	float x, y, z;
	is >> x >> y >> z;
	v = float3(x, y, z);
	return is;
}

}
#endif
