#ifndef PULSAR_SHADER_H
#define PULSAR_SHADER_H

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <PulsarMath.hpp>

namespace Pulsar
{

using namespace std;

class Texture;
class Projection;

class Shader
{
public:
	Shader();
	virtual ~Shader();
	bool addVertexShader(string text);
	bool addFragmentShader(string text);
	virtual bool compile();
	virtual void bind();
	virtual void unbind();
	bool setParameter(string name, float val);
	bool setParameter(string name, vec2 val);
	bool setParameter(string name, vec3 val);
	bool setParameter(string name, vec4 val);
	bool setParameter(string name, mat3x3 val);
	bool setParameter(string name, mat4x4 val);
	bool setParameter(string name, int val);
	bool setParameter(string name, bool val);

protected:
	bool addShader(string text, GLenum type);
	void addAllUniform();
	GLint getUniform(string text);

	GLuint program = 0;
	vector<GLuint> shaderList;
	unordered_map<string,GLint> uniforms;
};

}


#endif
