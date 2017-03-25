#ifndef PULSARSCENE_HPP
#define PULSARSCENE_HPP
#include <PulsarEngine.hpp>
#include <PulsarModel.hpp>
#include <PulsarCamera.hpp>
#include <PulsarTransform.hpp>
#include <ThreeDShader.hpp>

#include <vector>
namespace Pulsar
{

using namespace std;

class SceneItem
{
public:
	virtual void render(Camera* camera, mat4 preTransformMatrix = mat4()){}
	virtual ~SceneItem(){}

	void setTransform(Transform transformation);
protected:
	Transform transform;
};

class SceneMeshItem : public SceneItem
{
public:
	SceneMeshItem(Mesh* m = NULL, ThreeDShader* s = NULL);
	void render(Camera* camera, mat4 preTransformMatrix = mat4());
	void setShader(ThreeDShader* ThreeDShader);
protected:
	Mesh* mesh = NULL;
	ThreeDShader* shader = NULL;
	Quatf rotor = Quatf(1);
};

class SceneModelItem : public SceneItem
{
public:
	SceneModelItem(Model* m = NULL, ThreeDShader* s = NULL);
	virtual ~SceneModelItem();

	void setModel(Model* m);
	void setShader(ThreeDShader* ThreeDShader);
	void render(Camera* camera, mat4 preTransformMatrix = mat4());
	void releaseMeshItem();
protected:
	Model* model = NULL;
	ThreeDShader* shader = NULL;
	vector<SceneMeshItem*> meshItems;
};

class SceneNode : public SceneItem
{
public:
	void render(Camera* camera, mat4 preTransformMatrix = mat4());
	void addItem(SceneItem* item);
	void addNode(SceneNode* node);

protected:
	vector<SceneItem*> childItems;
	vector<SceneNode*> childNodes;
};

}

#endif
