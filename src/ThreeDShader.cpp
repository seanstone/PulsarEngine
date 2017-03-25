#include <ThreeDShader.hpp>
#include <PulsarTexture.hpp>
#include <PulsarEngine.hpp>
using namespace Pulsar;

void ThreeDShader::bind()
{
	if(texture != NULL)
		texture->bind();

	Shader::bind();
	updateInternalParameters();
}

void ThreeDShader::unbind()
{
	if(texture != NULL)
		texture->unbind();
	Shader::unbind();
}

void ThreeDShader::updateInternalParameters()
{
	setParameter("transformMatrix", transformMatrix);
	setParameter("cameraMatrix", camera->getCameraMatrix());
	setParameter("projectionMatrix", projection->getProjectionMatrix());
}
