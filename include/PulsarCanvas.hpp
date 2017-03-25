#ifndef PULSAR_CANVAS_HPP
#define PULSAR_CANVAS_HPP

#include <GL/glew.h>
#include <vector>
#include <string>
#include <iostream>

#include <PulsarMath.hpp>

namespace Pulsar
{
using namespace std;

class Canvas
{
public:
	Canvas();
	virtual ~Canvas();
    void setVertices();
	void render();
protected:
	GLuint vbo = 0;
	GLuint vao = 0;
};

}

#endif
