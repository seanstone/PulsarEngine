#ifndef PULSARMODEL_HPP
#define PULSARMODEL_HPP

#include <PulsarMesh.hpp>

namespace Pulsar
{

class Model
{
public:
	bool load(string path);
	void render();
	void unload();

	bool good();
	int getMeshNum();
	const Mesh** getMeshes();
protected:
	vector<Mesh*> meshList;
};

}

#endif
