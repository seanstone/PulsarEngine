#include <PulsarShader.hpp>
#include <PulsarEngine.hpp>
using namespace Pulsar;

Shader::Shader()
{
	program = glCreateProgram();
	if (program == 0)
		printf("Error: failed to create program.\n");
}

Shader::~Shader()
{
	glDeleteProgram(program);

	int size = shaderList.size();
	for(int i=0;i<size;i++)
		glDeleteShader(shaderList[i]);
	shaderList.clear();
}

void Shader::bind()
{
	glUseProgram(program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

bool Shader::loadVertexShader(string filepath)
{
	return addShader(File::readAllText(filepath), GL_VERTEX_SHADER);
}

bool Shader::loadFragmentShader(string filepath)
{
	return addShader(File::readAllText(filepath), GL_FRAGMENT_SHADER);
}

bool Shader::addShader(string text, GLenum type)
{
	#ifdef __EMSCRIPTEN__
	text = "#define WEBGL\r\n" + text;
	#else
	text = "#version 330 core\r\n" + text;
	#endif

	// Create vertex shader
	GLuint shader = glCreateShader(type);
	const char* str = text.c_str();

	if (shader == 0)
	{
		printf("Error: failed to create shader.\n");
		return false;
	}

	// Set vertex source
	glShaderSource(shader, 1, &str, NULL);

	// Compile vertex source
	glCompileShader(shader);

	// Check vertex shader for errors
	GLint result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		int size = -1;
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&size);
		char* data = new char[size];
		int length;
		glGetShaderInfoLog(shader,size,&length,data);
		string shaderType;
		switch (type)
		{
			case GL_VERTEX_SHADER:
				shaderType = "vertex";
				break;
			case GL_FRAGMENT_SHADER:
				shaderType = "fragment";
				break;
			default:
				shaderType = "Unknown";
		}
		cout << "Failed to compile " << shaderType << " shader" << endl << data << endl;
		delete [] data;
		return false;
	}
	// Attach vertex shader to program
	glAttachShader(program, shader);
	shaderList.push_back(shader);
	return true;
}

bool Shader::compile()
{
	glLinkProgram(program);

	int result;
	glGetProgramiv(program,GL_LINK_STATUS,&result);
	if(result != GL_TRUE)
	{
		int size = -1;
		glGetProgramiv(program,GL_INFO_LOG_LENGTH,&size);
		char* data = new char[size];
		int length;
		glGetProgramInfoLog(program,size,&length,data);
		cout << "Failed to link program" << endl << data << endl;
		delete [] data;
		return false;
	}

	glValidateProgram(program);
	glGetProgramiv(program,GL_VALIDATE_STATUS,&result);
	if(result == 0)
	{
		int size = -1;
		glGetProgramiv(program,GL_INFO_LOG_LENGTH,&size);
		char* data = new char[size];
		int length;
		glGetProgramInfoLog(program,size,&length,data);
		cout << "Failed to validate program" << endl << data << endl;
		delete [] data;
		return false;
	}
	// cache uniforms in a hash table for fast access
	addAllUniform();
	return true;
}

/**************************************************************************************************************************************************************/

bool Shader::setParameter(string name, bool val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniform1i(uniformLocation, val);
	return true;
}

bool Shader::setParameter(string name, int val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniform1i(uniformLocation, val);
	return true;
}

bool Shader::setParameter(string name, float val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniform1f(uniformLocation, val);
	return true;
}

bool Shader::setParameter(string name, vec2 val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniform2fv(uniformLocation, 1, (float*)&val);
	return true;
}

bool Shader::setParameter(string name, vec3 val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniform3fv(uniformLocation, 1, (float*)&val);
	return true;
}

bool Shader::setParameter(string name, vec4 val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniform4fv(uniformLocation, 1, (float*)&val);
	return true;
}

bool Shader::setParameter(string name, mat3x3 val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, (float*)&val);
	return true;
}

bool Shader::setParameter(string name, mat4x4 val)
{
	GLint uniformLocation = getUniform(name);
	if(uniformLocation == -1)
	{
		printf("Error: uniform \"%s\" not found.\n", name.c_str());
		return false;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (float*)&val);
	return true;
}

/**************************************************************************************************************************************************************/

void Shader::addAllUniform()
{
	int total = -1;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &total);

	int maxLength;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
	char* name = new char[maxLength];
	for(int i=0; i<total; i++)
	{
		int nameLen=-1, num=-1;
		GLenum type = GL_ZERO;
		glGetActiveUniform(program, (GLuint)i, maxLength,
			&nameLen, &num, &type, name);
		GLuint location = glGetUniformLocation(program, name);
		uniforms.insert({name,location});
	}
	delete [] name;
}

GLint Shader::getUniform(string name)
{
	// GLint uniformLocation = glGetUniformLocation(program, name.c_str());
	unordered_map<string,GLint>::const_iterator search = uniforms.find(name);
	if(search == uniforms.end())
		return -1;
	return search->second;
}
