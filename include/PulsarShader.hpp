#ifndef PULSARSHADER_HPP
#define PULSARSHADER_HPP

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <PulsarMath.hpp>
#include <PulsarFile.hpp>

namespace Pulsar
{

using namespace std;

class Shader
{
public:
	Shader();
	virtual ~Shader();
	bool loadVertexShader(string filepath);
	bool loadFragmentShader(string filepath);
	virtual bool compile();
	virtual void bind();
	virtual void unbind();
	bool setParameter(string name, bool val);
	bool setParameter(string name, int val);
	bool setParameter(string name, float val);
	bool setParameter(string name, vec2 val);
	bool setParameter(string name, vec3 val);
	bool setParameter(string name, vec4 val);
	bool setParameter(string name, mat3x3 val);
	bool setParameter(string name, mat4x4 val);

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
