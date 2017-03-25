#ifndef PULSARTRANSFORM_HPP
#define PULSARTRANSFORM_HPP

#include <PulsarEngine.hpp>
#include <PulsarMath.hpp>

namespace Pulsar
{

class Transform
{
public:

	vec3 getTranslation();
	mat4x4 getTransformation();
	mat4x4 getScalingMatrix();
	mat4x4 getTranlationMatrix();
	void translate(vec3 vec);
	void rotate(vec3 vec);
	void scale(vec3 vec);
	Quatf getRotor();
	void setRotor(Quatf r);

	mat4x4 getRotationMatrix();
protected:
	vec3 translation = vec3(0,0,0);
	vec3 rotation = vec3(0,0,0);
	vec3 scaling = vec3(1,1,1);
	Quatf rotor = Quatf(1, 0, 0, 0);
};

}

#endif
