#ifndef PULSARFILE_HPP
#define PULSARFILE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace Pulsar
{

using namespace std;

class File
{
public:
	static string readAllText(string path);
};

}

#endif
