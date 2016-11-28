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

	//Check if all uniforms we need are avliable
	string requiredUniform [] = {"transformMatrix","cameraMatrix","projectionMatrix"};
	for(string& str : requiredUniform)
	{
		if(getUniform(str) == -1)
		{
			cout << "Warrning : Missing uniform \"" << str << "\" in ThreeDShader. Maybe some programming error has occurred." << endl;
			success = false;
			//do not break here, Print as more error message as possible.
			//break;
		}
	}

	if(success == false)
		return false;

	return true;
}

void ThreeDShader::bind()
{
	if(texture != NULL)
		texture->bind();

	Shader::bind();
	updateInternalParametes();
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

void ThreeDShader::updateInternalParametes()
{
	setParameter("transformMatrix",transformMatrix);
	setParameter("cameraMatrix",camera->getCameraMatrix());
	setParameter("projectionMatrix",projection->getProjectionMatrix());
}
