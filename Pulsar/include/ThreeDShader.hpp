#ifndef THREEDSHADER_HPP
#define THREEDSHADER_HPP

#include <PulsarShader.hpp>

namespace Pulsar
{

class ThreeDShader : public Shader
{
public:
	void setTexture(Texture* tex);
	virtual bool compile();
	virtual void bind();
	virtual void unbind();
	void setTransformation(mat4 transformation);
	void setCamera(Camera* cam);
	void setProjection(Projection* project);
	void updateInternalParametes();

protected:
	Texture* texture = NULL;
	mat4 transformMatrix;
	Camera* camera = NULL;
	Projection* projection = NULL;
};

class MaterialShader : public ThreeDShader
{
};

}

#endif
