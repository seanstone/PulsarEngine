//#include <Pulsar.hpp>
#include <PulsarMesh.hpp>

using namespace Pulsar;

Mesh::Mesh()
{
	glGenVertexArrays(1, &vao);
}

Mesh::~Mesh()
{
	if(vao != 0)
		glDeleteVertexArrays(1,&vao);
	if(vbo != 0)
		glDeleteBuffers(1,&vbo);
	if(ebo != 0)
		glDeleteBuffers(1,&ebo);
	if(tco != 0)
		glDeleteBuffers(1,&tco);
	if(nbo != 0)
		glDeleteBuffers(1,&nbo);
}

void Mesh::setVertices(vec3* vertices, int size)
{
	glBindVertexArray(vao);
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,size*sizeof(vec3),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::setIndices(unsigned int* indices, int size)
{
	dataSize = size;

	glBindVertexArray(vao);
	glGenBuffers(1,&ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,size*sizeof(int),indices,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::setTextureCoord(vec2* uvCoord, int size)
{
	glBindVertexArray(vao);
	glGenBuffers(1,&tco);
	glBindBuffer(GL_ARRAY_BUFFER,tco);
	glBufferData(GL_ARRAY_BUFFER,size*sizeof(vec2),uvCoord,GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glBindVertexArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::setNormals(vec3* normals, int size)
{
	glBindVertexArray(vao);
	glGenBuffers(1,&nbo);
	glBindBuffer(GL_ARRAY_BUFFER,nbo);
	glBufferData(GL_ARRAY_BUFFER,size*sizeof(vec3),normals,GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::render()
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//glDrawArrays(GL_TRIANGLES, 0, dataSize);
	glDrawElements(GL_TRIANGLES, dataSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
