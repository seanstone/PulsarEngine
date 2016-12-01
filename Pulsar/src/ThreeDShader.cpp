#include <ThreeDShader.hpp>
#include <PulsarTexture.hpp>
#include <Pulsar.hpp>
using namespace Pulsar;

void ThreeDShader::setTexture(Texture* tex)
{
	texture = tex;
}

bool ThreeDShader::compile()
{
	bool success = true;
	success = Shader::compile();
	if(success == false)
		return false;

	// Check if all uniforms we need are avliable
	string requiredUniform [] = {"transformMatrix","cameraMatrix","projectionMatrix"};
	for(string& str : requiredUniform)
	{
		if(getUniform(str) == -1)
		{
			cout << "Warning : Missing uniform \"" << str << "\" in ThreeDShader." << endl;
			success = false;
		}
	}

	return success;
}

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

void ThreeDShader::setTransformation(mat4 transformation)
{
	transformMatrix = transformation;
}

void ThreeDShader::setCamera(Camera* cam)
{
	camera = cam;
}

void ThreeDShader::setProjection(Projection* project)
{
	projection = project;
}

void ThreeDShader::updateInternalParameters()
{
	setParameter("transformMatrix",transformMatrix);
	setParameter("cameraMatrix",camera->getCameraMatrix());
	setParameter("projectionMatrix",projection->getProjectionMatrix());
}
