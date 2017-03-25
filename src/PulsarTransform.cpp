#include <PulsarEngine.hpp>
#include <PulsarTransform.hpp>
using namespace Pulsar;

vec3 Transform::getTranslation()
{
	return translation;
}

mat4x4 Transform::getTransformation()
{
	mat4x4 translationMatrix = getTranlationMatrix();
	mat4x4 rotationMatrix = getRotationMatrix();
	mat4x4 scalingMatrix = getScalingMatrix();

	return translationMatrix * rotationMatrix * scalingMatrix;
}

void Transform::translate(vec3 vec)
{
	translation = vec;
}

void Transform::rotate(vec3 vec)
{
	rotation = vec;
}

void Transform::scale(vec3 vec)
{
	scaling = vec;
}

void Transform::setRotor(Quatf r)
{
	rotor = r;
}

Quatf Transform::getRotor()
{
	return rotor;
}

mat4x4 Transform::getRotationMatrix()
{
	mat4x4 rx;
	mat4x4 ry;
	mat4x4 rz;

	rx = glm::rotate(rotation.x,vec3(1,0,0));
	ry = glm::rotate(rotation.y,vec3(0,1,0));
	rz = glm::rotate(rotation.z,vec3(0,0,1));
	return rz*ry*rx;
}

mat4x4 Transform::getScalingMatrix()
{
	return glm::scale(scaling);
}

mat4x4 Transform::getTranlationMatrix()
{
	return glm::translate(translation);
}
