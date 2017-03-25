#include <PulsarFile.hpp>
using namespace Pulsar;

#include <fstream>
using namespace std;

string File::readAllText(string path)
{
	ifstream ifs(path);

	if(ifs.good() == false)
	{
		cout << "Failed to open file " << path << endl;
		return "";
	}

	string content( (istreambuf_iterator<char>(ifs) ),
		(istreambuf_iterator<char>()));
	return content;
}
