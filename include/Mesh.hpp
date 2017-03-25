#ifndef MESH_HPP
#define MESH_HPP

#include <Vec.hpp>
#include <DataBuffer.hpp>

namespace Incarnate
{

class Mesh
{
public:
	Mesh(){}
	virtual ~Mesh()
	{
	}

	void setVertices(const float4* verts, int num)
	{
		vertices.createBuffer(sizeof(float4)*num);
		float4* buffer = (float4*)vertices.getBuffer();

		for(int i=0;i<num;i++)
			buffer[i] = verts[i];
		dataBufferArray[0] = &vertices;
	}

	void setIndices(const int* inds, int num)
	{
		indices.createBuffer(sizeof(int)*num);
		int* buffer = (int*)indices.getBuffer();

		for(int i=0;i<num;i++)
			buffer[i] = inds[i];
		dataBufferArray[1] = &indices;
 	}

	void setNormals(const float4* norms, int num)
	{
		normals.createBuffer(sizeof(float4)*num);
		float4* buffer = (float4*)normals.getBuffer();

		for(int i=0;i<num;i++)
			buffer[i] = norms[i];
		dataBufferArray[2] = &normals;
	}

	void setUVs(const float2* uvPtr, int num)
	{
		uvs.createBuffer(sizeof(float2)*num);
		float2* buffer = (float2*)uvs.getBuffer();

		for(int i=0;i<num;i++)
			buffer[i] = uvPtr[i];
		dataBufferArray[3] = &uvs;
	}

	void setMaterial(Material* materialPtr)
	{
		material = materialPtr;
	}

	inline int getVerticesCount()
	{
		return vertices.getSize()/sizeof(float4);
	}

	inline float4* getVertices()
	{
		return (float4*)vertices.getBuffer();
	}

	inline int getIndicesCount()
	{
		return indices.getSize()/sizeof(int);
	}

	inline int* getIndices()
	{
		return (int*)indices.getBuffer();
	}

	inline Material* getMaterial()
	{
		return material;
	}

	DataBufferArray* getDataBufferArray()
	{
		return &dataBufferArray;
	}

protected:
	DataBufferArray dataBufferArray;
	DataBuffer vertices;
	DataBuffer indices;
	DataBuffer normals;
	DataBuffer uvs;

	Material* material = NULL;
};

}


#endif
