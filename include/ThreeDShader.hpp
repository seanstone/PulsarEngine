#ifndef THREEDSHADER_HPP
#define THREEDSHADER_HPP

#include <PulsarShader.hpp>
#include <PulsarCamera.hpp>
#include <PulsarTexture.hpp>

namespace Pulsar
{

class ThreeDShader : public Shader
{
public:
	virtual void bind();
	virtual void unbind();
	void updateInternalParameters();

	Texture* 	texture = NULL;
	mat4 		transformMatrix;
	Camera* 	camera = NULL;
	Projection* projection = NULL;
};

}

#endif
