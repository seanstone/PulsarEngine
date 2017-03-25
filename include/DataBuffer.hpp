#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <cstdint>
#include <cstdlib>

namespace Pulsar
{

class DataBuffer
{
public:
	virtual ~DataBuffer()
	{
		destroy();
	}
	void destroy()
	{
		free(data);//free() does nothing if ptr == nullptr
		data = nullptr;
		dataSize = 0;
	}
	void createBuffer(size_t sizeInByte)
	{
		destroy();
		dataSize = sizeInByte;
		data = malloc(dataSize);
	}

	inline void* getBuffer()
	{
		return data;
	}

	inline const void* getReadOnlyBuffer() const
	{
		return data;
	}

	inline size_t getSize() const
	{
		return dataSize;
	}

protected:
	size_t dataSize = 0;
	void* data = nullptr;
};

//This is something like the VAO in OpenGL
class DataBufferArray
{
public:
	inline DataBuffer* getBuffer(int index)
	{
		return buffers[index];
	}

	inline DataBuffer* getReadOnlyBuffer(int index) const
	{
		return buffers[index];
	}

	inline DataBuffer*& operator[](int index)
	{
		return buffers[index];
	}

	inline const DataBuffer* operator[](int index) const
	{
		return buffers[index];
	}

protected:
	DataBuffer* buffers[16] = {nullptr};
};

}

#endif
