#include <PulsarModel.hpp>

#ifdef ENABLE_ASSIMP
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#endif

using namespace Pulsar;

bool Model::load(string path)
{
	#ifdef ENABLE_ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( path,
		aiProcess_CalcTangentSpace       |
		aiProcess_Triangulate            |
		aiProcess_JoinIdenticalVertices  |
		aiProcess_SortByPType		 |
	 	aiProcess_GenSmoothNormals);
	if(scene == NULL)
	{
		cout << "Failed to load model " << path << "." << endl;
		return 0;
	}
	//cout << "there are " << scene->mNumMeshes << " meshes in model" << endl;
	int meshCount = scene->mNumMeshes;
	for(int i=0;i<meshCount;i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		int meshFaces = mesh->mNumFaces;
		Mesh* newMesh = new Mesh;
		int verticesNum = mesh->mNumVertices;

		//Copy from Assimp to a float array
		float* vertices = new float[mesh->mNumVertices*3];
		for(int j=0;j<verticesNum;j++)
		{
			vertices[j*3+0] = mesh->mVertices[j][0];
			vertices[j*3+1] = mesh->mVertices[j][1];
			vertices[j*3+2] = mesh->mVertices[j][2];

		}
		newMesh->setVertices((vec3*)vertices,verticesNum);

		unsigned int* indices = new unsigned int[meshFaces*3];
		for(int j=0;j<meshFaces;j++)
		{
			indices[j*3+0] = mesh->mFaces[j].mIndices[0];
			indices[j*3+1] = mesh->mFaces[j].mIndices[1];
			indices[j*3+2] = mesh->mFaces[j].mIndices[2];
		}

		newMesh->setIndices(indices,meshFaces*3);

		float* normals = new float[mesh->mNumVertices*3];
		if(mesh->HasNormals() == true)
		{
			for(int j=0;j<verticesNum;j++)
			{
				normals[j*3+0] = mesh->mNormals[j][0];
				normals[j*3+1] = mesh->mNormals[j][1];
				normals[j*3+2] = mesh->mNormals[j][2];
			}
		}
		else
			for(int j=0;j<verticesNum;j++)
			{
				normals[j*3+0] = 0;
				normals[j*3+1] = 1;
				normals[j*3+2] = 0;
			}
		newMesh->setNormals((vec3*)normals,verticesNum);

		float* uvs = new float[mesh->mNumVertices*2];
		if(mesh->mNumUVComponents[0])
		{
			for(int j=0;j<verticesNum;j++)
			{
				uvs[j*2+0] = mesh->mTextureCoords[0][j][0];
				uvs[j*2+1] = mesh->mTextureCoords[0][j][1];
			}
		}
		else
		{
			for(int j=0;j<verticesNum;j++)
			{
				uvs[j*2+0] = 0;
				uvs[j*2+1] = 0;
			}
		}

		newMesh->setTextureCoord((vec2*)uvs, verticesNum);

		delete [] vertices;
		delete [] indices;
		delete [] normals;
		delete [] uvs;
		meshList.push_back(newMesh);
	}
	#endif
	return true;
}

void Model::render()
{
	int size = meshList.size();
	for(int i=0;i<size;i++)
		meshList[i]->render();
}

void Model::unload()
{
	int size = meshList.size();
	for(int i=0;i<size;i++)
		delete meshList[i];
	meshList.clear();
}

bool Model::good()
{
	if(meshList.size() != 0)
		return true;
	return false;
}

int Model::getMeshNum()
{
	return meshList.size();
}

const Mesh** Model::getMeshes()
{
	return (const Mesh**)&meshList[0];
}
