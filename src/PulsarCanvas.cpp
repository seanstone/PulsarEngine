#include <PulsarCanvas.hpp>

using namespace Pulsar;

Canvas::Canvas()
{
	glGenVertexArrays(1, &vao);
}

Canvas::~Canvas()
{
	if(vao != 0)
		glDeleteVertexArrays(1,&vao);
	if(vbo != 0)
		glDeleteBuffers(1,&vbo);
}

void Canvas::setVertices()
{

	static const vec3 vertices[] = {
	   vec3(-1.0f, -1.0f, 0.0f),
	   vec3(1.0f, -1.0f, 0.0f),
	   vec3(-1.0f,  1.0f, 0.0f),
	   vec3(1.0f, 1.0f, 0.0f),
	   vec3(1.0f, -1.0f, 0.0f),
	   vec3(-1.0f,  1.0f, 0.0f),
	};

	int size = 6;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(vec3), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Canvas::render()
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}
